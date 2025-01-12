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

void painterUpdate() {

    if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
        mouseSelection();
    }
    else {
        for (auto& prefab : prefabsToPaint) {

            float x = short(worldMousePosition.x) / short(tileSide) * short(tileSide);
            float y = short(worldMousePosition.y) / short(tileSide) * short(tileSide);

            prefab->setPosition(sf::Vector2f(x, y));
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