
#pragma once
#include <ctime>
#include <cstdlib>

class DiceRoller {
public:
    DiceRoller() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    static int RollSingle(int size) {
        return (std::rand() % size) + 1;
    }

    static int RollMultiple(int numDice, int size) {
        int total = 0;
        for (int i = 0; i < numDice; ++i) {
            total += RollSingle(size);
        }
        return total;
    }
};
