#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "toltesek.h"
#include "tavolsag.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>




int main()
{
    bool chackbox = chackbocmutat();    // igaz akkor lelehet rakni hamis txt böl olvas be

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"My window",sf::State::Fullscreen);




    window.setFramerateLimit(60);
    std::vector<Toltesek*> toltesek;
    sf::Vector2f egerpozi;
    Toltesek b;


    sf::Vector2f upozi = {0,0};




    bool volt_box = false;
    bool aktiv = false;
    bool spaceNyomva = false;
    float epsilon = 0.1;
    float k = 100.f;
    float t = 0.01f;

    sf::View view = window.getView();
    float speed = 300.f;
    sf::Clock clock;


    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            egerpozi =  sf::Vector2f(sf::Mouse::getPosition());
            float dTime = clock.restart().asSeconds();

            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();

            if (chackbox) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                Toltesek* t = new Toltesek(1.f ,egerpozi, sf::Color::Red);
                toltesek.push_back(t);
            }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                Toltesek* t = new Toltesek(-1.f ,egerpozi, sf::Color::Blue);
                toltesek.push_back(t);
            }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
                    Toltesek* t = new Toltesek(0.f ,egerpozi, sf::Color::Yellow);
                    toltesek.push_back(t);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)){
                toltesek.clear();
            }
            }
            if (!chackbox  && !volt_box) {
                toltesek = faljbe("adatok.txt");
                volt_box = true;
            }



            bool spaceNyomva = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);




            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                view.move({0.f, -1 * speed*dTime});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                view.move({0.f, speed*dTime});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                view.move({speed*dTime, 0.f});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                view.move({-1 * speed*dTime, 0.f});
            }
            window.setView(view);

            if (spaceNyomva) {

                std::vector<sf::Vector2f> gyorsulasok(toltesek.size(), sf::Vector2f(0.f,0.f));
                for (size_t i = 0; i < toltesek.size(); i++) {
                    sf::Vector2f osszA(0.f,0.f);
                    for (size_t j = 0; j < toltesek.size(); j++) {
                        if (i == j) continue;
                        sf::Vector2f d_ossz (toltesek[i]->getPozi().x-toltesek[j]->getPozi().x,toltesek[i]->getPozi().y-toltesek[j]->getPozi().y);
                        float r = sqrt(d_ossz.x*d_ossz.x + d_ossz.y*d_ossz.y);
                        float F = k*((toltesek[i]->getQ()*toltesek[j]->getQ())/(r*r*r+epsilon));
                        sf::Vector2f F_ossz (F*d_ossz.x,F*d_ossz.y);
                        osszA += F_ossz/toltesek[i]->getM();
                    }
                    gyorsulasok[i] = osszA;
                }


                for (size_t i = 0; i < toltesek.size(); i++) {
                    sf::Vector2f ujSeb = toltesek[i]->getSeb() + gyorsulasok[i] * t;
                    toltesek[i]->setSeb(ujSeb);
                    toltesek[i]->move(ujSeb * t);
                }

                for (int i = 0; i < toltesek.size(); i++){
                    for (int j = i + 1; j < toltesek.size(); j++) {
                        if (toltesek[i]->getQ() == (toltesek[j]->getQ())*-1 and tav(toltesek[i]->getPozi(), toltesek[j]->getPozi())){
                            upozi = (toltesek[i]->getPozi() + toltesek[j]->getPozi()) / 2.0f;
                            delete toltesek[j];
                            delete toltesek[i];
                            toltesek.erase(toltesek.begin() + j);
                            toltesek.erase(toltesek.begin() + i);
                            Toltesek* t = new Toltesek(0.f ,upozi, sf::Color::Yellow);
                            toltesek.push_back(t);
                            break;
                        }
                    }
                }
            }
















        }



        window.clear(sf::Color::Black);

        for (Toltesek* t : toltesek) {
            window.draw(t->getKor());
        }


        window.display();
    }

    return 0;
}
