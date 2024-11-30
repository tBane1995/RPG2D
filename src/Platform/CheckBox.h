#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class CheckBox {
public:
	sf::Vector2f position;
	sf::RectangleShape rect;
	bool value;
	sf::Sprite checkSprite;
	
	CheckBox() {
		this->value = false;
	}

	CheckBox(sf::Vector2f size, sf::Vector2f position, bool value = false);
	~CheckBox() { }

	void edit(sf::Vector2f size, sf::Vector2f position);

	void update(float dt);
	void draw();
};
