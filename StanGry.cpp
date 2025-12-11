#include "StanGry.h"
#include <fstream>

void StanGry::przechwyc(const Paleta& paleta,
    const Kula& kula,
    const std::vector<Glaz>& bloki)
{
    pozPalety = sf::Vector2f(paleta.wezX(), paleta.wezY());
    pozKuli = sf::Vector2f(kula.wezX(), kula.wezY());
    predkoscKuli = sf::Vector2f(kula.wezVX(), kula.wezVY());

    blokiDane.clear();
    blokiDane.reserve(bloki.size());

    for (const auto& b : bloki)
    {
        BlokDane dane;
        dane.x = b.getPosition().x;
        dane.y = b.getPosition().y;
        dane.hp = b.czyZniszczony() ? 0 : b.wezWytrzymalosc();
        blokiDane.push_back(dane);
    }
}

bool StanGry::zapiszDoPliku(const std::string& nazwaPliku) const
{
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) return false;

    plik << "PALETA " << pozPalety.x << " " << pozPalety.y << "\n";
    plik << "KULA " << pozKuli.x << " " << pozKuli.y << " "
        << predkoscKuli.x << " " << predkoscKuli.y << "\n";

    plik << "LICZBA_BLOKOW " << blokiDane.size() << "\n";
    for (const auto& b : blokiDane)
        plik << b.x << " " << b.y << " " << b.hp << "\n";

    return true;
}

bool StanGry::wczytajZPliku(const std::string& nazwaPliku)
{
    std::ifstream plik(nazwaPliku);
    if (!plik.is_open()) return false;

    std::string etykieta;
    if (!(plik >> etykieta >> pozPalety.x >> pozPalety.y)) return false;
    if (!(plik >> etykieta >> pozKuli.x >> pozKuli.y >> predkoscKuli.x >> predkoscKuli.y)) return false;

    int liczba = 0;
    if (!(plik >> etykieta >> liczba)) return false;

    blokiDane.clear();
    blokiDane.reserve(liczba);
    for (int i = 0; i < liczba; ++i)
    {
        BlokDane dane;
        if (!(plik >> dane.x >> dane.y >> dane.hp)) return false;
        blokiDane.push_back(dane);
    }

    return true;
}

void StanGry::zastosuj(Paleta& paleta,
    Kula& kula,
    std::vector<Glaz>& bloki) const
{
    paleta.ustawPozycje(pozPalety);
    kula.reset(pozKuli, predkoscKuli);

    sf::Vector2f rozmiarBloku(0.f, 0.f);
    if (!bloki.empty())
        rozmiarBloku = bloki.front().getSize();

    bloki.clear();
    bloki.reserve(blokiDane.size());

    for (const auto& dane : blokiDane)
    {
        if (dane.hp <= 0) continue;
        bloki.emplace_back(sf::Vector2f(dane.x, dane.y), rozmiarBloku, dane.hp);
    }
}

