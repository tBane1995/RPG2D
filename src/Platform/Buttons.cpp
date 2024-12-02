#include "Buttons.h"
#include "Mouse.h"
#include "GUI.h"
#include "Camera.h"
#include "Time.h"
#include "Textures.h"
#include "Fonts.h"
#include "Window.h"

sf::Color idleColor = sf::Color(32.0f, 32.0f, 32.0f);
sf::Color hoverColor = sf::Color(48.0f, 48.0f, 48.0f);
sf::Color pressedColor = sf::Color(64.0f, 64.0f, 64.0f);

sf::Color spriteIdleColor = sf::Color(192.0f, 192.0f, 192.0f);
sf::Color spriteHoverColor = sf::Color(224.0f, 224.0f, 224.0f);
sf::Color spritePressedColor = sf::Color::White;

Btn::Btn(float width, float height, sf::Vector2f position)
{
    this->position = position;

    rect = sf::RectangleShape(sf::Vector2f(width, height));
    rect.setOrigin(width / 2, height / 2);
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    sprite = sf::Sprite();

    state = ButtonState::Idle;
    hover_func = { };
    onclick_func = { };

    clickTime = currentTime;

    changeColor();
}

Btn::Btn(Btn* btn)
{
    this->position = btn->position;

    this->rect = btn->rect;
    this->sprite = btn->sprite;

    state = ButtonState::Idle;
    this->hover_func = btn->hover_func;
    this->onclick_func = btn->onclick_func;

    clickTime = currentTime;

    changeColor();
}

Btn::Btn(Btn* btn, sf::Vector2f position)
{
    this->position = position;

    this->rect = btn->rect;
    this->rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    this->sprite = btn->sprite;
    this->sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    state = ButtonState::Idle;
    this->hover_func = btn->hover_func;
    this->onclick_func = btn->onclick_func;

    clickTime = currentTime;

    changeColor();
}

Btn::Btn(SingleTexture* texture, sf::Vector2f position)
{
    this->position = position;

    sf::Vector2f size = sf::Vector2f(texture->texture->getSize().x, texture->texture->getSize().y);
    rect = sf::RectangleShape(size);
    rect.setOrigin(size.x / 2, size.y / 2);
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    sprite = sf::Sprite();
    sprite.setTexture(*texture->texture);
    sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
    sf::Vector2f scale = sf::Vector2f(size.x / texture->texture->getSize().x, size.y / texture->texture->getSize().y);
    sprite.setScale(scale);
    sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    state = ButtonState::Idle;

    hover_func = { };
    onclick_func = { };

    clickTime = currentTime;

    changeColor();
}

void Btn::setTexture(SingleTexture* texture) {
    sf::Vector2f size = sf::Vector2f(texture->texture->getSize().x, texture->texture->getSize().y);
    rect = sf::RectangleShape(size);
    rect.setOrigin(size.x / 2, size.y / 2);
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    sprite = sf::Sprite();
    sprite.setTexture(*texture->texture);
    sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
    sf::Vector2f scale = sf::Vector2f(size.x / texture->texture->getSize().x, size.y / texture->texture->getSize().y);
    sprite.setScale(scale);
    sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    changeColor();
}

void Btn::setPosition(sf::Vector2f position) {
    this->position = position;
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
}

void Btn::changeColor() {

    if (state == ButtonState::Pressed) {
        rect.setFillColor(pressedColor);
        sprite.setColor(spritePressedColor);
    }
    else if (state == ButtonState::Hover) {
        rect.setFillColor(hoverColor);
        sprite.setColor(spriteHoverColor);
    }
    else {
        rect.setFillColor(idleColor);
        sprite.setColor(spriteIdleColor);
    }

}

void Btn::unclick() {
    if ((currentTime - clickTime).asSeconds() > 0.1f) {
        state = ButtonState::Idle;
        changeColor();
    }

}

bool Btn::hover() {
    if (state != ButtonState::Pressed) {

        float w = rect.getSize().x;
        float h = rect.getSize().y;
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

            state = ButtonState::Hover;
            changeColor();
            GUIwasHover = true;
            return true;
        }
    }
    else {
        // GUI WAS PRESSED
        GUIwasHover = true;
        return true;
    }

    return false;
}

bool Btn::click() {
    float w = rect.getSize().x;
    float h = rect.getSize().y;
    float x = rect.getPosition().x;
    float y = rect.getPosition().y;

    if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
        worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;

        if (onclick_func)
            onclick_func();

        return true;
    }

    return false;
}

void Btn::update(float dt) {
    rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
    sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
}

void Btn::draw() {
    window->draw(rect);
    if (sprite.getTexture() != nullptr)
        window->draw(sprite);
}



ButtonWithText::ButtonWithText(std::string s, sf::Vector2f position, short characterSize)
{
    this->position = position;
    margin = float(characterSize) * 0.4f;

    text = sf::Text();
    text.setFont(basicFont);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(characterSize);
    text.setString(s);
    text.setPosition(position.x + cam->position.x + float(margin)*0.95f, position.y + cam->position.y + float(margin) * 0.6f);

    rect = sf::RectangleShape();
    sf::Vector2f size;
    size.x = text.getLocalBounds().getSize().x + float(margin)*2.15f;
    size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
    rect.setSize(size);
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    state = ButtonState::Idle;
    hover_func = { };
    onclick_func = { };

    clickTime = currentTime;
}

