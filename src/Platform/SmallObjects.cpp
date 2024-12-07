#include "SmallObjects.h"
#include "Window.h"
#include "Textures.h"

SmallObject::SmallObject(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
	type = GameObjectType::SmallObject;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	SingleTexture::SetOriginForSprite(&sprite, texture, 1.0f, 1.0f);
}

SmallObject::SmallObject(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::SmallObject;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	SingleTexture::SetOriginForSprite(&sprite, texture, 1.0f, 1.0f);
	sprite.setPosition(position);

}

void SmallObject::draw() {

	if (mouseIsHover)
		GameObject::draw();

	window->draw(sprite);
}

std::vector < SmallObject* > smallObjects;
