#include "TextArea.h"
#include "Fonts.h"
#include "Camera.h"
#include "Theme.h"

TextArea::TextArea(std::wstring s, sf::Vector2f position, float line_length) {
	this->s = s;
	this->position = position;
	this->line_length = line_length;

	// format the text (add enters)
	lines = wrapText(s, basicFont, characterSize, this->line_length);
	
	text_color = textColor;
	rect.setFillColor(panelColor_normal);

	generateText();
	generateRect();
}

TextArea::~TextArea() {

}

void TextArea::setTextColor(sf::Color color) {
	this->text_color = color;

	for (auto& t : texts)
		t.setFillColor(text_color);
}

void TextArea::setRectColor(sf::Color color) {
	rect.setFillColor(color);
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
}

void TextArea::generateRect() {
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
			
	rect.setSize(size);
	rect.setPosition(position.x+cam->position.x, position.y+cam->position.y);

}

void TextArea::setRectSize(sf::Vector2f size) {
	rect.setSize(size);
}

void TextArea::setWstring(std::wstring s) {

	this->s = s;
	lines = wrapText(this->s, basicFont, characterSize, this->line_length);

	generateText();
}

void TextArea::setPosition(sf::Vector2f position) {
	this->position = position;

	rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
	generateText();

}

void TextArea::setCharacterSize(short val) {

	characterSize = val;

	generateText();
	generateRect();
}

sf::Vector2f TextArea::getSize() {
	return rect.getSize();
}


void TextArea::update() {

}

void TextArea::draw() {
	window->draw(rect);
	for (auto& t : texts)
		window->draw(t);
}
