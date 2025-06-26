#pragma once
#include <algorithm>
#include "Cell.h"
#include "Unit.h"
#include <vector>
#include <queue>
#include <iostream>

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
    /*
    void MoveUnit(int startX, int startY, int destX, int destY, std::shared_ptr<Unit> unit) {
        if (!unit) {
            std::cerr << "Error: No unit provided to move." << std::endl;
            return;
        }
        // ѕерев≥рка на ≥снуванн€ сус≥дн≥х кл≥тинок
        if (std::abs(startX - destX) > 1 || std::abs(startY - destY) > 1) {
            std::cerr << "Error: Destination is not a neighboring cell." << std::endl;
            return;
        }
        // ѕерев≥рка на те, чи кл≥тинка стартова д≥йсно м≥стить юн≥та
        if (std::find(Cells[startX][startY].CellTakers.begin(), Cells[startX][startY].CellTakers.end(), unit) == Cells[startX][startY].CellTakers.end()) {
            std::cerr << "Error: Unit is not in the start cell." << std::endl;
            return;
        }
        // ѕерев≥рка на перешкоди (непрох≥дний терен)
        if (Cells[destX][destY].Terrain->IsImpassable()) {
            std::cerr << "Error: Destination terrain is impassable." << std::endl;
            return;
        }
        // ѕерев≥рка на зайн€т≥сть кл≥тинки
        if (!Cells[destX][destY].IsEmpty()) {
            std::cerr << "Error: Destination cell is not empty." << std::endl;
            return;
        }

        // якщо все добре, перем≥щаЇмо юн≥та
        Cells[startX][startY].RemoveUnit(unit);
        Cells[destX][destY].AddUnit(unit);

        // ќновлюЇмо координати юн≥та
        unit->SetCoordinates(destX, destY);

        std::cout << "Unit moved to (" << destX << ", " << destY << ")." << std::endl;
    }
    */
    void MoveUnit(int startX, int startY, int destX, int destY, std::shared_ptr<Unit> unit) {
        if (!unit) {
            std::cerr << "Error: No unit provided to move." << std::endl;
            return;
        }

        // ѕерев≥рка на ≥снуванн€ сус≥дн≥х кл≥тинок
        if (std::abs(startX - destX) > 1 || std::abs(startY - destY) > 1) {
            std::cerr << "Error: Destination is not a neighboring cell." << std::endl;
            return;
        }

        // ѕерев≥рка на те, чи кл≥тинка стартова д≥йсно м≥стить юн≥та
        if (std::find(Cells[startX][startY].CellTakers.begin(), Cells[startX][startY].CellTakers.end(), unit) == Cells[startX][startY].CellTakers.end()) {
            std::cerr << "Error: Unit is not in the start cell." << std::endl;
            return;
        }

        // ѕерев≥рка на перешкоди (непрох≥дний терен)
        if (Cells[destX][destY].Terrain->IsImpassable()) {
            std::cerr << "Error: Destination terrain is impassable." << std::endl;
            return;
        }

        // ѕерев≥рка на зайн€т≥сть кл≥тинки
        if (!Cells[destX][destY].IsEmpty()) {
            auto enemyUnit = Cells[destX][destY].CellTakers[0];  // ѕрипускаЇмо, що на кл≥тинц≥ т≥льки один юн≥т
            if (enemyUnit->GetOwner() != unit->GetOwner()) {
                // якщо юн≥т на ц≥льов≥й кл≥тинц≥ належить ≥ншому гравцев≥, ≥н≥ц≥юЇмо б≥й
                std::cout << "Combat begins between " << unit->GetOwner()->Name
                    << " and " << enemyUnit->GetOwner()->Name << "!" << std::endl;
                EngageTheCombat(unit, enemyUnit);
                return;  // ¬иходимо з методу, бо б≥й вже в≥дбувс€
            }
            else {
                std::cerr << "Error: Destination cell is occupied by your own unit." << std::endl;
                return;
            }
        }

        // якщо все добре, перем≥щаЇмо юн≥та
        Cells[startX][startY].RemoveUnit(unit);
        Cells[destX][destY].AddUnit(unit);

        // ќновлюЇмо координати юн≥та
        unit->SetCoordinates(destX, destY);

        std::cout << "Unit moved to (" << destX << ", " << destY << ")." << std::endl;
    }

    void EngageTheCombat(std::shared_ptr<Unit> unit1, std::shared_ptr<Unit> unit2) {
        DiceRoller diceRoller;
        int maxAdvantage1 = std::min(unit1->GetCurrentAdvantage(), unit1->GetOwner()->supplies);
        int maxAdvantage2 = std::min(unit2->GetCurrentAdvantage(), unit2->GetOwner()->supplies);

        int roll1 = diceRoller.RollMultiple(maxAdvantage1, 6);
        int roll2 = diceRoller.RollMultiple(maxAdvantage2, 6);

        std::cout << unit1->GetOwner()->Name << " rolls: " << roll1 << " | "
            << unit2->GetOwner()->Name << " rolls: " << roll2 << std::endl;

        if (roll1 > roll2) {
            std::cout << unit1->GetOwner()->Name << " wins! " << unit2->GetOwner()->Name << " loses and is removed." << std::endl;
            Cells[unit2->GetCurrentX()][unit2->GetCurrentY()].RemoveUnit(unit2);
        }
        else if (roll1 < roll2) {
            std::cout << unit2->GetOwner()->Name << " wins! " << unit1->GetOwner()->Name << " loses and is removed." << std::endl;
            Cells[unit1->GetCurrentX()][unit1->GetCurrentY()].RemoveUnit(unit1);
        }
        else {
            std::cout << "It's a tie! Both units are removed." << std::endl;
            Cells[unit1->GetCurrentX()][unit1->GetCurrentY()].RemoveUnit(unit1);
            Cells[unit2->GetCurrentX()][unit2->GetCurrentY()].RemoveUnit(unit2);
        }
    }

};

