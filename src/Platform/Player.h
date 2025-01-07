#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"
#include "UnitStates.h"

class Inventory;
class Item;
class SingleTexture;

class Player : public GameObject {
public:
	Item* helmet;
	Item* armor;
	Item* pants;
	Item* rightHand;
	Item* leftHand;

	// TO-DO sf::Texture to Texture*
	// BODY
	std::string body;
	SingleTexture* bodyIdleTextures[16];	// idle for top, right, bottom, left
	SingleTexture* bodyRunTextures[16];	// run for top, right, bottom, left
	SingleTexture* bodyAttackTextures[16];	// fight for top, right, bottom, left

	// HELMET
	SingleTexture* helmetIdleTextures[16];
	SingleTexture* helmetRunTextures[16];
	SingleTexture* helmetAttackTextures[16];

	// ARMOR
	SingleTexture* armorIdleTextures[16];
	SingleTexture* armorRunTextures[16];
	SingleTexture* armorAttackTextures[16];

	// PANTS
	SingleTexture* pantsIdleTextures[16];
	SingleTexture* pantsRunTextures[16];
	SingleTexture* pantsAttackTextures[16];

	// WEAPON
	SingleTexture* rightHandIdleTextures[16];
	SingleTexture* rightHandRunTextures[16];
	SingleTexture* rightHandAttackTextures[16];

	// SHIELD
	SingleTexture* leftHandIdleTextures[16];
	SingleTexture* leftHandRunTextures[16];
	SingleTexture* leftHandAttackTextures[16];

	// SPRITES
	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;
	sf::Sprite rightHandSprite;
	sf::Sprite leftHandSprite;

	short direction;
	short frame;	// current frame number
	float stepSize;
	unitStates state;
	float actionRange;
	float viewRange;
	sf::CircleShape actionRangeArea;

	float countdown;	 // timer to determine current frame
	float attackTime;
	float cooldown;

	Inventory* bag;

	short HP, HP_FULL;
	short MP, MP_FULL;
	short STRENGTH;
	short DEXTERITY;
	short INTELLIGENCE;
	short LEVEL;
	short EXPERIENCE;
	short EXPERIENCE_TO_NEXT_LEVEL;
	short SKILL_POINTS;

	Player();

	virtual ~Player() {
	
	}
	
	void setDirection(int direction) {
		this->direction = direction;
		frame = 0.0f;
	}

	void move() {
		state = unitStates::run;
	}

	void attack() {
		state = unitStates::attack;
		frame = 0.0f;
		cooldown = attackTime;
	}

	void setPosition(float x, float y) {
		this->position.x = x;
		this->position.y = y;
	}

	void loadBody();
	void loadHelmet();
	void loadArmor();
	void loadPants();
	void loadRightHand();
	void loadLeftHand();

	void setActionRangeArea();
	void calculateCurrentFrame(float dt);

	int takeDamage(short damage);
	int getDamage();
	void heal(short HP);

	void collectItem(Item* item, short count = 1);

	void gainEXP(short EXP);
	bool levelUp();

	virtual void update() override;
	virtual void drawStatistics() override;
	virtual void draw() override;
};

extern Player* player;

void createPlayer();
