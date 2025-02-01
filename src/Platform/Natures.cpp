#include "Natures.h"
#include "Textures.h"
#include "Shaders.h"
#include "Camera.h"

Nature::Nature(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Elipse) {
	type = GameObjectType::Nature;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);

}

Nature::Nature(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::Nature;

	this->texture = getSingleTexture(name);

	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);

}

Nature::~Nature() {

}

void Nature::setPosition(sf::Vector2f position) {
	GameObject::setPosition(position);
	sprite.setPosition(position);
}

void Nature::update() {
	GameObject::update();
}

void Nature::drawStatistics() {
	GameObject::drawStatistics();
}

void Nature::draw() {

	window->draw(sprite);


}

std::vector < Nature* > natures;
