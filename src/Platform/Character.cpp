#include "Character.h"
#include "Window.h"
#include "Textures.h"
#include "Items.h"
#include "Player.h"
#include "Collisions.h"

Character::Character(std::string name, std::string bodySet) : Unit(name, bodySet, 36, 18, 64) {		
	type = GameObjectType::Character;
		
	helmet = nullptr;
	armor = nullptr;
	pants = nullptr;
	leftHand = nullptr;
	rightHand = nullptr;

	loadBody();
	loadHelmet();
	loadArmor();
	loadPants();
	loadLeftHand();
	loadRightHand();

	dialogue = nullptr;

	talkWithTexture = getSingleTexture("GUI/talk");
	talkWithSprite = sf::Sprite();
	talkWithSprite.setTexture(*talkWithTexture->texture);
	talkWithSprite.setOrigin(talkWithTexture->cx, talkWithTexture->cy);
	showHand = false;

}

Character::Character(GameObject* object, float x, float y) : Unit(object, x, y) {
	type = GameObjectType::Character;
				
	helmet = dynamic_cast <Character*>(object)->helmet;
	armor = dynamic_cast <Character*>(object)->armor;
	pants = dynamic_cast <Character*>(object)->pants;
	leftHand = dynamic_cast <Character*>(object)->leftHand;
	rightHand = dynamic_cast <Character*>(object)->rightHand;

	loadBody();
	loadHelmet();
	loadArmor();
	loadPants();
	loadLeftHand();
	loadRightHand();
		
	dialogue = dynamic_cast <Character*>(object)->dialogue;

	talkWithTexture = getSingleTexture("GUI/talk");
	talkWithSprite = sf::Sprite();
	talkWithSprite.setTexture(*talkWithTexture->texture);
	talkWithSprite.setOrigin(talkWithTexture->cx, talkWithTexture->cy);
	showHand = false;
}

void Character::loadBody() {
	for (short i = 0; i < 16; i++) {
		idleTextures[i] = nullptr;
		runTextures[i] = nullptr;
		attackTextures[i] = nullptr;

	}

	for (short i = 0; i < 4; i++) {

		idleTextures[i] = getSingleTexture(bodySet + "/idleTop" + std::to_string(i));
		idleTextures[4 + i] = getSingleTexture(bodySet + "/idleRight" + std::to_string(i));
		idleTextures[8 + i] = getSingleTexture(bodySet + "/idleBottom" + std::to_string(i));
		idleTextures[12 + i] = getSingleTexture(bodySet + "/idleLeft" + std::to_string(i));

		runTextures[i] = getSingleTexture(bodySet + "/runTop" + std::to_string(i));
		runTextures[4 + i] = getSingleTexture(bodySet + "/runRight" + std::to_string(i));
		runTextures[8 + i] = getSingleTexture(bodySet + "/runBottom" + std::to_string(i));
		runTextures[12 + i] = getSingleTexture(bodySet + "/runLeft" + std::to_string(i));

		attackTextures[i] = getSingleTexture(bodySet + "/attackTop" + std::to_string(i));
		attackTextures[4 + i] = getSingleTexture(bodySet + "/attackRight" + std::to_string(i));
		attackTextures[8 + i] = getSingleTexture(bodySet + "/attackBottom" + std::to_string(i));
		attackTextures[12 + i] = getSingleTexture(bodySet + "/attackLeft" + std::to_string(i));

	}

	sprite = sf::Sprite();
	sprite.setOrigin(32, 58);

}


