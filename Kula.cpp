#include "Kula.h"
#include "Paleta.h"
#include <iostream>
#include <cmath>

Kula::Kula(float x_in, float y_in, float vx_in, float vy_in, float r_in)
    : x(x_in), y(y_in), vx(vx_in), vy(vy_in), r(r_in)
{
    shape.setRadius(r);
    shape.setOrigin(r, r);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(200, 170, 120));
}

void Kula::drukuj() const {
    std::cout << " x=" << x << " y=" << y << " vx=" << vx << " vy=" << vy << "\n";
}

void Kula::ruch() {
    x += vx;
    y += vy;
    shape.setPosition(x, y);
}

void Kula::odbijX() {
    vx = -vx;
}

void Kula::odbijY() {
    vy = -vy;
}

void Kula::kolizjaZeScianami(float width, float height) {
    if (x - r <= 0.f) {
        x = r;
        odbijX();
        std::cout << "BALL HIT LEFT WALL\n";
    }
    if (x + r >= width) {
        x = width - r;
        odbijX();
        std::cout << "BALL HIT RIGHT WALL\n";
    }
    if (y - r <= 0.f) {
        y = r;
        odbijY();
        std::cout << "BALL HIT TOP WALL\n";
    }
    if (y + r >= height) {
        std::cout << "BALL HIT BOTTOM EDGE\n";
    }

    shape.setPosition(x, y);
}

bool Kula::kolizjaZPaleta(const Paleta& p) {
    float palX = p.wezX();
    float palY = p.wezY();
    float palW = p.wezSzerokosc();
    float palH = p.wezWysokosc();

    bool overlX = (x >= palX - palW / 2.f) && (x <= palX + palW / 2.f);
    bool overlY = ((y + r) >= (palY - palH / 2.f)) && (y < palY);

    if (overlX && overlY) {
        float rel = (x - palX) / (palW / 2.f);
        if (rel < -1.f) rel = -1.f;
        if (rel > 1.f)  rel = 1.f;

        const float maxAngle = 55.f * 3.14159265f / 180.f;

        float angle = rel * maxAngle;

        float speed = std::sqrt(vx * vx + vy * vy);
        if (speed < 0.01f) speed = 5.f;

        vx = speed * std::sin(angle);
        vy = -std::abs(speed * std::cos(angle));

        y = palY - palH / 2.f - r - 0.1f;
        shape.setPosition(x, y);

        return true;
    }

    return false;
}

void Kula::reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkosc) {
    x = pozycja.x;
    y = pozycja.y;
    vx = predkosc.x;
    vy = predkosc.y;
    shape.setPosition(x, y);
}

void Kula::ustawPredkosc(float nvx, float nvy) {
    vx = nvx;
    vy = nvy;
}
