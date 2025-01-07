#include "Doors.h"
#include "Textures.h"
#include "Time.h"
#include "GameObjects.h"
#include "Window.h"
#include "Player.h"
#include "Collisions.h"

Door::Door(std::string name, float width, float length, float height, float width_left, float width_right) : GameObject(name, 0, 0, width, length, height, width_left, width_right) {

	type = GameObjectType::Door;

	state = DoorState::Close;
	textures = getTexturesSet(name);
	this->texture = textures[0];
	current_frame = 0;

	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, textures[0]);
	sprite.setOrigin(textures[0]->cx, textures[0]->getSize().y - 1);

	takeItTexture = getSingleTexture("GUI/hand");
	takeItSprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&takeItSprite, takeItTexture);
	takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
	showHand = false;
}

Door::Door(GameObject* object, float x, float y) : GameObject(object, x, y) {

	type = GameObjectType::Door;

	state = DoorState::Close;
	textures = getTexturesSet(name);
	this->texture = textures[0];
	current_frame = 0;

	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, textures[0]);
	sprite.setOrigin(dynamic_cast<Door*>(object)->sprite.getOrigin());
	sprite.setPosition(position.x, position.y);

	takeItTexture = getSingleTexture("GUI/hand");
	takeItSprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&takeItSprite, takeItTexture);
	takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
	showHand = false;

	textname.setPosition(position.x, position.y - height - 3);
	takeItSprite.setPosition(position.x, position.y - 50);
}

void Door::open() {
	state = DoorState::Opening;
	last_action_time = currentTime;
}


void Door::close() {
	state = DoorState::Closing;
	float width = sprite.getGlobalBounds().getSize().x - colliders[0]->width - colliders[1]->width;
	colliders.push_back(new Collider(width, colliders[0]->length, position, 0, -8, ColliderType::Rectangle));
	last_action_time = currentTime;
}

bool Door::playerNextTo() {

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

void Door::update() {

	GameObject::update();

	(playerNextTo()) ? showHand = true : showHand = false;

	if ((currentTime - last_action_time).asSeconds() > 0.5f) {
		if (state == DoorState::Opening) {
			current_frame += 1;
			last_action_time = currentTime;
			SingleTexture::SetTextureForSprite(&sprite, textures[current_frame]);

			if (current_frame == textures.size() - 1) {
				state = DoorState::Open;
				delete colliders.back();
				colliders.pop_back();
			}
		}
		else if (state == DoorState::Closing) {
			current_frame -= 1;
			last_action_time = currentTime;
			SingleTexture::SetTextureForSprite(&sprite, textures[current_frame]);

			if (current_frame == 0) {
				state = DoorState::Close;
			}
		}
		else if (state == DoorState::Open) {
			close();
		}
		else if (state == DoorState::Close) {
			open();
		}

	}

	
}

void Door::drawStatistics() {
	GameObject::drawStatistics();
}

void Door::draw() {

	window->draw(sprite);

	if (showHand)
		window->draw(takeItSprite);

}

std::vector < Door* > doors;