void Character::loadHelmet() {

	for (short i = 0; i < 16; i++) {
		helmetIdleTextures[i] = nullptr;
		helmetRunTextures[i] = nullptr;
		helmetAttackTextures[i] = nullptr;

	}

	if (helmet != nullptr) {

		for (short i = 0; i < 4; i++) {
			helmetIdleTextures[i] = getSingleTexture("sets/" + helmet->name + "/idleTop" + std::to_string(i));
			helmetIdleTextures[4 + i] = getSingleTexture("sets/" + helmet->name + "/idleRight" + std::to_string(i));
			helmetIdleTextures[8 + i] = getSingleTexture("sets/" + helmet->name + "/idleBottom" + std::to_string(i));
			helmetIdleTextures[12 + i] = getSingleTexture("sets/" + helmet->name + "/idleLeft" + std::to_string(i));

			helmetRunTextures[i] = getSingleTexture("sets/" + helmet->name + "/runTop" + std::to_string(i));
			helmetRunTextures[4 + i] = getSingleTexture("sets/" + helmet->name + "/runRight" + std::to_string(i));
			helmetRunTextures[8 + i] = getSingleTexture("sets/" + helmet->name + "/runBottom" + std::to_string(i));
			helmetRunTextures[12 + i] = getSingleTexture("sets/" + helmet->name + "/runLeft" + std::to_string(i));

			helmetAttackTextures[i] = getSingleTexture("sets/" + helmet->name + "/attackTop" + std::to_string(i));
			helmetAttackTextures[4 + i] = getSingleTexture("sets/" + helmet->name + "/attackRight" + std::to_string(i));
			helmetAttackTextures[8 + i] = getSingleTexture("sets/" + helmet->name + "/attackBottom" + std::to_string(i));
			helmetAttackTextures[12 + i] = getSingleTexture("sets/" + helmet->name + "/attackLeft" + std::to_string(i));

		}
	}

	helmetSprite = sf::Sprite();
	helmetSprite.setOrigin(32, 58);

}

void Character::loadArmor() {

	for (short i = 0; i < 16; i++) {
		armorIdleTextures[i] = nullptr;
		armorRunTextures[i] = nullptr;
		armorAttackTextures[i] = nullptr;

	}

	if (armor != nullptr) {

		for (short i = 0; i < 4; i++) {
			armorIdleTextures[i] = getSingleTexture("sets/" + armor->name + "/idleTop" + std::to_string(i));
			armorIdleTextures[4 + i] = getSingleTexture("sets/" + armor->name + "/idleRight" + std::to_string(i));
			armorIdleTextures[8 + i] = getSingleTexture("sets/" + armor->name + "/idleBottom" + std::to_string(i));
			armorIdleTextures[12 + i] = getSingleTexture("sets/" + armor->name + "/idleLeft" + std::to_string(i));

			armorRunTextures[i] = getSingleTexture("sets/" + armor->name + "/runTop" + std::to_string(i));
			armorRunTextures[4 + i] = getSingleTexture("sets/" + armor->name + "/runRight" + std::to_string(i));
			armorRunTextures[8 + i] = getSingleTexture("sets/" + armor->name + "/runBottom" + std::to_string(i));
			armorRunTextures[12 + i] = getSingleTexture("sets/" + armor->name + "/runLeft" + std::to_string(i));

			armorAttackTextures[i] = getSingleTexture("sets/" + armor->name + "/attackTop" + std::to_string(i));
			armorAttackTextures[4 + i] = getSingleTexture("sets/" + armor->name + "/attackRight" + std::to_string(i));
			armorAttackTextures[8 + i] = getSingleTexture("sets/" + armor->name + "/attackBottom" + std::to_string(i));
			armorAttackTextures[12 + i] = getSingleTexture("sets/" + armor->name + "/attackLeft" + std::to_string(i));

		}
	}

	armorSprite = sf::Sprite();
	armorSprite.setOrigin(32, 58);
}

