#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TextManager.h"
#include "../Assets/Grid.h"
#include <functional>


class WindowRenderer {
    int window_width;
    int window_height;
    TextureManager textureManager;
    TextManager textManager;

public:
    WindowRenderer(int width, int height)
        : window_width(width), window_height(height),
        textManager("C:/Windows/Fonts/arial.ttf") {}

    void RenderGame(std::atomic<bool>& isRunning, std::function<Grid* ()> getGrid) {
        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Internship game");
        sf::Clock clock;

        textureManager.initializeInvalidTexture();
        textureManager.initializeAll();

        textManager.AddText("Hello, SFML!", 24, sf::Color::White, sf::Vector2f(900, 100));
        textManager.AddText("Looking for actions...", 24, sf::Color::White, sf::Vector2f(900, 150));

        while (window.isOpen() && isRunning) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    isRunning = false;
                }
            }

            sf::Time elapsed = clock.restart();
            window.clear();

            Grid* currentGrid = getGrid();
            if (currentGrid) {
                RenderTheField(window, *currentGrid);
            }

            textManager.DrawTexts(window);
            window.display();
        }
    }

private:
    void RenderTheField(sf::RenderWindow& window, const Grid& grid) {
        const float cellGap = 5.0f;
        float cellSize = static_cast<float>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;

        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
                auto terrain = grid.GetCell(x, y).Terrain;
                sf::Texture& terrainTexture = textureManager.getTextureForTerrain(terrain);

                cellShape.setTexture(&terrainTexture);
                cellShape.setPosition(x * (cellSize + cellGap), y * (cellSize + cellGap));
                window.draw(cellShape);

                const Cell& cell = grid.GetCell(x, y);
                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();

                    sf::CircleShape unitShape(cellSize * 0.4f); // коло меншого розміру
                    unitShape.setOrigin(unitShape.getRadius(), unitShape.getRadius());
                    unitShape.setPosition(x * (cellSize + cellGap) + cellSize / 2,
                        y * (cellSize + cellGap) + cellSize / 2);

                    // Текстура юніта
                    sf::Texture& unitTexture = textureManager.getTexture("unit");
                    unitShape.setTexture(&unitTexture);

                    window.draw(unitShape);
                }
            }
        }
    }

};
