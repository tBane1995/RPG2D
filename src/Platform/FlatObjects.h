#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class FlatObject : public GameObject {
public:

	sf::Sprite sprite;
	
	FlatObject(std::string name, float width, float length, float height);
	FlatObject(GameObject* object, float x, float y);

	virtual ~FlatObject() {
	
	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {

	}

	virtual void draw() override;
};

extern std::vector < FlatObject* > flatObjects;

bool isPathOnPosition(float x, float y);
