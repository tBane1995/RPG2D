#include "EditableTextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"

#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

EditableTextArea::EditableTextArea(std::wstring text) : TextArea(text) {

	isSelected = true;
}

EditableTextArea::~EditableTextArea() {

}

void EditableTextArea::update(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			(rect.getGlobalBounds().contains(worldMousePosition)) ? isSelected = true : isSelected = false;
		}
	}
}

void EditableTextArea::draw() {

	window->draw(rect);
	window->draw(background);
	for (auto& t : texts)
		window->draw(t);
	
}