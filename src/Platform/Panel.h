#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"


class Panel : public Dialog {
public:
	sf::Vector2f position;
	sf::RectangleShape rect;
	sf::Vector2f size;
	float margin = 8;

	Panel(sf::Vector2f size = sf::Vector2f(600, 400), DialogType dialog_type = DialogType::Panel);
	~Panel();
	virtual void handleEvent(sf::Event& event);
	virtual void update();
	virtual void draw();
};