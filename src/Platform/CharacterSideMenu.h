#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"
#include "Panel.h"
#include "Theme.h"
#include "Window.h"
#include "Camera.h"
#include "Buttons.h"
#include "Character.h"
#include "Textures.h"

enum class GameObjectSideMenuState { Idle, Close };

class GameObjectSideMenu {
public:
	GameObject* _object;
	GameObjectSideMenuState _state;
	std::vector < ButtonWithImage* > _buttons;

	GameObjectSideMenu(GameObject* object);
	~GameObjectSideMenu();
	void loadCharacterSideMenu(GameObject* object);
	void loadBuildingSideMenu(GameObject* object);
	virtual void handleEvent(sf::Event& event);
	virtual void update();
	virtual void draw();

};

extern GameObjectSideMenu* gameobject_side_menu;
