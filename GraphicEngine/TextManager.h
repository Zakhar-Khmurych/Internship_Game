#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

struct TextItem {
    sf::Text text;
    sf::Vector2f position;

    TextItem(const std::string& str, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& pos)
        : position(pos) {
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(charSize);
        text.setFillColor(color);
        text.setPosition(position);
    }
};

class TextManager {
    sf::Font font;
    std::vector<TextItem> texts;

public:
    TextManager(const std::string& fontPath) {
        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Error loading font!" << std::endl;
        }
    }

    void AddText(const std::string& str, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position) {
        texts.push_back(TextItem(str, font, charSize, color, position));
    }

    void UpdateText(unsigned int index, const std::string& newStr) {
        if (index < texts.size()) {
            texts[index].text.setString(newStr);
        }
    }

    void DrawTexts(sf::RenderWindow& window) {
        for (auto& textItem : texts) {
            window.draw(textItem.text);
        }
    }
};
