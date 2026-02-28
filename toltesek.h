#ifndef FIZIKA_TOLTESEK_H
#define FIZIKA_TOLTESEK_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Toltesek{
protected:
    float q;
    float m;
    sf::Vector2f pozi;
    sf::Vector2f seb;
    sf::Vector2f gyors;
    sf::CircleShape kor;

public:
    Toltesek(float q, sf::Vector2f pozi, sf::Color szin);
    virtual ~Toltesek() = default;

    float getQ();
    float getM();
    sf::Vector2f getPozi();
    sf::Vector2f getSeb();
    sf::Vector2f getGyors();
    sf::CircleShape& getKor();

    void setPozi(sf::Vector2f kov);
    void setSeb(sf::Vector2f ujSeb);
    void setGyors(sf::Vector2f ujGyors);
    void setQ(float ujQ);

};

#endif //FIZIKA_TOLTESEK_H