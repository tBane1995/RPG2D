#ifndef Player_hpp
#define Player_hpp

class Player : public GameObject {
public:
	Item* helmet;
	Item* armor;
	Item* pants;

	// TO-DO sf::Texture to Texture*
	// BODY
	string body;
	Texture* bodyIdleTextures[16];	// idle for top, right, bottom, left
	Texture* bodyRunTextures[16];	// run for top, right, bottom, left
	Texture* bodyAttackTextures[16];	// fight for top, right, bottom, left

	// HELMET
	Texture* helmetIdleTextures[16];
	Texture* helmetRunTextures[16];
	Texture* helmetAttackTextures[16];

	// ARMOR
	Texture* armorIdleTextures[16];
	Texture* armorRunTextures[16];
	Texture* armorAttackTextures[16];

	// PANTS
	Texture* pantsIdleTextures[16];
	Texture* pantsRunTextures[16];
	Texture* pantsAttackTextures[16];

	// SPRITES
	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;

	int direction;
	int frame;	// current frame number
	float stepSize;
	states state;
	float actionRange;
	float viewRange;
	sf::CircleShape actionRangeArea;
	
	float countdown;	 // timer to determine current frame
	float attackTime;
	float cooldown;

	Inventory* bag;

	float HP, HP_max;
	float MP, MP_max;
	int STRENGTH;
	int DEXTERITY;
	int INTELLIGENCE;

	Player() : GameObject("hero", 0, 0, 24, 12, true, false) {
		type = gameObjectType::Player;
		direction = 2;
		frame = 0;
		stepSize = 6.0f;
		countdown = 0.0f;
		state = states::idle;
		actionRange = 25.0f;
		cooldown = 0.0f;
		attackTime = 1.0f;

		position.x = 682;
		position.y = 226;

		isVisible = true;

		HP = 10;
		HP_max = 50;
		MP = 5;
		MP_max = 5;
		STRENGTH = 5;
		DEXTERITY = 5;
		INTELLIGENCE = 5;

		body = "sets/body/hero";
		
		helmet = nullptr;
		armor = getItem("items/torn shirt");
		pants = nullptr;

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();

		bag = new Inventory();
		bag->addItem("items/torn shirt");

		

		setActionRangeArea();

		
		
		toDelete = false;
		isVisible = false;
	}

	~Player() { }
	
	void setDirection(int direction) {
		this->direction = direction;
		frame = 0.0f;
	}

	void move() {
		state = states::walk;
	}

	void attack() {
		state = states::attack;
		frame = 0.0f;
		cooldown = attackTime;
	}

	void setPosition(float x, float y) {
		this->position.x = x;
		this->position.y = y;
	}

	void loadBody() {
		for (int i = 0; i < 16; i++) {
			bodyIdleTextures[i] = nullptr;
			bodyRunTextures[i] = nullptr;
			bodyAttackTextures[i] = nullptr;

		}

		for (int i = 0; i < 4; i++) {

			bodyIdleTextures[i] = getTexture(body + "/idleTop" + to_string(i));
			bodyIdleTextures[4 + i] = getTexture(body + "/idleRight" + to_string(i));
			bodyIdleTextures[8 + i] = getTexture(body + "/idleBottom" + to_string(i));
			bodyIdleTextures[12 + i] = getTexture(body + "/idleLeft" + to_string(i));

			bodyRunTextures[i] = getTexture(body + "/runTop" + to_string(i));
			bodyRunTextures[4 + i] = getTexture(body + "/runRight" + to_string(i));
			bodyRunTextures[8 + i] = getTexture(body + "/runBottom" + to_string(i));
			bodyRunTextures[12 + i] = getTexture(body + "/runLeft" + to_string(i));

			bodyAttackTextures[i] = getTexture(body + "/attackTop" + to_string(i));
			bodyAttackTextures[4 + i] = getTexture(body + "/attackRight" + to_string(i));
			bodyAttackTextures[8 + i] = getTexture(body + "/attackBottom" + to_string(i));
			bodyAttackTextures[12 + i] = getTexture(body + "/attackLeft" + to_string(i));

		}

		bodySprite = sf::Sprite();
		bodySprite.setOrigin(32, 58);

	}

