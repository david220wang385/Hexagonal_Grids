#include <SFML/Graphics.hpp>
#include "../Header_Files/Hex.h"
#include "../Header_Files/LabelHex.h"

int main(){

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

    sf::Text label;
    sf::Font font;

    // Directory to load from is ./hex_grid_implementation
    if (!font.loadFromFile("./Resources/arial.ttf")){}

    LabelHex label_hex("hello there", HEX_SIZE, font);

    label.setFont(font);
    label.setString("label_text");
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::Blue);
    label.setOrigin(10, 10);
    label.move(400,400);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // https://en.sfml-dev.org/forums/index.php?topic=8489.0
        window.clear(sf::Color::White);
        window.draw(label_hex);
        // window.draw(shape);
        // window.draw(label);
        window.display();
    }

    return 0;
}