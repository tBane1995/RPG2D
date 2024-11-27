#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


class JournalPanel {
public:

	sf::Sprite panel;
	std::vector < sf::Text > titles;
	sf::Text description;

	JournalPanel();

	void update();
	void draw();

};

extern JournalPanel* journal;
