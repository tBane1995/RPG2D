#include "Walls.h"
#include "Textures.h"
#include "Window.h"

Wall::Wall(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Rectangle) {
	type = GameObjectType::Wall;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	SingleTexture::SetOriginForSprite(&sprite, texture, 1.0f, 1.0f);
}

Wall::Wall(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::Wall;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	SingleTexture::SetOriginForSprite(&sprite, texture, 1.0f, 1.0f);
	sprite.setPosition(position);
}

void Wall::draw() {
	if (mouseIsHover)
		GameObject::draw();

	window->draw(sprite);
}

std::vector < Wall* > walls;
