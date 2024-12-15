#include "TextArea.h"
#include "Fonts.h"
#include "Camera.h"
#include "Theme.h"

TextArea::TextArea(std::wstring text, sf::Vector2f position, float line_length, sf::Vector2f size) {
	this->position = position;
	this->line_length = line_length;

	// format the text (add enters)
	lines = wrapText(text, basicFont, characterSize, this->line_length);
	
	text_color = textColor;
	background_color = panelColor_medium;
	rect_color = panelColor_dark;

	generateText();
	generateBackground();
	generateRect(size);
}

TextArea::~TextArea() {

}

void TextArea::setTextColor(sf::Color color) {
	this->text_color = color;

	for (auto& t : texts)
		t.setFillColor(text_color);
}

void TextArea::setBackgroundColor(sf::Color color) {
	background_color = color;
	background.setFillColor(background_color);
}

void TextArea::setRectColor(sf::Color color) {
	rect_color = color;
	rect.setFillColor(rect_color);;
}

float TextArea::getLineHeight() {
	return characterSize * 1.3f;
}

void TextArea::generateText() {
	texts.clear();

	float i = 0;
	for (auto& line : lines) {
		sf::Text t;
		t.setFont(basicFont);
		t.setFillColor(text_color);
		t.setCharacterSize(characterSize);
		t.setString(line);

		sf::Vector2f textPos;
		textPos.x = position.x + characterSize * 0.2f;
		textPos.y = position.y + getLineHeight() * float(i);
		t.setPosition(textPos.x + cam->position.x, textPos.y + cam->position.y);
		texts.push_back(t);
		i += 1.0f;
	}

	generateBackground();
}

void TextArea::generateBackground() {
	sf::Vector2f size;
	if (texts.size() > 0 && line_length > 0.0f) {
		size.x = line_length;
		size.y = texts.size() * getLineHeight();
	}
	else if(!texts.empty() && texts[0].getString() !="") {
		size.x = float(texts.front().getLocalBounds().getSize().x) + characterSize * 0.5f;
		size.y = getLineHeight();
	}
	else {
		size.x = 0;
		size.y = 0;
	}
			
	background.setSize(size);
	background.setFillColor(background_color);
	background.setPosition(position.x+cam->position.x, position.y+cam->position.y);

}

void TextArea::generateRect(sf::Vector2f size) {
	if (size == sf::Vector2f(0, 0)) {
		rect.setSize(background.getSize());
	}else
		rect.setSize(size);

	rect.setFillColor(rect_color);
	rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

}

void TextArea::setCharacterSize(short val) {

	characterSize = val;

	generateText();
	generateBackground();
}

void TextArea::setBackgroundSize(sf::Vector2f size) {
	background.setSize(size);
}

void TextArea::setRectSize(sf::Vector2f size) {
	rect.setSize(size);
}

void TextArea::setWstring(std::wstring text) {

	lines = wrapText(text, basicFont, characterSize, line_length);

	generateText();
}

void TextArea::setPosition(sf::Vector2f position) {
	this->position = position;

	background.setPosition(position.x + cam->position.x, position.y + cam->position.y);
	generateText();
	rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

}

sf::Vector2f TextArea::getSize() {
	return rect.getSize();
}


void TextArea::update() {

}

void TextArea::draw() {
	window->draw(rect);
	window->draw(background);
	for (auto& t : texts)
		window->draw(t);
}
