#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Scrollbar {
public:
    // TO-DO - must be a Scrollbar no Scrollbar3
    sf::Vector2f size;      // 16 x 16+16+16
    sf::Vector2f position;

    sf::Color bar_color;
    sf::Color scroll_color;

    short min_value;
    short max_value;
    short scroll_value;
    short scroll_length;

    sf::RectangleShape bar_top;
    sf::RectangleShape bar_center;
    sf::RectangleShape bar_bottom;

    sf::RectangleShape scroll_top;
    sf::RectangleShape scroll_center;
    sf::RectangleShape scroll_bottom;

    sf::Sprite spr_bar_top;
    sf::Sprite spr_bar_center;
    sf::Sprite spr_bar_bottom;

    sf::Sprite spr_scroll_top;
    sf::Sprite spr_scroll_center;
    sf::Sprite spr_scroll_bottom;

    float start_mouse_y;
    bool is_pressed;

    Scrollbar(sf::Vector2f size, sf::Vector2f position, short min_value, short max_value, short scroll_value, short scroll_length);
    void setPosition(sf::Vector2f pos);
    void setValue(short value);
    float getScrollSizeY();
    void scrollPositioning();
    bool isSelected();
    void handleEvent(sf::Event& event);
    void update();
    void draw();
};

#include <SFML/Graphics.hpp>
#include <iostream>
//size convention : 
/*
the cursor is 10% the size of the bar
so the bar starts and ends 5% before the limit defined by the variable location
*/

