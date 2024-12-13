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
	sf::Color text_color;

	TextArea(std::wstring s, sf::Vector2f position = sf::Vector2f(0, 0), float line_length = 0.0f);
	~TextArea();

	void setRectColor(sf::Color color);
	void setTextColor(sf::Color color);
	float getLineHeight();
	void generateText();
	void generateRect();
	void setRectSize(sf::Vector2f size);

	void setWstring(std::wstring s);
	void setPosition(sf::Vector2f position);
	void setCharacterSize(short val);
	sf::Vector2f getSize();

	void update();
	void draw();
};
