#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::string& label) {
    // Initialize button shape and text
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(0, 128, 0));  // Dark green background color

    // Load the font from a file
    if (!font.loadFromFile("C:/Users/hp/source/repos/DSA project/font/bold.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Initialize text properties
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);  // Text color
    text.setPosition(x + 10, y + 5);  // Adjust text position inside the button
}

void Button::draw(sf::RenderWindow& window) {
    // Draw button and its text on the window
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(const sf::Vector2i& mousePos) {
    // Check if the mouse position is within the button's bounds
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setFillColor(const sf::Color& color) {
    // Set the button's fill color
    shape.setFillColor(color);
}

// Add hover effect
void Button::hoverEffect(const sf::Vector2i& mousePos) {
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        shape.setFillColor(sf::Color(0, 255, 0)); // Light green when hovered
    } else {
        shape.setFillColor(sf::Color(0, 128, 0)); // Dark green when not hovered
    }
}
