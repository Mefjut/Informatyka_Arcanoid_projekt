#include "Przeszkoda.h"
#include <algorithm>

Przeszkoda::Przeszkoda(const sf::Vector2f& pozycja, float skala)
{
    ksztalt.setPointCount(6);

    ksztalt.setPoint(0, { 0.f * skala,  -30.f * skala });
    ksztalt.setPoint(1, { 25.f * skala,  -15.f * skala });
    ksztalt.setPoint(2, { 30.f * skala,   10.f * skala });
    ksztalt.setPoint(3, { 15.f * skala,   30.f * skala });
    ksztalt.setPoint(4, { -20.f * skala,  25.f * skala });
    ksztalt.setPoint(5, { -28.f * skala,   0.f * skala });

    ksztalt.setFillColor(sf::Color(140, 130, 120));
    ksztalt.setOutlineColor(sf::Color(70, 65, 60));
    ksztalt.setOutlineThickness(2.f);

    sf::FloatRect bounds = ksztalt.getLocalBounds();
    ksztalt.setOrigin(bounds.width / 2.f + bounds.left, bounds.height / 2.f + bounds.top);
    ksztalt.setPosition(pozycja);
}

sf::Vector2f Przeszkoda::najblizszyPunkt(const sf::Vector2f& p) const
{
    sf::Vector2f bestPoint(0.f, 0.f);
    float bestDist2 = 1e12f;

    int count = ksztalt.getPointCount();
    for (int i = 0; i < count; ++i)
    {
        sf::Vector2f A = ksztalt.getTransform().transformPoint(ksztalt.getPoint(i));
        sf::Vector2f B = ksztalt.getTransform().transformPoint(ksztalt.getPoint((i + 1) % count));

        sf::Vector2f AB = B - A;
        sf::Vector2f AP = p - A;

        float denom = AB.x * AB.x + AB.y * AB.y;
        if (denom < 1e-6f) continue;

        float t = (AP.x * AB.x + AP.y * AB.y) / denom;
        t = std::max(0.f, std::min(1.f, t));

        sf::Vector2f closest = A + AB * t;

        float dx = closest.x - p.x;
        float dy = closest.y - p.y;
        float dist2 = dx * dx + dy * dy;

        if (dist2 < bestDist2) {
            bestDist2 = dist2;
            bestPoint = closest;
        }
    }

    return bestPoint;
}