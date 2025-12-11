#include "Glaz.h"

Glaz::Glaz(sf::Vector2f startPos, sf::Vector2f rozmiar, int wytrzymalosc)
{
    m_zycie = wytrzymalosc;
    m_czyZniszczony = false;

    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->setOutlineThickness(1.5f);

    odswiezKolor();
}

void Glaz::otrzymajUderzenie()
{
    if (m_czyZniszczony)
        return;

    m_zycie--;
    odswiezKolor();

    if (m_zycie <= 0)
        m_czyZniszczony = true;
}

void Glaz::odswiezKolor()
{
    int indeks = m_zycie;
    if (indeks < 0) indeks = 0;
    if (indeks >= static_cast<int>(m_koloryLUT.size()))
        indeks = static_cast<int>(m_koloryLUT.size()) - 1;

    this->setFillColor(m_koloryLUT[indeks]);
}

void Glaz::rysuj(sf::RenderTarget& target) const
{
    if (!m_czyZniszczony)
        target.draw(*this);
}

const std::array<sf::Color, 4> Glaz::m_koloryLUT =
{
    sf::Color::Transparent,
    sf::Color(140, 110, 100),
    sf::Color(160, 150, 135),
    sf::Color(185, 175, 165)
};