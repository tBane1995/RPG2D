#pragma once

#include <SFML/Graphics.hpp>

// GAME
extern sf::Color dialoguesColor;
extern sf::Color dialoguesActiveColor;

// EDITOR
extern float borderWidth;
extern sf::Color panelColor_normal;
extern sf::Color panelColor_light;
extern sf::Color panelColor_medium;
extern sf::Color panelColor_dark;

extern sf::Color textColor;

extern float margin;

void initTheme();