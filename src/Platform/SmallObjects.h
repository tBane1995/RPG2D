#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class SmallObject : public GameObject {
public:

	sf::Sprite sprite;

	SmallObject(std::string name, float width, float length, float height);
	SmallObject(GameObject* object, float x, float y);
	~SmallObject();
	virtual void setPosition(sf::Vector2f position) override;
	virtual void update() override;
	virtual void drawStatistics() override;
	virtual void draw() override;
};

extern std::vector < SmallObject* > smallObjects;
