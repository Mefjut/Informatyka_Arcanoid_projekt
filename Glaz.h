#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

class Glaz : public sf::RectangleShape
{
public:
    Glaz(sf::Vector2f startPos, sf::Vector2f rozmiar, int wytrzymalosc);

    void otrzymajUderzenie();
    void odswiezKolor();
    void rysuj(sf::RenderTarget& target) const;

    bool czyZniszczony() const { return m_czyZniszczony; }
    int wezWytrzymalosc() const { return m_zycie; }

private:
    int m_zycie;
    bool m_czyZniszczony;
    static const std::array<sf::Color, 4> m_koloryLUT;
};