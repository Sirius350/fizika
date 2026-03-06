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

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"My window",sf::State::Fullscreen); //létrehozza az ablakot




    window.setFramerateLimit(60);       //fps limit
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

    sf::Font font;          //bal felsősarokban lévő szöveg dolgai
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Betűtípus betöltése sikertelen!" << std::endl;
        return -1;
    }
    sf::Text text(font);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({50, 50});     //eddig


    sf::Vector2u ablakMeret = window.getSize(); //a háttérben lévő rácshló
    sf::Texture gridTex = makeGrid(sf::Vector2i(ablakMeret.x, ablakMeret.y), 50, sf::Color::Black, sf::Color(50,50,50));
    sf::Sprite gridSprite(gridTex);     //eddig


    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            egerpozi =  sf::Vector2f(sf::Mouse::getPosition());
            float dTime = clock.restart().asSeconds();

            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))      //kilépés
                window.close();

            if (chackbox) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {      //bal klik pozitív
                Toltesek* t = new Toltesek(1.f ,egerpozi, sf::Color::Red);
                toltesek.push_back(t);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {      //jobb klik negatív
                Toltesek* t = new Toltesek(-1.f ,egerpozi, sf::Color::Blue);
                toltesek.push_back(t);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {         //h és ahol az egér van oda semleges
                    Toltesek* t = new Toltesek(0.f ,egerpozi, sf::Color::Yellow);
                    toltesek.push_back(t);
                }
            }
            if (!chackbox  && !volt_box) {      //fálj betöltés
                toltesek = faljbe("adatok.txt");
                volt_box = true;
            }



            bool spaceNyomva = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);    //space nyomva tartás ellenörzése



            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)){          //összes törlése
                for (Toltesek* t : toltesek)
                    delete t;
                toltesek.clear();
                volt_box = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add)) {       //a t növelése
                t += 0.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract)) {  //a t csökkentése
                t -= 0.1f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {        //kemera irányítása
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
            window.setView(view);                                            //eddig

            if (spaceNyomva) {      // a számolások indítása

                std::vector<sf::Vector2f> gyorsulasok(toltesek.size(), sf::Vector2f(0.f,0.f));
                for (size_t i = 0; i < toltesek.size(); i++) {      //gyorsulások kiszámítása
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


                for (size_t i = 0; i < toltesek.size(); i++) {      //a tényleges elmozdulás és sebesség kiszámítása
                    sf::Vector2f ujSeb = toltesek[i]->getSeb() + gyorsulasok[i] * t;
                    toltesek[i]->setSeb(ujSeb);
                    toltesek[i]->move(ujSeb * t);
                }

                for (int i = 0; i < toltesek.size(); i++){      //ha 2 találkozik és azok ellentétesek akkor egy semleges a 2 helyére
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
        std::ostringstream ss;
        ss << "t = " << t;
        text.setString(ss.str());

        window.clear(sf::Color::Black);

        window.draw(gridSprite);        //kirajzolások
        window.draw(text);

        for (Toltesek* t : toltesek) {
            window.draw(t->getKor());
        }


        window.display();
    }
    for (Toltesek* t : toltesek)
        delete t;
    return 0;
}
