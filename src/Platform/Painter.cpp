#include "Painter.h"
#include "PrefabToPaint.h"
#include "GUI.h"
#include "GameObjects.h"
#include "Tools.h"
#include "Mouse.h"
#include "Palette.h"
#include "TerrainAndFloors.h"
#include "Window.h"
#include "Natures.h"
#include "Objects.h"
#include "FlatObjects.h"
#include "SmallObjects.h"
#include "Items.h"
#include "Monsters.h"
#include "Furnitures.h"
#include "Map.h"
#include "Time.h"
#include "Walls.h"
#include "Doors.h"
#include "BuildingsManager.h"
#include "PrefabToPaint.h"
#include "GameObjectsManager.h"

void clearPrefabsToPaint() {

    for (auto& prefab : prefabsToPaint)
        delete prefab;

    prefabsToPaint.clear();
}

void painterUpdate() {

    clearPrefabsToPaint();

    if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
        mouseSelection();
    }
    else if (prefabToPaint != nullptr) {

        if (prefabToPaint->type == GameObjectType::Terrain || prefabToPaint->type == GameObjectType::Floor || prefabToPaint->type == GameObjectType::Water) {

            clearPrefabsToPaint();

            if (tool == toolType::Rectangle) {
                if (mouse_state == MouseState::Selecting) {
                    generateRectangle();
                }
            }
            else if (tool == toolType::Elipse) {
                if (mouse_state == MouseState::Selecting) {
                    generateElipse();
                }
            }
            else if (tool == toolType::Brush) {
                generateBrush();
            }
            else if (tool == toolType::RectBrush) {
                generateRectBrush();
            }

        }
        else {
            // prefab isn't Terrain/Floor/Water
            clearPrefabsToPaint();
            prefabsToPaint.push_back(getNewGameObject(prefabToPaint));

            float x = short(worldMousePosition.x) / short(tileSide) * short(tileSide);
            float y = short(worldMousePosition.y) / short(tileSide) * short(tileSide);

            for (auto& prefab : prefabsToPaint) {

                prefab->setPosition(sf::Vector2f(x, y));

                if (prefab->type == GameObjectType::Unit || prefab->type == GameObjectType::Monster || prefab->type == GameObjectType::Character) {
                    dynamic_cast<Unit*>(prefab)->idling(dt);
                }
                else {
                    prefab->update();
                    prefab->mouseIsHover = false;

                }
            }
        }
    }

}

void painterDraw() {

    if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
        window->draw(selectArea);

    }
    else {
        for (auto& p : prefabsToPaint) {
            p->draw();
        }
    }


}

void addPrefabsToMapAndLists() {


    Chunk* chunk = mapa->getChunk(worldMousePosition);

    if (chunk == nullptr)
        return;

    for (auto& prefab : prefabsToPaint) {

        float x = prefab->position.x;
        float y = prefab->position.y;

        if (prefab->type == GameObjectType::Nature) {

            Nature* nature = new Nature(prefab, x, y);
            nature->isInTheMainList = true;
            gameObjects.push_back(nature);
            natures.push_back(nature);
            chunk->_natures.push_back(nature);
        }

        if (prefab->type == GameObjectType::Object) {

            Object* object = new Object(prefab, x, y);
            object->isInTheMainList = true;
            gameObjects.push_back(object);
            objects.push_back(object);
            chunk->_objects.push_back(object);
        }

        if (prefab->type == GameObjectType::Monster) {

            Monster* monster = new Monster(prefab, x, y);
            monster->isInTheMainList = true;
            gameObjects.push_back(monster);
            monsters.push_back(monster);
            chunk->_monsters.push_back(monster);
        }

        if (prefab->type == GameObjectType::ItemOnMap) {

            ItemOnMap* item = new ItemOnMap(prefab, x, y);
            item->isInTheMainList = true;
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
            chunk->_items.push_back(item);
        }

        if (prefab->type == GameObjectType::FlatObject) {

            FlatObject* flat = new FlatObject(prefab, x, y);
            flat->isInTheMainList = true;
            gameObjects.push_back(flat);
            flatObjects.push_back(flat);
            chunk->_flatObjects.push_back(flat);
        }

        if (prefab->type == GameObjectType::SmallObject) {

            SmallObject* object = new SmallObject(prefab, x, y);
            object->isInTheMainList = true;
            gameObjects.push_back(object);
            smallObjects.push_back(object);
            chunk->_smallObjects.push_back(object);
        }

        if (prefab->type == GameObjectType::Door) {
            Door* door = new Door(prefab, x, y);
            door->isInTheMainList = true;
            gameObjects.push_back(door);
            doors.push_back(door);
            chunk->_doors.push_back(door);
        }

    }
}

void addPrefabsToBuildingAndLists() {
    if (building == nullptr)
        return;

    for (auto& prefab : prefabsToPaint) {

        float x = prefab->position.x;
        float y = prefab->position.y;

        if (prefab->type == GameObjectType::Wall) {
            Wall* wall = new Wall(prefab, x, y);
            wall->isInTheMainList = true;
            gameObjects.push_back(wall);
            walls.push_back(wall);
            building->_walls.push_back(wall);
        }

    }
}