﻿#include "Palette.h"
#include "Window.h"
#include "Textures.h"
#include "GameObjects.h"
#include "Water.h"
#include "Camera.h"
#include "Buttons.h"
#include "Objects.h"
#include "TerrainAndFloors.h"
#include "Prefabs.h"
#include "PrefabToPaint.h"
#include "Tips.h"
#include "Fonts.h"
#include "Shaders.h"
#include "Items.h"
#include "GUI.h"
#include "GameObjectsManager.h"
#include <iostream>

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

sf::Texture tileset;


PaletteButton::PaletteButton(sf::Vector2f position) : ButtonWithImage(getSingleTexture("GUI/slot2"), position) {
    object = nullptr;
}

void PaletteButton::setGameObject(GameObject* object) {
    this->object = object;

    sprite = sf::Sprite();

    if (object != nullptr) {
        SingleTexture* CurrentTextureForObject = nullptr;
        if (object->type != GameObjectType::Water) {
            CurrentTextureForObject = object->texture;
            SingleTexture::SetTextureForSprite(&sprite, CurrentTextureForObject);
        }
        else
        {
            CurrentTextureForObject = dynamic_cast<WaterPrefab*>(object)->terrain->texture;
            SingleTexture::SetTextureForSprite(&sprite, CurrentTextureForObject);
        }

        if (object->type == GameObjectType::Terrain || object->type == GameObjectType::Water) {
            sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
            sprite.setOrigin(8, 8);
            sprite.setScale(3.0f, 3.0f);
        }
        else
        {
            sf::Vector2f o; // origin
            o.x = CurrentTextureForObject->getSize().x / 2.0f;
            o.y = CurrentTextureForObject->getSize().y / 2.0f;
            sprite.setOrigin(o);

            sf::Vector2f s; // scale

            if (sprite.getLocalBounds().getSize().x > sprite.getLocalBounds().getSize().y) {
                s.x = 64.0f / float(CurrentTextureForObject->getSize().x) * 0.75f;
                s.y = 64.0f / float(CurrentTextureForObject->getSize().x) * 0.75f;
            }
            else if (sprite.getLocalBounds().getSize().x < sprite.getLocalBounds().getSize().y) {
                s.x = 64.0f / float(CurrentTextureForObject->getSize().y) * 0.75f;
                s.y = 64.0f / float(CurrentTextureForObject->getSize().y) * 0.75f;
            }
            else {
                s.x = 64.0f / float(CurrentTextureForObject->getSize().x) * 0.75f;
                s.y = 64.0f / float(CurrentTextureForObject->getSize().x) * 0.75f;
            }

            sprite.setScale(s);
        }
    }

    sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

}

void PaletteButton::handleEvent(sf::Event& event) {
    // TO-DO

    ButtonWithImage::handleEvent(event);

    if (ButtonWithImage::state == ButtonState::Pressed) {
        if (object != nullptr)
            std::cout << "kliknieto: " << object->name << "\n";
        else
            std::cout << "kliknieto: nullptr\n";
    }
    
}

void PaletteButton::update(bool hover_action) {
    ButtonWithImage::update(hover_action);
    sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
}

void PaletteButton::draw() {
    ButtonWithImage::draw();

    if (object != nullptr) {
        if (object->type == GameObjectType::Water) {
            window->draw(sprite, dynamic_cast<WaterPrefab*>(object)->shader->shader);
        }
        else
            window->draw(sprite);
    }



}

Palette::Palette(PaletteType type) {
    this->type = type;

    createPaletteButtons(5, 7);
    createToolsButtons();
    createNavButtons();
    createGroupButtons();


    if (type == PaletteType::MapEditor)        selectedGroupButton = btnGroupTerrain;
    if (type == PaletteType::BuildingEditor)   selectedGroupButton = btnGroupFloors;

    selectedToolButton = btnToolsCursor;
    selectedPaletteButton = nullptr;

    if (type == PaletteType::MapEditor)       setTerrainObjectsToPalette();
    if (type == PaletteType::BuildingEditor)  setFloorsObjectsToPalette();

    loadPalette();
}

void Palette::deletePaletteButtons() {
    if (paletteButtons.size() > 0) {
        for (int i = 0; i < paletteButtons.size(); i++) {
            delete paletteButtons[i];
        }

        paletteButtons.clear();
    }
}

