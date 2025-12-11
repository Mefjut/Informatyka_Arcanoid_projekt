#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Paleta
{
public:
    Paleta(float x_pocz, float y_pocz, float szer, float wys, float predkosc_in);

    void ruchLewo();                
    void ruchPrawo();              
    void ograniczDoEkranu(float szerokoscOkna);
    void rysuj(sf::RenderTarget& cel) const { cel.draw(ksztalt); }

    float wezX() const { return x; }
    float wezY() const { return y; }
    float wezSzerokosc() const { return szerokosc; }
    float wezWysokosc() const { return wysokosc; }

    void ustawPozycje(const sf::Vector2f& nowaPoz);

private:
    float x, y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape ksztalt;
};


