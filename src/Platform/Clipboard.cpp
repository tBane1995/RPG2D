#include "Clipboard.h"
#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "GameObjects.h"
#include "GameObjectsManager.h"
#include "TerrainAndFloors.h"
#include "PrefabToPaint.h"
#include "Palette.h"
#include <iostream>



Clipboard::Clipboard() {
	clear();
}

Clipboard::~Clipboard() {
	clear();
}

void Clipboard::clear() {
	for (auto& object : _objects)
		delete object;

	_objects.clear();
}

void Clipboard::copy() {
	std::cout << "copy\n";
	clear();

	_position.x = short(worldMousePosition.x) / short(tileSide) * short(tileSide);
	_position.y = short(worldMousePosition.y) / short(tileSide) * short(tileSide);

	std::cout << "clipboard position: x= " << _position.x << " y=" << _position.y << "\n";
	for (auto& so : selectedGameObjects) {

		_objects.push_back(getNewGameObject(so));
	}

	std::cout << "zawartosc schowka:\n";
	for (auto& o : _objects) {
		std::cout << o->name << " x=" << o->position.x << " y=" << o->position.y << "\n";
	}
}

void Clipboard::cut() {
	std::cout << "cut\n";
	copy();

	// TO-DO - remove objects
}

void Clipboard::paste() {
	std::cout << "paste\n";
	std::cout << "size: " << _objects.size() << "\n";
	tool = toolType::AddGameObject;

	clearPrefabsToPaint();

	for (auto& so : _objects) {
		prefabsToPaint.push_back(getNewGameObject(so));
	}
}

Clipboard* clipboard = nullptr;
