#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Borders;
class Building;
class Character;
class FlatObject;
class InventoryOnMap;
class ItemOnMap;
class Monster;
class Nature;
class Object;
class SmallObject;
class Terrain;
class Water;
class GameObject;

class Chunk {
public:
	sf::Vector2i coords;
    Terrain* terrain;
    Water* water;
    Borders* borders;

    sf::RectangleShape frame;
    sf::Text coordsText;

    std::vector < Nature* > _natures;
    std::vector < Object* > _objects;
    std::vector < ItemOnMap* > _items;
    std::vector < InventoryOnMap* > _inventories;
    std::vector < FlatObject* > _flatObjects;
    std::vector < Monster* > _monsters;
    std::vector < SmallObject* > _smallObjects;
    std::vector < Character* > _characters;
    std::vector < Building* > _buildings;

    bool visible;

    Chunk(short x, short y);
    ~Chunk();

    void addGameObjectsToMainLists();
    void removeGameObjectsFromMainLists();
    void deleteGameObject(GameObject* object);

	void update()
    {
	}

    void draw();
    void drawAllStatistics();

};

class Mapa {
public:
	std::vector < Chunk* > chunks;
    short width;
    short height;
    Mapa();

    Chunk* getChunk(short x, short y);
    Chunk* getChunk(sf::Vector2f position);

    void save(std::string filename = "world/world.map");
    void load(std::string filename = "world/world.map");

    bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {

        if (abs(x1 - x2) < (width1 + width2) / 2.0f && abs(y1 - y2) < (height1 + height2) / 2.0f)
            return true;

        return false;

    }

    void mapVisiblings();
    void generateBorders(Chunk* chunk);
    void generateBorders();

	void update() {

	}

    void draw();
    void drawStatistics();

};

extern Mapa* mapa;
