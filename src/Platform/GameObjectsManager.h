#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GameObject;
class Building;

extern std::vector < GameObject* > selectedGameObjects;

Building* isPartOfBuilding(GameObject* object);
void selectGameObjects(float rect_x, float rect_y, float rect_w, float rect_h);
void selectGameObjects();
bool unselectGameObjects();
GameObject* getNewGameObject(GameObject* object);
void deleteGameObjectFromMainLists(GameObject* object);
void clearAllMainListsOfGameObjects();
bool visiblings(GameObject* object);
GameObject* getNewGameObject(GameObject* object);
void updateGameObjects();
void sortGameObjects();
void drawGameObjects();