void Palette::deleteNavButtons() {
    if (buttonUp != nullptr) {
        delete buttonUp;
        buttonUp = nullptr;
    }

    if (buttonDown != nullptr) {
        delete buttonDown;
        buttonDown = nullptr;
    }
}

void Palette::deleteToolsButtons() {
    if (toolsButtons.size() > 0) {
        for (int i = 0; i < toolsButtons.size(); i++) {
            delete toolsButtons[i];
        }

        toolsButtons.clear();
    }

    std::cout << "delete Tools Buttons\n";
}

void Palette::deleteGroupButtons() {
    if (groupButtons.size() > 0) {
        for (int i = 0; i < groupButtons.size(); i++) {
            delete groupButtons[i];
        }

        groupButtons.clear();
    }
}

void Palette::createPaletteButtons(short size_x, short size_y) {

    deletePaletteButtons();
    
    size.x = size_x;
    size.y = size_y;

    sf::Vector2f start_pos; // left bottom 
    start_pos.x = 0;
    start_pos.x = screenWidth / 2.0f - size.x * 64 + 32;
    start_pos.y = screenHeight / 2.0f - 37 - 32;

    for (short y = 0; y < size.y; y++) {
        for (short x = 0; x < size.x; x++) {

            sf::Vector2f pos;
            pos.x = start_pos.x + x * 64;
            pos.y = start_pos.y - (size.y - 1 - y) * 64;

            PaletteButton* btn = new PaletteButton(pos);
            paletteButtons.push_back(btn);
        }
    }



}

void Palette::setTerrainObjectsToPalette() {

    availableGameObjects.clear();

    // skip the empty terrainGameObjects[0]

    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[5]);

    availableGameObjects.push_back(terrainGameObjects[6]);
    availableGameObjects.push_back(terrainGameObjects[7]);
    availableGameObjects.push_back(terrainGameObjects[8]);
    availableGameObjects.push_back(terrainGameObjects[9]);
    availableGameObjects.push_back(terrainGameObjects[10]);

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);


    short id = countOfBasicTerrain;
    // SET - SANDS_WATER
    id += 8;    // skip the SET - SANDS_WATER
    id += 8;    // skip the SET - WATER_SANDS

    // SET - SANDS_GRASS
    availableGameObjects.push_back(terrainGameObjects[id]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 2]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[2]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 5]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 7]);

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    // SET - GRASS_SANDS
    id += 8;
    availableGameObjects.push_back(terrainGameObjects[id + 0]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 2]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[1]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 5]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 7]);

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    // SET - GRASS_GRAVEL
    id += 8;
    availableGameObjects.push_back(terrainGameObjects[id + 0]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 2]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[3]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 5]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 7]);

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    // SET - GRAVEL_GRASS
    id += 8;
    availableGameObjects.push_back(terrainGameObjects[id + 0]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 1]);
    availableGameObjects.push_back(terrainGameObjects[id + 2]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 3]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[4]);
    availableGameObjects.push_back(terrainGameObjects[id + 4]);

    availableGameObjects.push_back(terrainGameObjects[id + 5]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 6]);
    availableGameObjects.push_back(terrainGameObjects[id + 7]);
}

void Palette::setFloorsObjectsToPalette() {

    availableGameObjects.clear();

    for (auto& floor : floorGameObjects)
        availableGameObjects.push_back(floor);

}

void Palette::setWaterObjectsToPalette() {

    availableGameObjects.clear();

    for (int i = 0; i < countOfBasicWater - 1; i++) {

        // WATER_TERRAIN
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 0]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 2]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 3]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 4]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 3]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 4]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 3]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(terrainGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 4]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 5]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 6]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 6]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 6]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 7]);

        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);
        availableGameObjects.push_back(nullptr);

        // TERRAIN_WATER
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 8]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 9]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 9]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 9]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 10]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 11]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 12]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 11]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 12]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 11]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[i + 1]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 12]);

        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 13]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 14]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 14]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 14]);
        availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 15]);

        if (i != countOfBasicWater - 2) {
            availableGameObjects.push_back(nullptr);
            availableGameObjects.push_back(nullptr);
            availableGameObjects.push_back(nullptr);
            availableGameObjects.push_back(nullptr);
            availableGameObjects.push_back(nullptr);
        }
    }




}

