#pragma once
#include <SFML/Graphics.hpp>

class Paleta; 

class Kula {
public:
    Kula(float x_in = 400.f, float y_in = 300.f, float vx_in = 4.f, float vy_in = 3.f, float r_in = 8.f);
        
    void ruch();
    void kolizjaZeScianami(float width, float height);
    bool kolizjaZPaleta(const Paleta& p); 
    void odbijX();
    void odbijY();
        
    void reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkosc);
    void ustawPredkosc(float nvx, float nvy);

   float wezX() const { return x; }
    float wezY() const { return y; }
    float wezVX() const { return vx; }
    float wezVY() const { return vy; }
    float wezPromien() const { return r; }
       
    void rysuj(sf::RenderTarget& cel) const { cel.draw(shape); }
        
    void drukuj() const;

private:
    float x, y;
    float vx, vy;
    float r;
    sf::CircleShape shape;
};
