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
        int maxAdvantage = std::min(unit1->GetCurrentAdvantage(), unit2->GetCurrentAdvantage());

        int roll1 = diceRoller.RollMultiple(maxAdvantage, 6);
        int roll2 = diceRoller.RollMultiple(maxAdvantage, 6);

        std::cout << unit1->GetOwner()->Name << " 1 rolls: " << roll1 << " " << unit2->GetOwner()->Name << ",  2 rolls: " << roll2 << std::endl;

        if (roll1 > roll2) {
            std::cout << unit1->GetOwner()->Name << " won, " << unit2->GetOwner()->Name << " lost, removing from the battlefield." << std::endl;
            RemoveUnit(unit2);
        }
        else if (roll1 < roll2) {
            std::cout << unit2->GetOwner()->Name << " won, " << unit1->GetOwner()->Name << " lost, removing from the battlefield." << std::endl;
            RemoveUnit(unit1);
        }
        else {
            std::cout << "It's a Pyrrhic victory! Both lost." << std::endl;
            RemoveUnit(unit1);
            RemoveUnit(unit2);
        }
    }


};
