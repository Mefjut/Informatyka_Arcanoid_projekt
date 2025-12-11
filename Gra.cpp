#include "Gra.h"
#include <algorithm>
#include <cmath>
#include <iostream>

Gra::Gra()
    : m_paleta(400.f, 540.f, 100.f, 20.f, 8.f),
    m_kula(400.f, 300.f, 3.f, -4.f, 8.f),            
    m_przeszkoda(sf::Vector2f(380.f, 250.f), 1.2f),
    m_gameOver(false)
{
    resetGra();
}

void Gra::resetGra()
{
    m_gameOver = false;

    m_paleta.ustawPozycje({ 400.f, 540.f });
    m_kula.reset({ 400.f, 300.f }, { 3.f, -4.f }); 

    m_klocki.clear();

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float WY_BLOK = 25.f;
    const float SZ_BLOK = (SZEROKOSC - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    m_klocki.reserve(ILOSC_KOLUMN * ILOSC_WIERSZY);

    for (int w = 0; w < ILOSC_WIERSZY; ++w)
    {
        for (int k = 0; k < ILOSC_KOLUMN; ++k)
        {
            float posX = k * (SZ_BLOK + 2.f);
            float posY = 50.f + w * (WY_BLOK + 2.f);

            int wytrzymalosc = (w == 0) ? 3 : (w < 3) ? 2 : 1;

            m_klocki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(SZ_BLOK, WY_BLOK),
                wytrzymalosc
            );
        }
    }
}

void Gra::aktualizuj(sf::Time)
{
    if (m_gameOver) return; 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        m_snapshot.przechwyc(m_paleta, m_kula, m_klocki);
        std::cout << "Game snapshot saved\n";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paleta.ruchLewo();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paleta.ruchPrawo();

    m_paleta.ograniczDoEkranu(SZEROKOSC);

    m_kula.ruch();
    m_kula.kolizjaZeScianami(SZEROKOSC, WYSOKOSC);

    if (m_kula.kolizjaZPaleta(m_paleta)) {
        std::cout << "BALL BOUNCED FROM PADDLE\n";
    }

    float bx = m_kula.wezX();
    float by = m_kula.wezY();
    float br = m_kula.wezPromien();

    for (auto& klocek : m_klocki)
    {
        if (klocek.czyZniszczony()) continue;

        float left = klocek.getPosition().x;
        float top = klocek.getPosition().y;
        float right = left + klocek.getSize().x;
        float bottom = top + klocek.getSize().y;

        bool kolizja =
            (bx + br > left) &&
            (bx - br < right) &&
            (by + br > top) &&
            (by - br < bottom);

        if (kolizja)
        {
            float overlapLeft = (bx + br) - left;
            float overlapRight = right - (bx - br);
            float overlapTop = (by + br) - top;
            float overlapBottom = bottom - (by - br);

            float minX = std::min(overlapLeft, overlapRight);
            float minY = std::min(overlapTop, overlapBottom);

            if (minX < minY) m_kula.odbijX();
            else             m_kula.odbijY();

            klocek.otrzymajUderzenie();
            break;         }
    }

    {
        sf::Vector2f center(bx, by);
        sf::Vector2f closest = m_przeszkoda.najblizszyPunkt(center);

        float dx = center.x - closest.x;
        float dy = center.y - closest.y;
        float dist2 = dx * dx + dy * dy;

        if (dist2 <= br * br)
        {
            float dist = std::sqrt(dist2);
            if (dist < 1e-6f) dist = br; 

            sf::Vector2f normal(dx / dist, dy / dist);

            float vx = m_kula.wezVX();
            float vy = m_kula.wezVY();
            float dot = vx * normal.x + vy * normal.y;

            float nvx = vx - 2.f * dot * normal.x;
            float nvy = vy - 2.f * dot * normal.y;

            m_kula.ustawPredkosc(nvx, nvy);

            float push = br + 1.f;
            float newx = closest.x + normal.x * push;
            float newy = closest.y + normal.y * push;

            m_kula.reset(sf::Vector2f(newx, newy), sf::Vector2f(nvx, nvy));
        }
    }

    if (m_kula.wezY() - m_kula.wezPromien() > WYSOKOSC)
    {
        std::cout << "BALL FELL OUT - GAME OVER\n";
        m_gameOver = true;
    }
}
void Gra::rysuj(sf::RenderTarget& cel)
{
    m_paleta.rysuj(cel);

    for (auto& k : m_klocki)
        k.rysuj(cel);

    m_przeszkoda.rysuj(cel);
    m_kula.rysuj(cel);
}

bool Gra::zapiszGre(const std::string& nazwaPliku)
{
    m_snapshot.przechwyc(m_paleta, m_kula, m_klocki);
    return m_snapshot.zapiszDoPliku(nazwaPliku);
}

bool Gra::wczytajGre(const std::string& nazwaPliku)
{
    StanGry stan;
    if (!stan.wczytajZPliku(nazwaPliku)) return false;

    stan.zastosuj(m_paleta, m_kula, m_klocki);
    m_snapshot = stan;
    m_gameOver = false;
    return true;
}
