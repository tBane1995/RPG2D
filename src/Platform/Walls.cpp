#include "Walls.h"
#include "Textures.h"
#include "Window.h"

Wall::Wall(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Rectangle) {
	type = GameObjectType::Wall;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
}

Wall::Wall(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::Wall;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);
}

void Wall::draw() {
	if (mouseIsHover)
		GameObject::draw();

	window->draw(sprite);
}

std::vector < Wall* > walls;