	void loadHelmet() {

		for (int i = 0; i < 16; i++) {
			helmetIdleTextures[i] = nullptr;
			helmetRunTextures[i] = nullptr;
			helmetAttackTextures[i] = nullptr;

		}

		if (helmet != nullptr) {

			for (int i = 0; i < 4; i++) {
				helmetIdleTextures[i] = getTexture("sets/" + helmet->name + "/idleTop" + to_string(i));
				helmetIdleTextures[4 + i] = getTexture("sets/" + helmet->name + "/idleRight" + to_string(i));
				helmetIdleTextures[8 + i] = getTexture("sets/" + helmet->name + "/idleBottom" + to_string(i));
				helmetIdleTextures[12 + i] = getTexture("sets/" + helmet->name + "/idleLeft" + to_string(i));

				helmetRunTextures[i] = getTexture("sets/" + helmet->name + "/runTop" + to_string(i));
				helmetRunTextures[4 + i] = getTexture("sets/" + helmet->name + "/runRight" + to_string(i));
				helmetRunTextures[8 + i] = getTexture("sets/" + helmet->name + "/runBottom" + to_string(i));
				helmetRunTextures[12 + i] = getTexture("sets/" + helmet->name + "/runLeft" + to_string(i));

				helmetAttackTextures[i] = getTexture("sets/" + helmet->name + "/attackTop" + to_string(i));
				helmetAttackTextures[4 + i] = getTexture("sets/" + helmet->name + "/attackRight" + to_string(i));
				helmetAttackTextures[8 + i] = getTexture("sets/" + helmet->name + "/attackBottom" + to_string(i));
				helmetAttackTextures[12 + i] = getTexture("sets/" + helmet->name + "/attackLeft" + to_string(i));

			}
		}

		helmetSprite = sf::Sprite();
		helmetSprite.setOrigin(32, 58);

	}

	void loadArmor() {

		for (int i = 0; i < 16; i++) {
			armorIdleTextures[i] = nullptr;
			armorRunTextures[i] = nullptr;
			armorAttackTextures[i] = nullptr;

		}

		if (armor != nullptr) {
		
			cout << armor->name << "\n";

			for (int i = 0; i < 4; i++) {
				armorIdleTextures[i] = getTexture("sets/" + armor->name + "/idleTop" + to_string(i));
				armorIdleTextures[4 + i] = getTexture("sets/" + armor->name + "/idleRight" + to_string(i));
				armorIdleTextures[8 + i] = getTexture("sets/" + armor->name + "/idleBottom" + to_string(i));
				armorIdleTextures[12 + i] = getTexture("sets/" + armor->name + "/idleLeft" + to_string(i));

				armorRunTextures[i] = getTexture("sets/" + armor->name + "/runTop" + to_string(i));
				armorRunTextures[4 + i] = getTexture("sets/" + armor->name + "/runRight" + to_string(i));
				armorRunTextures[8 + i] = getTexture("sets/" + armor->name + "/runBottom" + to_string(i));
				armorRunTextures[12 + i] = getTexture("sets/" + armor->name + "/runLeft" + to_string(i));

				armorAttackTextures[i] = getTexture("sets/" + armor->name + "/attackTop" + to_string(i));
				armorAttackTextures[4 + i] = getTexture("sets/" + armor->name + "/attackRight" + to_string(i));
				armorAttackTextures[8 + i] = getTexture("sets/" + armor->name + "/attackBottom" + to_string(i));
				armorAttackTextures[12 + i] = getTexture("sets/" + armor->name + "/attackLeft" + to_string(i));

			}
		}

		armorSprite = sf::Sprite();
		armorSprite.setOrigin(32, 58);
	}

	void loadPants() {

		for (int i = 0; i < 16; i++) {
			pantsIdleTextures[i] = nullptr;
			pantsRunTextures[i] = nullptr;
			pantsAttackTextures[i] = nullptr;

		}

		if (pants != nullptr) {

			for (int i = 0; i < 4; i++) {
				pantsIdleTextures[i] = getTexture("sets/" + pants->name + "/idleTop" + to_string(i));
				pantsIdleTextures[4 + i] = getTexture("sets/" + pants->name + "/idleRight" + to_string(i));
				pantsIdleTextures[8 + i] = getTexture("sets/" + pants->name + "/idleBottom" + to_string(i));
				pantsIdleTextures[12 + i] = getTexture("sets/" + pants->name + "/idleLeft" + to_string(i));

				pantsRunTextures[i] = getTexture("sets/" + pants->name + "/runTop" + to_string(i));
				pantsRunTextures[4 + i] = getTexture("sets/" + pants->name + "/runRight" + to_string(i));
				pantsRunTextures[8 + i] = getTexture("sets/" + pants->name + "/runBottom" + to_string(i));
				pantsRunTextures[12 + i] = getTexture("sets/" + pants->name + "/runLeft" + to_string(i));

				pantsAttackTextures[i] = getTexture("sets/" + pants->name + "/attackTop" + to_string(i));
				pantsAttackTextures[4 + i] = getTexture("sets/" + pants->name + "/attackRight" + to_string(i));
				pantsAttackTextures[8 + i] = getTexture("sets/" + pants->name + "/attackBottom" + to_string(i));
				pantsAttackTextures[12 + i] = getTexture("sets/" + pants->name + "/attackLeft" + to_string(i));

			}
		}

		pantsSprite = sf::Sprite();
		pantsSprite.setOrigin(32, 58);

	}

