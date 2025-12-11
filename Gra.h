#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Paleta.h"
#include "Kula.h"
#include "Glaz.h"
#include "Przeszkoda.h"
#include "StanGry.h"

class Gra {
public:
    Gra();

    void aktualizuj(sf::Time dt);
    void rysuj(sf::RenderTarget& cel);

    bool zapiszGre(const std::string& nazwaPliku);
    bool wczytajGre(const std::string& nazwaPliku);

    void resetGra();
    bool czyGameOver() const { return m_gameOver; }

private:
    Paleta m_paleta;
    Kula m_kula;
    std::vector<Glaz> m_klocki;
    Przeszkoda m_przeszkoda;
    StanGry m_snapshot;

    bool m_gameOver = false;

    const float SZEROKOSC = 800.f;
    const float WYSOKOSC = 600.f;
};

