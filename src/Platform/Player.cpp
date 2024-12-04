#include "Player.h"
#include "Items.h"
#include "Textures.h"
#include "HitTexts.h"
#include "Window.h"

Player::Player() : GameObject("hero", 0, 0, 24, 12, 64, true, ColliderType::Elipse) {
	type = GameObjectType::Player;
	direction = 2;
	frame = 0;
	stepSize = 6.0f;
	countdown = 0.0f;
	state = unitStates::idle;
	actionRange = 25.0f;
	cooldown = 0.0f;
	attackTime = 0.7f;

	//position.x = 950;
	//position.y = 1200 - 512;

	// TO-DO - to delete
	position.x = 1543;
	position.y = 800;
	//

	isVisible = true;
	isInTheMainList = true;

	HP = 10;
	HP_FULL = 40;
	MP = 5;
	MP_FULL = 5;
	STRENGTH = 5;
	DEXTERITY = 5;
	INTELLIGENCE = 5;

	LEVEL = 0;
	EXPERIENCE = 0;
	EXPERIENCE_TO_NEXT_LEVEL = 50;
	SKILL_POINTS = 0;

	body = "sets/body/boy-brownhaired";

	bag = new Inventory(-1);
	/*
	bag->addItem("items/torn shirt");
	bag->addItem("items/axe");
	bag->addItem("items/bone");
	bag->addItem("items/health herb");
	bag->addItem("items/skin helmet");
	bag->addItem("items/skin pants");
	bag->addItem("items/wooden club");
	bag->addItem("items/skin jacket");
	bag->addItem("items/club");
	bag->addItem("items/iron club");
	bag->addItem("items/stone hammer");
	bag->addItem("items/sword");
	bag->addItem("items/long sword");
	bag->addItem("items/gladius");
	bag->addItem("items/wide blade");
	bag->addItem("items/knife");
	bag->addItem("items/dagger");
	bag->addItem("items/hatchet");
	bag->addItem("items/curved sword");
	bag->addItem("items/chain mail");
	bag->addItem("items/chain mail pants");
	bag->addItem("items/wool hat");
	bag->addItem("items/wool pants");
	bag->addItem("items/wool shirt");
	bag->addItem("items/raw meat");
	bag->addItem("items/plate armor");
	*/
	// ITEMS TO-DO - CREATE ITEM SETS
	//bag->addItem("items/skin pants");

	helmet = nullptr;
	armor = nullptr;
	pants = nullptr;
	rightHand = nullptr;
	leftHand = nullptr;

	//helmet = getItem("items/skin helmet");
	//armor = getItem("items/skin jacket");
	//pants = getItem("items/skin pants");
	//rightHand = getItem("items/hatchet");
	//leftHand = nullptr;

	loadBody();
	loadHelmet();
	loadArmor();
	loadPants();
	loadRightHand();
	loadLeftHand();


	setActionRangeArea();
}

