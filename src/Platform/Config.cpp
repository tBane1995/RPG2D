#include "Platform/Config.h"

Config::Config() {

}

Config::~Config() {

}

void Config::save() {
    _menu_bar = menu_bar;
    _palette = palette;
    _painter = painter;
    _clipboard = clipboard;
    //_mapa = mapa;
    _cam = cam;


    _gameObjects = gameObjects;
    _natures = natures;
    _objects = objects;
    _monsters = monsters;
    _characters = characters;
    _itemsOnMap = itemsOnMap;
    _inventoriesOnMap = inventoriesOnMap;
    _flatObjects = flatObjects;
    _smallObjects = smallObjects;
    _doors = doors;
    _furnitures = furnitures;
    _walls = walls;
    _buildings = buildings;
}

void Config::load() {

    delete menu_bar;
    delete palette;
    delete painter;
    delete clipboard;
    //delete mapa;
    delete cam;

    menu_bar = _menu_bar;
    palette = _palette;
    painter = _painter;
    clipboard = _clipboard;
    //mapa = _mapa;
    cam = _cam;

    // TO-DO - must prev a delete
    gameObjects = _gameObjects;
    natures = _natures;
    objects = _objects;
    monsters = _monsters;
    characters = _characters;
    itemsOnMap = _itemsOnMap;
    inventoriesOnMap = _inventoriesOnMap;
    flatObjects = _flatObjects;
    smallObjects = _smallObjects;
    doors = _doors;
    furnitures = _furnitures;
    walls = _walls;
    buildings = _buildings;
}

Config* config = nullptr;