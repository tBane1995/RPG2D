#pragma once
#include "MenuBar.h"
#include "Palette.h"
#include "ClipBoard.h"
#include "Map.h"
#include "PrefabToPaint.h"

#include "GameObjects.h"
#include "Natures.h"
#include "Objects.h"
#include "Monsters.h"
#include "Character.h"
#include "Items.h"
#include "FlatObjects.h"
#include "SmallObjects.h"
#include "Doors.h"
#include "Furnitures.h"
#include "Walls.h"
#include "BuildingsManager.h"


class Config {
public:

    MenuBar* _menu_bar;
    Palette* _palette;
    Clipboard* _clipboard;
    Mapa* _mapa;
    Painter* _painter;

    std::vector < GameObject* > _gameObjects;
    std::vector < Nature* > _natures;
    std::vector < Object*> _objects;
    std::vector < Monster* > _monsters;
    std::vector < Character* > _characters;
    std::vector < ItemOnMap* > _itemsOnMap;
    std::vector < InventoryOnMap* > _inventoriesOnMap;
    std::vector < FlatObject* > _flatObjects;
    std::vector < SmallObject* > _smallObjects;
    std::vector < Door* > _doors;
    std::vector < Furniture* > _furnitures;
    std::vector < Wall* > _walls;
    std::vector < Building* > _buildings;

    Config();
    ~Config();
    void save();
    void load();
};

extern Config* config;
