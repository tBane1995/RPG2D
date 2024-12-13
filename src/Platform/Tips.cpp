#include "Tips.h"

#include "Buttons.h"
#include "TextArea.h"
#include "Window.h"
#include "Time.h"
#include "Textures.h"

Tip::Tip(std::wstring tip, ButtonWithImage* btn) {
		
	this->btn = btn;

	hover_start = currentTime;

	if (btn == nullptr) {
		position.x = 0;
		position.y = 0;
	}
	else
	{
		position.x = btn->position.x - btn->texture->getSize().x/2.0f;
		position.y = btn->position.y + btn->texture->getSize().y/2.0f;
	}
		

	text = new TextArea(tip, position);
	text->background.setOutlineThickness(2.0f);
	text->background.setOutlineColor(sf::Color::Black);
	
	if (this->position.x + text->background.getSize().x >= screenWidth / 2.0f) {
		this->position.x = screenWidth/2.0f - text->background.getSize().x;
		text->setPosition(this->position);
	}
}

Tip::Tip(std::wstring tip, sf::Vector2f position, ButtonWithImage* btn) {

	this->btn = btn;

	hover_start = currentTime;

	this->position = position;

	text = new TextArea(tip, position);
	text->background.setOutlineThickness(2.0f);
	text->background.setOutlineColor(sf::Color::Black);

	if (this->position.x + text->background.getSize().x >= screenWidth / 2.0f) {
		this->position.x = screenWidth/2.0f - text->background.getSize().x;
		text->setPosition(this->position);
	}
}

void Tip::update() {
	text->setPosition(position);
	text->update();
}

void Tip::draw() {
	if ((currentTime - hover_start).asSeconds() > 0.5f)
		text->draw();
}

Tip* tip = nullptr;
