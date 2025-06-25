#pragma once
#include <random>
#include "Grid.h"  // Припускаємо, що Grid вже підключено

class GridGenerator {
public:
    static void GenerateTerrain(Grid& grid) {
        // Список типів теренів, з яких будемо вибирати
        std::vector<std::shared_ptr<ITerrain>> terrainTypes = {
            std::make_shared<Plains>(),
            std::make_shared<Farmland>(),
            std::make_shared<Settlement>(),
            std::make_shared<Valley>(),
            std::make_shared<Hills>(),
            std::make_shared<Desert>(),
            std::make_shared<Creek>(),
            std::make_shared<Forest>(),
            std::make_shared<Swamp>(),
            std::make_shared<Bridge>(),
            std::make_shared<Chasm>(),
            std::make_shared<Mountain>(),
            std::make_shared<Impassable>()
        };

        // Генератор випадкових чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, terrainTypes.size() - 1);

        // Заповнення сітки випадковими теренами
        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                // Вибір випадкового терену
                auto randomTerrain = terrainTypes[dis(gen)];

                // Призначення терену клітинці
                grid.Cells[x][y].SetTerrain(randomTerrain);
            }
        }

        std::cout << "Terrain generation complete." << std::endl;
    }
};
