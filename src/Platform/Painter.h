#pragma once
#include "MouseMovedGameObjects.h"
#include <vector>

void clearPrefabsToPaint();
void painterUpdate();
void painterDraw();
void addGameObjectsToMapAndLists(std::vector <MouseMovedGameObject*> &prefabsToPaint, bool selectGameObjects);
void addPrefabsToBuildingAndLists();