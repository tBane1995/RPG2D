#pragma once

#include <SFML/Graphics.hpp>

extern sf::Vector2i mousePosition;
extern sf::Vector2f worldMousePosition;

extern sf::Time startClickTime;				// TO-DO selecting

extern sf::Vector2i startMousePosition;
extern sf::Vector2f startWorldMousePosition;
extern bool selection_state;
extern sf::RectangleShape selectArea;

void mouseSelection();
