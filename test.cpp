#include <SFML/Graphics.hpp>

int main()
{
    const int WINDOW_HEIGHT = 800;
    const int WINDOW_WIDTH = 800;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hex Test");

    // Drawing entities
    sf::CircleShape shape(100.f, 6);
    shape.setFillColor(sf::Color::Black);
    shape.move(0, 10);
    shape.rotate(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // https://en.sfml-dev.org/forums/index.php?topic=8489.0
        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }

    return 0;
}