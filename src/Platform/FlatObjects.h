#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class FlatObject : public GameObject {
public:

	sf::Sprite sprite;
	
	FlatObject(std::string name, float width, float length, float height ) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
		type = GameObjectType::FlatObject;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	FlatObject(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::FlatObject;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*getSingleTexture(name)->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
		
	}

	virtual ~FlatObject() {
	
	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {

	}

	virtual void draw() override {
		
		if(mouseIsHover)
			GameObject::draw();
	
		window->draw(sprite);
	}
};

extern std::vector < FlatObject* > flatObjects;

bool isPathOnPosition(float x, float y);
