#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "../Assets/Terrain.h"


class TextureManager {
private:
    static sf::Texture invalid;
    std::unordered_map<std::string, sf::Texture> textures;

public:
    bool loadTexture(const std::string& name, const std::string& filePath) {
        sf::Texture texture;
        if (!texture.loadFromFile(filePath)) {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            return false;
        }
        //std::cout << "Loaded texture: " << filePath << std::endl;
        textures[name] = std::move(texture);
        return true;
    }

    sf::Texture& getTexture(const std::string& name) {
        auto it = textures.find(name);
        if (it != textures.end()) {
            return it->second;
        }
        else {
            std::cerr << "Texture not found: " << name << std::endl;
            return invalid;// for error texture
        }
    }

    sf::Texture& getTextureForTerrain(const std::shared_ptr<ITerrain>& terrain) {
        return getTexture(terrain->GetTextureName());
    }

    void initializeInvalidTexture() {
        if (!invalid.loadFromFile("assets/invalid.png")) {
            std::cerr << "Failed to load invalid texture!" << std::endl;
            invalid.create(100, 100);
            sf::Image image;
            image.create(100, 100, sf::Color::Magenta);
            invalid.update(image);
        }
    }

    void initializeAll() {
        std::vector<std::pair<std::string, std::string>> texturePaths = {
            {"plains", "textures/plains.png"},
            {"forest", "textures/forest.png"},
            {"chasm", "textures/chasm.png"},
            {"farmland", "textures/farmland.png"},
            {"creek", "textures/creek.png"},
            {"bridge", "textures/bridge.png"},
            {"settlement", "textures/settlement.png"},
            {"hills", "textures/hills.png"},
            {"swamp", "textures/swamp.png"},
            {"valley", "textures/valley.png"},
            {"desert", "textures/desert.png"},
            {"mountain", "textures/mountain.png"},
            {"impassable", "textures/impassable.png"},
            {"unit", "textures/unit.png"}
        };

        for (const auto& [name, path] : texturePaths) {
            loadTexture(name, path);
        }
    }
};

