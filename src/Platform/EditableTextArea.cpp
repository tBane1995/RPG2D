#include "EditableTextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"

#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

EditableTextArea::EditableTextArea(std::wstring text) : TextArea(text) {

	isSelected = false;

	last_action_time = currentTime;
	cursorState = CursorState::ShowCursor;
	std::string t = texts.back().getString() + "|";
	texts.back().setString(t);
}

EditableTextArea::~EditableTextArea() {

}

void EditableTextArea::update() {
	if (isSelected) {
		if ((currentTime - last_action_time).asSeconds() > 0.25f) {
			last_action_time = currentTime;

			if (cursorState == CursorState::ShowCursor) {
				cursorState = CursorState::HideCursor;
				std::string t = texts.back().getString();
				t = t.substr(0, t.length() - 1);
				texts.back().setString(t);
			}
			else {
				cursorState = CursorState::ShowCursor;
				std::string t = texts.back().getString() + "|";
				texts.back().setString(t);
			}
		}
	}
}

void EditableTextArea::update(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (rect.getGlobalBounds().contains(worldMousePosition)) {

				isSelected = true;
				cursorState = CursorState::ShowCursor;
			}
			else {
				isSelected = false;
				cursorState = CursorState::HideCursor;
			}
				
		}
	}
	else if (event.type == sf::Event::KeyPressed) {
		
		if (isSelected) {

			char sign;

			// LETTERS
			if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					sign = 'A' + event.key.code - sf::Keyboard::A;
				else
					sign = 'a' + event.key.code - sf::Keyboard::A;
			}

			if (event.key.code == sf::Keyboard::Space)
				sign = ' ';

			if (event.key.code == sf::Keyboard::BackSpace)
				sign = '\b';

			std::string t = texts.back().getString();
			if (sign != '\b')
				(cursorState == CursorState::ShowCursor) ? t.insert(t.length() - 1, 1, sign) : t = t + sign;
	
			texts.back().setString(t);
		}
	}
}

void EditableTextArea::draw() {

	window->draw(rect);

	window->draw(background);
	for (auto& t : texts)
		window->draw(t);
	
}