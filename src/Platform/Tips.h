#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class ButtonWithImage;
class TextArea;

class Tip {
public:
	sf::Time hover_start;
	ButtonWithImage* btn;
	sf::Vector2f position;
	TextArea* text;
	
	Tip(std::wstring tip, ButtonWithImage* btn = nullptr);
	Tip(std::wstring tip, sf::Vector2f position, ButtonWithImage* btn = nullptr);

	~Tip() { 
		delete text;
	}

	void update();
	void draw();
};

extern Tip* tip;
