#pragma once
#include "Player.h"

class Unit {
public:

    Unit(int currentAdvantage, Player* owner)
        : current_advantage(currentAdvantage), owner(owner) {}


    int GetCurrentAdvantage() const {
        return current_advantage;
    }

    void SetCurrentAdvantage(int advantage) {
        current_advantage = advantage;
    }

    void ChangeCurrentAdvantage(int advantage) {
        current_advantage += advantage;
    }

    Player* GetOwner() const {
        return owner;
    }

    void SetOwner(Player* newOwner) {
        owner = newOwner;
    }

    int GetCurrentX() const {
        return currentX;
    }

    int GetCurrentY() const {
        return currentY;
    }

    void SetCoordinates(int x, int y) {
        currentX = x;
        currentY = y;
    }

private:
    int current_advantage;  // Поточна перевага юніта
    Player* owner;         // Власник юніта (вказівник на об'єкт класу Playe
    int currentX;
    int currentY;
};