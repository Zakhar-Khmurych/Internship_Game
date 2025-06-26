#pragma once
#include <vector>
#include <memory>
#include "Unit.h"
#include "Terrain.h"
#include "TerrainTypes.h"

class Cell {
public:
    std::vector<std::shared_ptr<Unit>> CellTakers;
    std::shared_ptr<ITerrain> Terrain;

    Cell(std::shared_ptr<ITerrain> terrain = std::make_shared<Plains>())
        : Terrain(terrain) {}


    bool IsEmpty() const {
        return CellTakers.empty();
    }
    void AddUnit(std::shared_ptr<Unit> unit) {
        if (unit) {
            CellTakers.push_back(unit);
        }
    }
    void RemoveUnit(std::shared_ptr<Unit> unit) {
        auto it = std::remove(CellTakers.begin(), CellTakers.end(), unit);
        if (it != CellTakers.end()) {
            CellTakers.erase(it);
        }
    }
    size_t GetUnitCount() const {
        return CellTakers.size();
    }
    void SetTerrain(std::shared_ptr<ITerrain> terrain) {
        this->Terrain = terrain;
    }

    void UseSupplies() {
        for (auto& unit : CellTakers) {
            Player* owner = unit->GetOwner();
            const ITerrain* terrain = this->Terrain.get();
            DiceRoller diceRoller;

            if (owner->money > 0) {
                const std::vector<int>& money_attrition = terrain->GetMoneyAttrition();
                int money_cost = diceRoller.RollMultiple(money_attrition[0], money_attrition[1]);
                owner->money -= money_cost;
            }
            else if (owner->supplies > 0) {
                const std::vector<int>& supply_attrition = terrain->GetMoneyAttrition();
                int supply_cost = diceRoller.RollMultiple(supply_attrition[0], supply_attrition[1]);
                owner->supplies -= supply_cost;

            }
            else {
                std::cout << owner->Name << "'s unit has run out of resources and is disbanded.\n";
                RemoveUnit(unit);
            }

        }
    }

    void HandleUnitsOnCell() {
        if (CellTakers.size() == 2) {
            auto unit1 = CellTakers[0];
            auto unit2 = CellTakers[1];

            if (unit1->GetOwner() == unit2->GetOwner()) {
                MergeUnits(unit1, unit2);
            }
            else {
                EngageTheCombat(unit1, unit2);
            }
        }
        else {
            std::cerr << "Merge or combat cannot occur: not exactly two units on the cell." << std::endl;
        }
    }

    void MergeUnits(std::shared_ptr<Unit> unit1, std::shared_ptr<Unit> unit2) {
        int mergedAdvantage = unit1->GetCurrentAdvantage() + unit2->GetCurrentAdvantage();
        std::cout << "Merging units. New advantage: " << mergedAdvantage << std::endl;
        unit1->SetCurrentAdvantage(mergedAdvantage);
        RemoveUnit(unit2);
    }

    
    void EngageTheCombat(std::shared_ptr<Unit> unit1, std::shared_ptr<Unit> unit2) {
        DiceRoller diceRoller;

        // Максимальна кількість кубиків для кожного юніта на основі їх поточної переваги
        int maxAdvantage1 = std::min(unit1->GetCurrentAdvantage(), unit1->GetOwner()->supplies); // Можна врахувати ресурси
        int maxAdvantage2 = std::min(unit2->GetCurrentAdvantage(), unit2->GetOwner()->supplies);

        // Кидаємо кубики для кожного юніта
        int roll1 = diceRoller.RollMultiple(maxAdvantage1, 6);  // Кількість кубиків та їх максимальний розмір
        int roll2 = diceRoller.RollMultiple(maxAdvantage2, 6);

        // Вивести результати кидків
        std::cout << unit1->GetOwner()->Name << " rolls: " << roll1 << " | "
            << unit2->GetOwner()->Name << " rolls: " << roll2 << std::endl;

        // Порівнюємо результати
        if (roll1 > roll2) {
            std::cout << unit1->GetOwner()->Name << " wins! " << unit2->GetOwner()->Name << " loses and is removed." << std::endl;
            RemoveUnit(unit2);  // Видаляємо програвшого
        }
        else if (roll1 < roll2) {
            std::cout << unit2->GetOwner()->Name << " wins! " << unit1->GetOwner()->Name << " loses and is removed." << std::endl;
            RemoveUnit(unit1);  // Видаляємо програвшого
        }
        else {
            std::cout << "It's a tie! Both units are removed." << std::endl;
            RemoveUnit(unit1);  // Видаляємо обох
            RemoveUnit(unit2);
        }
    }
    


};