void Player::loadBody() {
	for (short i = 0; i < 16; i++) {
		bodyIdleTextures[i] = nullptr;
		bodyRunTextures[i] = nullptr;
		bodyAttackTextures[i] = nullptr;

	}

	for (short i = 0; i < 4; i++) {

		bodyIdleTextures[i] = getSingleTextureInfo(body + "/idleTop" + std::to_string(i));
		bodyIdleTextures[4 + i] = getSingleTextureInfo(body + "/idleRight" + std::to_string(i));
		bodyIdleTextures[8 + i] = getSingleTextureInfo(body + "/idleBottom" + std::to_string(i));
		bodyIdleTextures[12 + i] = getSingleTextureInfo(body + "/idleLeft" + std::to_string(i));

		bodyRunTextures[i] = getSingleTextureInfo(body + "/runTop" + std::to_string(i));
		bodyRunTextures[4 + i] = getSingleTextureInfo(body + "/runRight" + std::to_string(i));
		bodyRunTextures[8 + i] = getSingleTextureInfo(body + "/runBottom" + std::to_string(i));
		bodyRunTextures[12 + i] = getSingleTextureInfo(body + "/runLeft" + std::to_string(i));

		bodyAttackTextures[i] = getSingleTextureInfo(body + "/attackTop" + std::to_string(i));
		bodyAttackTextures[4 + i] = getSingleTextureInfo(body + "/attackRight" + std::to_string(i));
		bodyAttackTextures[8 + i] = getSingleTextureInfo(body + "/attackBottom" + std::to_string(i));
		bodyAttackTextures[12 + i] = getSingleTextureInfo(body + "/attackLeft" + std::to_string(i));

	}

	bodySprite = sf::Sprite();
	bodySprite.setTexture(*singleTextures[0]->texture);
	bodySprite.setOrigin(32, 58);
	bodySprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Player::loadHelmet() {

	for (short i = 0; i < 16; i++) {
		helmetIdleTextures[i] = nullptr;
		helmetRunTextures[i] = nullptr;
		helmetAttackTextures[i] = nullptr;

	}

	if (helmet != nullptr) {

		for (short i = 0; i < 4; i++) {
			helmetIdleTextures[i] = getSingleTextureInfo("sets/" + helmet->name + "/idleTop" + std::to_string(i));
			helmetIdleTextures[4 + i] = getSingleTextureInfo("sets/" + helmet->name + "/idleRight" + std::to_string(i));
			helmetIdleTextures[8 + i] = getSingleTextureInfo("sets/" + helmet->name + "/idleBottom" + std::to_string(i));
			helmetIdleTextures[12 + i] = getSingleTextureInfo("sets/" + helmet->name + "/idleLeft" + std::to_string(i));

			helmetRunTextures[i] = getSingleTextureInfo("sets/" + helmet->name + "/runTop" + std::to_string(i));
			helmetRunTextures[4 + i] = getSingleTextureInfo("sets/" + helmet->name + "/runRight" + std::to_string(i));
			helmetRunTextures[8 + i] = getSingleTextureInfo("sets/" + helmet->name + "/runBottom" + std::to_string(i));
			helmetRunTextures[12 + i] = getSingleTextureInfo("sets/" + helmet->name + "/runLeft" + std::to_string(i));

			helmetAttackTextures[i] = getSingleTextureInfo("sets/" + helmet->name + "/attackTop" + std::to_string(i));
			helmetAttackTextures[4 + i] = getSingleTextureInfo("sets/" + helmet->name + "/attackRight" + std::to_string(i));
			helmetAttackTextures[8 + i] = getSingleTextureInfo("sets/" + helmet->name + "/attackBottom" + std::to_string(i));
			helmetAttackTextures[12 + i] = getSingleTextureInfo("sets/" + helmet->name + "/attackLeft" + std::to_string(i));

		}
	}

	helmetSprite = sf::Sprite();
	helmetSprite.setTexture(*singleTextures[0]->texture);
	helmetSprite.setOrigin(32, 58);
	helmetSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Player::loadArmor() {

	for (short i = 0; i < 16; i++) {
		armorIdleTextures[i] = nullptr;
		armorRunTextures[i] = nullptr;
		armorAttackTextures[i] = nullptr;

	}

	if (armor != nullptr) {

		for (short i = 0; i < 4; i++) {
			armorIdleTextures[i] = getSingleTextureInfo("sets/" + armor->name + "/idleTop" + std::to_string(i));
			armorIdleTextures[4 + i] = getSingleTextureInfo("sets/" + armor->name + "/idleRight" + std::to_string(i));
			armorIdleTextures[8 + i] = getSingleTextureInfo("sets/" + armor->name + "/idleBottom" + std::to_string(i));
			armorIdleTextures[12 + i] = getSingleTextureInfo("sets/" + armor->name + "/idleLeft" + std::to_string(i));

			armorRunTextures[i] = getSingleTextureInfo("sets/" + armor->name + "/runTop" + std::to_string(i));
			armorRunTextures[4 + i] = getSingleTextureInfo("sets/" + armor->name + "/runRight" + std::to_string(i));
			armorRunTextures[8 + i] = getSingleTextureInfo("sets/" + armor->name + "/runBottom" + std::to_string(i));
			armorRunTextures[12 + i] = getSingleTextureInfo("sets/" + armor->name + "/runLeft" + std::to_string(i));

			armorAttackTextures[i] = getSingleTextureInfo("sets/" + armor->name + "/attackTop" + std::to_string(i));
			armorAttackTextures[4 + i] = getSingleTextureInfo("sets/" + armor->name + "/attackRight" + std::to_string(i));
			armorAttackTextures[8 + i] = getSingleTextureInfo("sets/" + armor->name + "/attackBottom" + std::to_string(i));
			armorAttackTextures[12 + i] = getSingleTextureInfo("sets/" + armor->name + "/attackLeft" + std::to_string(i));

		}
	}

	armorSprite = sf::Sprite();
	armorSprite.setTexture(*singleTextures[0]->texture);
	armorSprite.setOrigin(32, 58);
	armorSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Player::loadPants() {

	for (short i = 0; i < 16; i++) {
		pantsIdleTextures[i] = nullptr;
		pantsRunTextures[i] = nullptr;
		pantsAttackTextures[i] = nullptr;

	}

	if (pants != nullptr) {

		for (short i = 0; i < 4; i++) {
			pantsIdleTextures[i] = getSingleTextureInfo("sets/" + pants->name + "/idleTop" + std::to_string(i));
			pantsIdleTextures[4 + i] = getSingleTextureInfo("sets/" + pants->name + "/idleRight" + std::to_string(i));
			pantsIdleTextures[8 + i] = getSingleTextureInfo("sets/" + pants->name + "/idleBottom" + std::to_string(i));
			pantsIdleTextures[12 + i] = getSingleTextureInfo("sets/" + pants->name + "/idleLeft" + std::to_string(i));

			pantsRunTextures[i] = getSingleTextureInfo("sets/" + pants->name + "/runTop" + std::to_string(i));
			pantsRunTextures[4 + i] = getSingleTextureInfo("sets/" + pants->name + "/runRight" + std::to_string(i));
			pantsRunTextures[8 + i] = getSingleTextureInfo("sets/" + pants->name + "/runBottom" + std::to_string(i));
			pantsRunTextures[12 + i] = getSingleTextureInfo("sets/" + pants->name + "/runLeft" + std::to_string(i));

			pantsAttackTextures[i] = getSingleTextureInfo("sets/" + pants->name + "/attackTop" + std::to_string(i));
			pantsAttackTextures[4 + i] = getSingleTextureInfo("sets/" + pants->name + "/attackRight" + std::to_string(i));
			pantsAttackTextures[8 + i] = getSingleTextureInfo("sets/" + pants->name + "/attackBottom" + std::to_string(i));
			pantsAttackTextures[12 + i] = getSingleTextureInfo("sets/" + pants->name + "/attackLeft" + std::to_string(i));

		}
	}

	pantsSprite = sf::Sprite();
	pantsSprite.setTexture(*singleTextures[0]->texture);
	pantsSprite.setOrigin(32, 58);
	pantsSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Player::loadRightHand() {

	for (short i = 0; i < 16; i++) {
		rightHandIdleTextures[i] = nullptr;
		rightHandRunTextures[i] = nullptr;
		rightHandAttackTextures[i] = nullptr;

	}

	if (rightHand != nullptr) {

		for (short i = 0; i < 4; i++) {
			rightHandIdleTextures[i] = getSingleTextureInfo("sets/" + rightHand->name + "/idleTop" + std::to_string(i));
			rightHandIdleTextures[4 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/idleRight" + std::to_string(i));
			rightHandIdleTextures[8 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/idleBottom" + std::to_string(i));
			rightHandIdleTextures[12 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/idleLeft" + std::to_string(i));

			rightHandRunTextures[i] = getSingleTextureInfo("sets/" + rightHand->name + "/runTop" + std::to_string(i));
			rightHandRunTextures[4 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/runRight" + std::to_string(i));
			rightHandRunTextures[8 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/runBottom" + std::to_string(i));
			rightHandRunTextures[12 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/runLeft" + std::to_string(i));

			rightHandAttackTextures[i] = getSingleTextureInfo("sets/" + rightHand->name + "/attackTop" + std::to_string(i));
			rightHandAttackTextures[4 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/attackRight" + std::to_string(i));
			rightHandAttackTextures[8 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/attackBottom" + std::to_string(i));
			rightHandAttackTextures[12 + i] = getSingleTextureInfo("sets/" + rightHand->name + "/attackLeft" + std::to_string(i));

		}
	}

	rightHandSprite = sf::Sprite();
	rightHandSprite.setTexture(*singleTextures[0]->texture);
	rightHandSprite.setOrigin(32, 58);
	rightHandSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Player::loadLeftHand() {

	for (short i = 0; i < 16; i++) {
		leftHandIdleTextures[i] = nullptr;
		leftHandRunTextures[i] = nullptr;
		leftHandAttackTextures[i] = nullptr;

	}

	if (leftHand != nullptr) {

		for (short i = 0; i < 4; i++) {
			leftHandIdleTextures[i] = getSingleTextureInfo("sets/" + leftHand->name + "/idleTop" + std::to_string(i));
			leftHandIdleTextures[4 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/idleRight" + std::to_string(i));
			leftHandIdleTextures[8 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/idleBottom" + std::to_string(i));
			leftHandIdleTextures[12 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/idleLeft" + std::to_string(i));

			leftHandRunTextures[i] = getSingleTextureInfo("sets/" + leftHand->name + "/runTop" + std::to_string(i));
			leftHandRunTextures[4 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/runRight" + std::to_string(i));
			leftHandRunTextures[8 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/runBottom" + std::to_string(i));
			leftHandRunTextures[12 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/runLeft" + std::to_string(i));

			leftHandAttackTextures[i] = getSingleTextureInfo("sets/" + leftHand->name + "/attackTop" + std::to_string(i));
			leftHandAttackTextures[4 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/attackRight" + std::to_string(i));
			leftHandAttackTextures[8 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/attackBottom" + std::to_string(i));
			leftHandAttackTextures[12 + i] = getSingleTextureInfo("sets/" + leftHand->name + "/attackLeft" + std::to_string(i));

		}
	}

	leftHandSprite = sf::Sprite();
	leftHandSprite.setTexture(*singleTextures[0]->texture);
	leftHandSprite.setOrigin(32, 58);
	leftHandSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void Player::setActionRangeArea() {
	actionRangeArea = sf::CircleShape(actionRange + colliders[0]->width / 2.0f);
	actionRangeArea.setFillColor(sf::Color(128, 64, 64, 128));
	actionRangeArea.setOutlineColor(sf::Color(196, 64, 64, 128));
	actionRangeArea.setOutlineThickness(4.0f);
	actionRangeArea.setOrigin(actionRange + colliders[0]->width / 2.0f, actionRange + colliders[0]->width / 2.0f);
	actionRangeArea.setScale(1.0f, colliders[0]->length / colliders[0]->width);
}


void Player::calculateCurrentFrame(float dt) {
	countdown -= dt;
	while (countdown <= 0.0f) {
		countdown += 1.0f / 8.0f;	// 8 FPS
		frame += 1;
	}

	if (frame > 3)
		frame = frame % 4;
}

int Player::takeDamage(short damage) {

	short defend = 0;

	if (armor != nullptr)
		defend += armor->attributes[attribute::DEFEND];

	if (helmet != nullptr)
		defend += helmet->attributes[attribute::DEFEND];

	if (pants != nullptr)
		defend += pants->attributes[attribute::DEFEND];

	if (leftHand != nullptr)
		defend += leftHand->attributes[attribute::DEFEND];

	short dam = damage - defend;

	if (dam > 0) {
		HP = HP - dam;

		if (HP < 0)
			HP = 0;
	}

	return dam;
}
	
int Player::getDamage() {
	int damage = STRENGTH * 2;

	if (rightHand != nullptr)
		damage += rightHand->attributes[attribute::ATTACK];

	damage = damage * (rand() % 50 + 75) / 100;		// 75% - 125% 

	return int(damage);
}

void Player::heal(short HP) {
	this->HP += HP;

	if (this->HP > HP_FULL)
		this->HP = HP_FULL;
}

void Player::collectItem(Item* item, short count) {

	bag->addItem(item, count);
}

void Player::gainEXP(short EXP) {
	EXPERIENCE += EXP;
	while (levelUp());
}

bool Player::levelUp() {

	short LEVEL_SCALAR = 2;

	if (EXPERIENCE >= EXPERIENCE_TO_NEXT_LEVEL) {
		LEVEL++;
		HP += 40;
		HP_FULL += 40;
		EXPERIENCE_TO_NEXT_LEVEL *= LEVEL_SCALAR;
		SKILL_POINTS += 5;

		hits->addHitText(sf::Vector2f(position.x, position.y - height), "lvl up!");
		return true;
	}

	return false;
}

void Player::update(float dt) {

	float distance = 20.0f * stepSize * dt;

	if (state == unitStates::attack)
	{
		if (cooldown <= 0.0f)
		{
			state = unitStates::idle;
			frame = 0;
		}
		frame = cooldown / attackTime * 4.0f - 1.0f;
		if (frame < 0)
			frame = 0;

		int Index = direction * 4 + frame;
		bodySprite.setTextureRect(sf::IntRect(bodyAttackTextures[Index]->x, bodyAttackTextures[Index]->y, bodyAttackTextures[Index]->Width, bodyAttackTextures[Index]->Height));

		if (helmet != nullptr)
		{
			helmetSprite.setTextureRect(sf::IntRect(helmetAttackTextures[Index]->x, helmetAttackTextures[Index]->y, helmetAttackTextures[Index]->Width, helmetAttackTextures[Index]->Height));
		}

		if (armor != nullptr)
		{
			armorSprite.setTextureRect(sf::IntRect(armorAttackTextures[Index]->x, armorAttackTextures[Index]->y, armorAttackTextures[Index]->Width, armorAttackTextures[Index]->Height));
		}

		if (pants != nullptr)
		{
			pantsSprite.setTextureRect(sf::IntRect(pantsAttackTextures[Index]->x, pantsAttackTextures[Index]->y, pantsAttackTextures[Index]->Width, pantsAttackTextures[Index]->Height));
		}

		if (rightHand != nullptr)
		{
			rightHandSprite.setTextureRect(sf::IntRect(rightHandAttackTextures[Index]->x, rightHandAttackTextures[Index]->y, rightHandAttackTextures[Index]->Width, rightHandAttackTextures[Index]->Height));
		}
		if (leftHand != nullptr)
		{
			leftHandSprite.setTextureRect(sf::IntRect(leftHandAttackTextures[Index]->x, leftHandAttackTextures[Index]->y, leftHandAttackTextures[Index]->Width, leftHandAttackTextures[Index]->Height));
		}
	}
	else if (state == unitStates::run)
	{
		calculateCurrentFrame(dt);
		state = unitStates::idle;

		int Index = direction * 4 + frame;

		if (direction == 0) position.y -= distance;
		if (direction == 1) position.x += distance;
		if (direction == 2) position.y += distance;
		if (direction == 3) position.x -= distance;

		bodySprite.setTextureRect(sf::IntRect(bodyRunTextures[Index]->x, bodyRunTextures[Index]->y, bodyRunTextures[Index]->Width, bodyRunTextures[Index]->Height));

		if (helmet != nullptr)
		{
			helmetSprite.setTextureRect(sf::IntRect(helmetRunTextures[Index]->x, helmetRunTextures[Index]->y, helmetRunTextures[Index]->Width, helmetRunTextures[Index]->Height));
		}
		if (armor != nullptr)
		{
			armorSprite.setTextureRect(sf::IntRect(armorRunTextures[Index]->x, armorRunTextures[Index]->y, armorRunTextures[Index]->Width, armorRunTextures[Index]->Height));
		}
		if (pants != nullptr)
		{
			pantsSprite.setTextureRect(sf::IntRect(pantsRunTextures[Index]->x, pantsRunTextures[Index]->y, pantsRunTextures[Index]->Width, pantsRunTextures[Index]->Height));
		}
		if (rightHand != nullptr)
		{
			rightHandSprite.setTextureRect(sf::IntRect(rightHandRunTextures[Index]->x, rightHandRunTextures[Index]->y, rightHandRunTextures[Index]->Width, rightHandRunTextures[Index]->Height));
		}
		if (leftHand != nullptr)
		{
			leftHandSprite.setTextureRect(sf::IntRect(leftHandRunTextures[Index]->x, leftHandRunTextures[Index]->y, leftHandRunTextures[Index]->Width, leftHandRunTextures[Index]->Height));
		}
	}
	else if (state == unitStates::idle) 
	{
		int Index = direction * 4 + frame;

		calculateCurrentFrame(dt);
		bodySprite.setTextureRect(sf::IntRect(bodyIdleTextures[Index]->x, bodyIdleTextures[Index]->y, bodyIdleTextures[Index]->Width, bodyIdleTextures[Index]->Height));

		if (helmet != nullptr)
		{
			helmetSprite.setTextureRect(sf::IntRect(helmetIdleTextures[Index]->x, helmetIdleTextures[Index]->y, helmetIdleTextures[Index]->Width, helmetIdleTextures[Index]->Height));
		}
		if (armor != nullptr)
		{
			armorSprite.setTextureRect(sf::IntRect(armorIdleTextures[Index]->x, armorIdleTextures[Index]->y, armorIdleTextures[Index]->Width, armorIdleTextures[Index]->Height));
		}
		if (pants != nullptr)
		{
			pantsSprite.setTextureRect(sf::IntRect(pantsIdleTextures[Index]->x, pantsIdleTextures[Index]->y, pantsIdleTextures[Index]->Width, pantsIdleTextures[Index]->Height));
		}
		if (rightHand != nullptr)
		{
			rightHandSprite.setTextureRect(sf::IntRect(rightHandIdleTextures[Index]->x, rightHandIdleTextures[Index]->y, rightHandIdleTextures[Index]->Width, rightHandIdleTextures[Index]->Height));
		}
		if (leftHand != nullptr)
		{
			leftHandSprite.setTextureRect(sf::IntRect(leftHandIdleTextures[Index]->x, leftHandIdleTextures[Index]->y, leftHandIdleTextures[Index]->Width, leftHandIdleTextures[Index]->Height));
		}
	}

	if (cooldown > 0.0f)
		cooldown -= dt;

	bodySprite.setPosition(position);

	helmetSprite.setPosition(position);
	armorSprite.setPosition(position);
	pantsSprite.setPosition(position);
	rightHandSprite.setPosition(position);
	leftHandSprite.setPosition(position);

	actionRangeArea.setPosition(position);

}

void Player::draw() {
	if (mouseIsHover) {
		window->draw(actionRangeArea);
		GameObject::draw();
	}

	window->draw(*colliders[0]->shape);	// TO-DO - to delete

	if (direction == 0) {
		// TOP
		window->draw(rightHandSprite);
		window->draw(leftHandSprite);
		window->draw(bodySprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);

	}

	if (direction == 1) {
		// RIGHT

		window->draw(leftHandSprite);
		window->draw(bodySprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		window->draw(rightHandSprite);
	}

	if (direction == 2) {
		// BOTTOM
		window->draw(bodySprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		window->draw(leftHandSprite);
		window->draw(rightHandSprite);
	}

	if (direction == 3) {
		// LEFT
		window->draw(rightHandSprite);
		window->draw(bodySprite);
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		window->draw(leftHandSprite);

	}

}

Player* player = nullptr;

void createPlayer() {
	player = new Player();
	gameObjects.push_back(player);

	//player->gainEXP(50 + 100 + 200 + 400 + 800 + 1600);

	//player->STRENGTH += 8;
	//player->DEXTERITY += 4;

	//player->SKILL_POINTS -= 12;

	player->gainEXP(40);
	player->HP = 10;
}
