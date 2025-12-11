#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Paleta.h"
#include "Kula.h"
#include "Glaz.h"

struct BlokDane
{
    float x;
    float y;
    int   hp;
};

class StanGry
{
public:
    StanGry() = default;
    StanGry(const Paleta& paleta, const Kula& kula, const std::vector<Glaz>& bloki) {
        przechwyc(paleta, kula, bloki);
    }

    void przechwyc(const Paleta& paleta, const Kula& kula, const std::vector<Glaz>& bloki);
    bool zapiszDoPliku(const std::string& nazwaPliku) const;
    bool wczytajZPliku(const std::string& nazwaPliku);
    void zastosuj(Paleta& paleta, Kula& kula, std::vector<Glaz>& bloki) const;

    const sf::Vector2f& wezPozycjePalety()  const { return pozPalety; }
    const sf::Vector2f& wezPozycjeKuli()    const { return pozKuli; }
    const sf::Vector2f& wezPredkoscKuli()   const { return predkoscKuli; }
    const std::vector<BlokDane>& wezBloki() const { return blokiDane; }

private:
    sf::Vector2f pozPalety;
    sf::Vector2f pozKuli;
    sf::Vector2f predkoscKuli;
    std::vector<BlokDane> blokiDane;
};
