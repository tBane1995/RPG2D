#include "Panel.h"
#include "Theme.h"
#include "Window.h"
#include "Camera.h"

Panel::Panel(DialogType dialog_type) : Dialog(dialog_type) {

	rect = sf::RectangleShape(sf::Vector2f(width - 2 * borderWidth, height - 2 * borderWidth));
	rect.setFillColor(panelColor_normal);
	rect.setPosition(cam->position.x - width / 2.0f + borderWidth, cam->position.y - height / 2.0f + borderWidth);
	rect.setOutlineThickness(borderWidth);
	rect.setOutlineColor(panelColor_dark);
}

Panel::~Panel() {

}

void Panel::update(sf::Event& event) {

}

void Panel::draw() {
	window->draw(rect);
}