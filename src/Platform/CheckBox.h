#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Window.h"

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

	void update(float dt) {
		rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
		checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
	}

	void draw() {
		//window->draw(rect);
		if (value)
		{
			window->draw(checkSprite);
		}
	}
};
