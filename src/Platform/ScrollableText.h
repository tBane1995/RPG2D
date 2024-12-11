#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"
#include "Panel.h"

class TextArea;
class Scrollbar;
class Panel;

class ScrollableText : public Panel {
public:

	TextArea* textarea;
	Scrollbar* scrollbar;
	sf::RenderTexture text_texture;
	sf::Sprite text_sprite;

	ScrollableText(std::wstring text);

	~ScrollableText();

	virtual void update(sf::Event& event) override;
	virtual void draw() override;
};
