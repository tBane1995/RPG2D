#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"


class Panel : public Dialog {
public:
	sf::Vector2f position;
	sf::RectangleShape rect;
	float width = 600;
	float height = 400;
	float margin = 8;

	Panel(DialogType dialog_type=DialogType::Panel);
	~Panel();
	virtual void update(sf::Event& event);
	virtual void draw();
};