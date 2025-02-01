#include "Furnitures.h"
#include "Mouse.h"
#include "Player.h"
#include "Textures.h"
#include "Items.h"
#include "Collisions.h"
#include "Window.h"

Furniture::Furniture(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Rectangle) {
	type = GameObjectType::Furniture;
		
	texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);

	inventory = nullptr;
	takeItTexture = getSingleTexture("GUI/hand");
	takeItSprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&takeItSprite, takeItTexture);
	takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
	showHand = false;
}
	
Furniture::Furniture(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::Furniture;
		
	texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);

	inventory = nullptr;
		
	takeItTexture = getSingleTexture("GUI/hand");
	takeItSprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&takeItSprite, takeItTexture);
	takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
	showHand = false;

	sprite.setPosition(position);
	takeItSprite.setPosition(position.x, position.y - 50);
}

Furniture::~Furniture() {

}

void Furniture::setPosition(sf::Vector2f position) {
	GameObject::setPosition(position);
	sprite.setPosition(position);
}


void Furniture::update() {

		
	showHand = false;

	if (player != nullptr) {

		if (inventory != nullptr) {

			// SHOW HAND
			float x1, y1, rx1, ry1;
			float x2, y2, rx2, ry2;
				
			x1 = player->position.x;
			y1 = player->position.y;
			rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
			ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

			x2 = position.x;
			y2 = position.y;
			rx2 = colliders[0]->width;
			ry2 = colliders[0]->length;

			if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1)) {
				showHand = true;

				if (inventory->items.size() > 0)
				{
					SingleTexture::SetTextureForSprite(&takeItSprite, getSingleTexture("GUI/hand"));
				}
				else
				{
					SingleTexture::SetTextureForSprite(&takeItSprite, getSingleTexture("GUI/grey_hand"));
				}
			}

		}

	}

	// TO-DO
	if (player == nullptr) {
		if (inventory != nullptr) {
			if (pointInRectangle(worldMousePosition.x, worldMousePosition.y, position.x, position.y, colliders[0]->width, colliders[0]->length)) {
				showHand = true;
			}
		}
	}
	//

}

void Furniture::drawStatistics() {
	GameObject::drawStatistics();
}

void Furniture::draw() {

	window->draw(sprite);

	if (showHand)
		window->draw(takeItSprite);
}

std::vector < Furniture* > furnitures;
