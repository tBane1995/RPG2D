#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Tools.h"
#include "Buttons.h"

/*
sf::Vector2f paletteButtonSize = sf::Vector2f(80.0f, 80.0f);
sf::Vector2f palettePosition;
std::vector < GameObject* > availableGameObjects;
std::vector < GameObject* > terrainGameObjects;
std::vector < GameObject* > floorGameObjects;
std::vector < GameObject* > buildingGameObjects;


short paletteScroll;
short paletteCols;
short paletteRows;
*/

extern toolType tool;
extern short brushSize;
extern sf::Texture tileset;


class GameObject;

enum class PaletteType { MapEditor, BuildingEditor };

class PaletteButton : public ButtonWithImage {
public:

    GameObject* object;
    sf::Sprite sprite;

    PaletteButton(sf::Vector2f position);

    void setGameObject(GameObject* object);

    virtual void handleEvent(sf::Event& event) override;
    virtual void update() override;
    virtual void draw() override;
};

class Palette {
public:

    PaletteType type;
    sf::Vector2i size;

    std::vector < ButtonWithImage* > groupButtons;
    std::vector < ButtonWithImage* > toolsButtons;
    std::vector < PaletteButton* > paletteButtons;

    ButtonWithImage* selectedGroupButton = nullptr;
    ButtonWithImage* selectedToolButton = nullptr;
    PaletteButton* selectedPaletteButton = nullptr;

    ButtonWithImage* buttonUp = nullptr;
    ButtonWithImage* buttonDown = nullptr;

    short scroll;

    ButtonWithImage* btnGroupEmpty = nullptr;
    ButtonWithImage* btnGroupTerrain = nullptr;
    ButtonWithImage* btnGroupFloors = nullptr;
    ButtonWithImage* btnGroupWater = nullptr;
    ButtonWithImage* btnGroupFurnitures = nullptr;
    ButtonWithImage* btnGroupWalls = nullptr;
    ButtonWithImage* btnGroupMonsters = nullptr;
    ButtonWithImage* btnGroupFlatObjects = nullptr;
    ButtonWithImage* btnGroupItems = nullptr;
    ButtonWithImage* btnGroupNatures = nullptr;
    ButtonWithImage* btnGroupSmallObjects = nullptr;
    ButtonWithImage* btnGroupObjects = nullptr;

    ButtonWithImage* btnToolsEmpty = nullptr;
    ButtonWithImage* btnToolsCursor = nullptr;
    ButtonWithImage* btnToolsBrush = nullptr;
    ButtonWithImage* btnToolsRectBrush = nullptr;
    ButtonWithImage* btnToolsIncrease = nullptr;
    ButtonWithImage* btnToolsDecrease = nullptr;
    ButtonWithImage* btnToolsRectangle = nullptr;
    ButtonWithImage* btnToolsElipse = nullptr;
    ButtonWithImage* btnToolsFill = nullptr;
    ButtonWithImage* btnToolsEraser = nullptr;

    std::vector < GameObject* > availableGameObjects;

    Palette(PaletteType type);

    void deletePaletteButtons();
    void deleteNavButtons();
    void deleteToolsButtons();
    void deleteGroupButtons();

    void createPaletteButtons(short size_x, short size_y);

    void setTerrainObjectsToPalette();
    void setFloorsObjectsToPalette();
    void setWaterObjectsToPalette();
    void setFurnituresObjectsToPalette();
    void setWallsObjectsToPalette();
    void setMonstersObjectsToPalette();
    void setFlatObjectsToPalette();
    void setItemsObjectsToPalette();
    void setNaturesObjectsToPalette();
    void setObjectsToPalette();
    void setSmallObjectsToPalette();

    void loadPalette();
    void createNavButtons();
    void createToolsButtons();
    void createGroupButtons();

    void scrollUp() {
        if (scroll > 0)
            scroll -= 1;
    }

    void scrollDown() {

        short maxScroll = availableGameObjects.size() - size.x * size.y;
        if (maxScroll < 0)
            maxScroll = 0;

        if (scroll * size.x < maxScroll)
            scroll += 1;
    }

    void handleEvent(sf::Event& event);
    void update();
    void draw();
};

extern Palette* palette;
