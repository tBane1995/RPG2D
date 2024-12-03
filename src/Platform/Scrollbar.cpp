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

Scrollbar2::Scrollbar2(sf::Color color, bool sel, int loc0, int loc1, int siz0, int siz1, float progress) {
    //conversion
    sf::Vector2f x(loc0, loc1);
    changeProgress(progress);

    //affectation
    sf::Vector2f v(siz0, siz1);
    size = v;
    location[0] = loc0;
    location[1] = loc1;
    //rectangle
    initShapes(loc0, loc1);
};

void Scrollbar2::initShapes(int loc0, int loc1) {
    //initializing the bar
    sf::Vector2f barSize(0.9 * size.x, size.y);
    scroll = sf::RectangleShape(barSize);
    scroll.setPosition(loc0, loc1 + 0.05 * size.y);
    scroll.setFillColor(sf::Color(100, 100, 100));
    scroll.setOutlineColor(sf::Color::White);

    //initializing the cursor
    //we need to manage the offset
    sf::Vector2f cursorSize(size.x, 0.1 * size.y);
    bar = sf::RectangleShape(cursorSize);
    bar.setPosition(loc0, loc1 + 0.90 * progress * size.y);
    bar.setFillColor(sf::Color(150, 150, 150));
    bar.setOutlineColor(sf::Color::White);

};

//getter & setter
void Scrollbar2::changeProgress(float pro) {
    if (pro > 1) {
        progress = 1;
    }
    else if (pro < 0) {
        progress = 0;
    }
    else {
        progress = pro;
    };
};

//render function

void Scrollbar2::updateCursor() {
    //bar.setPosition(location[0] + 0.90 * progress * size.x, location[1]);
    bar.setPosition(location[0], location[1] + 0.90 * progress * size.y);
};

void Scrollbar2::chooseColor(bool b) {
    //if selected we choose the brighter color
    if (b) {
        bar.setFillColor(sf::Color::White);
    }
    else {
        bar.setFillColor(sf::Color(150, 150, 150));
    };

};

void Scrollbar2::drawTo(sf::RenderWindow* window) {
    window->draw(scroll);
    window->draw(bar);
};

void Scrollbar2::render(bool clicked, sf::RenderWindow* window) {
    //if the button is and was clicked earlier we change progress to the corresponding value

    //detection
    bool detected = detect(window);
    bool isSelected;
    if (wasSelected) {
        isSelected = clicked;
    }
    else {
        isSelected = clicked && detected;
    }
    float mouseY = sf::Mouse::getPosition(*window).y;
    float delta = mouseY - oldMouseY;
    //true if the bar is "held"
    if (isSelected && wasSelected) {
        //we need to convert the delta in x into percentage
        float addProgress = delta / size.y / 0.9;
        changeProgress(progress + addProgress);
        updateCursor();
    }
    //memorizing old configuration
    oldMouseY = mouseY;
    wasSelected = isSelected;//isheld
    //choosing color and drawing
    chooseColor(isSelected || detected);
    drawTo(window);
};

bool Scrollbar2::detect(sf::RenderWindow* window) {
    bool result = true;
    //float mouseX = sf::Mouse::getPosition(*window).x;
    //float mouseY = sf::Mouse::getPosition(*window).y;
    
    float mouseX = worldMousePosition.x;
    float mouseY = worldMousePosition.y;
    //coordinate of corners
    float minX = location[0];
    float minY = location[1] - 0.9 * progress * size.y;
    float maxX = minX + size.x;
    float maxY = minY + 0.1 * size.y;
    //we check if the mouse is inside the frame
    result &= (minX < mouseX);
    result &= (mouseX < maxX);
    result &= (minY < mouseY);
    result &= (mouseY < maxY);
    return result;
};
//utilitary fonction
