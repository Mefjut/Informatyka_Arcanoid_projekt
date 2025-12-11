#include "Menu.h"
#include <cmath>

Menu::Menu(float szerokosc, float wysokosc)
{
    wybranaOpcja = 0;

    if (!czcionka.loadFromFile("arial.ttf"))
    {
        std::cout << "BLAD: Nie udalo sie wczytac czcionki arial.ttf\n";
    }

    for (int i = 0; i < MAX_LICZBA_OPCJI; i++)
    {
        opcje[i].setFont(czcionka);
        opcje[i].setCharacterSize(34);
        opcje[i].setFillColor(sf::Color(200, 200, 195));
        opcje[i].setStyle(sf::Text::Regular);
    }

    float odst = wysokosc / (MAX_LICZBA_OPCJI + 1);

    opcje[0].setString("Nowa gra");
    opcje[0].setPosition(szerokosc / 3.f, odst * 1);

    opcje[1].setString("Wczytaj gre");
    opcje[1].setPosition(szerokosc / 3.f, odst * 2);

    opcje[2].setString("Ostatnie wyniki");
    opcje[2].setPosition(szerokosc / 3.f, odst * 3);

    opcje[3].setString("Wyjscie");
    opcje[3].setPosition(szerokosc / 3.f, odst * 4);

    opcje[0].setFillColor(sf::Color(160, 155, 140));
    opcje[0].setStyle(sf::Text::Bold);

    tekstAnimowany.setFont(czcionka);
    tekstAnimowany.setCharacterSize(26);
    tekstAnimowany.setString("Nacisnij ENTER");
    tekstAnimowany.setFillColor(sf::Color(200, 200, 190));
    tekstAnimowany.setPosition(szerokosc / 3.f, odst * 5);
}

void Menu::przesunWGore()
{
    opcje[wybranaOpcja].setFillColor(sf::Color(200, 200, 195));
    opcje[wybranaOpcja].setStyle(sf::Text::Regular);

    wybranaOpcja--;
    if (wybranaOpcja < 0) wybranaOpcja = MAX_LICZBA_OPCJI - 1;

    opcje[wybranaOpcja].setFillColor(sf::Color(160, 155, 140));
    opcje[wybranaOpcja].setStyle(sf::Text::Bold);
}

void Menu::przesunWDol()
{
    opcje[wybranaOpcja].setFillColor(sf::Color(200, 200, 195));
    opcje[wybranaOpcja].setStyle(sf::Text::Regular);

    wybranaOpcja++;
    if (wybranaOpcja >= MAX_LICZBA_OPCJI) wybranaOpcja = 0;

    opcje[wybranaOpcja].setFillColor(sf::Color(160, 155, 140));
    opcje[wybranaOpcja].setStyle(sf::Text::Bold);
}

void Menu::rysuj(sf::RenderWindow& okno)
{
    for (int i = 0; i < MAX_LICZBA_OPCJI; i++)
        okno.draw(opcje[i]);

    float t = zegarAnimacji.getElapsedTime().asSeconds();
    float puls = 0.6f + 0.4f * std::sin(t * 3.f);

    tekstAnimowany.setFillColor(sf::Color(
        static_cast<sf::Uint8>(220.f * puls),
        static_cast<sf::Uint8>(220.f * puls),
        static_cast<sf::Uint8>(210.f * puls)
    ));

    okno.draw(tekstAnimowany);
}

