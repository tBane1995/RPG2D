#include "EditableTextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"

#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

EditableTextArea::EditableTextArea(std::wstring text) : TextArea(text) {

	editable_text = text;
	isSelected = false;
	cursor_position = editable_text.size();
	last_action_time = currentTime;
	cursorState = CursorState::ShowCursor;
}

EditableTextArea::~EditableTextArea() {

}

void EditableTextArea::update(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (rect.getGlobalBounds().contains(worldMousePosition)) {

				isSelected = true;
				cursorState = CursorState::ShowCursor;
				cursor_position = editable_text.size();
				std::cout << "TextArea is selected\n";
			}
			else {
				isSelected = false;
				cursorState = CursorState::HideCursor;
				std::cout << "TextArea is no selected\n";
			}

		}
	}

	if (isSelected) {


		if (event.type == sf::Event::TextEntered) {
			if (isSelected) {

				

				if (event.text.unicode < 128) {

					if (event.text.unicode == '\b') {
						if (editable_text.size() > 0) {
							editable_text.erase(cursor_position - 1, 1);
							cursor_position -= 1;
						}

					}
					else if (event.text.unicode != 13) {
						editable_text.insert(cursor_position, 1, char(event.text.unicode));
						cursor_position += 1;

					}
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				cursor_position -= 1;
			}
			else if (event.key.code == sf::Keyboard::Right) {
				cursor_position += 1;
			}
		}

	}
}

void EditableTextArea::update() {
	if (isSelected) {
		if ((currentTime - last_action_time).asSeconds() > 0.25f) {
			last_action_time = currentTime;

			if (cursorState == CursorState::ShowCursor) {
				cursorState = CursorState::HideCursor;
				std::wstring text = editable_text;
				text.insert(cursor_position, 1, '|');
				setWstring(text);

			}
			else {
				cursorState = CursorState::ShowCursor;
				setWstring(editable_text);
			}
		}
	}
}

void EditableTextArea::draw() {

	window->draw(rect);

	window->draw(background);
	for (auto& t : texts)
		window->draw(t);
	
}