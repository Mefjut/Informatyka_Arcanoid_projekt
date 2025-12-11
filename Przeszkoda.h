#pragma once

#include <SFML/Graphics.hpp>

class Przeszkoda
{
public:
    Przeszkoda(const sf::Vector2f& pozycja, float skala = 1.f);

    void rysuj(sf::RenderTarget& cel) const { cel.draw(ksztalt); }
    const sf::ConvexShape& wezKsztalt() const { return ksztalt; }

    sf::Vector2f najblizszyPunkt(const sf::Vector2f& p) const;

private:
    sf::ConvexShape ksztalt;
};
