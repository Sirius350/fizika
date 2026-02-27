//
// Created by marto on 2026. 02. 27..
//

#ifndef FIZIKA_TOLTESEK_H
#define FIZIKA_TOLTESEK_H

#include <SFML/Graphics.hpp>

class Toltesek{
protected:
    int q;
    int m;
    float x;
    float y;
    float vx;
    float vy;
    float ax;
    float ay;
public:
    Toltesek(int q, int m, float x, float y, float vx, float vy, float ax, float ay) : q(q), m(m), x(x), y(y), vx(vx), vy(vy) {}
    virtual ~Toltesek() = default;
    int getQ(){return q;}
    int getM(){return m;}
    float getX(){return x;}
    float getY(){return y;}
    float getVX(){return vx;}
    float getVY(){return vy;}
    float getAx(){return ax;}
    float getAy(){return ay;}

};

#endif //FIZIKA_TOLTESEK_H