#pragma once
#include <string>
#include <vector>

class GameObject;

extern std::vector < GameObject* > prefabs;

GameObject* getPrefab(std::string name);
void loadPrefabs();
