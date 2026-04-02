#include<IRremote.hpp>
#include <BleKeyboard.h>

const int PIN=4;
const unsigned long lewo=0xE501AF, prawo=0x6509AF, srodek=0xD002FF, czerwony=0xFF000F, zielony=0xE8017F;
BleKeyboard klawiatura("Pilot Mac", "ESP32", 100);
bool klawiatura_stop=false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(PIN, DISABLE_LED_FEEDBACK);
  klawiatura.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(IrReceiver.decode())
  {
    if(!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)){
      unsigned long sygnal=IrReceiver.decodedIRData.decodedRawData;
      //Serial.println(sygnal, HEX);

      if(sygnal==czerwony)
      {
        if(klawiatura_stop==false)
          klawiatura_stop=true;
        else
          klawiatura_stop=false;
      }

      if(klawiatura_stop==false)
      {
        switch(sygnal){
        case lewo:
        klawiatura.write(KEY_LEFT_ARROW);
        break;

        case prawo:
        klawiatura.write(KEY_RIGHT_ARROW);
        break;

        case srodek:
        klawiatura.write(' ');
        break;

        case zielony:
        klawiatura.write(KEY_RETURN);
        break;
      }
      }
    }
    IrReceiver.resume();
  }
  
  
}
