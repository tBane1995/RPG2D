#pragma once
#include <SFML/Graphics.hpp>
#include "MouseMovedGameObjects.h"

class GameObject;

enum class ClipboardState { Idle, Copy, Paste, Cut };

class Clipboard {
public:
	sf::Vector2f _position;
	ClipboardState _state;
	std::vector < MouseMovedGameObject* > _objects;

	Clipboard();
	~Clipboard();
	void clear();
	void copy();
	void cut();
	void paste();
	void update();
};

extern Clipboard* clipboard;
