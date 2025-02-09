#include "Message.h"
#include "TextArea.h"
#include "Theme.h"
#include "Camera.h"
#include "GUI.h"

Message::Message(std::wstring message) : Dialog(DialogType::Message) {
	text = new TextArea(message, cam->position, 400.0f - 2*margin);
		
	float width = text->getSize().x;
	if (width < 400)
		width = 400;

	float height = text->getSize().y;
	if (height < 250)
		height = 250;

	text->setPosition(sf::Vector2f(cam->position.x-width/2.0f+margin, cam->position.y-height/2.0f+margin));

	rect = sf::RectangleShape(sf::Vector2f(width, height));
	rect.setFillColor(panelColor_normal);
	rect.setPosition(cam->position.x-width/2.0f, cam->position.y-height/2.0f);
}

void Message::handleEvent(sf::Event& event) {
	text->update();
}

void Message::update() {
	GUIwasOpen = true;
}

void Message::draw() {
	window->draw(rect);
	text->draw();
}
