#include "Scrollbar.h"
#include "Camera.h"
#include "Textures.h"
#include "Windows.h"
#include "Mouse.h"
#include <iostream>

Scrollbar::Scrollbar(sf::Vector2f size, sf::Vector2f position, float minValue, float maxValue, float scrollValue, float scrollLength) {
    this->size = size;
    this->position = position;

    this->minValue = minValue;
    this->maxValue = maxValue;
    this->scrollValue = scrollValue;

    this->scrollLength = scrollLength;

    pressed = false;

    // create bar
    bar = sf::RectangleShape(size);
    bar.setFillColor(sf::Color::Blue);
    bar.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    barTop = sf::Sprite();
    barTop.setTexture(*getSingleTexture("GUI/scrollbar/bar_top")->texture);
    barTop.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barTop.setScale(bar.getSize().x / 16.0f, bar.getSize().x / 16.0f);

    barCenter = sf::Sprite();
    barCenter.setTexture(*getSingleTexture("GUI/scrollbar/bar_center")->texture);
    barCenter.setPosition(position.x + cam->position.x, position.y + cam->position.y + scroll.getSize().x);
    barCenter.setScale(bar.getSize().x / 16.0f, (bar.getSize().y - 2.0f * bar.getSize().x) / 16.0f);

    barBottom = sf::Sprite();
    barBottom.setTexture(*getSingleTexture("GUI/scrollbar/bar_bottom")->texture);
    barBottom.setPosition(position.x + cam->position.x, position.y + cam->position.y + bar.getSize().y - bar.getSize().x);
    barBottom.setScale(bar.getSize().x / 16.0f, bar.getSize().x / 16.0f);

    // create scroll
    sf::Vector2f scrollPosition;
    scrollPosition.x = position.x;
    scrollPosition.y = position.y + (scrollValue - minValue) / (maxValue - scrollLength + 1) * (size.y - getScrollHeight());

    scroll = sf::RectangleShape(sf::Vector2f(size.x, getScrollHeight()));
    scroll.setOrigin(0, 0);
    scroll.setFillColor(sf::Color::Red);
    scroll.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);

    scrollTop = sf::Sprite();
    scrollTop.setTexture(*getSingleTexture("GUI/scrollbar/scroll_top")->texture);
    scrollTop.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollTop.setScale(scroll.getSize().x / 16.0f, scroll.getSize().x / 16.0f);

    scrollCenter = sf::Sprite();
    scrollCenter.setTexture(*getSingleTexture("GUI/scrollbar/scroll_center")->texture);
    scrollCenter.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + scroll.getSize().x);
    scrollCenter.setScale(scroll.getSize().x / 16.0f, (getScrollHeight() - 2.0f * scroll.getSize().x) / 16.0f);

    scrollBottom = sf::Sprite();
    scrollBottom.setTexture(*getSingleTexture("GUI/scrollbar/scroll_bottom")->texture);
    scrollBottom.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + getScrollHeight() - scroll.getSize().x);
    scrollBottom.setScale(scroll.getSize().x / 16.0f, scroll.getSize().x / 16.0f);

}

Scrollbar::Scrollbar(sf::Vector2f size, float minValue, float maxValue, float scrollValue, float scrollLength) {
    this->size = size;
    this->position = sf::Vector2f(0, 0);

    this->minValue = minValue;
    this->maxValue = maxValue;
    this->scrollValue = scrollValue;

    this->scrollLength = scrollLength;

    pressed = false;

    // create bar
    bar = sf::RectangleShape(size);
    bar.setFillColor(sf::Color::Blue);
    bar.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    barTop = sf::Sprite();
    barTop.setTexture(*getSingleTexture("GUI/scrollbar/bar_top")->texture);
    barTop.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barTop.setScale(bar.getSize().x / 16.0f, bar.getSize().x / 16.0f);

    barCenter = sf::Sprite();
    barCenter.setTexture(*getSingleTexture("GUI/scrollbar/bar_center")->texture);
    barCenter.setPosition(position.x + cam->position.x, position.y + cam->position.y + scroll.getSize().x);
    barCenter.setScale(bar.getSize().x / 16.0f, (bar.getSize().y - 2.0f * bar.getSize().x) / 16.0f);

    barBottom = sf::Sprite();
    barBottom.setTexture(*getSingleTexture("GUI/scrollbar/bar_bottom")->texture);
    barBottom.setPosition(position.x + cam->position.x, position.y + cam->position.y + bar.getSize().y - bar.getSize().x);
    barBottom.setScale(bar.getSize().x / 16.0f, bar.getSize().x / 16.0f);

    // create scroll
    sf::Vector2f scrollPosition;
    scrollPosition.x = position.x;
    scrollPosition.y = position.y + (scrollValue - minValue) / (maxValue - scrollLength + 1) * (size.y - getScrollHeight());

    scroll = sf::RectangleShape(sf::Vector2f(size.x, getScrollHeight()));
    scroll.setOrigin(0, 0);
    scroll.setFillColor(sf::Color::Red);
    scroll.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);

    scrollTop = sf::Sprite();
    scrollTop.setTexture(*getSingleTexture("GUI/scrollbar/scroll_top")->texture);
    scrollTop.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollTop.setScale(scroll.getSize().x / 16.0f, scroll.getSize().x / 16.0f);

    scrollCenter = sf::Sprite();
    scrollCenter.setTexture(*getSingleTexture("GUI/scrollbar/scroll_center")->texture);
    scrollCenter.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + scroll.getSize().x);
    scrollCenter.setScale(scroll.getSize().x / 16.0f, (getScrollHeight() - 2.0f * scroll.getSize().x) / 16.0f);

    scrollBottom = sf::Sprite();
    scrollBottom.setTexture(*getSingleTexture("GUI/scrollbar/scroll_bottom")->texture);
    scrollBottom.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + getScrollHeight() - scroll.getSize().x);
    scrollBottom.setScale(scroll.getSize().x / 16.0f, scroll.getSize().x / 16.0f);

}

