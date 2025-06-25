#pragma once
#include <iostream>
#include <string>
#include "Command.h"
#include "Player.h"
#include "Grid.h"
#include <memory>

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};



class MoveCommand : public Command {
private:
    Grid& grid;
    std::shared_ptr<Unit> unit;
    int destX, destY;

public:
    MoveCommand(Grid& grid, std::shared_ptr<Unit> unit, int x, int y)
        : grid(grid), unit(unit), destX(x), destY(y) {}

    void execute() override {
        int startX = unit->GetCurrentX();
        int startY = unit->GetCurrentY();

        if (grid.IsValidPosition(destX, destY) &&
            std::abs(destX - startX) + std::abs(destY - startY) == 1) // тільки вертикальні/горизонтальні рухи
        {
            grid.MoveUnit(startX, startY, destX, destY, unit);
        }
        else {
            std::cout << "Invalid move.\n";
        }
    }
};



class SkipTurnCommand : public Command {
private:
    std::string playerName;
public:
    SkipTurnCommand(const std::string& playerName) : playerName(playerName) {}

    void execute() override {
        std::cout << playerName << " skipped their turn.\n";
    }
};