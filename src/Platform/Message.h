#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"

class TextArea;

class Message : public Dialog {
public:
	sf::RectangleShape rect;
	float margin = 8;
	TextArea* text;

	Message(std::wstring message);

	~Message() {
		delete text;
		text = nullptr;
	}

	virtual void handleEvent(sf::Event& event) override;
	virtual void update() override;
	virtual void draw() override;
};