void Character::loadPants() {

	for (short i = 0; i < 16; i++) {
		pantsIdleTextures[i] = nullptr;
		pantsRunTextures[i] = nullptr;
		pantsAttackTextures[i] = nullptr;

	}

	if (pants != nullptr) {

		for (short i = 0; i < 4; i++) {
			pantsIdleTextures[i] = getSingleTexture("sets/" + pants->name + "/idleTop" + std::to_string(i));
			pantsIdleTextures[4 + i] = getSingleTexture("sets/" + pants->name + "/idleRight" + std::to_string(i));
			pantsIdleTextures[8 + i] = getSingleTexture("sets/" + pants->name + "/idleBottom" + std::to_string(i));
			pantsIdleTextures[12 + i] = getSingleTexture("sets/" + pants->name + "/idleLeft" + std::to_string(i));

			pantsRunTextures[i] = getSingleTexture("sets/" + pants->name + "/runTop" + std::to_string(i));
			pantsRunTextures[4 + i] = getSingleTexture("sets/" + pants->name + "/runRight" + std::to_string(i));
			pantsRunTextures[8 + i] = getSingleTexture("sets/" + pants->name + "/runBottom" + std::to_string(i));
			pantsRunTextures[12 + i] = getSingleTexture("sets/" + pants->name + "/runLeft" + std::to_string(i));

			pantsAttackTextures[i] = getSingleTexture("sets/" + pants->name + "/attackTop" + std::to_string(i));
			pantsAttackTextures[4 + i] = getSingleTexture("sets/" + pants->name + "/attackRight" + std::to_string(i));
			pantsAttackTextures[8 + i] = getSingleTexture("sets/" + pants->name + "/attackBottom" + std::to_string(i));
			pantsAttackTextures[12 + i] = getSingleTexture("sets/" + pants->name + "/attackLeft" + std::to_string(i));

		}
	}

	pantsSprite = sf::Sprite();
	pantsSprite.setOrigin(32, 58);

}

void Character::loadLeftHand() {

	for (short i = 0; i < 16; i++) {
		leftHandIdleTextures[i] = nullptr;
		leftHandRunTextures[i] = nullptr;
		leftHandAttackTextures[i] = nullptr;

	}

	if (leftHand != nullptr) {

		for (short i = 0; i < 4; i++) {
			leftHandIdleTextures[i] = getSingleTexture("sets/" + leftHand->name + "/idleTop" + std::to_string(i));
			leftHandIdleTextures[4 + i] = getSingleTexture("sets/" + leftHand->name + "/idleRight" + std::to_string(i));
			leftHandIdleTextures[8 + i] = getSingleTexture("sets/" + leftHand->name + "/idleBottom" + std::to_string(i));
			leftHandIdleTextures[12 + i] = getSingleTexture("sets/" + leftHand->name + "/idleLeft" + std::to_string(i));

			leftHandRunTextures[i] = getSingleTexture("sets/" + leftHand->name + "/runTop" + std::to_string(i));
			leftHandRunTextures[4 + i] = getSingleTexture("sets/" + leftHand->name + "/runRight" + std::to_string(i));
			leftHandRunTextures[8 + i] = getSingleTexture("sets/" + leftHand->name + "/runBottom" + std::to_string(i));
			leftHandRunTextures[12 + i] = getSingleTexture("sets/" + leftHand->name + "/runLeft" + std::to_string(i));

			leftHandAttackTextures[i] = getSingleTexture("sets/" + leftHand->name + "/attackTop" + std::to_string(i));
			leftHandAttackTextures[4 + i] = getSingleTexture("sets/" + leftHand->name + "/attackRight" + std::to_string(i));
			leftHandAttackTextures[8 + i] = getSingleTexture("sets/" + leftHand->name + "/attackBottom" + std::to_string(i));
			leftHandAttackTextures[12 + i] = getSingleTexture("sets/" + leftHand->name + "/attackLeft" + std::to_string(i));

		}
	}

	leftHandSprite = sf::Sprite();
	leftHandSprite.setOrigin(32, 58);

}

