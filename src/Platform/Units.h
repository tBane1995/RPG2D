#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"
#include "UnitStates.h"

extern float diff_x, diff_y;
extern float dist;

class SingleTexture;

class Unit : public GameObject {
public:
	
	std::string name;
	std::string bodySet;

	short LEVEL;
	short EXPERIENCE;
	short SKILL_POINTS;

	short HP, HP_FULL;
	short MP, MP_FULL;
	short STRENGTH;
	short DEXTERITY;
	short INTELLIGENCE;

	short ACTION_RANGE;	// range of action 
	short VIEW_RANGE;	// range of view
	
	unitStates state;		// idle, run or attack
	short frame;			// current frame
	short direction;		// direction 0 - Top, 1 - Right, 2 - Bottom, 3 - Left

	float countdown;	// timer to calculate frame
	float cooldown;		// timer past attack to freeze
	float attackTime;	// attack time in seconds

	SingleTexture* idleTextures[16];		// idle textures	
	SingleTexture* runTextures[16];		// run textures
	SingleTexture* attackTextures[16];	// attack textures
	sf::Sprite sprite;				// sprite to render texture

	sf::CircleShape viewRangeArea;		// is a range of see of units // in this range player can be a select as target
	sf::CircleShape actionRangeArea;
	sf::RectangleShape lifeBarBackground;
	sf::RectangleShape lifeBar;

	sf::Vector2f target;


	Unit(std::string name, std::string bodySet, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Elipse);
	Unit(GameObject* object, float x, float y) : GameObject(object, x, y);

	virtual ~Unit() {
	
	}

	void loadBody();
	void createViewRangeArea();
	void createActionRangeArea();
	void setLifeBar();

	short takeDamage(short damage) {

		HP -= damage;

		if (HP < 0)
			HP = 0;
		
		return damage;
	}

	short getDamage() {
		short damage = STRENGTH * 2;
		damage = damage * (rand() % 50 + 75) / 100;	// 75% - 125%
		return damage;
	}

	void calculateCurrentFrame(float dt);

	void cooldownDecrease(float dt) {
		if (cooldown >= 0.0f)
			cooldown -= dt;
	}

	bool playerInActionRange() {

		if (player == nullptr)
			return false;

		return intersectionTwoEllipses(position.x, position.y, colliders[0]->width / 2.0f + ACTION_RANGE, (colliders[0]->length + ACTION_RANGE) / 2.0f, player->position.x, player->position.y, player->colliders[0]->width / 2.0f, player->colliders[0]->length / 2.0f);

	}

	bool playerInViewRange() {
		if (player == nullptr)
			return false;

		return intersectionTwoEllipses(position.x, position.y, colliders[0]->width/2.0f + VIEW_RANGE, (colliders[0]->length + VIEW_RANGE) / 2.0f, player->position.x, player->position.y, player->colliders[0]->width/2.0f, player->colliders[0]->length / 2.0f);
	}

	void goToTarget(float dt);
	void idle(float dt);

	void run(float dt) {
		
		goToTarget(dt);

		calculateCurrentFrame(dt);
		texture = runTextures[direction * 4 + frame];
		sprite.setTexture(*texture->texture);
	}

	void attack(float dt);

	void idling(float dt) {

		calculateCurrentFrame(dt);
		texture = idleTextures[direction * 4 + frame];
		sprite.setTexture(*texture->texture);
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {

		calculateCurrentFrame(dt);
		sprite.setPosition(position);
		setLifeBar();

		GameObject::update(dt);
	}

	virtual void updateStatistic(float dt) override {

		GameObject::updateStatistic(dt);

		viewRangeArea.setPosition(position);
		actionRangeArea.setPosition(position);
	}

	virtual void draw() override {

		GameObject::draw();

		window->draw(sprite);
		window->draw(lifeBarBackground);
		window->draw(lifeBar);

		GameObject::draw();
	}

	virtual void drawAllStatistics() override {
		window->draw(viewRangeArea);
		window->draw(actionRangeArea);

		GameObject::drawAllStatistics();
	}

};
