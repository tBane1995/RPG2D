#pragma once

#include <SFML/Graphics.hpp>

extern sf::Vector2i mousePosition;
extern sf::Vector2f worldMousePosition;

extern sf::Time mouse_start_time;

extern sf::Vector2i startMousePosition;
extern sf::Vector2f startWorldMousePosition;

extern sf::RectangleShape selectArea;

extern float mouseDoubleClickTime;

enum class MouseState { Idle, Click, Selecting };
extern MouseState mouse_state;

void mouseSelection();
