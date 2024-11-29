#ifndef Doors_hpp
#define Doors_hpp

enum class doorState { open, opening, close, closing };

class Door : public GameObject {
public:
	std::vector < SingleTexture* > textures;
	sf::Sprite sprite;
	sf::Time last_action_time;
	short current_frame;
	doorState state;
	SingleTexture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Door(string name, float width, float length, float height, float width_left, float width_right) : GameObject(name, 0, 0, width, length, height, width_left, width_right) {
		
		type = GameObjectType::Door;

		state = doorState::close;
		textures = getTexturesSet(name);
		this->texture = textures[0];
		current_frame = 0;

		sprite = sf::Sprite();
		sprite.setTexture(*textures[0]->texture);
		sprite.setOrigin(textures[0]->cx, textures[0]->texture->getSize().y - 1);

		takeItTexture = getSingleTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

	}

	Door(GameObject* object, float x, float y) : GameObject(object, x, y) {

		type = GameObjectType::Door;
		
		state = doorState::close;
		textures = getTexturesSet(name);
		this->texture = textures[0];
		current_frame = 0;

		sprite = sf::Sprite();
		sprite.setTexture(*textures[0]->texture);
		sprite.setOrigin(dynamic_cast<Door*>(object)->sprite.getOrigin());
		sprite.setPosition(position.x, position.y);

		takeItTexture = getSingleTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

		textname.setPosition(position.x, position.y - height - 3);
		takeItSprite.setPosition(position.x, position.y - 50);
	}

	virtual ~Door() {
	
	}

	void open() {
		state = doorState::opening;
		last_action_time = currentTime;
	}

	void close() {
		state = doorState::closing;
		float width = sprite.getGlobalBounds().getSize().x - colliders[0]->width - colliders[1]->width;
		colliders.push_back(new Collider(width, colliders[0]->length, position, 0, -8, ColliderType::Rectangle));
		last_action_time = currentTime;
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

		GameObject::update(dt);

		(playerNextTo()) ? showHand = true : showHand = false;

		if (state == doorState::opening) {

			if ((currentTime - last_action_time).asSeconds() > 0.5f) {
				current_frame += 1;
				last_action_time = currentTime;
				sprite.setTexture(*textures[current_frame]->texture);

				if (current_frame == textures.size() - 1) {
					state = doorState::open;
					delete colliders.back();
					colliders.pop_back();
				}
			}

		}

		if (state == doorState::closing) {
			if ((currentTime - last_action_time).asSeconds() > 0.5f) {
				current_frame -= 1;
				last_action_time = currentTime;
				sprite.setTexture(*textures[current_frame]->texture);

				if (current_frame == 0) {
					state = doorState::close;
				}
			}
		}

	}

	virtual void draw() {
		if (mouseIsHover)
			GameObject::draw();

		for(auto& col :colliders)
			window->draw(*col->shape);

		window->draw(sprite);

		if (showHand)
			window->draw(takeItSprite);
		
	}
};

std::vector < Door* > doors;

#endif