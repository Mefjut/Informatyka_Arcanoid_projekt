#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_OPCJI 4

class Menu
{
private:
    sf::Font czcionka;
    sf::Text opcje[MAX_LICZBA_OPCJI];
    int wybranaOpcja;

    sf::Text tekstAnimowany;
    sf::Clock zegarAnimacji;

public:
    Menu(float szerokosc, float wysokosc);
    ~Menu() {}

    void przesunWGore();
    void przesunWDol();

    int wezWybranaOpcje() const { return wybranaOpcja; }

    void rysuj(sf::RenderWindow& okno);
};


