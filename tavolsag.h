#ifndef FIZIKA_TAVOLSAG_H
#define FIZIKA_TAVOLSAG_H
#include <cmath>
#include "SFML/System/Vector2.hpp"

float d_tav(const  sf::Vector2f& v1, const  std::string n, const  sf::Vector2f& v2) {
    if(n == "x") {
        return v1.x - v2.x;
    }
    if(n == "y") {
        return v1.y - v2.y;
    }
}

inline bool tav(const  sf::Vector2f& v1, const  sf::Vector2f& v2) {
    float dx = d_tav(v1, "x", v2);
    float dy = d_tav(v1, "y", v2);
    return (dx*dx + dy*dy) < 400.f;
}

float tavszam_r(const  sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dx = d_tav(v1, "x", v2);
    float dy = d_tav(v1, "y", v2);
    float dxy = dx*dx + dy*dy;
    dxy = std::sqrt(dxy);
    return dxy;
}

sf::Vector2f ero(const Toltesek& v1,  const Toltesek& v2) {
    float k = 100.f;         //Coulomb-állandó
    float r = tavszam_r(v1.getPozi(), v2.getPozi());
    float epsilon = 0.1f;
    float dx = d_tav(v1.getPozi(), "x", v2.getPozi());
    float dy = d_tav(v1.getPozi(), "y", v2.getPozi());
    float f = k*((v1.getQ()*v2.getQ())/(r*r*r));
    return sf::Vector2f(dx * f, dy * f);
}

sf::Vector2f gyors(const Toltesek& v1,  const Toltesek& v2) {
    sf::Vector2f res = (ero(v1,v2));
    return sf::Vector2f(res.x/v1.getM(), res.y/v1.getM());
}
sf::Vector2f seb(const Toltesek& v1,  const Toltesek& v2) {
    float t = 0.01f ;       //0,01t
    sf::Vector2f gyor = gyors(v1,v2);
    return sf::Vector2f(gyor.x * t, gyor.y * t);
}

sf::Vector2f pozi(const Toltesek& v1,  const Toltesek& v2) {
    float t = 0.01f ;       //0,01t
    sf::Vector2f sebbes = seb(v1, v2);
    float x = sebbes.x*t;
    float y = sebbes.y*t;
    sf::Vector2f poti_p = {x,y};
    return poti_p;
}

#endif //FIZIKA_TAVOLSAG_H