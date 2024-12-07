#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"
#include "Theme.h"
#include "Window.h"
#include "TextArea.h"
#include "Buttons.h"
#include "Time.h"

class TextArea;
class ButtonWithText;

enum class ConfirmValue { Undefinded, True, False };

class Confirm : public Dialog {
public:
	sf::Vector2f position;
	sf::RectangleShape rect;
	TextArea* textarea;
	ButtonWithText* btn_yes;
	ButtonWithText* btn_no;
	ConfirmValue value;

	Confirm(std::wstring text);
	~Confirm();
	void update(sf::Event& event);
	void draw();
};