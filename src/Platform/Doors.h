#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

enum class DoorState { Open, Opening, Close, Closing };

class SingleTexture;

class Door : public GameObject {
public:
	std::vector < SingleTexture* > textures;
	sf::Sprite sprite;
	sf::Time last_action_time;
	short current_frame;
	DoorState state;
	SingleTexture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Door(std::string name, float width, float length, float height, float width_left, float width_right);
	Door(GameObject* object, float x, float y);

	virtual ~Door() {
	
	}

	void open();
	void close();
	bool playerNextTo();

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override;
	virtual void draw() override;
};

extern std::vector < Door* > doors;
