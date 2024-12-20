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

	Panel(DialogType dialog_type = DialogType::Panel, sf::Vector2f size = sf::Vector2f(600, 400));
	~Panel();
	virtual void update(sf::Event& event);
	virtual void draw();
};