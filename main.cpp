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
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"My window",sf::State::Fullscreen);





    std::vector<Toltesek*> toltesek;
    sf::Vector2f egerpozi;
    bool megy = false;
    sf::Clock clock;
    sf::Time vissza = sf::seconds(30);
    sf::Vector2f upozi = {0,0};


    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            egerpozi =  sf::Vector2f(sf::Mouse::getPosition(window));

            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)){
                toltesek.clear();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                if (megy) {
                    megy = false;
                }
                else {
                    megy = true;
                    clock.restart();
                }
            }
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


            if(megy) {
                for (int i = 0; i < toltesek.size(); i++){
                    for (int j = i + 1; j < toltesek.size(); j++) {
                        if (toltesek[i]->getQ() == (toltesek[j]->getQ())*-1 and tav(toltesek[i]->getPozi(), toltesek[j]->getPozi())){
                            upozi = toltesek[i]->getPozi();
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
