#ifndef FIZIKA_TAVOLSAG_H
#define FIZIKA_TAVOLSAG_H
#include <cmath>
#include <fstream>

#include "SFML/System/Vector2.hpp"
#include "Toltesek.h"

inline float d_tav(const  sf::Vector2f& v1, const  std::string n, const  sf::Vector2f& v2) {
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

bool chackbocmutat() {
    sf::RenderWindow window(sf::VideoMode({400, 200}), "Kezdeti beallitas", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::RectangleShape checkbox(sf::Vector2f(20.f, 20.f));
    checkbox.setPosition({50.f, 50.f});
    checkbox.setFillColor(sf::Color::Red);
    checkbox.setOutlineThickness(2.f);
    checkbox.setOutlineColor(sf::Color::Black);



    bool checked = false;
    bool done = false;
    bool mousePrev = false;

    while (window.isOpen() && !done) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        bool mouseNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (mouseNow && !mousePrev) {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePixel.x), static_cast<float>(mousePixel.y));
            if (checkbox.getGlobalBounds().contains(mousePosF)) {
                checked = !checked;
            }
        }
        mousePrev = mouseNow;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            done = true;
        }


        checkbox.setFillColor(checked ? sf::Color::Green : sf::Color::Red);

        window.clear(sf::Color(200, 200, 200));
        window.draw(checkbox);

        if (checked) {
            sf::Vertex line1[] = {
                sf::Vertex(sf::Vector2f(checkbox.getPosition().x, checkbox.getPosition().y)),
                sf::Vertex(sf::Vector2f(checkbox.getPosition().x + 20.f, checkbox.getPosition().y + 20.f))
            };
            sf::Vertex line2[] = {
                sf::Vertex(sf::Vector2f(checkbox.getPosition().x + 20.f, checkbox.getPosition().y)),
                sf::Vertex(sf::Vector2f(checkbox.getPosition().x, checkbox.getPosition().y + 20.f))
            };
            window.draw(line1, 2, sf::PrimitiveType::Lines);
            window.draw(line2, 2, sf::PrimitiveType::Lines);
        }

        window.display();
    }
    return checked;
}

sf::Color szinStingbol(const std::string& s) {
    if (s == "Red") return sf::Color::Red;
    else if (s == "Green") return sf::Color::Green;
    else if (s == "Blue") return sf::Color::Blue;
    else if (s == "Yellow") return sf::Color::Yellow;
    return sf::Color::White;
}

std::vector<Toltesek*> faljbe(const std::string& fajlNev) {
    std::ifstream file (fajlNev);
    std::vector<Toltesek*> v;
    if (!file.is_open()) {
        std::cerr << "Nem sikerult megnyitni a fajlt: " << fajlNev << std::endl;
        return v;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string mezo;
        std::vector<std::string> adatok;

        while (std::getline(ss, mezo, ';')) {
            adatok.push_back(mezo);
        }

        if (adatok.size() == 7) {
            float q = std::stof(adatok[0]);
            float m = std::stof(adatok[1]);
            sf::Vector2f pozi(std::stof(adatok[2]), std::stof(adatok[3]));
            sf::Vector2f seb(std::stof(adatok[4]), std::stof(adatok[5]));
            sf::Color szin = szinStingbol(adatok[6]);

            v.push_back(new Toltesek(q, m, pozi, seb, szin));
        }
    }
    file.close();
    return v;
}




/*inline float tavszam_r(const  sf::Vector2f& v1, const sf::Vector2f& v2) {
    float dx = d_tav(v1, "x", v2);
    float dy = d_tav(v1, "y", v2);
    float dxy = dx*dx + dy*dy;
    dxy = std::sqrt(dxy);
    return dxy;
}

inline sf::Vector2f ero(const Toltesek& v1,  const Toltesek& v2) {
    float k = 100.f;         //Coulomb-állandó
    float r = tavszam_r(v1.getPozi(), v2.getPozi());
    float epsilon = 0.1f;
    float dx = d_tav(v1.getPozi(), "x", v2.getPozi());
    float dy = d_tav(v1.getPozi(), "y", v2.getPozi());
    float f = k*((v1.getQ()*v2.getQ())/(r*r*r));
    return sf::Vector2f(dx * f, dy * f);
}

inline sf::Vector2f gyors(const Toltesek& v1,  const Toltesek& v2) {
    sf::Vector2f res = (ero(v1,v2));
    return sf::Vector2f(res.x/v1.getM(), res.y/v1.getM());
}
inline sf::Vector2f seb(const Toltesek& v1,  const Toltesek& v2) {
    float t = 0.01f ;       //0,01t
    sf::Vector2f gyor = gyors(v1,v2);
    return sf::Vector2f(gyor.x * t, gyor.y * t);
}

inline sf::Vector2f pozi(const Toltesek& v1,  const Toltesek& v2) {
    float t = 0.01f ;       //0,01t
    sf::Vector2f sebbes = seb(v1, v2);
    float x = sebbes.x*t;
    float y = sebbes.y*t;
    sf::Vector2f poti_p = {x,y};
    return poti_p;
}*/

#endif //FIZIKA_TAVOLSAG_H