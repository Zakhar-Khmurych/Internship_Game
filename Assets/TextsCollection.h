#pragma once
#include <string>

class TextsCollection {
public:
    std::string hi_asset = "hi";
    std::string cell_occupied_by_friendly = "You shall not pass! Destination cell is occupied by another your unit";
    std::string cell_impssable = "One does not simply walk on impassable cell";
    std::string wins = "Wins the battle ";
    std::string loses = " suffers a defeat ";
    std::string indecisive = " inconclusive ";
    

    TextsCollection() = default;

    std::string GetCurrentText() {
        return current_text;
    }    
    std::string RewriteCurrentText(std::string text) {
        current_text = text;
    }

private:
    std::string current_text = "";
};