void Palette::setFurnituresObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& p : prefabs)
        if (p->type == GameObjectType::Furniture)
            availableGameObjects.push_back(p);
}

void Palette::setWallsObjectsToPalette() {
    availableGameObjects.clear();

    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_0"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_2"));

    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_4"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/mud_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_5"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_6"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_7"));
    availableGameObjects.push_back(getPrefab("walls/set_mud_wall_8"));

    availableGameObjects.push_back(getPrefab("walls/mud_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/mud_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/mud_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/mud_wall_overgrown"));

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_0"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_2"));

    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_4"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/stone_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_5"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_6"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_7"));
    availableGameObjects.push_back(getPrefab("walls/set_stone_wall_8"));

    availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown"));

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_0"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_2"));

    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_4"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/wooden_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_5"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_6"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_7"));
    availableGameObjects.push_back(getPrefab("walls/set_wooden_wall_8"));

    availableGameObjects.push_back(getPrefab("walls/wooden_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/wooden_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/wooden_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/wooden_wall_overgrown"));

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_0"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_2"));

    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_4"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/brick_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_5"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_6"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_7"));
    availableGameObjects.push_back(getPrefab("walls/set_brick_wall_8"));

    availableGameObjects.push_back(getPrefab("walls/brick_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/brick_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/brick_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/brick_wall_overgrown"));

    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);
    availableGameObjects.push_back(nullptr);

    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_0"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_1"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_2"));

    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_4"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_3"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/mulch_wall"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_3"));

    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_5"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_6"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_7"));
    availableGameObjects.push_back(getPrefab("walls/set_mulch_wall_8"));

    availableGameObjects.push_back(getPrefab("walls/mulch_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/mulch_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/empty_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/mulch_wall_overgrown"));
    availableGameObjects.push_back(getPrefab("walls/mulch_wall_overgrown"));
}

void Palette::setMonstersObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& p : prefabs) {
        if (p->type == GameObjectType::Monster) {
            availableGameObjects.push_back(p);
        }
    }
}

void Palette::setFlatObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& f : prefabs) {
        if (f->type == GameObjectType::FlatObject) {
            availableGameObjects.push_back(f);
        }
    }
}

void Palette::setItemsObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& i : items) {
        availableGameObjects.push_back(getPrefab(i->name));
    }

}

void Palette::setNaturesObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& p : prefabs) {
        if (p->type == GameObjectType::Nature) {
            availableGameObjects.push_back(p);
        }
    }
}

void Palette::setObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& p : prefabs) {
        if (p->type == GameObjectType::Object) {
            availableGameObjects.push_back(p);
        }
    }

    availableGameObjects.push_back(getPrefab("doors/wooden_gate"));
}

void Palette::setSmallObjectsToPalette() {
    availableGameObjects.clear();

    for (auto& p : prefabs) {
        if (p->type == GameObjectType::SmallObject) {
            availableGameObjects.push_back(p);
        }
    }
}

void Palette::loadPalette() {
    for (int i = 0; i < paletteButtons.size(); i++) {

        int index = i + scroll * size.x;

        GameObject* object;
        (index < availableGameObjects.size()) ? object = availableGameObjects[index] : object = nullptr;
        paletteButtons[i]->setGameObject(object);

        if (object != nullptr) {
            auto button = paletteButtons[i];

            paletteButtons[i]->hover_func = [this, button]() {
                if (tip == nullptr || tip->btn != button) {
                    sf::Vector2f pos;
                    pos.x = button->position.x - button->sprite.getGlobalBounds().width / 2.0f;
                    pos.y = button->position.y + button->sprite.getGlobalBounds().height / 2.0f;
                    if (tip != nullptr)
                        delete tip;
                    tip = new Tip(ConvertUtf8ToWide(button->object->name), pos, button);       // TO-DO delete convert and use std::wstring
                }
                };

            paletteButtons[i]->onclick_func = [this, button]() {

                selectedPaletteButton = button;
                painter->setPrefabToPaint(button->object);

                if (button->object->type == GameObjectType::Terrain || button->object->type == GameObjectType::Floor || button->object->type == GameObjectType::Water) {
                    if (painter->tool == toolType::Cursor || painter->tool == toolType::AddGameObject) {
                        painter->tool = toolType::Brush;
                        selectedToolButton = btnToolsBrush;
                    }
                }
                else {
                    painter->tool = toolType::AddGameObject;
                    selectedToolButton = btnToolsEmpty;
                }
                };
        }
        else {
            paletteButtons[i]->hover_func = []() {};
            paletteButtons[i]->onclick_func = []() {};
        }
    }
}

