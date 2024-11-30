#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define M_PI 3.14159265358979323846f

extern float angle;
extern float px, py;
extern int numPoints;

bool pointInRectangle(float px, float py, float rx, float ry, float rwidth, float rheight);
bool pointInEllipse(float px, float py, float cx, float cy, float rx, float ry);
bool intersectionTwoEllipses(float x1, float y1, float rx1, float ry1, float x2, float y2, float rx2, float ry2);
bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
bool intersectionRectangleWithElipse(float r_x, float r_y, float r_width, float r_height, float e_x, float e_y, float e_radiusx, float e_radiusy);
bool onSegment(sf::Vector2f _p, sf::Vector2f _q, sf::Vector2f _r);
int orientation(sf::Vector2f _p, sf::Vector2f _q, sf::Vector2f _r);
bool intersectionTwoLines(sf::Vector2f _p1, sf::Vector2f _q1, sf::Vector2f _p2, sf::Vector2f _q2);
