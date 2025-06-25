#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "DiceRoller.h"
//#include "Cell.h"

class Grid;

class Player {
public:
    std::string Name;
    int supplies;
    int money;

    Player(const std::string& name) : Name(name) {
        supplies = 50;
        money = 50;
    }

};