ButtonWithText::ButtonWithText(std::string s, short characterSize) {

    this->position = sf::Vector2f(0,0);
    margin = float(characterSize) * 0.4f;

    text = sf::Text();
    text.setFont(basicFont);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(characterSize);
    text.setString(s);
    text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);

    rect = sf::RectangleShape();
    sf::Vector2f size;
    size.x = text.getLocalBounds().getSize().x + float(margin) * 2.15f;
    size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
    rect.setSize(size);
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    state = ButtonState::Idle;
    hover_func = { };
    onclick_func = { };

    clickTime = currentTime;
}

void ButtonWithText::setPosition(sf::Vector2f position) {
    this->position = position;
    text.setPosition(position.x + cam->position.x + margin, position.y + cam->position.y + float(margin) * 0.6f);
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

}

void ButtonWithText::changeColor() {

    if (state == ButtonState::Pressed) {
        rect.setFillColor(pressedColor);
    }
    else if (state == ButtonState::Hover) {
        rect.setFillColor(hoverColor);
    }
    else {
        rect.setFillColor(idleColor);
    }

}

void ButtonWithText::unclick() {
    if ((currentTime - clickTime).asSeconds() > 0.1f) {
        state = ButtonState::Idle;
        changeColor();
    }

}

bool ButtonWithText::hover() {
    if (state != ButtonState::Pressed) {

        float x1 = rect.getPosition().x;
        float x2 = x1 + rect.getSize().x;
        float y1 = rect.getPosition().y;
        float y2 = y1 + rect.getSize().y;

        if (worldMousePosition.x > x1 && worldMousePosition.x < x2 &&
            worldMousePosition.y > y1 && worldMousePosition.y < y2) {

            state = ButtonState::Hover;
            changeColor();
            GUIwasHover = true;
            return true;
        }
    }
    else {
        // GUI WAS PRESSED
        GUIwasHover = true;
        return true;
    }

    return false;
}

bool ButtonWithText::click() {

    float x1 = rect.getPosition().x;
    float x2 = x1 + rect.getSize().x;
    float y1 = rect.getPosition().y;
    float y2 = y1 + rect.getSize().y;

    if (worldMousePosition.x > x1 && worldMousePosition.x < x2 &&
        worldMousePosition.y > y1 && worldMousePosition.y < y2) {

        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;

        if (onclick_func)
            onclick_func();

        return true;
    }

    return false;
}

void ButtonWithText::update(float dt) {
    rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);
}

void ButtonWithText::draw() {

    window->draw(rect);
    window->draw(text);
}

ButtonWithImage::ButtonWithImage() {
    sprite = sf::Sprite();
    state = ButtonState::Idle;
    hover_func = { };
    onclick_func = { };

    clickTime = currentTime;
    changeColor();
}

ButtonWithImage::ButtonWithImage(ButtonWithImage* btn) {

    this->position = btn->position;
    this->sprite = btn->sprite;
    state = ButtonState::Idle;
    this->hover_func = btn->hover_func;
    this->onclick_func = btn->onclick_func;

    clickTime = currentTime;
    changeColor();
}

ButtonWithImage::ButtonWithImage(ButtonWithImage* btn, sf::Vector2f position)
{
    this->position = position;
    this->sprite = btn->sprite;
    state = ButtonState::Idle;
    this->hover_func = btn->hover_func;
    this->onclick_func = btn->onclick_func;

    clickTime = currentTime;
    changeColor();
}

ButtonWithImage::ButtonWithImage(SingleTexture* texture, sf::Vector2f position)
{
    this->position = position;

    sprite = sf::Sprite();

    state = ButtonState::Idle;

    if (texture != nullptr) {
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
    }

    hover_func = { };
    onclick_func = { };

    clickTime = currentTime;
    changeColor();
}

void ButtonWithImage::setTexture(SingleTexture* texture) {
    sprite = sf::Sprite();
    sprite.setTexture(*texture->texture);
    sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
}

void ButtonWithImage::changeColor()
{
    if (state == ButtonState::Pressed) {
        sprite.setColor(spritePressedColor);
    }
    else if (state == ButtonState::Hover) {
        sprite.setColor(spriteHoverColor);
    }
    else {
        sprite.setColor(spriteIdleColor);
    }

}

void ButtonWithImage::unclick()
{
    if ((currentTime - clickTime).asSeconds() > 0.1f) {
        state = ButtonState::Idle;
        changeColor();
    }
}

void ButtonWithImage::hover() {
    if (state != ButtonState::Pressed) {

        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

            state = ButtonState::Hover;
            changeColor();
            GUIwasHover = true;

            if (hover_func)
                hover_func();
        }
    }
    else {
        // GUI WAS PRESSED
        GUIwasHover = true;
    }
}

void ButtonWithImage::click() {
    float w = sprite.getTexture()->getSize().x;
    float h = sprite.getTexture()->getSize().y;
    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y;

    if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
        worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;

        if (onclick_func) {
            onclick_func();
        }


    }
}

void ButtonWithImage::update(float dt) {
    sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
}

void ButtonWithImage::draw() {

    window->draw(sprite);
}
