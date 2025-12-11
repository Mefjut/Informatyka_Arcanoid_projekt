#include "Paleta.h"

Paleta::Paleta(float x_pocz, float y_pocz, float szer, float wys, float predkosc_in)
{
    x = x_pocz;
    y = y_pocz;
    szerokosc = szer;
    wysokosc = wys;
    predkosc = predkosc_in;

    ksztalt.setSize({ szerokosc, wysokosc });
    ksztalt.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
    ksztalt.setPosition(x, y);
    ksztalt.setFillColor(sf::Color(120, 100, 95));
}

void Paleta::ruchLewo()
{
    x -= predkosc;
    ksztalt.setPosition(x, y);
}

void Paleta::ruchPrawo()
{
    x += predkosc;
    ksztalt.setPosition(x, y);
}

void Paleta::ograniczDoEkranu(float szerokoscOkna)
{
    if (x - szerokosc / 2.f < 0.f) x = szerokosc / 2.f;
    if (x + szerokosc / 2.f > szerokoscOkna) x = szerokoscOkna - szerokosc / 2.f;
    ksztalt.setPosition(x, y);
}

void Paleta::ustawPozycje(const sf::Vector2f& nowaPoz)
{
    x = nowaPoz.x;
    y = nowaPoz.y;
    ksztalt.setPosition(x, y);
}