#include "Natures.h"
#include "Textures.h"
#include "Shaders.h"
#include "Camera.h"

Nature::Nature(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Elipse) {
	type = GameObjectType::Nature;
	this->texture = getSingleTexture(name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	SingleTexture::SetOriginForSprite(&sprite, texture, 1.0f, 1.0f);
	sprite.setPosition(position);

}

Nature::Nature(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::Nature;

	this->texture = getSingleTexture(name);

	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	SingleTexture::SetOriginForSprite(&sprite, texture, 1.0f, 1.0f);
	sprite.setPosition(position);

}

void Nature::draw() {

	if (mouseIsHover)
		GameObject::draw();

	//window->draw(shadow);
	Shader* s = getShader("shaders/shadow");
	s->shader->setUniform("texture", texture->texture);
	s->shader->setUniform("camPosition", cam->position);
	s->shader->setUniform("resolution", sf::Vector2f(screenWidth, screenHeight));
	window->draw(sprite, s->shader);
	window->draw(sprite);

		
}

std::vector < Nature* > natures;
