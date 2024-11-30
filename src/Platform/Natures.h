#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class Nature : public GameObject {
public:
	sf::Sprite sprite;

	Nature(std::string name, float width, float length, float height);
	Nature(GameObject* object, float x, float y);

	virtual ~Nature() {
	
	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {

	}

	virtual void draw() override;
};

extern std::vector < Nature* > natures;
