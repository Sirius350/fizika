#ifndef FIZIKA_TOLTESEK_H
#define FIZIKA_TOLTESEK_H

#include <SFML/Graphics.hpp>

#include <vector>

// atöltések osztály
class Toltesek{
protected:
    float q;
    float m;
    sf::Vector2f pozi;      //ahova levan rakva
    sf::Vector2f seb;       //be lehet állítami
    sf::Vector2f gyors;     //nincs használva
    sf::CircleShape kor;

public:
    Toltesek(float q, sf::Vector2f pozi, sf::Color szin);   //ha kézzel tesszük le a konstuktora
    Toltesek(float q, float m, sf::Vector2f pozi, sf::Vector2f seb, sf::Color szin);    //ha fáljbololvassuk be a konstruktora
    Toltesek();
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
    void setM(float ujM);

    void move(sf::Vector2f ujMz);   //mozgatás
    Toltesek& operator<<=(std::vector<Toltesek*> & lista);  //<<= opraátor
    Toltesek& operator-=(std::vector<Toltesek*> & lista);   //-= operátor


};

#endif //FIZIKA_TOLTESEK_H