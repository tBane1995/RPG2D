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
#include "MouseMovedGameObjects.h"

void clearPrefabsToPaint() {

    for (auto& prefab : prefabsToPaint) {
        delete prefab->_object;
        delete prefab;
    }
        

    prefabsToPaint.clear();
}

void painterUpdate() {

    

    if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
        clearPrefabsToPaint();
        mouseSelection();
    }
    else if (prefabToPaint != nullptr) {
        clearPrefabsToPaint();
        if (prefabToPaint->type == GameObjectType::Terrain || prefabToPaint->type == GameObjectType::Floor || prefabToPaint->type == GameObjectType::Water) {

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
            MouseMovedGameObject* moved_object = new MouseMovedGameObject(getNewGameObject(prefabToPaint));
            prefabsToPaint.push_back(moved_object);

            float x = short(worldMousePosition.x) / short(tileSide) * short(tileSide);
            float y = short(worldMousePosition.y) / short(tileSide) * short(tileSide);

            for (auto& prefab : prefabsToPaint) {

                prefab->_object->setPosition(sf::Vector2f(x, y));

                if (prefab->_object->type == GameObjectType::Unit || prefab->_object->type == GameObjectType::Monster || prefab->_object->type == GameObjectType::Character) {
                    dynamic_cast<Unit*>(prefab->_object)->idling(dt);
                }
                else {
                    prefab->_object->update();
                    prefab->_object->mouseIsHover = false;

                }
            }
        }
    }
    else {

        // a few GameObjects to draw
        for (auto& prefab : prefabsToPaint) {
            prefab->update();

            if (prefab->_object->type == GameObjectType::Unit || prefab->_object->type == GameObjectType::Monster || prefab->_object->type == GameObjectType::Character) {
                dynamic_cast<Unit*>(prefab->_object)->idling(dt);
            }
            else {
                prefab->update();
                prefab->_object->mouseIsHover = false;

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

void addGameObjectsToMapAndLists(std::vector <MouseMovedGameObject*> &prefabsToPaint, bool selectGameObjects) {

    Chunk* chunk;
    sf::Vector2f pos;

    if (selectGameObjects) {
        unselectGameObjects();
    }


    for (auto& prefab : prefabsToPaint) {

        (prefab->_object->type == GameObjectType::Monster) ? pos = dynamic_cast<Monster*>(prefab->_object)->base : pos = prefab->_object->position;

        chunk = mapa->getChunk(pos);

        if (chunk == nullptr)
            break;

        if (prefab->_object->type == GameObjectType::Nature) {

            Nature* nature = new Nature(prefab->_object, pos.x, pos.y);
            nature->isInTheMainList = true;
            if (selectGameObjects) {
                nature->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(nature));
            }
            gameObjects.push_back(nature);
            natures.push_back(nature);
            chunk->_natures.push_back(nature);
        }

        if (prefab->_object->type == GameObjectType::Object) {

            Object* object = new Object(prefab->_object, pos.x, pos.y);
            object->isInTheMainList = true;
            if (selectGameObjects) {
                object->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(object));
            }
            gameObjects.push_back(object);
            objects.push_back(object);
            chunk->_objects.push_back(object);
        }

        if (prefab->_object->type == GameObjectType::Monster) {

            Monster* monster = new Monster(prefab->_object, pos.x, pos.y);
            monster->isInTheMainList = true;
            if (selectGameObjects) {
                monster->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(monster));
            }
            gameObjects.push_back(monster);
            monsters.push_back(monster);
            chunk->_monsters.push_back(monster);
        }

        if (prefab->_object->type == GameObjectType::ItemOnMap) {

            ItemOnMap* item = new ItemOnMap(prefab->_object, pos.x, pos.y);
            item->isInTheMainList = true;
            if (selectGameObjects) {
                item->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(item));
            }
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
            chunk->_items.push_back(item);
        }

        if (prefab->_object->type == GameObjectType::FlatObject) {

            FlatObject* flat = new FlatObject(prefab->_object, pos.x, pos.y);
            flat->isInTheMainList = true;
            if (selectGameObjects) {
                flat->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(flat));
            }
            gameObjects.push_back(flat);
            flatObjects.push_back(flat);
            chunk->_flatObjects.push_back(flat);
        }

        if (prefab->_object->type == GameObjectType::SmallObject) {

            SmallObject* object = new SmallObject(prefab->_object, pos.x, pos.y);
            object->isInTheMainList = true;
            if (selectGameObjects) {
                object->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(object));
            }
            gameObjects.push_back(object);
            smallObjects.push_back(object);
            chunk->_smallObjects.push_back(object);
        }

        if (prefab->_object->type == GameObjectType::Door) {
            Door* door = new Door(prefab->_object, pos.x, pos.y);
            door->isInTheMainList = true;
            if (selectGameObjects) {
                door->isSelected = true;
                selectedGameObjects.push_back(new MouseMovedGameObject(door));
            }
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

        float x = prefab->_object->position.x;
        float y = prefab->_object->position.y;

        if (prefab->_object->type == GameObjectType::Wall) {
            Wall* wall = new Wall(prefab->_object, x, y);
            wall->isInTheMainList = true;
            gameObjects.push_back(wall);
            walls.push_back(wall);
            building->_walls.push_back(wall);
        }

    }
}