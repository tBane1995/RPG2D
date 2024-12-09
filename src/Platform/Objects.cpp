#include "Objects.h"
#include "GameObjects.h"
#include "Textures.h"
#include "Time.h"
#include "Window.h"

Object::Object(std::string name, float width, float length, float height, bool collisioning) : GameObject(name, 0, 0, width, length, height, collisioning, ColliderType::Rectangle) {
	type = GameObjectType::Object;
		
	textures.clear();
	textures = getTexturesSet(name);
	frame = 0;
	texture = textures[0];
	last_action_time = currentTime;

	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
}

Object::Object(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::Object;
		
	textures.clear();
	textures = getTexturesSet(name);
	frame = 0;
	texture = textures[0];
	last_action_time = currentTime;

	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);

}

void Object::update(float dt) {
	if ((currentTime - last_action_time).asSeconds() > 0.1f) {
			
		last_action_time = currentTime;
		frame += 1;

		if (frame >= textures.size())
			frame = 0;

		texture = textures[frame];

		SingleTexture::SetTextureForSprite(&sprite, texture);
	}
		

}
void Object::draw() {

	if (mouseIsHover)
		GameObject::draw();

	window->draw(sprite);
}

std::vector < Object* > objects;
