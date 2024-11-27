#include "CheckBox.h"

CheckBox::CheckBox(sf::Vector2f size, sf::Vector2f position, bool value=false) {

	this->position = position;
	this->value = value;

	rect = sf::RectangleShape(size);
	//rect.setFillColor(sf::Color::Red);
	rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
	rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);

	checkSprite = sf::Sprite();
	checkSprite.setTexture(*getSingleTexture("GUI/checkbox/check")->texture);
	sf::Vector2f texsize = sf::Vector2f( checkSprite.getTexture()->getSize().x, checkSprite.getTexture()->getSize().y);
	checkSprite.setOrigin(texsize.x / 2.0f, texsize.y / 2.0f);
	checkSprite.setScale(size.x/texsize.x, size.y/texsize.y);
	checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
		
}

void CheckBox::edit(sf::Vector2f size, sf::Vector2f position) {

	this->position = position;

	rect = sf::RectangleShape(size);
	rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
	rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);

	checkSprite = sf::Sprite();
	checkSprite.setTexture(*getSingleTexture("GUI/checkbox/check")->texture);
	sf::Vector2f texsize = sf::Vector2f(checkSprite.getTexture()->getSize().x, checkSprite.getTexture()->getSize().y);
	checkSprite.setOrigin(texsize.x / 2.0f, texsize.y / 2.0f);
	checkSprite.setScale(size.x / texsize.x, size.y / texsize.y);
	checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
}
