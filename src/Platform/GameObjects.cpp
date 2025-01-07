#include "GameObjects.h"
#include "Window.h"
#include "Fonts.h"
#include "Mouse.h"
#include "Collisions.h"
#include "Theme.h"
#include "RenderParameters.h"
#include "GUI.h"
#include <iostream>

Collider::Collider(float width, float length, sf::Vector2f position, float dx, float dy, ColliderType type) {
	this->width = width;
	this->length = length;
	this->position = position;
	this->dx = dx;
	this->dy = dy;
	this->type = type;

	if (type == ColliderType::Rectangle) {
		shape = new sf::RectangleShape(sf::Vector2f(width, length));
		shape->setFillColor(sf::Color(128, 64, 128, 96));
		shape->setOutlineColor(sf::Color(196, 64, 196, 128));
		shape->setOutlineThickness(4.0f);
		shape->setOrigin(width / 2.0f, length / 2.0f);
		shape->setScale(1, 1);
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}

	else if (type == ColliderType::Elipse) {
		shape = new sf::CircleShape(width / 2.0f);
		shape->setFillColor(sf::Color(128, 64, 128, 96));
		shape->setOutlineColor(sf::Color(196, 64, 196, 128));
		shape->setOutlineThickness(4.0f);
		shape->setOrigin(width / 2.0f, width / 2.0f);
		shape->setScale(1, length / width);
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}
}

Collider::Collider(Collider* col) {
	this->width = col->width;
	this->length = col->length;
	this->type = col->type;
	this->position = col->position;
	this->dx = col->dx;
	this->dy = col->dy;

	if (type == ColliderType::Rectangle) {
		shape = new sf::RectangleShape(sf::Vector2f(width, length));
		shape->setFillColor(col->shape->getFillColor());
		shape->setOutlineColor(col->shape->getOutlineColor());
		shape->setOutlineThickness(col->shape->getOutlineThickness());
		shape->setOrigin(col->shape->getOrigin());
		shape->setScale(col->shape->getScale());
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}
	else if (type == ColliderType::Elipse) {
		shape = new sf::CircleShape(width / 2.0f);
		shape->setFillColor(col->shape->getFillColor());
		shape->setOutlineColor(col->shape->getOutlineColor());
		shape->setOutlineThickness(col->shape->getOutlineThickness());
		shape->setOrigin(col->shape->getOrigin());
		shape->setScale(col->shape->getScale());
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}
}

Collider::Collider(Collider* col, sf::Vector2f position) {
	this->width = col->width;
	this->length = col->length;
	this->type = col->type;
	this->position = position;
	this->dx = col->dx;
	this->dy = col->dy;

	if (type == ColliderType::Rectangle) {
		shape = new sf::RectangleShape(sf::Vector2f(width, length));
		shape->setFillColor(col->shape->getFillColor());
		shape->setOutlineColor(col->shape->getOutlineColor());
		shape->setOutlineThickness(col->shape->getOutlineThickness());
		shape->setOrigin(col->shape->getOrigin());
		shape->setScale(col->shape->getScale());
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}
	else if (type == ColliderType::Elipse) {
		shape = new sf::CircleShape(width / 2.0f);
		shape->setFillColor(col->shape->getFillColor());
		shape->setOutlineColor(col->shape->getOutlineColor());
		shape->setOutlineThickness(col->shape->getOutlineThickness());
		shape->setOrigin(col->shape->getOrigin());
		shape->setScale(col->shape->getScale());
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}
}

void Collider::draw() {
	window->draw(*shape);
}


GameObject::GameObject(std::string name, float x, float y, float width, float length, float height, bool collisioning, ColliderType col_type) {
	// CREATE PREFAB
	this->name = name;

	type = GameObjectType::GameObject;
	position.x = x;
	position.y = y;
	this->height = height;

	this->collisioning = collisioning;
	colliders.clear();
	colliders.push_back(new Collider(width, length, position, 0, 0, col_type));

	mouseIsHover = false;

	createTextname();

	isInTheMainList = false;
	isVisible = false;
	isSelected = false;
}

GameObject::GameObject(std::string name, float x, float y, float width, float length, float height, float width_left, float width_right) {
	// FOR DOORS/GATES
	this->name = name;

	type = GameObjectType::GameObject;
	position.x = x;
	position.y = y;
	this->height = height;

	this->collisioning = true;
	colliders.clear();
	colliders.push_back(new Collider(width_left, length, position, -width / 2 + width_left / 2, -8, ColliderType::Rectangle));
	colliders.push_back(new Collider(width_right, length, position, +width / 2 - width_right / 2, -8, ColliderType::Rectangle));
	colliders.push_back(new Collider(width - width_left - width_right, length, position, 0, -8, ColliderType::Rectangle));

	mouseIsHover = false;

	createTextname();

	isInTheMainList = false;
	isVisible = false;
	isSelected = false;
}

GameObject::GameObject(GameObject* go, float x, float y) {
	// CREATE GAMEOBJECT FROM PREFAB
	this->name = go->name;
	type = GameObjectType::GameObject;
	position.x = x;
	position.y = y;
	this->height = go->height;

	this->collisioning = go->collisioning;
	colliders.clear();
	for (auto& col : go->colliders)
		colliders.push_back(new Collider(col, position));

	mouseIsHover = false;


	createTextname();

	isInTheMainList = false;
	isVisible = false;
	isSelected = false;
}

