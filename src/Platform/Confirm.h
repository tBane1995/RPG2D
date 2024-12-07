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

	Confirm(std::wstring text) : Dialog(DialogType::Confirm) {

		position = sf::Vector2f(0, 0);

		short width = 256;
		short height = 128;

		rect = sf::RectangleShape(sf::Vector2f(width, height));
		rect.setFillColor(panelColor_normal);
		sf::Vector2f pos;
		pos.x = position.x - width / 2.0f;
		pos.y = position.y - height / 2.0f;
		rect.setPosition(pos);

		textarea = new TextArea(text, pos, width);

		btn_yes = new ButtonWithText("tak", 17);
		btn_yes->setPosition(sf::Vector2f(position.x - 64 - btn_yes->rect.getSize().x/2.0f, position.y + 16));
		
		btn_no = new ButtonWithText("nie", 17);
		btn_no->setPosition(sf::Vector2f(position.x + 64 - btn_no->rect.getSize().x/2.0f, position.y + 16));

		value = ConfirmValue::Undefinded;
	}

	~Confirm() {
		if(textarea != nullptr)
			delete textarea;

		if(btn_yes != nullptr)
			delete btn_yes;

		if(btn_no != nullptr)
			delete btn_no;
	}

	void update(sf::Event& event) {

		btn_yes->unclick();
		btn_no->unclick();

		btn_yes->hover();
		btn_no->hover();

		if (btn_yes->click()) {
			value = ConfirmValue::True;
		}

		if (btn_no->click()) {
			value = ConfirmValue::False;
		}

		btn_yes->update(dt);
		btn_no->update(dt);
		
	}

	void draw() {
		window->draw(rect);
		textarea->draw();
		btn_yes->draw();
		btn_no->draw();
	}
};