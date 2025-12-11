/*
Opis gry: Program jest gr¹ typu Arkanoid. Grafika wykorzystywana w 
kodzie zosta³a stworzona przy pomocy wykorzystania 
bibliotek SFML. 
Celem gry jest odbijanie pi³ki niszcz¹cej bloki.
Program zawiera menu g³ówne w którym s¹ poszczególne opcje
: nowa gra, wczytanie ostatniego zapisu, sprawdzenie 
poprzednich wyników oraz opuszczenie gry.

Sterowanie:
W menu g³ównym mo¿na sterowaæ programem za pomoca
strza³ek, przycisku enter oraz przycisku Esc.
Podczas samej w sobie rozrywki ruch umo¿liwiaj¹ strza³ki
oraz poza nimi przyciski A oraz D. W celu wykonania zapisu
s¹ dwie mo¿liwoœci (F5 i P).

Elementy Gry:
W programie istnieje pare elementów, którymi mo¿na sterowaæ 
lub wp³ywaæ na ich ruch poœrenio. 
Paletka - prostopad³a belka któr¹ mo¿na sterowaæ
(pi³ka odbija siê od paletki w zale¿noœci od miejsca
odbicia).
Pi³ka - pi³ka porusza sie bez przerwy, odbija sie ona
od scian, bloków, paletki oraz przeszkody
Bloki - bloki maj¹ takie same rozmiary, ró¿ni¹ siê od
siebie kolorem który jest zale¿ny od pozosta³ych punktów
¿ycia (jezeli punkty zycia osiagn¹ 0 blok znika).
Przeszkoda - niereguralny kszta³tem element, który jest 
niezniszczalny oraz odbija pi³ke w zale¿noœci jak 
uderzy ona w przestrzeñ przeszkody.

Zapis:
Podczas zapisu gry zapamiêtywane s¹ pozycje paletki,
pi³ki, stany oraz liczby bloków.

Koniec gry:
W momencie jak pi³ka wypadnie poza dolna krawedz 
rozgrywka sie konczy i nastepuje przeniesienie 
do menu.




*/