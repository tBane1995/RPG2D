#include "Window.h"

float screenWidth = 1280;
float screenHeight = 720;

sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(int(screenWidth), int(screenHeight)), "");
