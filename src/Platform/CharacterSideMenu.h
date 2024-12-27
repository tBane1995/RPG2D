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
enum class CharacterSideMenuState { Idle, Close };

class CharacterSideMenu {
public:
	Character* _character;
	CharacterSideMenuState state;

	ButtonWithImage* btn_info;
	ButtonWithImage* btn_remove;
	ButtonWithImage* btn_cancel;

	CharacterSideMenu(Character* character);
	~CharacterSideMenu();
	virtual void update();
	virtual void handleEvent(sf::Event& event);
	virtual void draw();

};

extern CharacterSideMenu* character_side_menu;
