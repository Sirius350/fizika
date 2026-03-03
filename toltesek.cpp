#include "Toltesek.h"

Toltesek::Toltesek(float q, sf::Vector2f pozi, sf::Color szin) : q(q), m(0.01f), pozi(pozi), seb(0.f, 0.f), gyors(0.f, 0.f) {
    kor.setRadius(10.f);
    kor.setOrigin({10.f, 10.f});
    kor.setPosition(pozi);
    kor.setFillColor(szin);
}

Toltesek::Toltesek() {
    q = 0;
    m = 0;
    pozi = sf::Vector2f(0,0);
    seb = sf::Vector2f(0,0);
    gyors = sf::Vector2f(0,0);

}


Toltesek::Toltesek(float q, float m, sf::Vector2f pozi, sf::Vector2f seb, sf::Color szin) : q(q), m(m), pozi(pozi), seb(seb) {
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
void Toltesek::setSeb(sf::Vector2f ujSeb) {seb = ujSeb;}
void Toltesek::setGyors(sf::Vector2f ujGyors) {gyors = ujGyors;}
void Toltesek::setQ(float ujQ) {q = ujQ;}
void Toltesek::setM(float ujM) {m = ujM;}

void Toltesek::move(sf::Vector2f ujMz) {
    pozi += ujMz;
    kor.setPosition(pozi);
}

Toltesek& Toltesek::operator<<= (std::vector<Toltesek*> &lista) {
    if (lista.empty()) {
        return *this;
    }
    int db = lista.size();
    int sorsz = rand() % db;
    lista[sorsz]->setM((static_cast<float>(rand() / RAND_MAX) * (2*lista[sorsz]->getQ()+1) - lista[sorsz]->getQ()));
}

Toltesek &Toltesek::operator-=(std::vector<Toltesek *> &lista) {
    if (lista.empty()) {
        return *this;
    }
    int szaml = 0;
    int db = lista.size();
    while (szaml < db) {
        int i = rand() % lista.size();
        delete lista[i];
        lista.erase(lista.begin() + i);
    }
}



