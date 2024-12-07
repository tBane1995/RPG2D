#include "Scrollbar.h"
#include "Camera.h"
#include "Textures.h"
#include "Windows.h"
#include "Mouse.h"

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
    SingleTexture::SetTextureForSprite(&barTop, getSingleTexture("GUI/scrollbar/bar_top"));
    barTop.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barTop.setScale(bar.getSize().x / 16.0f, bar.getSize().x / 16.0f);

    barCenter = sf::Sprite();
    SingleTexture::SetTextureForSprite(&barCenter, getSingleTexture("GUI/scrollbar/bar_center"));
    barCenter.setPosition(position.x + cam->position.x, position.y + cam->position.y + scroll.getSize().x);
    barCenter.setScale(bar.getSize().x / 16.0f, (bar.getSize().y - 2.0f * bar.getSize().x) / 16.0f);

    barBottom = sf::Sprite();
    SingleTexture::SetTextureForSprite(&barBottom, getSingleTexture("GUI/scrollbar/bar_bottom"));
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
    SingleTexture::SetTextureForSprite(&scrollTop, getSingleTexture("GUI/scrollbar/scroll_top"));
    scrollTop.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollTop.setScale(scroll.getSize().x / 16.0f, scroll.getSize().x / 16.0f);

    scrollCenter = sf::Sprite();
    SingleTexture::SetTextureForSprite(&scrollCenter, getSingleTexture("GUI/scrollbar/scroll_center"));
    scrollCenter.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + scroll.getSize().x);
    scrollCenter.setScale(scroll.getSize().x / 16.0f, (getScrollHeight() - 2.0f * scroll.getSize().x) / 16.0f);

    scrollBottom = sf::Sprite();
    SingleTexture::SetTextureForSprite(&scrollBottom, getSingleTexture("GUI/scrollbar/scroll_bottom"));
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
    SingleTexture::SetTextureForSprite(&barTop, getSingleTexture("GUI/scrollbar/bar_top"));
    barTop.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    barTop.setScale(bar.getSize().x / 16.0f, bar.getSize().x / 16.0f);

    barCenter = sf::Sprite();
    SingleTexture::SetTextureForSprite(&barCenter, getSingleTexture("GUI/scrollbar/bar_center"));
    barCenter.setPosition(position.x + cam->position.x, position.y + cam->position.y + scroll.getSize().x);
    barCenter.setScale(bar.getSize().x / 16.0f, (bar.getSize().y - 2.0f * bar.getSize().x) / 16.0f);

    barBottom = sf::Sprite();
    SingleTexture::SetTextureForSprite(&barBottom, getSingleTexture("GUI/scrollbar/bar_bottom"));
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
    SingleTexture::SetTextureForSprite(&scrollTop, getSingleTexture("GUI/scrollbar/scroll_top"));
    scrollTop.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y);
    scrollTop.setScale(scroll.getSize().x / 16.0f, scroll.getSize().x / 16.0f);

    scrollCenter = sf::Sprite();
    SingleTexture::SetTextureForSprite(&scrollCenter, getSingleTexture("GUI/scrollbar/scroll_center"));
    scrollCenter.setPosition(scrollPosition.x + cam->position.x, scrollPosition.y + cam->position.y + scroll.getSize().x);
    scrollCenter.setScale(scroll.getSize().x / 16.0f, (getScrollHeight() - 2.0f * scroll.getSize().x) / 16.0f);

    scrollBottom = sf::Sprite();
    SingleTexture::SetTextureForSprite(&scrollBottom, getSingleTexture("GUI/scrollbar/scroll_bottom"));
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
    else
        return size.y;
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
