#include "Clipboard.h"
#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "GameObjects.h"
#include "GameObjectsManager.h"
#include "TerrainAndFloors.h"
#include "PrefabToPaint.h"
#include "Palette.h"
#include "Painter.h"
#include <iostream>



Clipboard::Clipboard() {
	clear();
	_state = ClipboardState::Idle;
}

Clipboard::~Clipboard() {
	clear();
}

void Clipboard::clear() {
	for (auto& object : _objects) {
		delete object->_object;
		delete object;
	}

	_objects.clear();
}

void Clipboard::copy() {
	std::cout << "copy\n";
	_state = ClipboardState::Copy;

	clear();

	// calculate center point
	sf::Vector2f center(0, 0);
	for (auto& so : selectedGameObjects) {
		center.x += so->_object->position.x;
		center.y += so->_object->position.y;
	}

	center.x /= selectedGameObjects.size();
	center.y /= selectedGameObjects.size();

	// copying the Selected GameObjects and set the offset
	for (auto& so : selectedGameObjects) {

		MouseMovedGameObject* object = new MouseMovedGameObject(getNewGameObject(so->_object));
		sf::Vector2f offset = sf::Vector2f(so->_object->position.x - center.x, so->_object->position.y - center.y);
		object->setOffset(offset);
		_objects.push_back(object);
	}

	std::cout << "zawartosc schowka:\n";
	for (auto& o : _objects) {
		std::cout << o->_object->name << " x=" << o->_object->position.x << " y=" << o->_object->position.y << "\n";
	}
}

void Clipboard::cut() {
	std::cout << "cut\n";
	_state = ClipboardState::Cut;
	copy();

	// TO-DO - remove objects
}

void Clipboard::paste() {
	std::cout << "paste\n";
	_state = ClipboardState::Pase;
	std::cout << "size: " << _objects.size() << "\n";
	tool = toolType::AddGameObject;

	// paste GameObjects
	std::vector < MouseMovedGameObject* > objects_to_paste;
	sf::Vector2f offset;
	for (auto& obj : _objects) {
		MouseMovedGameObject* mv = new MouseMovedGameObject(getNewGameObject(obj->_object));
		mv->setOffset(obj->_offset);
		mv->update();
		objects_to_paste.push_back(mv);
	}

	addGameObjectsToMapAndLists(objects_to_paste, true);
}

void Clipboard::update() {
	_state = ClipboardState::Idle;
}

Clipboard* clipboard = nullptr;
