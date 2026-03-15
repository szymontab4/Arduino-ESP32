Automatyczne podlewanie roślin

Cel - stworzenie automatycznego systemu którego celem będzie sprawdzanie wilgotności gleby i automatyczne podlewanie. 
Źródło pomysłu - strona forbot.pl
Realizacja - wiedza własna, dokumentacja, strony w internecie, gemini, tinkercad - realizacja planu układu 

Sprzęt:
- Projekt jest oparty na mikrokontrolerze esp32-c3 super mini - wybór padł na niego ze względu na cenę oraz niski pobór prądu
- Czujnik wilgotności pojemnościowy - wybrany ze względu na trwałość w porównaniu do czujnika opartego na rezystancji
- Mała pompa wodna zanurzeniowa 120L/h 3-6V - wystarczająca do podlania rośliny przez parę sekund, możliwe że zostanie wymieniona na suchą, znajdująca się poza zbiornikiem wody
- Zasilanie - pojedyncze ogniwo 18650 - wystarczające do kilkumiesięcznego zasilania układu 
- Kod - Pisane na Arduino IDE, ze względu na znajomość tego języku, możliwe przejście na czystego c++ z biegem czasu

Plan rozwoju:
1. Stworzenie samego układu podlewania
2. Postawienie bota na discorzie który będzie informował o momencie podlewania oraz wilgotności ziemii
3. Rozbudowa układu, każda doniczka będzie posiadać swój własny czujnik wilgotności. Istnieją dwie opcje nawadniania:
  3.2. Użycie jednej pompy lecz zastosowanie elektrozaworów
4. Rozbudowanie pomysłu poprzez zrobienie jego wodoodpornej wersji która będzie mogła stać na dworze, największy problem to samo zabezpieczenie czujnika wilgotności oraz esp32
5. Jeżeli uda się stowrzyć bezpieczny wodoodporny system, to stowrzenie automatycznego podlewania kilkunastu krzaków pomidorów

  

Update 11.03.2026
Wystąpiło sporo problemów związanych z elektroniką samą w sobie. Najpierw dokładna nauka działania tranzysotra mosfet, potem przygotowanie samego schematu podłączenia całego układu jeszcze bez esp32. Niestety po podłączeniu esp wszystko się zepsuło, problemy z ciągłym działaniem silnika, niezatrzymywaniem się, restartami esp były ciągłe. Raz myślałem że rozwiązałem, a raz nie. Zeszło mi na tym sporo godzin i prawie tydzień czasu. Nie pomagały dodatkowe kondensatory, zmiany układu zasilania itd.. Rozwiązałem ten problem przez zastosowanie transoptora, jak narazie wszystko działa. 

Update 15.03.2026 
Najprawdopodobniej cały układ jest już gotowy, pomiar wilgotnosci jak i bot na discordzie dziala poprawnie. W najbliższych dniach (jeżeli bazylia będzie wciąż dobrze się trzymać) podłączę pompę do układu. Pozostaje wtedy tylko ustalenie czasu podlewania i cały projekt będzie zakończony. 
