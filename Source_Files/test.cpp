#include <SFML/Graphics.hpp>
#include "../Header_Files/Hex.h"

int main()
{
    std::vector<Hex> range = hex_range(Hex(0,0,0), 2);
    for(auto it = range.begin(); it != range.end(); it++){
        std::cout << it->q << " " << it->r << " " << it->s << std::endl;
    }
    const int WINDOW_HEIGHT = 800;
    const int WINDOW_WIDTH = 800;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hex Test");

    // Colors
    sf::Color hex_background(244, 244, 241);
    sf::Color hex_outline(179, 179, 179);

    // Hex Sizes
    const double HEX_SIZE = 50.f;
    const double HEX_OUTLINE = HEX_SIZE/25.f;

    // Drawing entities
    // https://en.sfml-dev.org/forums/index.php?topic=19206.0
    sf::CircleShape shape(HEX_SIZE, 6);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setFillColor(hex_background);
    shape.setOutlineColor(hex_outline);
    shape.setOutlineThickness(HEX_OUTLINE);
    shape.move(400, 400);
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