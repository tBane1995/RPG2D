#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "Point.h"

extern float stepsize;

class GameObject;

namespace std {
    template < >
    struct hash < Point > {
        size_t operator()(const Point& p) const {
            return hash < float >()(p.x) ^ hash < float >()(p.y);
        }
    };
}

float heuristic(const Point& a, const Point& b);
std::vector < Point > getNeighbors(GameObject* object, const Point& p);
std::vector < Point > aStar(GameObject* object, const Point& goal);
