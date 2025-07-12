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

        // �������� �� ��������� ������ �������
        if (std::abs(startX - destX) > 1 || std::abs(startY - destY) > 1) {
            std::cerr << "Error: Destination is not a neighboring cell." << std::endl;
            return;
        }

        // �������� �� ��, �� ������� �������� ����� ������ ����
        if (std::find(Cells[startX][startY].CellTakers.begin(), Cells[startX][startY].CellTakers.end(), unit) == Cells[startX][startY].CellTakers.end()) {
            std::cerr << "Error: Unit is not in the start cell." << std::endl;
            return;
        }

        // �������� �� ��������� (����������� �����)
        if (Cells[destX][destY].Terrain->IsImpassable()) {
            std::cerr << "Error: Destination terrain is impassable." << std::endl;
            return;
        }

        // �������� �� ��������� �������
        if (!Cells[destX][destY].IsEmpty()) {
            auto enemyUnit = Cells[destX][destY].CellTakers[0];  // ����������, �� �� ������� ����� ���� ���
            if (enemyUnit->GetOwner() != unit->GetOwner()) {
                // ���� ��� �� ������� ������� �������� ������ �������, �������� ��
                std::cout << "Combat begins between " << unit->GetOwner()->Name
                    << " and " << enemyUnit->GetOwner()->Name << "!" << std::endl;
                EngageTheCombat(unit, enemyUnit);
                return;  // �������� � ������, �� �� ��� �������
            }
            else {
                std::cerr << textCollection.cell_occupied_by_friendly << std::endl;
                return;
            }
        }

        // ���� ��� �����, ��������� ����
        Cells[startX][startY].RemoveUnit(unit);
        Cells[destX][destY].AddUnit(unit);

        // ��������� ���������� ����
        unit->SetCoordinates(destX, destY);

        // �������� current advantage � ������ ������� �������
        int currentAdvantage = Cells[destX][destY].Terrain->GetMaxAdvantage();  // �������, �� ���� ���� �������� �������� �������� ��� ������
        std::cout << "Unit moved to (" << destX << ", " << destY << "). "
            << "Current advantage on this terrain: " << currentAdvantage << ". Own advantage: " << unit->GetCurrentAdvantage() << std::endl;
    }

    void EngageTheCombat(std::shared_ptr<Unit> unit1, std::shared_ptr<Unit> unit2) {
        DiceRoller diceRoller;

        // �������� ���������� ���� ����
        int x1 = unit1->GetCurrentX();
        int y1 = unit1->GetCurrentY();
        int x2 = unit2->GetCurrentX();
        int y2 = unit2->GetCurrentY();

        // �������� ������ �������, �� ����������� ����
        auto terrain1 = Cells[x1][y1].Terrain;
        auto terrain2 = Cells[x2][y2].Terrain;

        // ����������� ������� ������ ��� ������� ���� �� ����� ������
        int maxAdvantage1 = std::min(terrain1->GetMaxAdvantage(), terrain1->GetMaxAdvantage()); // ������������� �������� ������
        int maxAdvantage2 = std::min(terrain2->GetMaxAdvantage(), terrain2->GetMaxAdvantage());

        // ������ ������ ��� ������� ��+�
        int roll1 = diceRoller.RollMultiple(maxAdvantage1, 6);  // ʳ������ ������ �� �� ������������ �����
        int roll2 = diceRoller.RollMultiple(maxAdvantage2, 6);

        // ������� ���������� �����
        std::cout << unit1->GetOwner()->Name << " rolls: " << roll1 << " | "
            << unit2->GetOwner()->Name << " rolls: " << roll2 << std::endl;

        // ��������� ����������
        if (roll1 > roll2) {
            std::cout << unit1->GetOwner()->Name << " wins! " << unit2->GetOwner()->Name << " loses and is removed." << std::endl;
            Cells[x2][y2].RemoveUnit(unit2);  // ��������� �����������
        }
        else if (roll1 < roll2) {
            std::cout << unit2->GetOwner()->Name << " wins! " << unit1->GetOwner()->Name << " loses and is removed." << std::endl;
            Cells[x1][y1].RemoveUnit(unit1);  // ��������� �����������
        }
        else {
            std::cout << "It's a tie! Both units are removed." << std::endl;
            Cells[x1][y1].RemoveUnit(unit1);  // ��������� ����
            Cells[x2][y2].RemoveUnit(unit2);
        }
    }

    
    std::vector<std::shared_ptr<Unit>> GetUnitsAt(int x, int y) {
        if (IsValidPosition(x, y)) {
            return Cells[x][y].CellTakers;
        }
        return {};  // ��������� ������� ������, ���� ������� �������
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



