#pragma once
#include <string>
#include <vector>

class ITerrain {
public:
    virtual ~ITerrain() = default;

    virtual const std::string& GetTextureName() const = 0;
    virtual const std::vector<int>& GetSupplyAttrition() const = 0;
    virtual const std::vector<int>& GetMoneyAttrition() const = 0;
    virtual int GetMaxAdvantage() const = 0;
    virtual bool IsImpassable() const = 0;


    virtual void PrintInfo() const = 0;
};
