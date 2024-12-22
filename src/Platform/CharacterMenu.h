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

enum class CharacterMenuState { Idle, Close };

class CharacterMenu {
public:
	Character* character;
	CharacterMenuState state;

	ButtonWithImage* btn_info;
	ButtonWithImage* btn_remove;
	ButtonWithImage* btn_cancel;

	CharacterMenu(Character* character);
	~CharacterMenu();
	void update();
	void handleEvent(sf::Event& event);
	void draw();

};

extern CharacterMenu* character_menu;
