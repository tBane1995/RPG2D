#include "MouseMovedGameObjects.h"
#include "GameObjects.h"
#include "Mouse.h"
#include "TerrainAndFloors.h"

MouseMovedGameObject::MouseMovedGameObject(GameObject* object) {
	_object = object;
	_offset = sf::Vector2f(0, 0);
}

MouseMovedGameObject::~MouseMovedGameObject() {

}


void MouseMovedGameObject::setOffset(sf::Vector2f offset) {
	_offset = offset;
}

void MouseMovedGameObject::update() {
	sf::Vector2f pos;
	pos.x = short(worldMousePosition.x + _offset.x) / short(tileSide) * short(tileSide);
	pos.y = short(worldMousePosition.y + _offset.y) / short(tileSide) * short(tileSide);

	_object->setPosition(pos);
}

void MouseMovedGameObject::draw() {
	_object->draw();
}