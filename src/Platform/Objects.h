#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class GameObject;

class Object : public GameObject {
public:

	std::vector < SingleTexture* > textures;
	short frame;
	sf::Time last_action_time;
	sf::Sprite sprite;


	Object(std::string name, float width, float length, float height, bool collisioning);
	Object(GameObject* object, float x, float y);

	virtual ~Object() { }

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override;

	virtual void draw() override;
};

extern std::vector < Object* > objects;
