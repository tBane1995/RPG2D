﻿#include "Collisions.h"

float angle;
float px, py;
int numPoints = 8;

bool intersectionTwoEllipses(float x1, float y1, float rx1, float ry1, float x2, float y2, float rx2, float ry2) {

    // Sprawdzenie punktów na pierwszej elipsie względem drugiej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = x1 + rx1 * std::cos(angle);
        py = y1 + ry1 * std::sin(angle);

        if (pointInEllipse(px, py, x2, y2, rx2, ry2)) {
            return true;
        }
    }

    // Sprawdzenie punktów na drugiej elipsie względem pierwszej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = x2 + rx2 * std::cos(angle);
        py = y2 + ry2 * std::sin(angle);

        if (pointInEllipse(px, py, x1, y1, rx1, ry1)) {
            return true;
        }
    }

    // Brak przecięcia
    return false;
}

bool intersectionRectangleWithElipse(float r_x, float r_y, float r_width, float r_height, float e_x, float e_y, float e_radiusx, float e_radiusy) {

    // Sprawdzenie punktów na pierwszej elipsie względem drugiej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = e_x + e_radiusx * std::cos(angle);
        py = e_y + e_radiusy * std::sin(angle);

        if (px > r_x - r_width / 2.0f && px < r_x + r_width / 2.0f && py > r_y - r_height / 2.0f && py < r_y + r_height / 2.0f)
            return true;

    }

    return false;

}

bool intersectionTwoLines( sf::Vector2f _p1, sf::Vector2f _q1, sf::Vector2f _p2, sf::Vector2f _q2) {

    // if line is a point return false
    if (_p1 == _q1 || _p2 == _q2)
        return false;

    int o1 = orientation(_p1, _q1, _p2);
    int o2 = orientation(_p1, _q1, _q2);
    int o3 = orientation(_p2, _q2, _p1);
    int o4 = orientation(_p2, _q2, _q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(_p1, _p2, _q1)) return true;

    if (o2 == 0 && onSegment(_p1, _q2, _q1)) return true;

    if (o3 == 0 && onSegment(_p2, _p1, _q2)) return true;

    if (o4 == 0 && onSegment(_p2, _q1, _q2)) return true;

    return false;
}
