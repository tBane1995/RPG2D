#pragma once
#include <SFML/Graphics.hpp>
#include "MouseMovedGameObjects.h"

class GameObject;

class Clipboard {
public:
	sf::Vector2f _position;
	std::vector < MouseMovedGameObject* > _objects;

	Clipboard();
	~Clipboard();
	void clear();
	void copy();
	void cut();
	void paste();
};

extern Clipboard* clipboard;
