#ifndef FIZIKA_TOLTESEK_H
#define FIZIKA_TOLTESEK_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Toltesek{
protected:
    float q;
    float m;
    sf::Vector2f pozi;      //ahova levan rakva
    sf::Vector2f seb;       //
    sf::Vector2f gyors;     //nincs használva
    sf::CircleShape kor;

public:
    Toltesek(float q, sf::Vector2f pozi, sf::Color szin);
    ~Toltesek() = default;

    float getQ() const ;
    float getM() const ;
    sf::Vector2f getPozi() const ;
    sf::Vector2f getSeb() const ;
    sf::Vector2f getGyors() const ;
    sf::CircleShape& getKor();

    void setPozi(sf::Vector2f kov);
    void setSeb(sf::Vector2f ujSeb);
    void setGyors(sf::Vector2f ujGyors);
    void setQ(float ujQ);

    void move(sf::Vector2f ujMz);

};

#endif //FIZIKA_TOLTESEK_H