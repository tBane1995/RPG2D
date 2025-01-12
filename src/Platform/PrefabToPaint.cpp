#include "PrefabToPaint.h"
#include "GameObjects.h"

std::vector < GameObject* > prefabsToPaint;

void clearPrefabsToPaint() {

    for (auto& prefab : prefabsToPaint)
        delete prefab;


    prefabsToPaint.clear();
}