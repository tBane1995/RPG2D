﻿#include "EditableTextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"

#include "Mouse.h"
#include "Textures.h"
#include "Time.h"
#include "Theme.h"

EditableTextArea::EditableTextArea(std::wstring text) : TextArea(text) {

	isSelected = false;

	cursor = sf::RectangleShape(sf::Vector2f(2, getLineHeight()));
	cursor.setFillColor(textColor);
	cursor_position = lines[0].size();

	last_action_time = currentTime;
	cursorState = CursorState::HideCursor;

}

EditableTextArea::~EditableTextArea() {

}

void EditableTextArea::setPosition(sf::Vector2f position) {
	this->position = position;

	background.setPosition(position.x + cam->position.x, position.y + cam->position.y);
	generateText();
	rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	cursorPositioning();
}

void EditableTextArea::cursorPositioning() {
	sf::Vector2f pos = texts[0].getPosition(); // Startowa pozycja tekstu

	// Przejdź przez każdy znak przed kursorem
	for (size_t i = 0; i < cursor_position; ++i) {
		char currentChar = lines[0][i];
		char nextChar = (i + 1 < lines[0].size()) ? lines[0][i + 1] : 0;

		// Pobierz szerokość znaku z Glyph
		sf::Glyph glyph = texts[0].getFont()->getGlyph(currentChar, texts[0].getCharacterSize(), false);
		pos.x += glyph.advance; // Dodaj szerokość znaku (advance)

		// Dodaj kerning między aktualnym znakiem a następnym znakiem
		pos.x += texts[0].getFont()->getKerning(currentChar, nextChar, texts[0].getCharacterSize());
	}

	// Ustaw kursor na precyzyjnie obliczoną pozycję
	cursor.setPosition(pos);
}

void EditableTextArea::handleEvent(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (rect.getGlobalBounds().contains(worldMousePosition)) {

				isSelected = true;
				cursorState = CursorState::ShowCursor;
				cursor_position = lines[0].size();
				cursorPositioning();
			}
			else {
				isSelected = false;
				cursorState = CursorState::HideCursor;
			}

		}
	}

	if (isSelected) {

		if (event.type == sf::Event::TextEntered) {

			if (event.text.unicode < 128) {

				if (event.text.unicode == '\b') {
					if (lines[0].size() > 0 && cursor_position > 0) {
						lines[0].erase(cursor_position - 1, 1);
						cursor_position -= 1;
					}

				}
				else if (event.text.unicode == 32) {
					lines[0].insert(cursor_position, 1, ' ');
					cursor_position += 1;
				}
				else if (event.text.unicode != 13) {
					lines[0].insert(cursor_position, 1, char(event.text.unicode));
					cursor_position += 1;
				}

				generateText();
				cursorPositioning();
			}
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				if (cursor_position > 0) {
					cursor_position -= 1;
					cursorPositioning();
				}

			}
			else if (event.key.code == sf::Keyboard::Right) {
				if (cursor_position < lines[0].size()) {
					cursor_position += 1;
					cursorPositioning();
				}

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

	if (cursorState == CursorState::ShowCursor)
		window->draw(cursor);

}