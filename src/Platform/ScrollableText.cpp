#include "ScrollableText.h"
#include "Theme.h"
#include "Window.h"
#include "TextArea.h"
#include "Scrollbar.h"
#include "Camera.h"

ScrollableText::ScrollableText(std::wstring text) : Panel(DialogType::ScrollableText) {

	sf::Vector2f scrollbar_size = sf::Vector2f(16, height - 2.0f * borderWidth);

	textarea = new TextArea(text, cam->position, width - 2.0f*borderWidth - 2.0f*margin - scrollbar_size.x);
	textarea->setPosition(sf::Vector2f(- width/2.0f + borderWidth + margin, - height/2.0f + borderWidth + margin));

	sf::Vector2f scrollbar_position = sf::Vector2f(width/2.0f-borderWidth-scrollbar_size.x, -height/2.0f + borderWidth);
	float scroll_max = textarea->getSize().y + textarea->getLineHeight() + 2*margin;
	float scroll_len = height;
	scrollbar = new Scrollbar(scrollbar_size, scrollbar_position, 0, scroll_max, 0, scroll_len);
	
	// TO-DO - generowanie tekstury przewijalnej dla tekstu
	text_texture.create(width-2.0f*(borderWidth+margin) - scrollbar_size.x, height-2.0f*(borderWidth+margin));
	sf::View v = sf::View(sf::FloatRect(sf::Vector2f(cam->position.x-width/2.0f+borderWidth+margin, cam->position.y-height/2.0f+borderWidth+margin), sf::Vector2f(width-2*(borderWidth+margin)-scrollbar->size.x, height-2*(borderWidth+margin))));
	text_texture.setView(v);
	text_texture.setSmooth(true);
	text_texture.clear(sf::Color::Transparent);
	text_texture.draw(textarea->background);
	for (auto& text : textarea->texts)
		text_texture.draw(text);
	text_texture.display();
	text_sprite = sf::Sprite(text_texture.getTexture());
	sf::Vector2f textpos;
	textpos.x = cam->position.x + position.x - width / 2.0f + borderWidth + margin - (textarea->texts[0].getPosition().x-textarea->background.getPosition().x);
	textpos.y = cam->position.y + position.y - height / 2.0f + borderWidth + margin - (textarea->texts[0].getPosition().y - textarea->background.getPosition().y);
	text_sprite.setPosition(textpos);
	// TO-DO
}

ScrollableText::~ScrollableText() {
	delete textarea;
	delete scrollbar;
}

void ScrollableText::update(sf::Event& event) {

	scrollbar->handleEvent(event);

	sf::Vector2f position;
	position.x = textarea->position.x;
	position.y = borderWidth + margin -scrollbar->scroll_value - height / 2.0f;
	textarea->setPosition(position);

	sf::View v = sf::View(sf::FloatRect(sf::Vector2f(cam->position.x - width / 2.0f + borderWidth + margin, cam->position.y - height / 2.0f + borderWidth + margin), sf::Vector2f(width - 2 * (borderWidth + margin)-scrollbar->size.x, height - 2 * (borderWidth + margin))));
	text_texture.setView(v);
	text_texture.clear(sf::Color::Transparent);
	text_texture.draw(textarea->background);
	for (auto& text : textarea->texts)
		text_texture.draw(text);
	text_texture.display();

}

void ScrollableText::draw() {
	window->draw(rect);
	scrollbar->draw();
	window->draw(text_sprite);
}
