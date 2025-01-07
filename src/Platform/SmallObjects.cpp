#include "SmallObjects.h"
#include "Window.h"
#include "Textures.h"

SmallObject::SmallObject(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
	type = GameObjectType::SmallObject;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
}

SmallObject::SmallObject(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::SmallObject;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);

}

SmallObject::~SmallObject() {

}

void SmallObject::setPosition(sf::Vector2f position) {
	this->position = position;
	sprite.setPosition(position);
}

void SmallObject::update() {

}

void SmallObject::drawStatistics() {
	GameObject::drawStatistics();
}

void SmallObject::draw() {

	window->draw(sprite);
}
std::vector < SmallObject* > smallObjects;
