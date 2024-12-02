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

    virtual void update(float dt) override;
    virtual void draw() override;
};

class Palette {
public:

    PaletteType type;
    sf::Vector2i size;

    std::vector < ButtonWithImage* > groupButtons;
    std::vector < ButtonWithImage* > toolsButtons;
    std::vector < PaletteButton* > paletteButtons;

    ButtonWithImage* selectedGroupButton;
    ButtonWithImage* selectedToolButton;
    PaletteButton* selectedPaletteButton;

    ButtonWithImage* buttonUp;
    ButtonWithImage* buttonDown;

    short scroll;

    ButtonWithImage* btnGroupEmpty;
    ButtonWithImage* btnGroupTerrain;
    ButtonWithImage* btnGroupFloors;
    ButtonWithImage* btnGroupWater;
    ButtonWithImage* btnGroupFurnitures;
    ButtonWithImage* btnGroupWalls;
    ButtonWithImage* btnGroupMonsters;
    ButtonWithImage* btnGroupFlatObjects;
    ButtonWithImage* btnGroupItems;
    ButtonWithImage* btnGroupNatures;
    ButtonWithImage* btnGroupSmallObjects;
    ButtonWithImage* btnGroupObjects;

    ButtonWithImage* btnToolsEmpty;
    ButtonWithImage* btnToolsCursor;
    ButtonWithImage* btnToolsBrush;
    ButtonWithImage* btnToolsRectBrush;
    ButtonWithImage* btnToolsIncrease;
    ButtonWithImage* btnToolsDecrease;
    ButtonWithImage* btnToolsRectangle;
    ButtonWithImage* btnToolsElipse;
    ButtonWithImage* btnToolsFill;
    ButtonWithImage* btnToolsEraser;

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

    void unclickButtons();
    void hoverButtons();
    void clickButtons();

    void update(float dt);
    void draw();
};

extern Palette* palette;
