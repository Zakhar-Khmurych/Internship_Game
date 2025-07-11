#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TextManager.h"
#include "../Assets/Grid.h"
#include <functional>
#include "InputKey.h"
#include "../Assets/Grid.h"


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

    void RenderGame(std::atomic<bool>& isRunning, std::function<Grid* ()> getGrid, InputQueue& inputQueue) {
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
                    isRunning = false;
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                    case sf::Keyboard::W: inputQueue.Push(InputKey::Up); break;
                    case sf::Keyboard::S: inputQueue.Push(InputKey::Down); break;
                    case sf::Keyboard::A: inputQueue.Push(InputKey::Left); break;
                    case sf::Keyboard::D: inputQueue.Push(InputKey::Right); break;
                    case sf::Keyboard::Q: inputQueue.Push(InputKey::EndTurn); break;
                    default: break;
                    }
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
    void _RenderTheField(sf::RenderWindow& window, const Grid& grid) {
        const float cellGap = 10.0f;
        float cellSize = static_cast<float>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;

        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                const Cell& cell = grid.GetCell(x, y);
                auto terrain = cell.Terrain;
                sf::Texture& terrainTexture = textureManager.getTextureForTerrain(terrain);

                float currentCellSize = cellSize;
                sf::Vector2f cellPosition(
                    x * (cellSize + cellGap) + cellGap,
                    y * (cellSize + cellGap) + cellGap
                );

                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();
                    if (unit->GetOwner()->IsYourTurn) {
                        currentCellSize *= 1.1f; // ЦЮ МИ ПІДСВІЧУЄМО!!!
                        float offset = (currentCellSize - cellSize) / 2.0f;
                        cellPosition.x -= offset;
                        cellPosition.y -= offset;
                    }
                }

                sf::RectangleShape cellShape(sf::Vector2f(currentCellSize, currentCellSize));
                cellShape.setTexture(&terrainTexture);
                cellShape.setPosition(cellPosition);
                window.draw(cellShape);


                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();

                    sf::CircleShape unitShape(cellSize * 0.4f); // коло меншого розміру
                    unitShape.setOrigin(unitShape.getRadius(), unitShape.getRadius());
                    unitShape.setPosition(x * (cellSize + cellGap) + cellGap + cellSize / 2,
                        y * (cellSize + cellGap) + cellGap + cellSize / 2);

                    // Текстура юніта
                    sf::Texture& unitTexture = textureManager.getTexture("unit");
                    unitShape.setTexture(&unitTexture);

                    window.draw(unitShape);
                }
            }
        }
    }

    void RenderTheField(sf::RenderWindow& window, const Grid& grid) {
        const float cellGap = 10.0f;
        float cellSize = static_cast<float>(std::min(window.getSize().x / grid.Width, window.getSize().y / grid.Height)) - cellGap;

        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                const Cell& cell = grid.GetCell(x, y);
                auto terrain = cell.Terrain;
                sf::Texture& terrainTexture = textureManager.getTextureForTerrain(terrain);

                float currentCellSize = cellSize;
                sf::Vector2f cellPosition(
                    x * (cellSize + cellGap) + cellGap,
                    y * (cellSize + cellGap) + cellGap
                );

                bool drawHighlight = false;

                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();
                    if (unit->GetOwner()->IsYourTurn) {
                        drawHighlight = true;

                        // Збільшуємо саму клітинку
                        currentCellSize *= 1.1f;
                        float offset = (currentCellSize - cellSize) / 2.0f;
                        cellPosition.x -= offset;
                        cellPosition.y -= offset;
                    }
                }

                if (drawHighlight) {
                    float highlightSize = currentCellSize + 8.0f;
                    float offset = (highlightSize - currentCellSize) / 2.0f;
                    sf::RectangleShape highlight(sf::Vector2f(highlightSize, highlightSize));
                    highlight.setFillColor(sf::Color::White);
                    highlight.setPosition(cellPosition.x - offset, cellPosition.y - offset);
                    window.draw(highlight);
                }

                sf::RectangleShape cellShape(sf::Vector2f(currentCellSize, currentCellSize));
                cellShape.setTexture(&terrainTexture);
                cellShape.setPosition(cellPosition);
                window.draw(cellShape);

                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();

                    sf::CircleShape unitShape(cellSize * 0.4f);
                    unitShape.setOrigin(unitShape.getRadius(), unitShape.getRadius());
                    unitShape.setPosition(
                        x * (cellSize + cellGap) + cellGap + cellSize / 2,
                        y * (cellSize + cellGap) + cellGap + cellSize / 2
                    );

                    sf::Texture& unitTexture = textureManager.getTexture("unit");
                    unitShape.setTexture(&unitTexture);
                    window.draw(unitShape);
                }
            }
        }
    }

};
