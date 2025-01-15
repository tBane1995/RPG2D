#pragma once
#include "GameObjects.h"

class MouseMovedGameObject {
public:
	GameObject* _object;
	sf::Vector2f _offset;

	MouseMovedGameObject(GameObject* object);
	~MouseMovedGameObject();
	void setOffset(sf::Vector2f offset);
	void update();
	void draw();
};
