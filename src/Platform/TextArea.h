#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TextArea {
public:
	std::wstring s;
	sf::Vector2f position;
	float characterSize = 16;
	float line_length;
	std::vector < std::wstring > lines;
	std::vector < sf::Text > texts;
	sf::RectangleShape rect;
	
	TextArea(std::wstring s, sf::Vector2f position = sf::Vector2f(0, 0), float line_length = 0.0f);

	~TextArea() {

	}

	void generateText();

	float getLineHeight() {
		return characterSize * 1.3f;
	}

	void generateRect();

	void setRectSize(sf::Vector2f size) {
		rect.setSize(size);
	}

	void setWstring(std::wstring s);
	void setPosition(sf::Vector2f position);

	void setCharacterSize(short val) {
		
		characterSize = val;

		generateText();
		generateRect();
	}

	void setRectColor(sf::Color color) {
		rect.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		for (auto& text : texts)
			text.setFillColor(color);
		
	}

	sf::Vector2f getSize() {
		return rect.getSize();
	}

	void update() {
		
	}

	void draw();
};
