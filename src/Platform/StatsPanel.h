#pragma once

#include <SFML/Graphics.hpp>

class StatsPanel {
public:
	sf::Sprite panel;
	sf::Text LEVEL;
	sf::Text EXPERIENCE;
	sf::Text SKILLPOINTS;
	
	sf::Text HP;
	sf::Text MP;
	sf::Text STRENGTH;
	sf::Text DEXTERITY;
	sf::Text INTELLIGENCE;

	StatsPanel();

	void update();
	void draw();
};

extern StatsPanel* stats;
