#ifndef FIZIKA_TAVOLSAG_H
#define FIZIKA_TAVOLSAG_H

#include <fstream>

#include "SFML/System/Vector2.hpp"
#include "Toltesek.h"
#include <cstdlib>

//dx vagy dy-t adja vissza
inline float d_tav(const  sf::Vector2f& v1, const  std::string n, const  sf::Vector2f& v2) {
    if(n == "x") {
        return v1.x - v2.x;
    }
    if(n == "y") {
        return v1.y - v2.y;
    }
}

//a 2 közt a távolság kiszámítása
inline bool tav(const  sf::Vector2f& v1, const  sf::Vector2f& v2) {
    float dx = d_tav(v1, "x", v2);
    float dy = d_tav(v1, "y", v2);
    return (dx*dx + dy*dy) < 400.f;
}

// a kezdeti checkbox megjelenítése
bool chackbocmutat() {
    sf::RenderWindow window(sf::VideoMode({400, 200}), "Kezdeti beallitas", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::RectangleShape checkbox(sf::Vector2f(20.f, 20.f));  //maga az ami mutatja hogy mi van kiválasztva
    checkbox.setPosition({50.f, 50.f});
    checkbox.setFillColor(sf::Color::Red);
    checkbox.setOutlineThickness(2.f);
    checkbox.setOutlineColor(sf::Color::Black);
    bool checked = false;
    bool done = false;
    bool mousePrev = false;
    while (window.isOpen() && !done) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::exit(0);
            }
        }
        bool mouseNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);    //kattintás érzékelés egyszer
        if (mouseNow && !mousePrev) {
            sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePixel.x), static_cast<float>(mousePixel.y));
            if (checkbox.getGlobalBounds().contains(mousePosF)) {
                checked = !checked;
            }
        }
        mousePrev = mouseNow;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) { //enter a továblépés
            done = true;
        }
        checkbox.setFillColor(checked ? sf::Color::Green : sf::Color::Red);     //2 állás piros vagy zöld
        window.clear(sf::Color(200, 200, 200));
        window.draw(checkbox);
        window.display();
    }
    return checked;
}

sf::Color szinStingbol(const std::string& s) {  //megkap egy szint stringben és vissza adja azt Color-ként
    if (s == "Red") return sf::Color::Red;
    else if (s == "Green") return sf::Color::Green;
    else if (s == "Blue") return sf::Color::Blue;
    else if (s == "Yellow") return sf::Color::Yellow;
    return sf::Color::White;
}

std::vector<Toltesek*> faljbe(const std::string& fajlNev) { //fáljbeolvasás
    std::ifstream file (fajlNev);
    std::vector<Toltesek*> v;
    if (!file.is_open()) {                                                      //létezik-e a fálj ellenörzés
        std::cerr << "Nem sikerult megnyitni a fajlt: " << fajlNev << std::endl;
        return v;
    }
    std::string line;
    while (std::getline(file, line)) {  //a fáljbeolvasás kezdete
        std::stringstream ss(line);
        std::string mezo;
        std::vector<std::string> adatok;
        while (std::getline(ss, mezo, ';')) {   //a ; mentén feldarabolja a szöveget
            adatok.push_back(mezo);
        }
        if (adatok.size() == 7) {   //a feldarabolt szövegböl létre hoz egy objektumot és beleteszi egy listába
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

sf::Texture makeGrid(const sf::Vector2i& size, int boxSize, const sf::Color& bgColor, const sf::Color& lineColor) { //a rácsháló létrehozása
    sf::RenderTexture out({(unsigned)size.x, (unsigned)size.y});
    out.clear(bgColor);
    sf::RectangleShape line;
    line.setFillColor(lineColor);
    for(int y = 0; y <= size.y; y += boxSize) {         //vízszintes rácsvonalak
        line.setSize({(float)size.x, 1.f});
        line.setPosition({0.f, (float)y});
        out.draw(line);
    }
    for(int x = 0; x <= size.x; x += boxSize) {         //függőleges rácsvonalak
        line.setSize({1.f, (float)size.y});
        line.setPosition({(float)x, 0.f});
        out.draw(line);
    }
    out.display();
    return out.getTexture();
}
#endif //FIZIKA_TAVOLSAG_H
