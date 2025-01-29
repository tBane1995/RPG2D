#pragma once

#include <vector>
#include "MouseMovedGameObjects.h"
#include "Mouse.h"
#include "TerrainAndFloors.h"
#include "Water.h"
#include "Map.h"
#include "GameObjectsManager.h"
#include "Natures.h"
#include "Objects.h"
#include "Monsters.h"
#include "Items.h"
#include "FlatObjects.h"
#include "SmallObjects.h"
#include "Walls.h"
#include "Doors.h"
#include "Window.h"

enum class toolType { Cursor, Brush, RectBrush, Rectangle, Elipse, Fill, Eraser, AddGameObject };

extern std::vector<std::vector<std::vector<bool>>> brushes;

class Painter {
public:
    GameObject* prefabToPaint;
    std::vector < MouseMovedGameObject* > prefabsToPaint;

    toolType tool;
    short brushSize;

    std::vector<std::vector<bool>> brush;

    Painter();
    ~Painter();
    void setPrefabToPaint(GameObject* prefab);
    void setBrushSize(short size);
    void decreaseBrush();
    void increaseBrush();
    void coutBrush();
    void generateBrush();
    void generateRectBrush();
    void generateRectangle();
    void generateElipse();
    void clear();
    void addGameObjectsToMapAndLists(std::vector <MouseMovedGameObject*>& prefabsToPaint, bool selectGameObjects);
    void update();
    void draw();
    
};

extern Painter* painter;