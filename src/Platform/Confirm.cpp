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
	rect.setPosition(cam->position.x+pos.x+borderWidth, cam->position.y+pos.y+borderWidth);

	sf::Vector2f textpos = sf::Vector2f(pos.x + borderWidth + margin, pos.y + borderWidth + margin);
	textarea = new TextArea(text, textpos, width-2*borderWidth-2*margin);

	textarea->setTextColor(textColor);
	textarea->setBackgroundColor(sf::Color::Transparent);
	textarea->setRectColor(panelColor_medium);

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

void Confirm::handleEvent(sf::Event& event) {
	btn_yes->handleEvent(event);
	btn_no->handleEvent(event);

	if (btn_yes->state == ButtonState::Pressed)
		value = ConfirmValue::True;

	if (btn_no->state == ButtonState::Pressed)
		value = ConfirmValue::False;
}

void Confirm::update() {
	btn_yes->update();
	btn_no->update();
}

void Confirm::draw() {
	window->draw(rect);
	textarea->draw();
	btn_yes->draw();
	btn_no->draw();
}