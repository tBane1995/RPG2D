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
	Door(GameObject* object, float x, float y) : GameObject(object, x, y);

	virtual ~Door() {
	
	}

	void open() {
		startActionTime = currentTime;
		state = doorState::opening;
		delete colliders.back();
		colliders.pop_back();
	}

	void close() {
		startActionTime = currentTime;
		state = doorState::closing;
		colliders.push_back(new Collider(sprite.getGlobalBounds().getSize().x, colliders[0]->length, sf::Vector2f(position.x, position.y), ColliderType::Rectangle));
	}

	bool playerNextTo();

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override;

	virtual void draw() override {
		if (mouseIsHover)
			GameObject::draw();

		window->draw(sprite);

		if (showHand)
			window->draw(takeItSprite);
		
	}
};

extern std::vector < Door* > doors;
