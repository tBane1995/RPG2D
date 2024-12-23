#include "CheckBox.h"
#include "Window.h"
#include "Camera.h"
#include "Textures.h"

CheckBox::CheckBox(sf::Vector2f size, sf::Vector2f position, bool value) {

	this->position = position;
	this->value = value;

	rect = sf::RectangleShape(size);
	//rect.setFillColor(sf::Color::Red);
	rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
	rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);

	SingleTexture* CheckTexture = getSingleTexture("GUI/checkbox/check");
	checkSprite = sf::Sprite();
	sf::Vector2f texsize = sf::Vector2f(CheckTexture->getSize().x, CheckTexture->getSize().y);
	SingleTexture::SetTextureForSprite(&checkSprite, CheckTexture);
	checkSprite.setOrigin(texsize.x / 2.0f, texsize.y / 2.0f);
	checkSprite.setScale(size.x/texsize.x, size.y/texsize.y);
	checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
		
}

void CheckBox::edit(sf::Vector2f size, sf::Vector2f position) {

	this->position = position;

	rect = sf::RectangleShape(size);
	rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
	rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);

	SingleTexture* CheckTexture = getSingleTexture("GUI/checkbox/check");
	checkSprite = sf::Sprite();
	sf::Vector2f texsize = sf::Vector2f(CheckTexture->getSize().x, CheckTexture->getSize().y);
	SingleTexture::SetTextureForSprite(&checkSprite, CheckTexture);
	checkSprite.setOrigin(texsize.x / 2.0f, texsize.y / 2.0f);
	checkSprite.setScale(size.x / texsize.x, size.y / texsize.y);
	checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
}

void CheckBox::update(float dt) {
	rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
	checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
}

void CheckBox::draw() {
	//window->draw(rect);
	if (value)
	{
		window->draw(checkSprite);
	}
}
