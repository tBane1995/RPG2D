#ifndef Doors_hpp
#define Doors_hpp

enum class doorState { open, opening, close, closing };

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

	Door(string name) : GameObject(name, 0, 0, 64, 16, 64, 12, 12) {
		state = doorState::close;
		type = GameObjectType::Door;

		this->textureOpen = getSingleTexture("buildings/parts/door_open");
		this->textureClose = getSingleTexture("buildings/parts/door_close");
		this->texture = textureClose;
		
		sprite = sf::Sprite();
		sprite.setTexture(*textureClose->texture);
		sprite.setOrigin(textureClose->cx, textureClose->texture->getSize().y-1);

		takeItTexture = getSingleTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

		colliders[0]->shape->setPosition(colliders[0]->position.x, colliders[0]->position.y-8);
		colliders[1]->shape->setPosition(colliders[1]->position.x, colliders[1]->position.y-8);

	}

	Door(GameObject* object, float x, float y) : GameObject(object, x, y) {
		state = doorState::close;
		
		type = GameObjectType::Door;
		
		this->textureClose = dynamic_cast<Door*>(object)->textureClose;
		this->textureOpen = dynamic_cast<Door*>(object)->textureOpen;
		this->texture = textureClose;

		sprite = sf::Sprite();
		sprite.setTexture(*textureClose->texture);
		sprite.setOrigin(dynamic_cast<Door*>(object)->sprite.getOrigin());
		sprite.setPosition(position.x, position.y);

		takeItTexture = getSingleTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

		colliders[0]->shape->setPosition(colliders[0]->position.x, colliders[0]->position.y-8);
		colliders[1]->shape->setPosition(colliders[1]->position.x, colliders[1]->position.y-8);

		textname.setPosition(position.x, position.y - height);
		takeItSprite.setPosition(position.x, position.y - 50);

	}

	virtual ~Door() {
	
	}

	void open() {
		startActionTime = currentTime;
		state = doorState::opening;
	}

	void close() {
		startActionTime = currentTime;
		state = doorState::closing;
		collisioning = true;
	}

	bool playerNextTo() {

		if (player == nullptr)
			return false;

		float x1, y1, rx1, ry1;
		float x2, y2, rx2, ry2;
		float x3, y3, rx3, ry3;

		x1 = player->position.x;
		y1 = player->position.y;
		rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
		ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

		x3 = player->position.x;
		y3 = player->position.y;
		rx3 = (player->colliders[0]->width / 2.0f);
		ry3 = (player->colliders[0]->length / 2.0f);

		x2 = position.x;
		y2 = position.y;
		rx2 = colliders[0]->width;
		ry2 = colliders[0]->length;

		if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1) && !intersectionRectangleWithElipse(x2, y2, rx2, ry2, x3, y3, rx3, ry3))
			return true;
		else
			return false;
	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) {

		(playerNextTo()) ? showHand = true : showHand = false;

		if (state == doorState::opening) {
			if ((currentTime - startActionTime).asSeconds() > 0.5f) {
				state = doorState::open;
				sprite.setTexture(*textureOpen->texture);
				collisioning = false;
			}
		}

		if (state == doorState::closing) {
			if ((currentTime - startActionTime).asSeconds() > 0.5f) {
				state = doorState::close;
				sprite.setTexture(*textureClose->texture);

			} 
		}

	}

	virtual void draw() {
		if (mouseIsHover)
			GameObject::draw();

		window->draw(sprite);

		if (showHand)
			window->draw(takeItSprite);
		
	}
};

std::vector < Door* > doors;

#endif