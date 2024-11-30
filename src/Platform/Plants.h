#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

enum class animState { stop, anim, end };

class SingleTexture;

class Plant : public GameObject {
public:
	std::vector < SingleTexture* > textures;
	short current_texture;
	sf::Time time_last_frame;

	sf::Sprite sprite;

	animState state;
	sf::Time start_anim;
	sf::Time last_anim;
	short rotate;
	bool growing;

	Plant(std::string name, float width, float length, float height);
	Plant(GameObject* object, float x, float y);

	virtual ~Plant() {

	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override;
	virtual void draw() override;
};

extern std::vector < Plant* > plants;
