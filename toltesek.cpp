#include "Toltesek.h"

Toltesek::Toltesek(float q, sf::Vector2f pozi, sf::Color szin) : q(q), m(0.01f), pozi(pozi), seb(0.f, 0.f), gyors(0.f, 0.f) {
    kor.setRadius(10.f);
    kor.setOrigin({10.f, 10.f});
    kor.setPosition(pozi);
    kor.setFillColor(szin);
}

float Toltesek::getQ() const  {return q;}
float Toltesek::getM() const  {return m;}
sf::Vector2f Toltesek::getPozi() const  {return pozi;}
sf::Vector2f Toltesek::getSeb() const  {return seb;}
sf::Vector2f Toltesek::getGyors() const  {return gyors;}
sf::CircleShape& Toltesek::getKor() {return kor;}

void Toltesek::setPozi(sf::Vector2f kov) {pozi += kov;}
void Toltesek::setSeb(sf::Vector2f ujSeb) {seb = ujSeb;kor.setPosition(pozi);}
void Toltesek::setGyors(sf::Vector2f ujGyors) {gyors = ujGyors;}
void Toltesek::setQ(float ujQ) {q = ujQ;}

void Toltesek::move(sf::Vector2f ujMz) {
    pozi += ujMz;
    kor.move(pozi);
}