void Character::loadRightHand() {

	for (short i = 0; i < 16; i++) {
		rightHandIdleTextures[i] = nullptr;
		rightHandRunTextures[i] = nullptr;
		rightHandAttackTextures[i] = nullptr;

	}

	if (rightHand != nullptr) {

		for (short i = 0; i < 4; i++) {
			rightHandIdleTextures[i] = getSingleTexture("sets/" + rightHand->name + "/idleTop" + std::to_string(i));
			rightHandIdleTextures[4 + i] = getSingleTexture("sets/" + rightHand->name + "/idleRight" + std::to_string(i));
			rightHandIdleTextures[8 + i] = getSingleTexture("sets/" + rightHand->name + "/idleBottom" + std::to_string(i));
			rightHandIdleTextures[12 + i] = getSingleTexture("sets/" + rightHand->name + "/idleLeft" + std::to_string(i));

			rightHandRunTextures[i] = getSingleTexture("sets/" + rightHand->name + "/runTop" + std::to_string(i));
			rightHandRunTextures[4 + i] = getSingleTexture("sets/" + rightHand->name + "/runRight" + std::to_string(i));
			rightHandRunTextures[8 + i] = getSingleTexture("sets/" + rightHand->name + "/runBottom" + std::to_string(i));
			rightHandRunTextures[12 + i] = getSingleTexture("sets/" + rightHand->name + "/runLeft" + std::to_string(i));

			rightHandAttackTextures[i] = getSingleTexture("sets/" + rightHand->name + "/attackTop" + std::to_string(i));
			rightHandAttackTextures[4 + i] = getSingleTexture("sets/" + rightHand->name + "/attackRight" + std::to_string(i));
			rightHandAttackTextures[8 + i] = getSingleTexture("sets/" + rightHand->name + "/attackBottom" + std::to_string(i));
			rightHandAttackTextures[12 + i] = getSingleTexture("sets/" + rightHand->name + "/attackLeft" + std::to_string(i));

		}
	}

	rightHandSprite = sf::Sprite();
	rightHandSprite.setOrigin(32, 58);

}

void Character::update(float dt) {
	calculateCurrentFrame(dt);
	GameObject::update(dt);
	textname.setPosition(position.x, position.y - height - 10);

	sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
	sprite.setPosition(position);

	if (helmet != nullptr) {
		helmetSprite.setTexture(*helmetIdleTextures[direction * 4 + frame]->texture);
		helmetSprite.setPosition(position);

	}

	if (armor != nullptr) {
		armorSprite.setTexture(*armorIdleTextures[direction * 4 + frame]->texture);
		armorSprite.setPosition(position);
	}

	if (pants != nullptr) {
		pantsSprite.setTexture(*pantsIdleTextures[direction * 4 + frame]->texture);
		pantsSprite.setPosition(position);
	}

	if (rightHand != nullptr) {
		rightHandSprite.setTexture(*rightHandIdleTextures[direction * 4 + frame]->texture);
		rightHandSprite.setPosition(position);
	}

	if (leftHand != nullptr) {
		leftHandSprite.setTexture(*leftHandIdleTextures[direction * 4 + frame]->texture);
		leftHandSprite.setPosition(position);
	}

	viewRangeArea.setPosition(position);
	actionRangeArea.setPosition(position);

	setLifeBar();

	showHand = false;
	talkWithSprite.setPosition(position.x, position.y - 90);

	if (dialogue != nullptr) {
		if (player != nullptr) {

			float x1, y1, rx1, ry1;
			float x2, y2, rx2, ry2;

			x1 = player->position.x;
			y1 = player->position.y;
			rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
			ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

			x2 = position.x;
			y2 = position.y;
			rx2 = (colliders[0]->width / 2.0f + ACTION_RANGE);
			ry2 = (colliders[0]->length + ACTION_RANGE) / 2.0f;

			if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {
				showHand = true;
			}
		}

	}

}

void Character::draw() {

	if (direction == 0) {
		// TOP
		window->draw(rightHandSprite);
		window->draw(leftHandSprite);
		window->draw(sprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);

	}

	if (direction == 1) {
		// RIGHT

		window->draw(leftHandSprite);
		window->draw(sprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		window->draw(rightHandSprite);
	}

	if (direction == 2) {
		// BOTTOM
		window->draw(sprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		window->draw(leftHandSprite);
		window->draw(rightHandSprite);
	}

	if (direction == 3) {
		// LEFT
		window->draw(rightHandSprite);
		window->draw(sprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		window->draw(leftHandSprite);

	}
		
	if (showHand == true)
		window->draw(talkWithSprite);
		
	GameObject::draw();
	//window->draw(lifeBarBackground);
	//window->draw(lifeBar);
}

std::vector < Character* > characters;
