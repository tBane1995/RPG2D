#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Point.h"
#include "Units.h"

class GameObject;

class Monster : public Unit {
public:

	bool isAlive;
	sf::Vector2f base;
	sf::Time deathTime;
	short EXPERIENCE;
	std::vector < Point > path;
	std::vector < sf::CircleShape > pathpoints;

	Monster(std::string name, float width, float length, float height, short EXP);
	Monster(GameObject* object, float x, float y);

	virtual ~Monster() {

	}

	void loadTextures();
	void dropLoot();
	void loadTheTarget();
	void loadThePath();
	void followThePath(float dt);
	void idle(float dt);
	void run(float dt);
	virtual void update() override;
	virtual void drawStatistics() override;
	virtual void draw() override;
};

extern std::vector < Monster* > monsters;