void Scrollbar::setValue(int value) {

    scrollValue = value;

    if (scrollValue > maxValue - scrollLength + 1)
        scrollValue = maxValue - scrollLength + 1;

    if (scrollValue < minValue)
        scrollValue = minValue;

}

float Scrollbar::getScrollHeight() {
    if (maxValue - minValue + 1 >= scrollLength) {
        float height = scrollLength / maxValue * size.y;
        if (height < size.x * 3)
            height = size.x * 3;

        return height;
    }
    else {
        std::cout << "scroll jest za maly\n";
        return size.y;
    }
        
}

void Scrollbar::setPosition(sf::Vector2f position) {
    this->position = position;

    update();
}

void Scrollbar::update() {
    // bar positioning
    bar.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barTop.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barCenter.setPosition(position.x + cam->position.x, position.y + cam->position.y + scroll.getSize().x);
    barBottom.setPosition(position.x + cam->position.x, position.y + cam->position.y + bar.getSize().y - bar.getSize().x);

    sf::Vector2f scrollPosition;
    scrollPosition.x = position.x;
    scrollPosition.y = position.y + (scrollValue - minValue) / (maxValue - scrollLength + 1) * (size.y - getScrollHeight());

    // scroll positioning
    scroll.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollTop.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollCenter.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + scroll.getSize().x);
    scrollBottom.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + getScrollHeight() - scroll.getSize().x);
}

void Scrollbar::update(sf::Event& event) {

    // bar positioning
    bar.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barTop.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barCenter.setPosition(position.x + cam->position.x, position.y + cam->position.y + scroll.getSize().x);
    barBottom.setPosition(position.x + cam->position.x, position.y + cam->position.y + bar.getSize().y - bar.getSize().x);

    sf::Vector2f scrollPosition;
    scrollPosition.x = position.x;
    scrollPosition.y = position.y + (scrollValue - minValue) / (maxValue - scrollLength + 1) * (size.y - getScrollHeight());

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            if (scroll.getGlobalBounds().contains(worldMousePosition)) {
                pressed = true;
                mouseStartPos = mousePos;
                mouseOffset = scrollPosition - mousePos;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            pressed = false;
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        if (pressed) {
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

            if (fabs(mousePos.x - mouseStartPos.x) > 100) // Te zachwoanie scrolla w Windowsie jak odjedziesz za daleko w bok
                mousePos = mouseStartPos;

            float value = (mousePos.y + mouseOffset.y - position.y) / (size.y - getScrollHeight()) * (maxValue - minValue) + minValue;

            setValue(value);
        }
    }

    // scroll positioning
    scroll.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollTop.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollCenter.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + scroll.getSize().x);
    scrollBottom.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + getScrollHeight() - scroll.getSize().x);
}

void Scrollbar::draw() {
    window->draw(bar);
    window->draw(barTop);
    window->draw(barBottom);
    window->draw(barCenter);

    window->draw(scroll);
    window->draw(scrollTop);
    window->draw(scrollCenter);
    window->draw(scrollBottom);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Scrollbar3::Scrollbar3(sf::Vector2f size, sf::Vector2f position, short min_value, short max_value, short scroll_value, short scroll_length) {

    this->size = size;
    this->position = position;

    this->min_value = min_value;
    this->max_value = max_value;
    this->scroll_length = scroll_length;

    setValue(scroll_value);

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
    scroll_top.setPosition(position.x+16, position.y);
    scroll_top.setFillColor(scroll_color);

    scroll_center = sf::RectangleShape(sf::Vector2f(size.x, getScrollSizeY()-2*size.x));
    scroll_center.setPosition(position.x+16, position.y+size.x);
    scroll_center.setFillColor(sf::Color::Green);

    scroll_bottom = sf::RectangleShape(sf::Vector2f(size.x, size.x));
    scroll_bottom.setPosition(position.x+16, position.y+size.x+getScrollSizeY()-2*size.x);
    scroll_bottom.setFillColor(scroll_color);
}

void Scrollbar3::setValue(short value) {
    scroll_value = value;

    if (scroll_value < min_value)
        scroll_value = min_value;

    if (scroll_value > max_value - scroll_value + 1)
        scroll_value = max_value - scroll_value + 1;

}

float Scrollbar3::getScrollSizeY() {

    return float(size.y) * float(scroll_length)/float(max_value - min_value + 1);
}

void Scrollbar3::update() {

}

void Scrollbar3::update(sf::Event& event) {

}

void Scrollbar3::draw() {

    window->draw(bar_top);
    window->draw(bar_center);
    window->draw(bar_bottom);

    window->draw(scroll_top);
    window->draw(scroll_center);
    window->draw(scroll_bottom);

}