#include "EditableTextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"

#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

EditableTextArea::EditableTextArea(std::wstring text) : TextArea(text) {

	cursor = sf::RectangleShape(sf::Vector2f(2, getLineHeight()));
	cursor.setFillColor(sf::Color::Red);

	sf::Vector2f pos;
	pos.x = texts[0].getPosition().x + texts[0].getGlobalBounds().getSize().x;
	pos.y = texts[0].getPosition().y;
	cursor.setPosition(pos);

	isSelected = false;
	cursor_position = lines[0].size();
	last_action_time = currentTime;
	cursorState = CursorState::ShowCursor;
}

EditableTextArea::~EditableTextArea() {

}

void EditableTextArea::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (rect.getGlobalBounds().contains(worldMousePosition)) {

				isSelected = true;
				cursorState = CursorState::ShowCursor;
				cursor_position = lines[0].size();
			}
			else {
				isSelected = false;
				cursorState = CursorState::HideCursor;
			}

		}
	}

	if (isSelected) {

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {

			lines[0].insert(cursor_position, 1, ' ');
			cursor_position += 1;
			generateText();
		}
		else if (event.type == sf::Event::TextEntered) {

			if (event.text.unicode < 128) {

				if (event.text.unicode == '\b') {
					if (lines[0].size() > 0 && cursor_position > 0) {
						lines[0].erase(cursor_position - 1, 1);
						cursor_position -= 1;
					}

				}
				else if (event.text.unicode != 13) {
					lines[0].insert(cursor_position, 1, char(event.text.unicode));
					cursor_position += 1;
				}

			}

			generateText();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				if (cursor_position > 0)
					cursor_position -= 1;
			}
			else if (event.key.code == sf::Keyboard::Right) {
				if (cursor_position < lines[0].size())
					cursor_position += 1;
			}
		}

		std::wstring text_before_cursor = lines[0].substr(0, cursor_position);
		TextArea text = TextArea(text_before_cursor);

		sf::Vector2f pos;
		pos.x = texts[0].getPosition().x + text.texts[0].getGlobalBounds().getSize().x;
		pos.y = texts[0].getPosition().y;
		cursor.setPosition(pos);
	}
}

void EditableTextArea::update() {
	if (isSelected) {
		if ((currentTime - last_action_time).asSeconds() > 0.25f) {
			last_action_time = currentTime;

			if (cursorState == CursorState::ShowCursor) {
				cursorState = CursorState::HideCursor;
			}
			else {
				cursorState = CursorState::ShowCursor;
			}
		}
	}
}

void EditableTextArea::draw() {

	window->draw(rect);

	window->draw(background);
	for (auto& t : texts)
		window->draw(t);

	window->draw(cursor);
	
}