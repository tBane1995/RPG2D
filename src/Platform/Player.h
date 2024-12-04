#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"
#include "UnitStates.h"

class Inventory;
class Item;
class SingleTexture;
class TTextureEntry;

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
	TTextureEntry* bodyIdleTextures[16];	// idle for top, right, bottom, left
	TTextureEntry* bodyRunTextures[16];	// run for top, right, bottom, left
	TTextureEntry* bodyAttackTextures[16];	// fight for top, right, bottom, left

	// HELMET
	TTextureEntry* helmetIdleTextures[16];
	TTextureEntry* helmetRunTextures[16];
	TTextureEntry* helmetAttackTextures[16];

	// ARMOR
	TTextureEntry* armorIdleTextures[16];
	TTextureEntry* armorRunTextures[16];
	TTextureEntry* armorAttackTextures[16];

	// PANTS
	TTextureEntry* pantsIdleTextures[16];
	TTextureEntry* pantsRunTextures[16];
	TTextureEntry* pantsAttackTextures[16];

	// WEAPON
	TTextureEntry* rightHandIdleTextures[16];
	TTextureEntry* rightHandRunTextures[16];
	TTextureEntry* rightHandAttackTextures[16];

	// SHIELD
	TTextureEntry* leftHandIdleTextures[16];
	TTextureEntry* leftHandRunTextures[16];
	TTextureEntry* leftHandAttackTextures[16];

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

	virtual void update(float dt) override;
	virtual void draw() override;
};

extern Player* player;

void createPlayer();
