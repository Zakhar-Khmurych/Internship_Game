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
            std::cerr << "Error: Destination cell is not empty." << std::endl;
            return;
        }

        // ���� ��� �����, ��������� ����
        Cells[startX][startY].RemoveUnit(unit);
        Cells[destX][destY].AddUnit(unit);

        // ��������� ���������� ����
        unit->SetCoordinates(destX, destY);

        std::cout << "Unit moved to (" << destX << ", " << destY << ")." << std::endl;
    }
};

