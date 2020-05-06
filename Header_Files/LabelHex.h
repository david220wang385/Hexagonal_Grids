#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// https://www.geeksforgeeks.org/inheritance-in-c/
struct LabelHex : public sf::Drawable{
//struct LabelHex{

    // Remove this later
    sf::Color hex_background = sf::Color(0, 150, 16);
    sf::Color hex_outline = sf::Color(179, 179, 179);;

    // Internal Text member to store the label information
    sf::Text label;
    sf::CircleShape hex;

    // Constructor
    LabelHex(std::string label_text, int radius, sf::Font& font){

        label.setString(label_text);
        label.setCharacterSize(24);
        label.setFillColor(sf::Color::Blue);
        label.setOrigin(radius, radius);
        label.move(400,400);

        setupHexDisplay(radius);
        textSetFont(font);
    }

    // Make the actual shape appear as a hexagon
    void setupHexDisplay(int radius){
        hex.setRadius(radius);
        hex.setPointCount(6); // Cause hexagon
        hex.setOrigin(hex.getRadius(), hex.getRadius());
        hex.setFillColor(hex_background);
        hex.setOutlineColor(hex_outline);
        hex.setOutlineThickness(hex.getRadius()/25.f);
        hex.move(400,400);
        hex.rotate(30);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(hex);
        target.draw(label);
    }

    void textSetFont(sf::Font& font){
        label.setFont(font);
    }
};