void Palette::createNavButtons() {

    deleteNavButtons();

    scroll = 0;

    sf::Vector2f pos;
    pos.x = screenWidth / 2.0f - 160;

    pos.y = screenHeight / 2.0f - 37.0f - float(size.y) * 64.0f - 37.0f / 2.0f;
    buttonUp = new ButtonWithImage(getSingleTexture("GUI/wideArrowUp2"), pos);
    buttonUp->onclick_func = [this]() {
        scrollUp();
        loadPalette();
        };

    pos.y = screenHeight / 2.0f - 37.0f / 2.0f;
    buttonDown = new ButtonWithImage(getSingleTexture("GUI/wideArrowDown2"), pos);
    buttonDown->onclick_func = [this]() {
        scrollDown();
        loadPalette();
        };

}

void Palette::createToolsButtons() {
    // delete old Tools Buttons
    deleteToolsButtons();

    std::cout << "create Tools Buttons\n";
    btnToolsEmpty = new ButtonWithImage();
    btnToolsEmpty->setTexture(getSingleTexture("GUI/toolButtons/toolbutton"));

    btnToolsCursor = new ButtonWithImage();
    btnToolsCursor->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-cursor"));
    btnToolsCursor->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsCursor) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Cursor", btnToolsCursor);
        }
            


        };
    btnToolsCursor->onclick_func = [this]() {
        selectedToolButton = btnToolsCursor;
        painter->tool = toolType::Cursor;
        painter->setPrefabToPaint(nullptr);
        selectedPaletteButton = nullptr;
        };


    btnToolsBrush = new ButtonWithImage();
    btnToolsBrush->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-brush"));
    btnToolsBrush->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsBrush) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Brush", btnToolsBrush);

        }
            

        };
    btnToolsBrush->onclick_func = [this]() {
        selectedToolButton = btnToolsBrush;
        painter->tool = toolType::Brush;
        if (selectedPaletteButton == nullptr)
            selectedPaletteButton = paletteButtons[1];

        std::cout << selectedPaletteButton->object->name << "\n";
        };


    btnToolsRectBrush = new ButtonWithImage();
    btnToolsRectBrush->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-rect_brush"));
    btnToolsRectBrush->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsRectBrush) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Rectangle Brush", btnToolsRectBrush);
        }
        };

    btnToolsRectBrush->onclick_func = [this]() {
        selectedToolButton = btnToolsRectBrush;
        painter->tool = toolType::RectBrush;
        if (selectedPaletteButton == nullptr)
            selectedPaletteButton = paletteButtons[1];

        painter->setPrefabToPaint(selectedPaletteButton->object);
        };


    btnToolsIncrease = new ButtonWithImage();
    btnToolsIncrease->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-increase"));
    btnToolsIncrease->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsIncrease) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Increase", btnToolsIncrease);
        }
        };

    btnToolsIncrease->onclick_func = [this]() {
        if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
            painter->increaseBrush();
        }
        };


    btnToolsDecrease = new ButtonWithImage();
    btnToolsDecrease->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-decrease"));
    btnToolsDecrease->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsDecrease) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Decrease", btnToolsDecrease);
        }
        };

    btnToolsDecrease->onclick_func = [this]() {
        if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
            painter->decreaseBrush();
        }
        };


    btnToolsRectangle = new ButtonWithImage();
    btnToolsRectangle->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-rectangle"));
    btnToolsRectangle->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsRectangle) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Rectangle", btnToolsRectangle);
        }
        };

    btnToolsRectangle->onclick_func = [this]() {
        selectedToolButton = btnToolsRectangle;
        painter->tool = toolType::Rectangle;
        if (painter->prefabToPaint == nullptr) {
            selectedPaletteButton = paletteButtons[1];
            painter->setPrefabToPaint(selectedPaletteButton->object);
        }
        };


    btnToolsElipse = new ButtonWithImage();
    btnToolsElipse->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-elipse"));
    btnToolsElipse->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsElipse) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Elipse", btnToolsElipse);
        }
        };

    btnToolsElipse->onclick_func = [this]() {
        selectedToolButton = btnToolsElipse;
        painter->tool = toolType::Elipse;
        if (painter->prefabToPaint == nullptr) {
            selectedPaletteButton = paletteButtons[1];
            painter->setPrefabToPaint(selectedPaletteButton->object);
        }
        };


    btnToolsFill = new ButtonWithImage();
    btnToolsFill->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-fill"));
    btnToolsFill->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsElipse) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Fill", btnToolsFill);
        }      
        };

    btnToolsFill->onclick_func = [this]() {
        selectedToolButton = btnToolsFill;
        painter->tool = toolType::Fill;
        };


    btnToolsEraser = new ButtonWithImage();
    btnToolsEraser->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-eraser"));
    btnToolsEraser->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnToolsEraser) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Eraser", btnToolsEraser);
        }
        };

    btnToolsEraser->onclick_func = [this]() {
        selectedToolButton = btnToolsEraser;
        selectedPaletteButton = nullptr;
        painter->tool = toolType::Eraser;
        };

    ////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f sp;    // start position
    sp.x = screenWidth / 2.0f - 10 * 32 + 16;
    sp.y = -screenHeight / 2.0f + 2 * 52 + 16 + 30;

    btnToolsCursor->setPosition(sf::Vector2f(sp.x, sp.y));
    btnToolsBrush->setPosition(sf::Vector2f(sp.x + 32, sp.y));
    btnToolsRectBrush->setPosition(sf::Vector2f(sp.x + 64, sp.y));
    btnToolsIncrease->setPosition(sf::Vector2f(sp.x + 96, sp.y));
    btnToolsDecrease->setPosition(sf::Vector2f(sp.x + 128, sp.y));
    btnToolsRectangle->setPosition(sf::Vector2f(sp.x + 160, sp.y));
    btnToolsElipse->setPosition(sf::Vector2f(sp.x + 192, sp.y));
    btnToolsFill->setPosition(sf::Vector2f(sp.x + 224, sp.y));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 256, sp.y));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 288, sp.y));

    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 32, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 64, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 96, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 128, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 160, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 192, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 224, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 256, sp.y + 32));
    //btnToolsEmpty->setPosition(sf::Vector2f(sp.x + 288, sp.y + 32));


    ////////////////////////////////////////////////////////////////////////////////////

    toolsButtons.push_back(btnToolsCursor);
    toolsButtons.push_back(btnToolsBrush);
    toolsButtons.push_back(btnToolsRectBrush);
    toolsButtons.push_back(btnToolsIncrease);
    toolsButtons.push_back(btnToolsDecrease);
    toolsButtons.push_back(btnToolsRectangle);
    toolsButtons.push_back(btnToolsElipse);
    toolsButtons.push_back(btnToolsFill);
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 256, sp.y)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 288, sp.y)));

    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 32, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 64, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 96, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 128, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 160, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 192, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 224, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 256, sp.y + 32)));
    toolsButtons.push_back(new ButtonWithImage(btnToolsEmpty, sf::Vector2f(sp.x + 288, sp.y + 32)));
}

