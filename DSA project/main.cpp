#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Pointer.h"
#include "Button.h"  

int main() {
    int rows = 30;  // Maze dimensions
    int cols = 30;
    int cellSize = 20;

    Maze maze(rows, cols);
    maze.generateMaze();

    const auto& grid = maze.getGrid();

    // Create a pointer starting at (1, 1) and ending at (rows - 2, cols - 2)
    Pointer pointer(1, 1, cols - 2, rows - 2, grid);

    sf::RenderWindow window(sf::VideoMode(cols * cellSize + 200, rows * cellSize), "Maze Pointer");
    sf::Clock clock; // Clock to control movement speed
    float movementDelay = 0.2f; // Delay in seconds between movements

    // Create buttons
    Button regenerateButton(cols * cellSize + 20, 50, 150, 50, "change Maze");
    Button resetButton(cols * cellSize + 20, 120, 150, 50, "Reset");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for mouse click on buttons
            if (event.type == sf::Event::MouseButtonPressed) {
                if (regenerateButton.isClicked(sf::Mouse::getPosition(window))) {
                    maze.generateMaze(); // Generate a new maze
                    pointer.reset(1, 1, cols - 2, rows - 2, maze.getGrid()); // Reset pointer
                }
                if (resetButton.isClicked(sf::Mouse::getPosition(window))) {
                    // Only reset the pointer to the start, don't regenerate the maze
                    pointer.reset(1, 1, cols - 2, rows - 2, maze.getGrid()); // Reset pointer
                }
            }
        }

        // Handle button hover effect
        regenerateButton.hoverEffect(sf::Mouse::getPosition(window));
        resetButton.hoverEffect(sf::Mouse::getPosition(window));

        // Check if enough time has passed since the last move
        if (clock.getElapsedTime().asSeconds() > movementDelay) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                pointer.moveUp();
                clock.restart(); // Reset the clock
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                pointer.moveDown();
                clock.restart(); // Reset the clock
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                pointer.moveLeft();
                clock.restart(); // Reset the clock
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                pointer.moveRight();
                clock.restart(); // Reset the clock
            }
        }

        window.clear(sf::Color::Black);

        // Draw the maze
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                if (grid[i][j] == 1) {
                    cell.setFillColor(sf::Color::Black); // Wall
                }
                else {
                    cell.setFillColor(sf::Color::White); // Path
                }

                window.draw(cell);
            }
        }

        // Draw the pointer
        sf::CircleShape pointerShape(cellSize / 2 - 2);
        pointerShape.setPosition(pointer.getX() * cellSize + 2, pointer.getY() * cellSize + 2);
        pointerShape.setFillColor(sf::Color::Blue);
        window.draw(pointerShape);

        // Draw buttons
        regenerateButton.draw(window);
        resetButton.draw(window);

        window.display();

        // Check if the pointer reached the end
        if (pointer.isAtEnd()) {
            sf::sleep(sf::seconds(1));
            window.close();
        }
    }

    return 0;
}
