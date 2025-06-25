#pragma once
#include "Terrain.h"
#include <iostream>
#include <vector>

class Plains : public ITerrain {
public:
    Plains() {
        supply_attrition = { 2, 4 };
        money_attrition = { 1, 8 };
        max_advantage = 10;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "plains";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Plains Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Farmland : public ITerrain {
public:
    Farmland() {
        supply_attrition = { 1, 4 };
        money_attrition = { 1, 8 };
        max_advantage = 10;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "farmland";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Farmland Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};


class Settlement : public ITerrain {
public:
    Settlement() {
        supply_attrition = { 1, 4 };
        money_attrition = { 2, 12 };
        max_advantage = 8;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "settlement";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Settlement Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Valley : public ITerrain {
public:
    Valley() {
        supply_attrition = { 1, 6 };
        money_attrition = { 1, 8 };
        max_advantage = 8;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "valley";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Valley Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Hills : public ITerrain {
public:
    Hills() {
        supply_attrition = { 1, 8 };
        money_attrition = { 1, 8 };
        max_advantage = 7;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "hills";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Hills Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};


class Desert : public ITerrain {
public:
    Desert() {
        supply_attrition = { 4, 6 };
        money_attrition = { 2, 6 };
        max_advantage = 6;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "desert";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Desert Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Creek : public ITerrain {
public:
    Creek() {
        supply_attrition = { 1, 8 };
        money_attrition = { 2, 4 };
        max_advantage = 5;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "creek";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Creek Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Forest : public ITerrain {
public:
    Forest() {
        supply_attrition = { 1, 12 };
        money_attrition = { 1, 8 };
        max_advantage = 5;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "forest";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Forest Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Swamp : public ITerrain {
public:
    Swamp() {
        supply_attrition = { 2, 8 };
        money_attrition = { 2, 6 };
        max_advantage = 4;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "swamp";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Swamp Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Bridge : public ITerrain {
public:
    Bridge() {
        supply_attrition = { 2, 6 };
        money_attrition = { 1, 8 };
        max_advantage = 3;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "bridge";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Bridge Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Mountain : public ITerrain {
public:
    Mountain() {
        supply_attrition = { 3, 4 };
        money_attrition = { 2, 8 };
        max_advantage = 4;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "mountain";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Mountain Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Chasm : public ITerrain {
public:
    Chasm() {
        supply_attrition = { 2, 6 };
        money_attrition = { 1, 12 };
        max_advantage = 2;
        impassable = false;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "chasm";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Chasm Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};

class Impassable : public ITerrain {
public:
    Impassable() {
        supply_attrition = { 1, 1 };
        money_attrition = { 1, 1 };
        max_advantage = 0;
        impassable = true;
    }

    const std::string& GetTextureName() const override {
        static const std::string texture = "impassable";
        return texture;
    }
    const std::vector<int>& GetSupplyAttrition() const override {
        return supply_attrition;
    }
    const std::vector<int>& GetMoneyAttrition() const override {
        return money_attrition;
    }
    int GetMaxAdvantage() const override {
        return max_advantage;
    }
    bool IsImpassable() const override {
        return impassable;
    }

    void PrintInfo() const override {
        std::cout << "Impassable Terrain\n"
            << "Texture: " << GetTextureName() << "\n"
            << "Supply Attrition: ";
        for (int value : supply_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        std::cout << "Money Attrition: ";
        for (int value : money_attrition) {
            std::cout << value << " ";
        }
        std::cout << "\n";
        std::cout << "Max Advantage: " << GetMaxAdvantage() << "\n";
    }

private:
    std::vector<int> supply_attrition;  // Вектор для supply_attrition
    std::vector<int> money_attrition;   // Вектор для money_attrition
    int max_advantage;                  // Фіксоване значення для max_advantage
    bool impassable;                  // Фіксоване значення для max_advantage
};













