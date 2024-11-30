#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape;  // The button shape (a rectangle)
    sf::Text text;             // Text displayed on the button
    sf::Font font;             // Font used for the button text

public:
    // Constructor to initialize the button
    Button(float x, float y, float width, float height, const std::string& label);

    // Function to draw the button
    void draw(sf::RenderWindow& window);

    // Function to check if the button was clicked
    bool isClicked(const sf::Vector2i& mousePos);

    // Function to set the button's fill color
    void setFillColor(const sf::Color& color);

    // Function to add hover effect to the button
    void hoverEffect(const sf::Vector2i& mousePos);

};

#endif
