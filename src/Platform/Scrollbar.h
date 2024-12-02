#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Scrollbar {
public:
    sf::Vector2f size;
    sf::Vector2f position;
    float minValue;
    float maxValue;
    float scrollValue;
    float scrollLength;

    sf::RectangleShape bar;
    sf::Sprite barTop;
    sf::Sprite barBottom;
    sf::Sprite barCenter;

    sf::RectangleShape scroll;
    sf::Sprite scrollTop;
    sf::Sprite scrollBottom;
    sf::Sprite scrollCenter;

    //////////////////////////////////////
    bool pressed;
    sf::Vector2f mouseStartPos;
    sf::Vector2f mouseOffset;
    //////////////////////////////////////

    Scrollbar(sf::Vector2f size, sf::Vector2f position, float minValue, float maxValue, float scrollValue, float scrollLength);
    Scrollbar(sf::Vector2f size, float minValue, float maxValue, float scrollValue, float scrollLength);

    ~Scrollbar() {

    }

    void setValue(int value);
    float getScrollHeight();
    void setPosition(sf::Vector2f position);
    void update();
    void update(sf::Event& event);
    void draw();
};
