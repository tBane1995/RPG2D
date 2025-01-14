#pragma once
#include "GameObjects.h"

class MouseMovedGameObject {
public:
	GameObject* _object;
	sf::Vector2f _offset;

	MouseMovedGameObject(GameObject* object);
	~MouseMovedGameObject();
	void setOffset(sf::Vector2f offset = sf::Vector2f(0, 0));
	void update();
	void draw();
};
