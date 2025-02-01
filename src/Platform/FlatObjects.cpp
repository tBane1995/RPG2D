#include "FlatObjects.h"
#include "Textures.h"
#include "Window.h"
#include "Mouse.h"
#include "Collisions.h"

std::vector < FlatObject* > flatObjects;

FlatObject::FlatObject(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
	type = GameObjectType::FlatObject;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
}

FlatObject::FlatObject(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::FlatObject;
	texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);

}

FlatObject::~FlatObject() {

}

void FlatObject::setPosition(sf::Vector2f position) {
	GameObject::setPosition(position);
	sprite.setPosition(position);
}

void FlatObject::update() {
	GameObject::update();
}

void FlatObject::drawStatistics() {
	GameObject::drawStatistics();
}

void FlatObject::draw() {

	window->draw(sprite);
}

bool isPathOnPosition( float x, float y) {
	// TO-DO
	for (auto& path : flatObjects) {
		if (pointInEllipse(x, y, path->position.x, path->position.y, path->colliders[0]->width/2.0f, path->colliders[0]->length / 2.0f))
			return true;
	}

	return false;
}
