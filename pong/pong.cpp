#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode({ 800, 600 }), "PONG GAME");
    window.setFramerateLimit(60);


    sf::RectangleShape rectanglePlayer1(sf::Vector2f(15.f, 100.f));
    rectanglePlayer1.setFillColor(sf::Color::White);
    rectanglePlayer1.setOrigin(rectanglePlayer1.getSize() / 2.f);
    rectanglePlayer1.setPosition(sf::Vector2f(150.f, window.getSize().y / 2.f));

 
    while (window.isOpen())
    {
        
        
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.draw(rectanglePlayer1);
        window.display();
    }

    return 0;
}