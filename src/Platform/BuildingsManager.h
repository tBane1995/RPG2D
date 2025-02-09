﻿#pragma once

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
    
    SingleTexture* texture_top_walls = nullptr;
    SingleTexture* texture_walls = nullptr;
    SingleTexture* texture_bottom_walls = nullptr;
    SingleTexture* texture_windows = nullptr;
    Door* _door = nullptr;
    Floors* floors = nullptr;

    sf::Sprite sprite;

    short x1, x2, y1, y2; // corners of building

    Building(int width, int height);
    Building(std::string name);
    Building(std::string name, float x, float y);
    ~Building();

    void calculateCorners();
    void mouseHovering();
    void addGameObject(GameObject* object);
    void deleteGameObject(GameObject* object);
    void addGameObjectsToMainLists();
    //void deleteGameObjectsFromMainLists();
    bool playerInside();
    bool isPart(GameObject* object);

    void loadTexture();
    void load(bool positioning=false);
    void save(std::string filename);
    void save();

    void update();
    void drawStatistics();
    void draw();
};

extern std::vector < Building* > buildings;
extern Building* building_to_edit;

void createNewBuilding();