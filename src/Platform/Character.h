#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Units.h"

class Item;
class SingleTexture;
class Dialogue;

class Character : public Unit {
public:

	// EQUIPMENT
	Item* helmet;
	Item* armor;
	Item* pants;
	Item* leftHand;
	Item* rightHand;

	// HELMET - textures
	SingleTexture* helmetIdleTextures[16];
	SingleTexture* helmetRunTextures[16];
	SingleTexture* helmetAttackTextures[16];

	// ARMOR - textures
	SingleTexture* armorIdleTextures[16];
	SingleTexture* armorRunTextures[16];
	SingleTexture* armorAttackTextures[16];

	// PANTS - textures
	SingleTexture* pantsIdleTextures[16];
	SingleTexture* pantsRunTextures[16];
	SingleTexture* pantsAttackTextures[16];

	// LEFT HAND - textures
	SingleTexture* leftHandIdleTextures[16];
	SingleTexture* leftHandRunTextures[16];
	SingleTexture* leftHandAttackTextures[16];

	// RIGHT HAND - textures
	SingleTexture* rightHandIdleTextures[16];
	SingleTexture* rightHandRunTextures[16];
	SingleTexture* rightHandAttackTextures[16];

	// SPRITES
	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;
	sf::Sprite leftHandSprite;
	sf::Sprite rightHandSprite;
	
	Dialogue* dialogue;

	SingleTexture* talkWithTexture;
	sf::Sprite talkWithSprite;
	bool showHand;


	Character(std::string name, std::string bodySet = "sets/body/hero");
	Character(GameObject* object, float x, float y);

	virtual ~Character() {
		
	}

	void loadBody();
	void loadHelmet();
	void loadArmor();
	void loadPants();
	void loadLeftHand();
	void loadRightHand();
	void loadAppearance();

	virtual void update(float dt) override;
	virtual void draw() override;
};

extern std::vector < Character* > characters;
