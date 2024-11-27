#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define M_PI 3.14159265358979323846f

extern float angle;
extern float px, py;
extern int numPoints;

bool pointInRectangle(float px, float py, float rx, float ry, float rwidth, float rheight) {

    if (px > rx - rwidth / 2.0f && px < rx + rwidth / 2.0f && py > ry - rheight / 2.0f && py < ry + rheight / 2.0f)
        return true;
    
    return false;
}

bool pointInEllipse(float px, float py, float cx, float cy, float rx, float ry) {
    // Sprawdza, czy punkt (px, py) znajduje się wewnątrz elipsy o środku (cx, cy) i półosiach rx, ry
    return (std::pow(px - cx, 2) / std::pow(rx, 2)) + (std::pow(py - cy, 2) / std::pow(ry, 2)) <= 1;
}

bool intersectionTwoEllipses(float x1, float y1, float rx1, float ry1, float x2, float y2, float rx2, float ry2);

bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {

    if ( abs(x1 - x2) < (width1 + width2) / 2.0f && abs(y1-y2) < (height1 + height2) / 2.0f )
        return true;

    return false;

}

bool intersectionRectangleWithElipse(float r_x, float r_y, float r_width, float r_height, float e_x, float e_y, float e_radiusx, float e_radiusy);

bool onSegment(sf::Vector2f _p, sf::Vector2f _q, sf::Vector2f _r)  {
    return _q.x <= std::max(_p.x, _r.x) && _q.x >= std::min(_p.x, _r.x) &&
        _q.y <= std::max(_p.y, _r.y) && _q.y >= std::min(_p.y, _r.y);
}

int orientation(sf::Vector2f _p, sf::Vector2f _q, sf::Vector2f _r)  {
    float val = (_q.y - _p.y) * (_r.x - _q.x) - (_q.x - _p.x) * (_r.y - _q.y);
    if (val == 0) return 0; // kolinearne

    return(val > 0) ? 1
        : 2; // 1 = zgodnie ze wskazówkami zegara, 2 = przeciwnie
}


bool intersectionTwoLines(sf::Vector2f _p1, sf::Vector2f _q1, sf::Vector2f _p2, sf::Vector2f _q2);
