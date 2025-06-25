#pragma once
#include "../Assets/Grid.h"
#include <iostream>
#include <cctype>

class ConsoleGameStateDrawer
{
public:
    ConsoleGameStateDrawer() = default;
    ~ConsoleGameStateDrawer() = default;

    void Draw(const Grid& grid) {
        for (int y = 0; y < grid.Height; ++y) {
            for (int x = 0; x < grid.Width; ++x) {
                const Cell& cell = grid.GetCell(x, y);

                std::cout << " "; 

                if (cell.IsEmpty()) {
                    std::cout << ".";
                }
                else {
                    std::shared_ptr<Unit> unit = cell.CellTakers.front();
                    Player* owner = unit->GetOwner();
                    if (owner && !owner->Name.empty()) {
                        char symbol = std::tolower(owner->Name[0]);
                        std::cout << symbol;
                    }
                    else {
                        std::cout << "?";
                    }
                }
            }
            std::cout << "\n";
        }
    }
};
