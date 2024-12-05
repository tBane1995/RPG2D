﻿#include "Scrollbar.h"
#include "Camera.h"
#include "Textures.h"
#include "Windows.h"
#include "Mouse.h"
#include <iostream>


Scrollbar::Scrollbar(sf::Vector2f size, sf::Vector2f position, short min_value, short max_value, short scroll_value, short scroll_length) {

    this->size = size;
    this->position = position;

    this->min_value = min_value;
    this->max_value = max_value;
    this->scroll_length = scroll_length;

    setValue(scroll_value);
    
    this->start_mouse_y = 0;
    this->is_pressed = false;

    // COLORS
    bar_color = sf::Color::Red;
    scroll_color = sf::Color::Blue;

    // BAR
    bar_top = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    bar_top.setPosition(position);
    bar_top.setFillColor(bar_color);

    bar_center = sf::RectangleShape(sf::Vector2f(size.x, size.y-2.0f*size.x));
    bar_center.setPosition(position.x, position.y + size.x);
    bar_center.setFillColor(bar_color);

    bar_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    bar_bottom.setPosition(position.x, position.y + size.y - size.x);
    bar_bottom.setFillColor(bar_color);
   
    // SCROLL
    scroll_top = sf::RectangleShape(sf::Vector2f(size.x,size.x));
    scroll_top.setPosition(position.x, position.y);
    scroll_top.setFillColor(scroll_color);

    scroll_center = sf::RectangleShape(sf::Vector2f(size.x, getScrollSizeY()-2*size.x));
    scroll_center.setPosition(position.x, position.y+size.x);
    scroll_center.setFillColor(sf::Color::Green);

    scroll_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    scroll_bottom.setPosition(position.x, position.y+size.x+getScrollSizeY()-2*size.x);
    scroll_bottom.setFillColor(scroll_color);
}

void Scrollbar::setPosition(sf::Vector2f pos) {
    this->position = pos;

    // BAR
    bar_top.setPosition(position);
    bar_center.setPosition(position.x, position.y + size.x);
    bar_bottom.setPosition(position.x, position.y + size.y - size.x);

    // SCROLL
    scroll_top.setPosition(position.x, position.y);
    scroll_center.setPosition(position.x, position.y + size.x);
    scroll_bottom.setPosition(position.x, position.y + size.x + getScrollSizeY() - 2 * size.x);

}

void Scrollbar::setValue(short value) {
    scroll_value = value;

    if (scroll_value < min_value)
        scroll_value = min_value;

    else if ( max_value - scroll_length > 0 && scroll_value > max_value - scroll_length + 1)
        scroll_value = max_value - scroll_length + 1;

}

float Scrollbar::getScrollSizeY() {

    return float(size.y) * float(scroll_length)/float(max_value - min_value + 1);
}

void Scrollbar::scrollPositioning() {

    float delta_y = float(scroll_value) * (size.y/float(max_value-min_value+1));
    scroll_top.setPosition(position.x, position.y + delta_y);
    scroll_center.setPosition(position.x, position.y + size.x + delta_y);
    scroll_bottom.setPosition(position.x, position.y + size.x + getScrollSizeY() - 2 * size.x + delta_y);
}

bool Scrollbar::isSelected() {
    
    float min_x = scroll_top.getPosition().x;
    float min_y = scroll_top.getPosition().y;
    float max_x = scroll_bottom.getPosition().x + scroll_bottom.getSize().x;
    float max_y = scroll_bottom.getPosition().y + scroll_bottom.getSize().y;

    if (worldMousePosition.x >= min_x && worldMousePosition.x <= max_x && worldMousePosition.y >= min_y && worldMousePosition.y <= max_y)
        return true;
    else
        return false;
}

void Scrollbar::update() {
    scrollPositioning();
}

void Scrollbar::update(sf::Event& event) {
    
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isSelected()) {
                start_mouse_y = worldMousePosition.y - scroll_top.getPosition().y;
                is_pressed = true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            is_pressed = false;
        }
    }
    else if (is_pressed) {
        float scrollPos = worldMousePosition.y - start_mouse_y;

        if (scrollPos < position.y)
            scrollPos = position.y;

        if (scrollPos > position.y + size.y - getScrollSizeY())
            scrollPos = position.y + size.y - getScrollSizeY();

        setValue((scrollPos-position.y) * (max_value - min_value + 1) / size.y);
        scrollPositioning();
    }
    

}

void Scrollbar::draw() {

    window->draw(bar_top);
    window->draw(bar_center);
    window->draw(bar_bottom);

    window->draw(scroll_top);
    window->draw(scroll_center);
    window->draw(scroll_bottom);

}