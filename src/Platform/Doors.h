#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

enum class doorState { open, opening, close, closing };

class SingleTexture;

class Door : public GameObject {
public:
	SingleTexture* textureOpen;
	SingleTexture* textureClose;
	sf::Sprite sprite;
	sf::Time startActionTime;
	doorState state;
	SingleTexture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Door(std::string name);
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
