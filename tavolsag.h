#ifndef FIZIKA_TAVOLSAG_H
#define FIZIKA_TAVOLSAG_H
#include "SFML/System/Vector2.hpp"

inline bool tav(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return (dx*dx + dy*dy) < 400.f;
}

#endif //FIZIKA_TAVOLSAG_H