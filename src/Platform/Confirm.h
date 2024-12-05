#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"

class TextArea;
class ButtonWithText;

class Confirm : public Dialog {
public:
	sf::Vector2f position;
	sf::RectangleShape rect;
	TextArea* textarea;
	ButtonWithText* btn_yes = nullptr;
	ButtonWithText* btn_no = nullptr;

	Confirm(std::wstring text);
	~Confirm();
};