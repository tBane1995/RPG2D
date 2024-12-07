#pragma once
#include "Theme.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>


extern sf::Color idleColor;
extern sf::Color hoverColor;
extern sf::Color pressedColor;

extern sf::Color spriteIdleColor;
extern sf::Color spriteHoverColor;
extern sf::Color spritePressedColor;

enum class ButtonState { Idle, Hover, Pressed };

class SingleTexture;

class Btn {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Sprite sprite;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;

    Btn(float width = 64, float height = 64, sf::Vector2f position = sf::Vector2f(0, 0));
    Btn(Btn* btn);
    Btn(Btn* btn, sf::Vector2f position);
    Btn(SingleTexture* texture, sf::Vector2f position);

    virtual void setTexture(SingleTexture* texture);
    virtual void setPosition(sf::Vector2f position);
    virtual void changeColor();
    virtual void unclick();
    virtual bool hover();
    virtual bool click();

    virtual void update(float dt);
    virtual void draw();
};

class ButtonWithText {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Text text;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;
    short margin;

    ButtonWithText(std::string s, sf::Vector2f position = sf::Vector2f(0, 0), short characterSize = 17);
    ButtonWithText(std::string s, short characterSize);

    virtual void setPosition(sf::Vector2f position);
    virtual void changeColor();

    virtual void unclick();
    virtual bool hover();
    virtual bool click();

    virtual void update(float dt);
    virtual void draw();

};

class ButtonWithImage {
public:

    sf::Vector2f position;
    sf::Sprite sprite;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;

    ButtonWithImage();
    ButtonWithImage(ButtonWithImage* btn);
    ButtonWithImage(ButtonWithImage* btn, sf::Vector2f position);
    ButtonWithImage(SingleTexture* texture, sf::Vector2f position);

    virtual void setTexture(SingleTexture* texture);

    virtual void setPosition(sf::Vector2f position) {
        this->position = position;
        sprite.setPosition(position);
    }

    virtual void changeColor();

    virtual void unclick();
    virtual void hover();
    virtual void click();

    virtual void update(float dt);
    virtual void draw();
};


void initButtonsGlobalVariables();
