#pragma once
#include <algorithm>
#include "Cell.h"
#include "TextsCollection.h"
#include "Unit.h"
#include "Player.h"
#include <vector>
#include <queue>
#include <iostream>
#include <set>

class Grid
{
public:
    int Width;
    int Height;
    std::vector<std::vector<Cell>> Cells;

    Grid(int width, int height) : Width(width), Height(height) {
        Cells.resize(width, std::vector<Cell>(height));
    }

    const Cell& GetCell(int x, int y) const {
        return Cells[x][y];
    }

    bool IsValidPosition(int x, int y) const {
        return x >= 0 && x < Width&& y >= 0 && y < Height;
    }
    void MoveUnit(int startX, int startY, int destX, int destY, std::shared_ptr<Unit> unit) {
        if (!unit) {
            std::cerr << "Error: No unit provided to move." << std::endl;
            return;
        }

        // Перевірка на існування сусідніх клітинок
        if (std::abs(startX - destX) > 1 || std::abs(startY - destY) > 1) {
            std::cerr << "Error: Destination is not a neighboring cell." << std::endl;
            return;
        }

        // Перевірка на те, чи клітинка стартова дійсно містить юніта
        if (std::find(Cells[startX][startY].CellTakers.begin(), Cells[startX][startY].CellTakers.end(), unit) == Cells[startX][startY].CellTakers.end()) {
            std::cerr << "Error: Unit is not in the start cell." << std::endl;
            return;
        }

        // Перевірка на перешкоди (непрохідний терен)
        if (Cells[destX][destY].Terrain->IsImpassable()) {
            std::cerr << "Error: Destination terrain is impassable." << std::endl;
            return;
        }

        // Перевірка на зайнятість клітинки
        if (!Cells[destX][destY].IsEmpty()) {
            auto enemyUnit = Cells[destX][destY].CellTakers[0];  // Припускаємо, що на клітинці тільки один юніт
            if (enemyUnit->GetOwner() != unit->GetOwner()) {
                // Якщо юніт на цільовій клітинці належить іншому гравцеві, ініціюємо бій
                std::cout << "Combat begins between " << unit->GetOwner()->Name
                    << " and " << enemyUnit->GetOwner()->Name << "!" << std::endl;
                EngageTheCombat(unit, enemyUnit);
                return;  // Виходимо з методу, бо бій вже відбувся
            }
            else {
                std::cerr << textCollection.cell_occupied_by_friendly << std::endl;
                return;
            }
        }

        // Якщо все добре, переміщаємо юніта
        Cells[startX][startY].RemoveUnit(unit);
        Cells[destX][destY].AddUnit(unit);

        // Оновлюємо координати юніта
        unit->SetCoordinates(destX, destY);

        // Виводимо current advantage з терену цільової клітинки
        int currentAdvantage = Cells[destX][destY].Terrain->GetMaxAdvantage();  // Технічно, це може бути поточний максимум переваги для терену
        std::cout << "Unit moved to (" << destX << ", " << destY << "). "
            << "Current advantage on this terrain: " << currentAdvantage << ". Own advantage: " << unit->GetCurrentAdvantage() << std::endl;
    }

    void EngageTheCombat(std::shared_ptr<Unit> unit1, std::shared_ptr<Unit> unit2) {
        DiceRoller diceRoller;

        // Отримуємо координати обох юнітів
        int x1 = unit1->GetCurrentX();
        int y1 = unit1->GetCurrentY();
        int x2 = unit2->GetCurrentX();
        int y2 = unit2->GetCurrentY();

        // Отримуємо терени клітинок, де знаходяться юніти
        auto terrain1 = Cells[x1][y1].Terrain;
        auto terrain2 = Cells[x2][y2].Terrain;

        // Максимальна кількість кубиків для кожного юніта на основі терену
        int maxAdvantage1 = std::min(terrain1->GetMaxAdvantage(), terrain1->GetMaxAdvantage()); // Використовуємо перевагу терену
        int maxAdvantage2 = std::min(terrain2->GetMaxAdvantage(), terrain2->GetMaxAdvantage());

        // Кидаємо кубики для кожного юні+а
        int roll1 = diceRoller.RollMultiple(maxAdvantage1, 6);  // Кількість кубиків та їх максимальний розмір
        int roll2 = diceRoller.RollMultiple(maxAdvantage2, 6);

        // Вивести результати кидків
        std::cout << unit1->GetOwner()->Name << " rolls: " << roll1 << " | "
            << unit2->GetOwner()->Name << " rolls: " << roll2 << std::endl;

        // Порівнюємо результати
        if (roll1 > roll2) {
            std::cout << unit1->GetOwner()->Name << " wins! " << unit2->GetOwner()->Name << " loses and is removed." << std::endl;
            Cells[x2][y2].RemoveUnit(unit2);  // Видаляємо програвшого
        }
        else if (roll1 < roll2) {
            std::cout << unit2->GetOwner()->Name << " wins! " << unit1->GetOwner()->Name << " loses and is removed." << std::endl;
            Cells[x1][y1].RemoveUnit(unit1);  // Видаляємо програвшого
        }
        else {
            std::cout << "It's a tie! Both units are removed." << std::endl;
            Cells[x1][y1].RemoveUnit(unit1);  // Видаляємо обох
            Cells[x2][y2].RemoveUnit(unit2);
        }
    }

    
    std::vector<std::shared_ptr<Unit>> GetUnitsAt(int x, int y) {
        if (IsValidPosition(x, y)) {
            return Cells[x][y].CellTakers;
        }
        return {};  // Повертаємо порожній вектор, якщо клітинка недійсна
    }

    std::set<Player*> cachedPlayers;
    void UpdateCachedPlayers() {
        cachedPlayers.clear();
        for (int x = 0; x < Width; ++x) {
            for (int y = 0; y < Height; ++y) {
                const auto& cell = Cells[x][y];
                for (const auto& unit : cell.CellTakers) {
                    cachedPlayers.insert(unit->GetOwner());
                }
            }
        }
    }
    const std::set<Player*>& GetCachedPlayers() const {
        return cachedPlayers;
    }




    private:
        TextsCollection textCollection;

};