	void setActionRangeArea() {
		actionRangeArea = sf::CircleShape(actionRange + collider->width/2.0f);
		actionRangeArea.setFillColor(sf::Color(128, 64, 64, 128));
		actionRangeArea.setOutlineColor(sf::Color(196, 64, 64, 128));
		actionRangeArea.setOutlineThickness(4.0f);
		actionRangeArea.setOrigin(actionRange + collider->width / 2.0f, actionRange + collider->width/2.0f);
		actionRangeArea.setScale(1.0f, collider->height/collider->width);
	}


	void calculateCurrentFrame(float dt) {
		countdown -= dt;
		while (countdown <= 0.0f) {
			countdown += 1.0f / 8.0f;	// 8 FPS
			frame += 1;
		}

		if (frame > 3)
			frame = frame % 4;
	}

	void takeDamage(float damage) {

		int defend = 0;

		if (armor != nullptr)
			defend += armor->attributes[attribute::DEFEND];

		if (helmet != nullptr)
			defend += helmet->attributes[attribute::DEFEND];

		if (pants != nullptr)
			defend += pants->attributes[attribute::DEFEND];

		int dam = damage - defend;

		if (dam > 0) {
			HP = HP - dam;

			if (HP < 0)
				HP = 0;
		}
	}
	
	float getDamage() {
		return STRENGTH * 3 + DEXTERITY;
	}

	void heal(float HP) {
		this->HP += HP;

		if (this->HP > HP_max)
			this->HP = HP_max;
	}

	void collectItem(Item* item, int count = 1) {

		bag->addItem(item,count);
	}

	void update(float dt) {

		GameObject::update(dt);

		float distance = 20.0f * stepSize * dt;

		if (state == states::attack) {
		
			if (cooldown <= 0.0f)
			{
				state = states::idle;
				frame = 0;
			}
			frame = cooldown / attackTime * 4.0f - 1.0f;
			if (frame < 0)
				frame = 0;

			bodySprite.setTexture(*bodyAttackTextures[direction * 4 + frame]->texture);
			
			if(helmet!=nullptr)
				helmetSprite.setTexture(*helmetAttackTextures[direction * 4 + frame]->texture);
			
			if(armor!=nullptr)
				armorSprite.setTexture(*armorAttackTextures[direction * 4 + frame]->texture);
			
			if(pants!=nullptr)
				pantsSprite.setTexture(*pantsAttackTextures[direction * 4 + frame]->texture);
		}		
		else if (state == states::walk) {

			calculateCurrentFrame(dt);
			state = states::idle;

			if (direction == 0) position.y -= distance;
			if (direction == 1) position.x += distance;
			if (direction == 2) position.y += distance;
			if (direction == 3) position.x -= distance;

			bodySprite.setTexture(*bodyRunTextures[direction * 4 + frame]->texture);
			
			if(helmet!=nullptr)
				helmetSprite.setTexture(*helmetRunTextures[direction * 4 + frame]->texture);
			
			if(armor!=nullptr)
				armorSprite.setTexture(*armorRunTextures[direction * 4 + frame]->texture);
			
			if(pants!=nullptr)
				pantsSprite.setTexture(*pantsRunTextures[direction * 4 + frame]->texture);
		}
		else if(state == states::idle) {

			calculateCurrentFrame(dt);
			bodySprite.setTexture(*bodyIdleTextures[direction * 4 +frame]->texture);
			
			if(helmet!=nullptr)
				helmetSprite.setTexture(*helmetIdleTextures[direction * 4 +frame]->texture);
			
			if(armor!=nullptr)
				armorSprite.setTexture(*armorIdleTextures[direction * 4 +frame]->texture);
			
			if(pants!=nullptr)
				pantsSprite.setTexture(*pantsIdleTextures[direction * 4 +frame]->texture);
			
		}

		if (cooldown > 0.0f)
			cooldown -= dt;

		bodySprite.setPosition(position);
		helmetSprite.setPosition(position);
		armorSprite.setPosition(position);
		pantsSprite.setPosition(position);
		actionRangeArea.setPosition(position);
		
	}

	void draw(sf::RenderWindow* window) {
		if (mouseIsOver) {
			window->draw(actionRangeArea);
			GameObject::draw(window);
		}
		
		window->draw(bodySprite);		
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);		
		
		
	}
};

Player* player = nullptr;

void createPlayer() {
	player = new Player();
	gameObjects.push_back(player);
}
#endif