#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void zamien(int dY, int dX, bool tab[][64], int pozX, int pozY) //funkcja do przesuwania pojedynczych pikseli "ziaren"
{
  if(pozX+dX<64 && pozX+dX>=0 && pozY+dY<32 && pozY+dY>=0 && tab[pozY+dY][pozX+dX]==0)
  {
    tab[pozY][pozX]=0;
    tab[pozY+dY][pozX+dX]=1;
  }
  else if(pozY+dY>=0 && pozY+dY<32 && tab[pozY+dY][pozX]==0)
  {
    tab[pozY][pozX]=0;
    tab[pozY+dY][pozX]=1;
  }
  else if(pozX+dX>=0 && pozX+dX<64 && tab[pozY][pozX+dX]==0)
  {
    tab[pozY][pozX]=0;
    tab[pozY][pozX+dX]=1;
  }
}

void przesun(int dY, int dX, bool tab[][64], int szansa) //funkcja do symulacji calej tablicy
{
  if(dY==1)
  {
    for(int i=31; i>=0; i--)
    {
      for(int j=0; j<64; j++)
      {
        if(szansa>=random(101) && tab[i][j]==1)
        {
          zamien(dY, dX, tab, j, i);
        }
      }
    }
  }

  else
  {
    for(int i=0; i<32; i++)
    {
      for(int j=0; j<64; j++)
      {
        if(szansa>=random(101) && tab[i][j]==1)
        {
          zamien(dY, dX, tab, j, i);
        }
      }
    }
  }
}




Adafruit_SSD1306 display(128, 64, &Wire, -1);
bool tab[32][64]={0};

void setup() {
  Serial.begin(115200);
  delay(500); //bufor zasilania dla MPU

  Wire.begin(3, 4);
  Wire.setClock(400000); //przyspieszenie I2C

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //inicjalizacja zyroskopu
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  //wypelnienie dolnych rzedow tablicy jedynkami
  for(int i=23; i<32; i++)
  {
      for(int j=0; j<64; j++)
      {
        tab[i][j]=1;
      }
  }
}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  int8_t dX=0, dY=0;

  int16_t rawZ = Wire.read() << 8 | Wire.read();
  int16_t rawX = Wire.read() << 8 | Wire.read();
  int16_t rawY = Wire.read() << 8 | Wire.read();

  //ustalenie kierunku X
  if(rawX>0)
  dX=1;
  else if(rawX<0)
  dX=-1;

  //ustalenie kierunku Y
  if(rawY>0)
  dY=-1;
  else if(rawY<0)
  dY=1;

  //okreslenie "szybkosci" czyli w tym przypadku prawdopodobienstwa od 1 do 100
  int szansaX=abs(rawX)*100/16384;
  int szansaY=abs(rawY)*100/16384;

  int szansa;
  if(szansaX>szansaY)
    szansa=szansaX;
  else
    szansa=szansaY;

  
  przesun(dY, dX, tab, szansa);

  //wypisywanie tablicy na ekranie, kazda wartosc w talibcy to piksel 2x2
  display.clearDisplay(); 
  for(int i=0; i<32; i++)
  {
    for(int j=0; j<64; j++)
    {
      if(tab[i][j]==1)
      {
        display.fillRect(j*2, i*2, 2, 2, WHITE);
      }
    }
  }
  display.display();


  //delay(10); 
}