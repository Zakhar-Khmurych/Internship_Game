#pragma once
#include <random>
#include "Grid.h"  // ����������, �� Grid ��� ���������

class GridGenerator {
public:
    static void GenerateTerrain(Grid& grid) {
        // ������ ���� ������, � ���� ������ ��������
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

        // ��������� ���������� �����
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, terrainTypes.size() - 1);

        // ���������� ���� ����������� ��������
        for (int x = 0; x < grid.Width; ++x) {
            for (int y = 0; y < grid.Height; ++y) {
                // ���� ����������� ������
                auto randomTerrain = terrainTypes[dis(gen)];

                // ����������� ������ �������
                grid.Cells[x][y].SetTerrain(randomTerrain);
            }
        }

        std::cout << "Terrain generation complete." << std::endl;
    }
};
