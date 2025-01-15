#pragma once

#include <SFML/Graphics.hpp>
#include "Buttons.h"
#include "GameObjects.h"
enum class ContextMenuState { Idle, Closing, Close };

class ContextMenu {
public:
	ContextMenuState _state;
	sf::Vector2f _position;
	std::vector < ButtonWithTextAndIcon* > _buttons;

	ContextMenu(GameObject* object);
	~ContextMenu();
	void loadDefaultMenu();
	void loadCharacterMenu(GameObject* object);
	void loadBuildingMenu(GameObject* object);
	void loadObjectMenu(GameObject* object);

	void handleEvent(sf::Event& event);
	void update();
	void draw();

};

extern ContextMenu* context_menu;
