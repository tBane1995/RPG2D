#include "Confirm.h"
#include "Buttons.h"
#include "TextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"
#include "Theme.h"
#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

Confirm::Confirm(std::wstring text) : Dialog(DialogType::Confirm) {

	position = sf::Vector2f(0, 0);

	short width = 256;
	short height = 128;
	
	rect = sf::RectangleShape(sf::Vector2f(width-2*borderWidth, height-2*borderWidth));
	rect.setFillColor(panelColor_normal);
	rect.setOutlineThickness(borderWidth);
	rect.setOutlineColor(panelColor_dark);

	sf::Vector2f pos;
	pos.x = position.x - width / 2.0f;
	pos.y = position.y - height / 2.0f;
	rect.setPosition(pos.x+borderWidth, pos.y+borderWidth);

	sf::Vector2f textpos = sf::Vector2f(pos.x + borderWidth + margin, pos.y + borderWidth + margin);
	textarea = new TextArea(text, textpos, width-2*borderWidth-2*margin);

	btn_yes = new ButtonWithText("tak", 17);
	btn_yes->setPosition(sf::Vector2f(position.x - 64 - btn_yes->rect.getSize().x / 2.0f, position.y + 16));

	btn_no = new ButtonWithText("nie", 17);
	btn_no->setPosition(sf::Vector2f(position.x + 64 - btn_no->rect.getSize().x / 2.0f, position.y + 16));

	value = ConfirmValue::Undefinded;
}

Confirm::~Confirm() {
	if (textarea != nullptr)
		delete textarea;

	if (btn_yes != nullptr)
		delete btn_yes;

	if (btn_no != nullptr)
		delete btn_no;
}

void Confirm::update(sf::Event& event) {

	btn_yes->unclick();
	btn_no->unclick();

	btn_yes->hover();
	btn_no->hover();

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {

			if (btn_yes->click()) {
				value = ConfirmValue::True;
			}

			if (btn_no->click()) {
				value = ConfirmValue::False;
			}

		}
	}


	

	btn_yes->update(dt);
	btn_no->update(dt);

}

void Confirm::draw() {
	window->draw(rect);
	textarea->draw();
	btn_yes->draw();
	btn_no->draw();
}