GameObject::GameObject(std::string name)
{
	// FOR TILES PALETTE (TERRAIN OR FLOOR) 
	this->name = name;
	position.x = 0;
	position.y = 0;
	this->height = 16;

	collisioning = true;
	colliders.clear();
	colliders.push_back(new Collider(16, 16, position, 0, 0, ColliderType::Rectangle));

	// TO-DO -
	dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setOrigin(sf::Vector2f(0, 0));
	dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setSize(sf::Vector2f(16, 16));
	dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setOutlineThickness(0);
	dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setPosition(position);
	//

	mouseIsHover = false;

	createTextname();

	isInTheMainList = false;
	isVisible = false;
	isSelected = false;
}

GameObject::GameObject(std::string name, float x, float y)
{
	// FOR BUILDINGS

	this->name = name;
	position.x = x;
	position.y = y;
	this->height = 0;

	collisioning = false;
	colliders.clear();

	mouseIsHover = false;
	createTextname();

	isInTheMainList = false;
	isVisible = false;
	isSelected = false;
}

GameObject::~GameObject()
{
	// TO-DO
	if (!colliders.empty()) {
		for (auto& col : colliders) {
			delete col;
		}

		colliders.clear();
	}
}

void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;

	for (auto& col : colliders)
		col->setPosition(position);

	textname.setPosition(position.x, position.y - height - 35);
}

void GameObject::createTextname() {
	textname = sf::Text(getShortName(name), basicFont, 16);
	textname.setOrigin(textname.getGlobalBounds().width / 2.f, textname.getGlobalBounds().height / 2.f);
	textname.setFillColor(dialoguesColor);
	textname.setOutlineColor(sf::Color::Black);
	textname.setOutlineThickness(2.0f);

	textname.setPosition(position.x, position.y - height - 35);
}

void GameObject::mouseHovering()
{

	mouseIsHover = false;

	for (int i = 0; i < colliders.size() && mouseIsHover == false; i++) {
		if (colliders[i]->type == ColliderType::Elipse) {

			if (pointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x+colliders[i]->dx, position.y+colliders[i]->dy, colliders[i]->width / 2.0f, colliders[i]->length / 2.0f))
				mouseIsHover = true;

		}

		if (colliders[i]->type == ColliderType::Rectangle) {

			if (pointInRectangle(worldMousePosition.x, worldMousePosition.y, position.x+colliders[i]->dx, position.y+colliders[i]->dy, colliders[i]->width, colliders[i]->length))
				mouseIsHover = true;
		}
	}
}


void GameObject::update() {

	mouseHovering();
	createTextname();

	for (auto& col : colliders) {
		col->setPosition(position);
	}
}

void GameObject::drawStatistics() {
	if (renderColliders || isSelected || (!GUIwasOpen && !GUIwasClicked && !GUIwasHover && mouseIsHover)) {

		for (auto& col : colliders) {
			window->draw(*col->shape);
		}
	}

}

void GameObject::draw() {

	if (isSelected || (!GUIwasOpen && !GUIwasClicked && !GUIwasHover && mouseIsHover)) {
		window->draw(textname);
	}
}


std::vector < GameObject* > gameObjects;



bool collisionPrediction(GameObject* object, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	for (auto& collider_1 : object->colliders) {

		if (collider_1->type == ColliderType::Elipse) {

			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {

					for (auto& collider_2 : go->colliders) {
						if (collider_2->type == ColliderType::Elipse) {
							// elipse with elipse
							if (intersectionTwoEllipses(object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.f, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.f)) {
								std::cout << "collision " << object->name << " - " << go->name << "\n";
								return true;
							}

						}

						if (collider_2->type == ColliderType::Rectangle) {
							// elipse with rectangle
							if (intersectionRectangleWithElipse(go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length, object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.0f)) {
								std::cout << "collision " << object->name << " - " << go->name << "\n";
								return true;
							}


						}
					}

				}
			}
		}
		else if (collider_1->type == ColliderType::Rectangle) {

			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {

					for (auto& collider_2 : go->colliders) {
						if (collider_2->type == ColliderType::Elipse) {
							// rectangle with elipse
							if (intersectionRectangleWithElipse(object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.0f))
								return true;
						}

						if (collider_2->type == ColliderType::Rectangle) {
							// rectangle with rectangle
							if (intersectionTwoRectangles(object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length))
								return true;

						}
					}

				}
			}
		}

	}

	return false;
}

bool collisionPrediction(GameObject* object, Point p, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	for (auto& collider_1 : object->colliders) {

		if (collider_1->type == ColliderType::Elipse) {

			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {
					for (auto& collider_2 : go->colliders) {
						if (collider_2->type == ColliderType::Elipse) {
							// elipse with elipse
							if (intersectionTwoEllipses(p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.f, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.f))
								return true;
						}

						if (collider_2->type == ColliderType::Rectangle) {
							// elipse with rectangle
							if (intersectionRectangleWithElipse(go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length, p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.0f))
								return true;

						}
					}
				}
			}
		}
		else if (collider_1->type == ColliderType::Rectangle) {
			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {
					for (auto& collider_2 : go->colliders) {

						if (collider_2->type == ColliderType::Elipse) {
							// rectangle with elipse
							if (intersectionRectangleWithElipse(p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.0f))
								return true;
						}

						if (collider_2->type == ColliderType::Rectangle) {
							// rectangle with rectangle
							if (intersectionTwoRectangles(p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length))
								return true;

						}
					}
				}
			}
		}

	}

	return false;
}