void Palette::createGroupButtons() {

    deleteGroupButtons();

    // create Group Buttons
    btnGroupEmpty = new ButtonWithImage();
    btnGroupEmpty->setTexture(getSingleTexture("GUI/menuButtons/menuButton"));

    btnGroupTerrain = new ButtonWithImage();
    btnGroupTerrain->setTexture(getSingleTexture("GUI/menuButtons/menuButton-terrain"));
    btnGroupTerrain->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupTerrain) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Terrains", btnGroupTerrain);
        }
            
        };

    btnGroupTerrain->onclick_func = [this]() {
        selectedGroupButton = btnGroupTerrain;
        painter->tool = toolType::Cursor;
        painter->setPrefabToPaint(nullptr);
        selectedPaletteButton = nullptr;
        createPaletteButtons(5, 7);
        createNavButtons();
        createToolsButtons();
        setTerrainObjectsToPalette();
        loadPalette();
        };

    btnGroupFloors = new ButtonWithImage();
    btnGroupFloors->setTexture(getSingleTexture("GUI/menuButtons/menuButton-floors"));
    btnGroupFloors->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupFloors) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Floors", btnGroupFloors);
        }
            
        };
    btnGroupFloors->onclick_func = [this]() {
        selectedGroupButton = btnGroupFloors;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 7);
        createNavButtons();
        createToolsButtons();
        setFloorsObjectsToPalette();
        loadPalette();
        };

    btnGroupWater = new ButtonWithImage();
    btnGroupWater->setTexture(getSingleTexture("GUI/menuButtons/menuButton-water"));
    btnGroupWater->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupWater) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Waters", btnGroupWater);
        }
            
        };
    btnGroupWater->onclick_func = [this]() {
        selectedGroupButton = btnGroupWater;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 7);
        createNavButtons();
        createToolsButtons();
        setWaterObjectsToPalette();
        loadPalette();
        };

    btnGroupFurnitures = new ButtonWithImage();
    btnGroupFurnitures->setTexture(getSingleTexture("GUI/menuButtons/menuButton-furnitures"));
    btnGroupFurnitures->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupFurnitures) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Furnitures", btnGroupFurnitures);
        }
            
        };
    btnGroupFurnitures->onclick_func = [this]() {
        selectedGroupButton = btnGroupFurnitures;
        painter->tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setFurnituresObjectsToPalette();
        loadPalette();
        };

    btnGroupWalls = new ButtonWithImage();
    btnGroupWalls->setTexture(getSingleTexture("GUI/menuButtons/menuButton-walls"));
    btnGroupWalls->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupWalls) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Walls", btnGroupWalls);
        }
            
        };
    btnGroupWalls->onclick_func = [this]() {
        selectedGroupButton = btnGroupWalls;
        painter->tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setWallsObjectsToPalette();
        loadPalette();
        };

    btnGroupMonsters = new ButtonWithImage();
    btnGroupMonsters->setTexture(getSingleTexture("GUI/menuButtons/menuButton-monsters"));
    btnGroupMonsters->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupMonsters) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Monsters", btnGroupMonsters);
        }
            
        };
    btnGroupMonsters->onclick_func = [this]() {
        selectedGroupButton = btnGroupMonsters;
        painter->tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setMonstersObjectsToPalette();
        loadPalette();
        };

    btnGroupFlatObjects = new ButtonWithImage();
    btnGroupFlatObjects->setTexture(getSingleTexture("GUI/menuButtons/menuButton-flat_objects"));
    btnGroupFlatObjects->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupFlatObjects) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Flat Objects", btnGroupFlatObjects);
        }
            
        };
    btnGroupFlatObjects->onclick_func = [this]() {
        selectedGroupButton = btnGroupFlatObjects;
        painter->tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setFlatObjectsToPalette();
        loadPalette();
        };

    btnGroupItems = new ButtonWithImage();
    btnGroupItems->setTexture(getSingleTexture("GUI/menuButtons/menuButton-items"));
    btnGroupItems->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupItems) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Items", btnGroupItems);
        }
            
        };
    btnGroupItems->onclick_func = [this]() {
        selectedGroupButton = btnGroupItems;
        painter->tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setItemsObjectsToPalette();
        loadPalette();
        };

    btnGroupNatures = new ButtonWithImage();
    btnGroupNatures->setTexture(getSingleTexture("GUI/menuButtons/menuButton-natures"));
    btnGroupNatures->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupNatures) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Natures Objects", btnGroupNatures);
        }
            
        };
    btnGroupNatures->onclick_func = [this]() {
        painter->tool = toolType::Cursor;
        selectedGroupButton = btnGroupNatures;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setNaturesObjectsToPalette();
        loadPalette();
        };

    btnGroupObjects = new ButtonWithImage();
    btnGroupObjects->setTexture(getSingleTexture("GUI/menuButtons/menuButton-objects"));
    btnGroupObjects->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupObjects) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Objects", btnGroupObjects);
        }
            
        };
    btnGroupObjects->onclick_func = [this]() {
        painter->tool = toolType::Cursor;
        selectedGroupButton = btnGroupObjects;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setObjectsToPalette();
        loadPalette();
        };

    btnGroupSmallObjects = new ButtonWithImage();
    btnGroupSmallObjects->setTexture(getSingleTexture("GUI/menuButtons/menuButton-smallObjects"));
    btnGroupSmallObjects->hover_func = [this]() {
        if (tip == nullptr || tip->btn != btnGroupSmallObjects) {
            if (tip != nullptr)
                delete tip;
            tip = new Tip(L"Small Objects", btnGroupSmallObjects);
        }
            
        };
    btnGroupSmallObjects->onclick_func = [this]() {
        painter->tool = toolType::Cursor;
        selectedGroupButton = btnGroupSmallObjects;
        selectedPaletteButton = nullptr;
        painter->clear();
        createPaletteButtons(5, 8);
        createNavButtons();
        deleteToolsButtons();
        setSmallObjectsToPalette();
        loadPalette();
        };

    // create Group Buttons Menu
    groupButtons.resize(10);

    if (type == PaletteType::MapEditor) {
        groupButtons[0] = btnGroupTerrain;
        groupButtons[1] = btnGroupWater;
        groupButtons[2] = btnGroupNatures;
        groupButtons[3] = btnGroupFlatObjects;
        groupButtons[4] = btnGroupMonsters;
        groupButtons[5] = btnGroupItems;
        groupButtons[6] = btnGroupSmallObjects;
        groupButtons[7] = btnGroupObjects;
        groupButtons[8] = new ButtonWithImage(btnGroupEmpty);
        groupButtons[9] = new ButtonWithImage(btnGroupEmpty);
    }
    else if (type == PaletteType::BuildingEditor) {
        groupButtons[0] = btnGroupFloors;
        groupButtons[1] = btnGroupWalls;
        groupButtons[2] = btnGroupFurnitures;
        groupButtons[3] = btnGroupItems;
        groupButtons[4] = new ButtonWithImage(btnGroupEmpty);
        groupButtons[5] = new ButtonWithImage(btnGroupEmpty);
        groupButtons[6] = new ButtonWithImage(btnGroupEmpty);
        groupButtons[7] = new ButtonWithImage(btnGroupEmpty);
        groupButtons[8] = new ButtonWithImage(btnGroupEmpty);
        groupButtons[9] = new ButtonWithImage(btnGroupEmpty);
    }

    for (auto i = 0; i < 10; i++) {
        sf::Vector2f position;
        position.x = screenWidth / 2.0f - (4 - i % 5) * 64 - 32;
        position.y = -screenHeight / 2.0f + i / 5 * 52 + 26 + 30;
        groupButtons[i]->setPosition(position);
    }
}

