#include "Theme.h"

// GAME
sf::Color dialoguesColor = sf::Color(234, 224, 175);
sf::Color dialoguesActiveColor = sf::Color(255, 201, 14);

// EDITOR
float borderWidth;
sf::Color panelColor_normal;
sf::Color panelColor_light;
sf::Color panelColor_medium;
sf::Color panelColor_dark;
sf::Color textColor;

float margin;

sf::Color backgroundColor;


void initTheme() {

	// GAME
	dialoguesColor = sf::Color(234, 224, 175);
	dialoguesActiveColor = sf::Color(255, 201, 14);

	// EDITOR
	borderWidth = 8.0f;
	panelColor_normal = sf::Color(64, 64, 64);
	panelColor_light = sf::Color(80, 80, 80);
	panelColor_medium = sf::Color(48, 48, 48);
	panelColor_dark = sf::Color(32, 32, 32);

	textColor = sf::Color::White;

	margin = 8;

	backgroundColor = sf::Color(48, 48, 48);	// color of outside map


}