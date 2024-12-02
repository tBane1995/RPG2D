#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class Building;
class Door;
class Floors;
class Furniture;
class ItemOnMap;
class SingleTexture;
class Wall;

void clearAllMainListsOfGameObjects();

class Building : public GameObject {
public:
    sf::Vector2i size;

    std::vector < ItemOnMap* > _items;      // from item Manager
    std::vector < Furniture* > _furnitures; // from furniture Manager
    std::vector < Wall* > _walls;           // from wall Manager
    
    SingleTexture* top_walls = nullptr;
    SingleTexture* walls = nullptr;
    SingleTexture* bottom_walls = nullptr;
    SingleTexture* windows = nullptr;
    Door* _door = nullptr;
    Floors* floors = nullptr;

    sf::Sprite sprite;

    short x1, x2, y1, y2; // corners of building

    Building(int width, int height);

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

    virtual void mouseHovering() override;
    void deleteGameObject(GameObject* object);
    bool playerInside();

    void loadName(std::ifstream& file);
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
void deleteGameObjectsFromMainLists();
void createNewBuilding();
void loadBuildingFromFile(std::string filename = "assets/buildings/test_building.building");
void saveBuildingToFile(std::string filename = "assets/buildings/test_building.building");