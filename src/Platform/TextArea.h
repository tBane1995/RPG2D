#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TextArea {
public:
	sf::Vector2f position;
	float characterSize = 17;
	float line_length;
	std::vector < std::wstring > lines;
	std::vector < sf::Text > texts;		// texts
	sf::RectangleShape background;		// texts background
	sf::RectangleShape rect;			// rectangle field
	sf::Color text_color;
	sf::Color background_color;
	sf::Color rect_color;

	TextArea(std::wstring text, sf::Vector2f position = sf::Vector2f(0, 0), float line_length = 0.0f, sf::Vector2f size = sf::Vector2f(0, 0));
	~TextArea();

	void setTextColor(sf::Color color);
	void setBackgroundColor(sf::Color color);
	void setRectColor(sf::Color color);

	float getLineHeight();

	void generateText();
	void generateBackground();
	void generateRect(sf::Vector2f size=sf::Vector2f(0,0));

	void setCharacterSize(short val);
	void setBackgroundSize(sf::Vector2f size);
	void setRectSize(sf::Vector2f size);

	void setWstring(std::wstring s);
	void setPosition(sf::Vector2f position);
	
	sf::Vector2f getSize();

	void update();
	void draw();
};
