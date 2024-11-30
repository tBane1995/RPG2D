#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class Wall : public GameObject {
public:
	sf::Sprite sprite;

	Wall(std::string name, float width, float length, float height);
	Wall(GameObject* object, float x, float y);

	virtual ~Wall() {

	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {
		
	}

	virtual void draw() override;
};

extern std::vector < Wall* > walls;
