#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class Building;
class Door;
class Floors;
class SingleTexture;

class Building : public GameObject {
public:
    sf::Vector2i size;

    std::vector < ItemOnMap* > _items;      // from item Manager
    std::vector < Furniture* > _furnitures; // from furniture Manager
    std::vector < Wall* > _walls;           // from wall Manager
    
    SingleTexture* top_walls;
    SingleTexture* walls;
    SingleTexture* bottom_walls;
    SingleTexture* windows;
    Door* _door;
    Floors* floors;

    sf::Sprite sprite;

    short x1, x2, y1, y2; // corners of building

    Building(int width, int height) : GameObject("empty", 0, 0);

    // FOR BUILDING EDITOR
    Building(std::string name) : GameObject(name, 0, 0)
    {
        type = GameObjectType::Building;
        loadWithPositioning();
    }

    // NORMAL INIT FOR GAME/MAP EDITOR
    Building(std::string name, float x, float y) : GameObject(name, x, y)
    {
        type = GameObjectType::Building;
        load();
    }

    virtual ~Building();

    void calculateCorners()
    {
        x1 = position.x - size.x / 2 * 16;
        x2 = position.x + size.x / 2 * 16;
        y1 = position.y - size.y * 16;
        y2 = position.y;
    }

    virtual void mouseHovering() override
    {
        if (worldMousePosition.x > x1 && worldMousePosition.x < x2 && worldMousePosition.y > y1 && worldMousePosition.y < y2)
            mouseIsHover = true;
        else
            mouseIsHover = false;
    }

    void addGameObject(GameObject* object);
    void deleteGameObject(GameObject* object);
    bool playerInside();

    void loadName(std::ifstream& file) {
        std::string line;
        std::getline(file, line);
    }

    void loadTexture2(std::ifstream& file);
    void loadSize(std::ifstream& file);
    void loadCollider();
    void loadDoor(std::ifstream& file);
    void loadWalls(std::ifstream& file);
    void loadWindows(std::ifstream& file);
    void loadFloors(std::ifstream& file);
    void loadGameObjects(std::ifstream& file);
    void load();
    void loadWithPositioning();
    void save(std::string filename);
    bool isPart(GameObject* object);

    virtual void update(float dt) override {
        calculateCorners();
        mouseHovering();
    }

    virtual void updateStatistic(float dt) override
    {
    }

    virtual void draw() override;

    virtual void drawAllStatistics() override
    {
    }
};

extern std::vector < Building* > buildings;
extern Building* building;

void addGameObjectsToMainLists();
void removeGameObjectsFromMainLists();
void createNewBuilding();
void loadBuildingFromFile(std::string filename = "assets/buildings/test_building.building");
void saveBuildingToFile(std::string filename = "assets/buildings/test_building.building") {
    building->save(filename);
}
