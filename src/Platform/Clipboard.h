#pragma once
#include <SFML/Graphics.hpp>

class GameObject;

class Clipboard {
public:
	sf::Vector2f _position;
	std::vector < GameObject* > _objects;

	Clipboard();
	~Clipboard();
	void clear();
	void copy();
	void cut();
	void paste();
};

extern Clipboard* clipboard;