void Palette::scrollUp() {
    if (scroll > 0)
        scroll -= 1;
}

void Palette::scrollDown() {

    short maxScroll = availableGameObjects.size() - size.x * size.y;
    if (maxScroll < 0)
        maxScroll = 0;

    if (scroll * size.x < maxScroll)
        scroll += 1;
}

bool Palette::unselectPaletteButton() {

    if (selectedPaletteButton != nullptr) {
        selectedPaletteButton = nullptr;
        selectedToolButton = btnToolsCursor;
        painter->tool = toolType::Cursor;
        painter->clear();
        return true;
    }
    else
        return false;

}

void Palette::handleEvent(sf::Event& event) {
    for (auto& tool : toolsButtons)
        tool->handleEvent(event);

    for (auto& btn : groupButtons)
        btn->handleEvent(event);

    for (auto& btn : paletteButtons)
        btn->handleEvent(event);

    buttonUp->handleEvent(event);
    buttonDown->handleEvent(event);
}


void Palette::update() {
    
    bool hover_action = !GUIwasOpen;

    for (auto& tool : toolsButtons)
        tool->update(hover_action);

    for (auto& btn : groupButtons)
        btn->update(hover_action);

    for (auto& btn : paletteButtons)
        btn->update(hover_action);

    buttonUp->update(hover_action);
    buttonDown->update(hover_action);
}

void Palette::draw()
{
    for (auto& tool : toolsButtons)
        tool->draw();

    for (auto& btn : groupButtons)
        btn->draw();

    for (auto& btn : paletteButtons) {
        btn->draw();
    }

    buttonUp->draw();
    buttonDown->draw();
}

Palette* palette = nullptr;
