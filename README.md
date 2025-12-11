# Informatyka_Arcanoid_projekt
Kod tworzący gre typu arcanoid

Opis gry: Program jest grą typu Arkanoid. Grafika wykorzystywana w 
kodzie została stworzona przy pomocy wykorzystania 
bibliotek SFML. 
Celem gry jest odbijanie piłki niszczącej bloki.
Program zawiera menu główne w którym są poszczególne opcje
: nowa gra, wczytanie ostatniego zapisu, sprawdzenie 
poprzednich wyników oraz opuszczenie gry.

Sterowanie:
W menu głównym można sterować programem za pomoca
strzałek, przycisku enter oraz przycisku Esc.
Podczas samej w sobie rozrywki ruch umożliwiają strzałki
oraz poza nimi przyciski A oraz D. W celu wykonania zapisu
są dwie możliwości (F5 i P).

Elementy Gry:
W programie istnieje pare elementów, którymi można sterować 
lub wpływać na ich ruch pośrenio. 
Paletka - prostopadła belka którą można sterować
(piłka odbija się od paletki w zależności od miejsca
odbicia).
Piłka - piłka porusza sie bez przerwy, odbija sie ona
od scian, bloków, paletki oraz przeszkody
Bloki - bloki mają takie same rozmiary, różnią się od
siebie kolorem który jest zależny od pozostałych punktów
życia (jezeli punkty zycia osiagną 0 blok znika).
Przeszkoda - niereguralny kształtem element, który jest 
niezniszczalny oraz odbija piłke w zależności jak 
uderzy ona w przestrzeń przeszkody.

Zapis:
Podczas zapisu gry zapamiętywane są pozycje paletki,
piłki, stany oraz liczby bloków.

Koniec gry:
W momencie jak piłka wypadnie poza dolna krawedz 
rozgrywka sie konczy i nastepuje przeniesienie 
do menu.

