#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class Inventory;
class SingleTexture;

class Furniture : public GameObject {
public:
	sf::Sprite sprite;

	Inventory* inventory;
	SingleTexture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Furniture(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Rectangle);
	
	Furniture(GameObject* object, float x, float y) : GameObject(object, x, y);

	virtual ~Furniture() {

	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override;

	virtual void draw() override {
		if (mouseIsHover)
			GameObject::draw();

		window->draw(sprite);

		if(showHand)
			window->draw(takeItSprite);
	}
};

extern std::vector < Furniture* > furnitures;
