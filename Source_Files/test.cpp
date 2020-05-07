#include <SFML/Graphics.hpp>
#include "../Header_Files/Hex.h"
#include "../Header_Files/Orientation.h"
#include "../Header_Files/LabelHex.h"
#include <cstdlib> // Random
#include <sstream> // String stream

int main(){

    const int WINDOW_HEIGHT = 800;
    const int WINDOW_WIDTH = 800;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hex Test");

    // Colors
    sf::Color hex_background(244, 244, 241);
    sf::Color hex_outline(179, 179, 179);

    // Hex Sizes
    const double HEX_SIZE = 100.f;
    const double HEX_OUTLINE = HEX_SIZE/25.f;

    // Drawing entities
    // https://en.sfml-dev.org/forums/index.php?topic=19206.0
    sf::Font font;

    // Directory to load from is ./hex_grid_implementation
    if (!font.loadFromFile("./Resources/arial.ttf")){}

    std::vector<LabelHex> hex_group;
    hex_group.reserve(7);

    LabelHex label_hex("(0, 0, 0)", HEX_SIZE, font, Hex(0,0,0));
    hex_group.push_back(label_hex);
    hex_group[0].setPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    for(int i = 0; i < hex_adjacents.size(); i++){

        // https://stackoverflow.com/questions/191757/how-to-concatenate-a-stdstring-and-an-int
        std::stringstream sstm;
        sstm << "(" << hex_adjacents[i].q << ", "
                    << hex_adjacents[i].r << ", "
                    << hex_adjacents[i].q << ")";

        LabelHex adj(sstm.str() , HEX_SIZE, font, hex_adjacents[i]);

        // Position hex relative to origin hex
        Layout grid_layout(orientation_flat, Point(HEX_SIZE, HEX_SIZE), Point(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f));
        Point p = hex_to_pixel(grid_layout, hex_adjacents[i]);
        adj.setPosition(p.x, p.y);
        hex_group.push_back(adj);
    }


    while (window.isOpen()){
        sf::Event event;
        double scale = 1;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){ window.close(); }

            // https://stackoverflow.com/questions/30372484/sfml-mouse-click-detection
            if (event.type == sf::Event::MouseButtonPressed){
                // for(auto it = hex_group.begin(); it != hex_group.end(); it++){
                //     it->scale(scale, scale);
                // }  
            }
        }

        // https://en.sfml-dev.org/forums/index.php?topic=8489.0
        window.clear(sf::Color::White);
        for(auto it = hex_group.begin(); it != hex_group.end(); it++){
            window.draw(*it);
            it->scale(scale, scale);
        }
        scale -= 0.0001;
        window.display();
    }

    return 0;
}