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

#include <SFML/Graphics.hpp>
#include <iostream>
//size convention : 
/*
the cursor is 10% the size of the bar
so the bar starts and ends 5% before the limit defined by the variable location
*/


class Scrollbar2 {
public:
    //initialisation
    Scrollbar2(sf::Color color, bool sel, int loc0, int loc1, int siz0, int siz1, float progress);  //conversion
    void initShapes(int loc0, int loc1);    //initializing the bar
    void changeProgress(float pro);
    void updateCursor();
    void chooseColor(bool b);
    void drawTo(sf::RenderWindow* window);
    void render(bool clicked, sf::RenderWindow* window);
    bool detect(sf::RenderWindow* window);


private:
    float progress;     //float between 0 and 1, "percentage" of where the cursor is
    sf::Vector2f size;
    int location[2];
    sf::Color colorBar;
    sf::Color colorCursor;
    bool wasSelected = false;
    float oldMouseY = 0;
    sf::RectangleShape scroll;
    sf::RectangleShape bar;

};

class Scrollbar3 {
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

    bool is_pressed;

    Scrollbar3(sf::Vector2f size, sf::Vector2f position, short min_value, short max_value, short scroll_value, short scroll_length);
    float getScrollSizeY();
    void update();
    void update(sf::Event& event);
    void draw();
};