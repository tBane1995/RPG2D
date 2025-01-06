#include "Panel.h"
#include "Theme.h"
#include "Window.h"
#include "Camera.h"
#include "GUI.h"

Panel::Panel(sf::Vector2f size, DialogType dialog_type) : Dialog(dialog_type) {

	this->size = size;

	rect = sf::RectangleShape(sf::Vector2f(size.x - 2 * borderWidth, size.y - 2 * borderWidth));
	rect.setFillColor(panelColor_normal);
	rect.setPosition(cam->position.x - size.x / 2.0f + borderWidth, cam->position.y - size.y / 2.0f + borderWidth);
	rect.setOutlineThickness(borderWidth);
	rect.setOutlineColor(panelColor_dark);
}

Panel::~Panel() {

}

void Panel::handleEvent(sf::Event& event) {

}

void Panel::update() {
	GUIwasOpen = true;
}

void Panel::draw() {
	window->draw(rect);
}