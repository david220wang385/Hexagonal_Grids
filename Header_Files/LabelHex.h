#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// Hex Colors
const sf::Color hex_background(244, 244, 241);
const sf::Color hex_outline(179, 179, 179);

// https://www.geeksforgeeks.org/inheritance-in-c/
struct LabelHex : public sf::Drawable, sf::Transformable{

    // Internal Text member to store the label information
    sf::Text label;
    sf::CircleShape hexShape;
    Hex hex;

    // Constructor
    // https://stackoverflow.com/questions/59459450/sfml-2-4-2-segmentation-fault-when-drawing-text
    // This answer took me over 2 hours to find
    LabelHex(std::string label_text, int radius, sf::Font& font, Hex hex_) : hex(hex_){
        
        // Text label styling
        label.setFont(font); // Font 
        label.setString(label_text);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::Blue);

        // https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
        sf::FloatRect textRect = label.getLocalBounds();
        label.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

        // Hexagon styling
        hexShape.setRadius(radius);
        hexShape.setPointCount(6); // Cause hexagon
        hexShape.setOrigin(radius, radius);
        hexShape.setFillColor(hex_background);
        hexShape.setOutlineColor(hex_outline);
        hexShape.setOutlineThickness(radius/50.f);
        hexShape.rotate(30);
    }

    // Overwritten draw function to draw both the hex and label
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(hexShape);
        target.draw(label);
    }

    void setPosition(float x, float y){
        hexShape.setPosition(x, y);
        label.setPosition(x, y);
    }

    void scale(float x, float y){
        hexShape.scale(x, y);
        label.scale(x, y);
    }
};