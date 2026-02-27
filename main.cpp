#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode::getDesktopMode(),
        "My window",
        sf::State::Fullscreen
    );

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition({300.f, 200.f});

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        window.clear(sf::Color::Black);   // háttér szín
        window.draw(shape);               // alakzat kirajzolása
        window.display();                 // megjelenítés
    }

    return 0;
}