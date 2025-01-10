#include "GameObjectsManager.h"
#include "GameObjects.h"
#include "Items.h"
#include "BuildingsManager.h"
#include "Furnitures.h"
#include "Walls.h"
#include "Doors.h"
#include "Natures.h"
#include "Objects.h"
#include "FlatObjects.h"
#include "SmallObjects.h"
#include "Collisions.h"
#include "Character.h"
#include "Monsters.h"
#include "Camera.h"
#include "Time.h"
#include "Mouse.h"
#include "TerrainAndFloors.h"

std::vector < GameObject* > selectedGameObjects;

Building* isPartOfBuilding(GameObject* object) {

    if (object == nullptr)
        return nullptr;

    for (auto& building : buildings)
        if (building->isPart(object)) {
            //cout << "is a part of building\n";
            return building;
        }
            
    //cout << "is not a part of building\n";
    return nullptr;
}

void selectGameObjects(float rect_x, float rect_y, float rect_w, float rect_h) {

    if (!selectedGameObjects.empty())
        for (auto& s : selectedGameObjects)
            s->isSelected = false;

    selectedGameObjects.clear();

    for (auto& go : gameObjects) {

        if (go->type == GameObjectType::Building) {

            float x = go->colliders[0]->position.x + go->colliders[0]->dx;
            float y = go->colliders[0]->position.y + go->colliders[0]->dy - dynamic_cast<Building*>(go)->size.y * 16 / 2;
            float w = go->colliders[0]->width;
            float h = go->colliders[0]->length;

            if (intersectionTwoRectangles(rect_x, rect_y, rect_w, rect_h, x, y, w, h)) {
                go->isSelected = true;
                selectedGameObjects.push_back(go);
            }

        }
        else if (go->type != GameObjectType::Wall) {

            for (auto& collider : go->colliders) {
                if (collider->type == ColliderType::Rectangle) {
                    if (intersectionTwoRectangles(rect_x, rect_y, rect_w, rect_h, collider->position.x + collider->dx, collider->position.y + collider->dy, collider->width, collider->length)) {
                        go->isSelected = true;
                        selectedGameObjects.push_back(go);
                    }
                }
                else if (collider->type == ColliderType::Elipse) {
                    if (intersectionRectangleWithElipse(rect_x, rect_y, rect_w, rect_h, go->position.x + collider->dx, go->position.y + collider->dy, collider->width / 2, collider->length / 2)) {
                        go->isSelected = true;
                        selectedGameObjects.push_back(go);
                    }
                }
            }
        }

    }
}

void selectGameObjects() {
    float x = selectArea.getPosition().x;
    float y = selectArea.getPosition().y;
    float w = selectArea.getSize().x;
    float h = selectArea.getSize().y;

    if (w < 16) w = 16;
    if (h < 16) h = 16;

    selectGameObjects(x, y, w, h);
}

bool unselectGameObjects() {
    if (!selectedGameObjects.empty()) {
        for (auto& sgo : selectedGameObjects)
            sgo->isSelected = false;

        selectedGameObjects.clear();
        return true;
    }
    else
        return false;

}

