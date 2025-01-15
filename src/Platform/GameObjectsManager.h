#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "MouseMovedGameObjects.h"

class GameObject;
class Building;

extern std::vector < MouseMovedGameObject* > selectedGameObjects;

Building* isPartOfBuilding(GameObject* object);
bool unselectGameObjects();
void selectGameObjects(float rect_x, float rect_y, float rect_w, float rect_h);
void selectGameObjects();
GameObject* getNewGameObject(GameObject* object);
void deleteGameObjectFromMainLists(GameObject* object);
void clearAllMainListsOfGameObjects();
bool visiblings(GameObject* object);
void updateGameObjects();
void sortGameObjects();
void drawGameObjects();
