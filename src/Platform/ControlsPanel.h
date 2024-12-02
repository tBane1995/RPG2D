#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class ControlsPanel {
public:

    sf::Text title;
    sf::Text press;

    sf::Sprite panel;

    sf::Sprite up;
    sf::Sprite down;
    sf::Sprite left;
    sf::Sprite right;
    sf::Sprite space;
    sf::Sprite e;
    sf::Sprite h;
    sf::Sprite j;

    sf::Text uptext;
    sf::Text downtext;
    sf::Text lefttext;
    sf::Text righttext;
    sf::Text spacetext;
    sf::Text etext;
    sf::Text htext;
    sf::Text jtext;


    ControlsPanel();
	~ControlsPanel() { }

    void update();

    void draw();
};

extern ControlsPanel* controls;
