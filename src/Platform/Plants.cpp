#include "Plants.h"
#include "Window.h"
#include "Textures.h"
#include "Time.h"
#include "Collisions.h"
#include "Mouse.h"

Plant::Plant(std::string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
	textures.push_back(getSingleTexture("plants/grass_0"));
	textures.push_back(getSingleTexture("plants/grass_1"));

	SingleTexture::SetTextureForSprite(&sprite, textures[0]);
	SingleTexture::SetOriginForSprite(&sprite, textures[0], 1.0f, 1.0f);
	sprite.setPosition(position);

	current_texture = 0;
	time_last_frame = sf::Time::Zero;

	state = animState::stop;
}

Plant::Plant(GameObject* object, float x, float y) : GameObject(object, x, y) {

	for (auto& t : dynamic_cast<Plant*>(object)->textures) {
		textures.push_back(t);
	}
			
	SingleTexture::SetTextureForSprite(&sprite, textures[0]);
	SingleTexture::SetOriginForSprite(&sprite, textures[0], 1.0f, 1.0f);
	sprite.setPosition(position);

	current_texture = 0;
	time_last_frame = sf::Time::Zero;

	state = animState::stop;
}

void Plant::update(float dt) {
	/*
	if ((currentTime - time_last_frame).asSeconds() > 0.2f) {
		sprite.setTexture(*textures[current_texture]->texture);

		time_last_frame = currentTime;

		current_texture += 1;
		if (current_texture >= textures.size())
			current_texture = 0;
	}
	*/

	if (state == animState::stop && pointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x, position.y, colliders[0]->width / 2.0f, height / 2.0f)) {
			
		state = animState::anim;
		start_anim = currentTime;
		last_anim = currentTime;
		(rand() % 2 == 0) ? growing = true : growing = false;
		rotate = 0;
	}
		
	if (state == animState::end && !pointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x, position.y, colliders[0]->width / 2.0f, height / 2.0f)) {
		state = animState::stop;
	}
	else if ((currentTime - start_anim).asSeconds() > 0.3f) {
		state = animState::end;
		if ((currentTime - last_anim).asSeconds() > 0.001f) {

			if (rotate < 0) rotate += 1;
			else if (rotate > 0) rotate -= 1;

			last_anim = currentTime;

			sprite.setRotation(rotate);
		}

	}
	else if (state == animState::anim && (currentTime - last_anim).asSeconds() > 0.001f) {

		(growing == true) ? rotate += 1 : rotate -= 1;
				
		if (rotate > 10) growing = false;
		else if (rotate < -10) growing = true;

		last_anim = currentTime;

		sprite.setRotation(rotate);
			
	}

		

}

void Plant::draw() {
	window->draw(sprite);
}

std::vector < Plant* > plants;
