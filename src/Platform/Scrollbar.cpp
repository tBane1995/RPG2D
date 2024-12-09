#include "Scrollbar.h"
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

    sf::Vector2f p;
    p.x += cam->position.x + position.x;
    p.y += cam->position.y + position.y;

    // BAR RECT
    bar_top = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    bar_top.setPosition(p);
    bar_top.setFillColor(bar_color);

    bar_center = sf::RectangleShape(sf::Vector2f(size.x, size.y-2.0f*size.x));
    bar_center.setPosition(p.x, p.y + size.x);
    bar_center.setFillColor(bar_color);

    bar_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    bar_bottom.setPosition(p.x, p.y + size.y - size.x);
    bar_bottom.setFillColor(bar_color);
   
    // SCROLL RECT
    scroll_top = sf::RectangleShape(sf::Vector2f(size.x,size.x));
    scroll_top.setPosition(p.x, p.y+size.x);
    scroll_top.setFillColor(scroll_color);

    scroll_center = sf::RectangleShape(sf::Vector2f(size.x, getScrollSizeY()-2*size.x));
    scroll_center.setPosition(p.x, p.y+size.x+size.x);
    scroll_center.setFillColor(sf::Color::Green);

    scroll_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    scroll_bottom.setPosition(p.x, p.y+size.x+size.x+getScrollSizeY()-2*size.x);
    scroll_bottom.setFillColor(scroll_color);

    // BAR SPRITES
    spr_bar_top = sf::Sprite(*getSingleTexture("GUI/scrollbar/bar_top")->texture);
    spr_bar_top.setScale(size.x/16.0f, size.x/16.0f);
    spr_bar_top.setPosition(p);

    spr_bar_center = sf::Sprite(*getSingleTexture("GUI/scrollbar/bar_center")->texture);
    spr_bar_center.setScale(size.x/16.0f, (size.y-2.0f*size.x)/16.0f);
    spr_bar_center.setPosition(p.x, p.y + size.x);

    spr_bar_bottom = sf::Sprite(*getSingleTexture("GUI/scrollbar/bar_bottom")->texture);
    spr_bar_bottom.setScale(size.x/16.0f, size.x/16.0f);
    spr_bar_bottom.setPosition(p.x, p.y + size.y - size.x);

    // SCROLL SPRITES
    spr_scroll_top = sf::Sprite(*getSingleTexture("GUI/scrollbar/scroll_top")->texture);
    spr_scroll_top.setScale(size.x/16.0f, size.x/16.0f);
    spr_scroll_top.setPosition(p.x, p.y+size.x);

    spr_scroll_center = sf::Sprite(*getSingleTexture("GUI/scrollbar/scroll_center")->texture);
    spr_scroll_center.setScale(size.x/16.0f, (getScrollSizeY()-2*size.x)/16.0f);
    spr_scroll_center.setPosition(p.x, p.y+size.x+size.x);

    spr_scroll_bottom = sf::Sprite(*getSingleTexture("GUI/scrollbar/scroll_bottom")->texture);
    spr_scroll_bottom.setScale(size.x/16.0f, size.x/16.0f);
    spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY()-2*size.x);

}

void Scrollbar::setPosition(sf::Vector2f pos) {
    this->position = pos;

    sf::Vector2f p;
    p.x += cam->position.x + position.x;
    p.y += cam->position.y + position.y;
    // BAR RECT
    bar_top.setPosition(position);
    bar_center.setPosition(p.x, p.y + size.x);
    bar_bottom.setPosition(p.x, p.y + size.y - size.x);

    // BAR SPRITES
    spr_bar_top.setPosition(p);
    spr_bar_center.setPosition(p.x, p.y + size.x);
    spr_bar_bottom.setPosition(p.x, p.y + size.y - size.x);

    // SCROLL RECT
    scroll_top.setPosition(p.x, p.y+size.x);
    scroll_center.setPosition(p.x, p.y + size.x+size.x);
    scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x);

    // SCROLL SPRITES
    spr_scroll_top.setPosition(p.x, p.y+size.x);
    spr_scroll_center.setPosition(p.x, p.y + size.x + size.x);
    spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x);
}

void Scrollbar::setValue(short value) {
    scroll_value = value;

    if (scroll_value < min_value)
        scroll_value = min_value;

    else if ( scroll_value > max_value - scroll_length + 1)
        scroll_value = max_value - scroll_length + 1;

}

float Scrollbar::getScrollSizeY() {
    if (scroll_length > max_value - min_value + 1)
        return size.y - 2*size.x;
    else
        return float(size.y-2*size.x) * float(scroll_length)/float(max_value - min_value + 1);
}

void Scrollbar::scrollPositioning() {

    float delta_y = float(scroll_value) * ((size.y-2*size.x)/float(max_value-min_value+1));

    sf::Vector2f p;
    p.x += cam->position.x + position.x;
    p.y += cam->position.y + position.y;

    // SCROLL RECT
    scroll_top.setPosition(p.x, p.y + size.x + delta_y);
    scroll_center.setPosition(p.x, p.y + size.x + size.x + delta_y);
    scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x + delta_y);

    // SCROLL SPRITES
    spr_scroll_top.setPosition(p.x, p.y + size.x + delta_y);
    spr_scroll_center.setPosition(p.x, p.y + size.x + size.x + delta_y);
    spr_scroll_bottom.setPosition(p.x, p.y + size.x + size.x + getScrollSizeY() - 2 * size.x + delta_y);
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

        sf::Vector2f p;
        p.x += cam->position.x + position.x;
        p.y += cam->position.y + position.y;

        if (scrollPos < p.y)
            scrollPos = p.y;

        if (scrollPos > p.y + size.y - getScrollSizeY())
            scrollPos = p.y + size.y - getScrollSizeY();

        setValue((scrollPos-p.y) * (max_value - min_value + 1) / size.y);
        scrollPositioning();
    }
    

}

void Scrollbar::draw() {

    // BAR RECT
    window->draw(bar_top);
    window->draw(bar_center);
    window->draw(bar_bottom);

    // BAR SPRITES
    window->draw(spr_bar_top);
    window->draw(spr_bar_center);
    window->draw(spr_bar_bottom);

    // SCROLL RECT
    window->draw(scroll_top);
    window->draw(scroll_center);
    window->draw(scroll_bottom);

    // SCROLL SPRITES
    window->draw(spr_scroll_top);
    window->draw(spr_scroll_center);
    window->draw(spr_scroll_bottom);
}