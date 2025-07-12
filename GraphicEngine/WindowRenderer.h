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
                RenderPlayerResources(window, *currentGrid);
            }

           /*
            const auto& players = currentGrid->GetCachedPlayers();
            std::cout << "Players on the grid:\n";
            for (const auto* player : players) {
                if (player) {
                    std::cout << " - " << player->Name << " | Supplies: " << player->supplies << ", Money: " << player->money << "\n";
                }
            }
            */

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

                bool drawHighlight = false;

                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();
                    if (unit->GetOwner()->IsYourTurn) {
                        drawHighlight = true;

                        // «б≥льшуЇмо саму кл≥тинку
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

                // === ён≥т ===
                if (!cell.CellTakers.empty()) {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();

                    // ¬изначаЇмо рад≥ус юн≥та на основ≥ його переваги
                    float baseRadius = 5.0f;
                    float radiusStep = 5.0f;
                    int advantage = unit->GetCurrentAdvantage();

                    float maxRadius = cellSize / 2.5f;  // ќбмежуЇмо, щоби не вилазив з кл≥тинки
                    float unitRadius = std::clamp(baseRadius + advantage * radiusStep, 2.0f, maxRadius);

                    sf::CircleShape unitShape(unitRadius);
                    unitShape.setOrigin(unitRadius, unitRadius);
                    unitShape.setPosition(
                        x * (cellSize + cellGap) + cellGap + cellSize / 2,
                        y * (cellSize + cellGap) + cellGap + cellSize / 2
                    );

                    sf::Texture& unitTexture = textureManager.getTexture("unit");
                    unitShape.setTexture(&unitTexture);
                    window.draw(unitShape);

                    // ƒл€ дебагу (опц≥онально)
                    // std::cout << "Unit at (" << x << ", " << y << ") has advantage " << advantage << " => radius: " << unitRadius << "\n";
                }
            }
        }
    }


    void RenderPlayerResources(sf::RenderWindow& window, const Grid& grid) {
        const auto& players = grid.GetCachedPlayers();

        int index = 0;
        for (const Player* player : players) {
            if (!player) continue;

            float baseY = 50.0f + index * 600.0f;
            float rightMargin = 50.0f;
            float iconSize = 100.0f;

            // === SUPPLIES ===
            int maxSupplies = 100;
            float suppliesOpacity = std::clamp(static_cast<float>(player->supplies) / maxSupplies, 0.0f, 1.0f);
            sf::Uint8 suppliesAlpha = static_cast<sf::Uint8>(suppliesOpacity * 255);

            sf::RectangleShape suppliesBox(sf::Vector2f(iconSize, iconSize));
            suppliesBox.setPosition(window.getSize().x - rightMargin - iconSize, baseY);
            suppliesBox.setTexture(&textureManager.getTexture("supplies"));

            sf::Color suppliesColor = sf::Color::White;
            suppliesColor.a = suppliesAlpha;
            suppliesBox.setFillColor(suppliesColor);

            window.draw(suppliesBox);

            // === MONEY ===
            int maxMoney = 100;
            float moneyOpacity = std::clamp(static_cast<float>(player->money) / maxMoney, 0.0f, 1.0f);
            sf::Uint8 moneyAlpha = static_cast<sf::Uint8>(moneyOpacity * 255);

            sf::RectangleShape moneyBox(sf::Vector2f(iconSize, iconSize));
            moneyBox.setPosition(window.getSize().x - rightMargin - iconSize * 2 - 10.0f, baseY);
            moneyBox.setTexture(&textureManager.getTexture("money"));

            sf::Color moneyColor = sf::Color::White;
            moneyColor.a = moneyAlpha;
            moneyBox.setFillColor(moneyColor);

            window.draw(moneyBox);

            ++index;
        }
    }





};
