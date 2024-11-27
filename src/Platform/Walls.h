#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class Wall : public GameObject {
public:
	sf::Sprite sprite;

	Wall(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Rectangle) {
		type = GameObjectType::Wall;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Wall(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Wall;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
	}

	virtual ~Wall() {

	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {
		
	}

	virtual void draw() override {
		if (mouseIsHover)
			GameObject::draw();

		window->draw(sprite);
	}
};

extern std::vector < Wall* > walls;
