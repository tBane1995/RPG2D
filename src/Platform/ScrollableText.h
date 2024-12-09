#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"

class TextArea;
class Scrollbar;

class ScrollableText : public Dialog {
public:

	sf::Vector2f position;
	sf::RectangleShape rect;
	float width = 600;
	float height = 400;
	float margin = 8;
	TextArea* textarea;
	Scrollbar* scrollbar;
	sf::RenderTexture text_texture;
	sf::Sprite text_sprite;

	ScrollableText(std::wstring text);

	~ScrollableText() {
		delete textarea;
		delete scrollbar;
	}

	virtual void update(sf::Event& event) override;
	virtual void draw() override;
};
