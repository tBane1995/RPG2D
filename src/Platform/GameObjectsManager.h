#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GameObject;

std::vector < GameObject* > selectedGameObjects;

Building* isPartOfBuilding(GameObject* object);
void selectGameObjects(float rect_x, float rect_y, float rect_w, float rect_h);
void deleteGameObjectFromMainLists(GameObject* object);
void clearAllMainListsOfGameObjects();
bool visiblings(GameObject* object);
void updateGameObjects();

void sortGameObjects()
{
    std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });
}

void drawGameObjects();