void deleteGameObjectFromMainLists(GameObject* object) {

    if (object->type == GameObjectType::Nature) {
        auto it = std::find(natures.begin(), natures.end(), object);
        if (it != natures.end())
            natures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Object) {
        auto it = std::find(objects.begin(), objects.end(), object);
        if (it != objects.end())
            objects.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::ItemOnMap) {
        auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), object);
        if (it != itemsOnMap.end())
            itemsOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::FlatObject) {
        auto it = std::find(flatObjects.begin(), flatObjects.end(), object);
        if (it != flatObjects.end())
            flatObjects.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Furniture) {
        auto it = std::find(furnitures.begin(), furnitures.end(), object);
        if (it != furnitures.end())
            furnitures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Wall) {
        auto it = std::find(walls.begin(), walls.end(), object);
        if (it != walls.end())
            walls.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Door) {
        auto it = std::find(doors.begin(), doors.end(), object);
        if (it != doors.end())
            doors.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Monster) {
        auto it = std::find(monsters.begin(), monsters.end(), object);
        if (it != monsters.end())
            monsters.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::SmallObject) {
        auto it = std::find(smallObjects.begin(), smallObjects.end(), object);
        if (it != smallObjects.end())
            smallObjects.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::Character) {
        auto it = std::find(characters.begin(), characters.end(), object);
        if (it != characters.end())
            characters.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    if (object->type == GameObjectType::InventoryOnMap) {
        auto it = std::find(inventoriesOnMap.begin(), inventoriesOnMap.end(), object);
        if (it != inventoriesOnMap.end())
            inventoriesOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    // TO-DO BUILDINGS
    if (object->type == GameObjectType::Building) {

        Building* b = dynamic_cast<Building*>(object);

        // delete Doors
        auto d = std::find(doors.begin(), doors.end(), b->_door);
        if (d != doors.end())
            doors.erase(d);

        auto dgo = std::find(gameObjects.begin(), gameObjects.end(), b->_door);
        if (dgo != gameObjects.end())
            gameObjects.erase(dgo);

        // delete items
        for (auto& item : b->_items) {
            auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), item);
            if (it != itemsOnMap.end())
                itemsOnMap.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), item);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete furnitures
        for (auto& furniture : b->_furnitures) {
            auto it = std::find(furnitures.begin(), furnitures.end(), furniture);
            if (it != furnitures.end())
                furnitures.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), furniture);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        // delete walls
        for (auto& wall : b->_walls) {
            auto it = std::find(walls.begin(), walls.end(), wall);
            if (it != walls.end())
                walls.erase(it);

            auto go = std::find(gameObjects.begin(), gameObjects.end(), wall);
            if (go != gameObjects.end())
                gameObjects.erase(go);
        }

        auto it = std::find(buildings.begin(), buildings.end(), object);
        if (it != buildings.end())
            buildings.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), object);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

}

void clearAllMainListsOfGameObjects() {
    // clear all main lists

    gameObjects.clear();

    natures.clear();
    objects.clear();
    itemsOnMap.clear();
    flatObjects.clear();
    furnitures.clear();
    walls.clear();
    doors.clear();
    monsters.clear();
    smallObjects.clear();
    characters.clear();
    inventoriesOnMap.clear();
    buildings.clear();
}

bool visiblings(GameObject* object) {
    // return true if GameObject is visible

    if (object != nullptr) {

        if (object->colliders[0] != nullptr) {
            if (object->colliders[0]->type == ColliderType::Elipse) {
                if (intersectionRectangleWithElipse(cam->position.x, cam->position.y, screenWidth * 2.0f, screenHeight * 2.0f, object->position.x, object->position.y, object->colliders[0]->width / 2.0f, object->colliders[0]->length / 2.0f)) {
                    return true;
                }
            }

            else if (object->colliders[0]->type == ColliderType::Rectangle) {
                if (intersectionTwoRectangles(cam->position.x, cam->position.y, screenWidth * 2.0f, screenHeight * 2.0f, object->position.x, object->position.y, object->colliders[0]->width, object->colliders[0]->length))
                    return true;
            }
        }
        else
            return true;
    }

    return true;
}

void updateGameObjects() {

    for (auto& go : gameObjects) {
        if (visiblings(go)) {

            go->isVisible = true;
            go->update();
            go->mouseHovering();
        }
        else
            go->isVisible = false;
    }
}

void sortGameObjects()
{
    std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });
}

void drawGameObjects() {

    for (auto& f : flatObjects) {
        if (f->isVisible) {
            f->drawStatistics();
        }
    }

    for (auto& f : flatObjects) {
        if (f->isVisible) {
            f->draw();
        }
    }

    for (auto& building : buildings) {
        window->draw(*building->floors);
        building->draw();
    }

    for (auto& go : gameObjects) {
        if (go->type != GameObjectType::FlatObject)
            if (go->isVisible) {
                go->drawStatistics();
            }
    }

    for (auto& go : gameObjects)
        if (go->type == GameObjectType::Building || go->isVisible == true)
            go->draw();

}
