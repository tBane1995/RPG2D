#pragma once

#include <vector>
#include "MouseMovedGameObjects.h"
#include "Mouse.h"
#include "TerrainAndFloors.h"
#include "Water.h"
#include "Map.h"
#include "GameObjectsManager.h"
#include "Natures.h"
#include "Objects.h"
#include "Monsters.h"
#include "Items.h"
#include "FlatObjects.h"
#include "SmallObjects.h"
#include "Walls.h"
#include "Doors.h"
#include "Window.h"

enum class toolType { Cursor, Brush, RectBrush, Rectangle, Elipse, Fill, Eraser, AddGameObject };

extern std::vector<std::vector<std::vector<bool>>> brushes;

class Painter {
public:
    GameObject* prefabToPaint;
    std::vector < MouseMovedGameObject* > prefabsToPaint;

    toolType tool;
    short brushSize;

    std::vector<std::vector<bool>> brush;

    Painter() {
        prefabToPaint = nullptr;
        prefabsToPaint.clear();
        tool = toolType::Cursor;
        setBrushSize(2);
    }

    ~Painter() { }

    void setBrushSize(short size) {
        brushSize = size;
        brush = brushes[size];
    }

    void decreaseBrush() {
        if (brushSize > 0) {
            setBrushSize(brushSize-1);
            coutBrush();
            //cout << "\n\n";
        }
    }

    void increaseBrtush() {
        if (brushSize < 5) {
            setBrushSize(brushSize+1);
            coutBrush();
            //cout << "\n\n";
        }
    }

    void coutBrush() {

        for (auto& row : brush) {
            for (bool cell : row)
                std::cout << cell << " ";
            std::cout << "\n";
        }
    }

    void generateBrush() {
        int baseX = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
        int baseY = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

        int brushHalfWdt = brush.size() / 2;
        int brushHalfHgh = brush.size() / 2;

        for (int y = 0; y < brush.size(); y++) {
            for (int x = 0; x < brush[y].size(); x++) {
                if (brush[y][x] == true) {

                    int xx = baseX + (x - brushHalfWdt) * tileSide;
                    int yy = baseY + (y - brushHalfHgh) * tileSide;

                    if (prefabToPaint->type == GameObjectType::Terrain) {
                        TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, static_cast<TerrainPrefab*>(prefabToPaint)->id);
                        ter->position = sf::Vector2f(xx + 8, yy + 8);
                        ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                        ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                        MouseMovedGameObject* moved_object = new MouseMovedGameObject(ter);
                        prefabsToPaint.push_back(moved_object);
                    }

                    if (prefabToPaint->type == GameObjectType::Floor) {
                        FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, static_cast<FloorPrefab*>(prefabToPaint)->id);
                        flo->position = sf::Vector2f(xx + 8, yy + 8);
                        flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                        flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                        MouseMovedGameObject* moved_object = new MouseMovedGameObject(flo);
                        prefabsToPaint.push_back(moved_object);
                    }

                    if (prefabToPaint->type == GameObjectType::Water) {
                        WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                        wat->position = sf::Vector2f(xx + 8, yy + 8);
                        wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                        wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                        MouseMovedGameObject* moved_object = new MouseMovedGameObject(wat);
                        prefabsToPaint.push_back(moved_object);
                    }

                }
            }
        }
    }

    void generateRectBrush() {
        int baseX = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
        int baseY = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

        int brushHalfWdt = brush.size() / 2;
        int brushHalfHgh = brush.size() / 2;

        for (int y = 0; y < brush.size(); y++) {
            for (int x = 0; x < brush[y].size(); x++) {

                int xx = baseX + (x - brushHalfWdt) * tileSide;
                int yy = baseY + (y - brushHalfHgh) * tileSide;

                if (prefabToPaint->type == GameObjectType::Terrain) {
                    TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, dynamic_cast<TerrainPrefab*>(prefabToPaint)->id);
                    ter->position = sf::Vector2f(xx + 8, yy + 8);
                    ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(ter);
                    prefabsToPaint.push_back(moved_object);
                }

                if (prefabToPaint->type == GameObjectType::Floor) {
                    FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                    flo->position = sf::Vector2f(xx + 8, yy + 8);
                    flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(flo);
                    prefabsToPaint.push_back(moved_object);
                }

                if (prefabToPaint->type == GameObjectType::Water) {
                    WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                    wat->position = sf::Vector2f(xx + 8, yy + 8);
                    wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(wat);
                    prefabsToPaint.push_back(moved_object);
                }



            }
        }
    }

    void generateRectangle() {
        int start_x = std::min((startWorldMousePosition.x / tileSide), (worldMousePosition.x / tileSide));
        int start_y = std::min((startWorldMousePosition.y / tileSide), (worldMousePosition.y / tileSide));
        int end_x = std::max(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
        int end_y = std::max(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));

        std::cout << "start: " << start_x << ", " << start_y << "\n";
        std::cout << "end: " << end_x << ", " << end_y << "\n";
        std::cout << "\n\n";

        for (int y = start_y; y < end_y; y++)
            for (int x = start_x; x < end_x; x++) {
                int xx = x * int(tileSide);
                int yy = y * int(tileSide);

                if (prefabToPaint->type == GameObjectType::Terrain) {
                    TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, dynamic_cast<TerrainPrefab*>(prefabToPaint)->id);
                    ter->position = sf::Vector2f(xx + 8, yy + 8);
                    ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(ter);
                    prefabsToPaint.push_back(moved_object);
                }

                if (prefabToPaint->type == GameObjectType::Floor) {
                    FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                    flo->position = sf::Vector2f(xx + 8, yy + 8);
                    flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(flo);
                    prefabsToPaint.push_back(moved_object);
                }

                if (prefabToPaint->type == GameObjectType::Water) {
                    WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                    wat->position = sf::Vector2f(xx + 8, yy + 8);
                    wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    MouseMovedGameObject* moved_object = new MouseMovedGameObject(wat);
                    prefabsToPaint.push_back(moved_object);
                }

            }

    }

    void generateElipse() {
        int start_x = std::min((startWorldMousePosition.x / tileSide), (worldMousePosition.x / tileSide));
        int start_y = std::min((startWorldMousePosition.y / tileSide), (worldMousePosition.y / tileSide));
        int end_x = std::max(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
        int end_y = std::max(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));

        int width = end_x - start_x;
        int height = end_y - start_y;

        // ?rodek p?dzla
        float centerX = (start_x + end_x) / 2.0f;
        float centerY = (start_y + end_y) / 2.0f;

        // Pó?osie elipsy
        float a = width / 2.0f;
        float b = height / 2.0f;

        // Generowanie elipsy w oparciu o p?dzel
        for (int y = start_y; y < end_y; ++y) {
            for (int x = start_x; x < end_x; ++x) {
                // Obliczanie pozycji w stosunku do ?rodka
                float dx = (x - centerX) / a;
                float dy = (y - centerY) / b;

                // Sprawd?, czy p?dzel na tej pozycji ma warto?? 1
                if (dx * dx + dy * dy <= 0.995f) {
                    int xx = x * int(tileSide);
                    int yy = y * int(tileSide);

                    if (prefabToPaint->type == GameObjectType::Terrain) {
                        TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, dynamic_cast<TerrainPrefab*>(prefabToPaint)->id);
                        ter->position = sf::Vector2f(xx + 8, yy + 8);
                        ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                        ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                        MouseMovedGameObject* moved_object = new MouseMovedGameObject(ter);
                        prefabsToPaint.push_back(moved_object);
                    }

                    if (prefabToPaint->type == GameObjectType::Floor) {
                        FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                        flo->position = sf::Vector2f(xx + 8, yy + 8);
                        flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                        flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                        MouseMovedGameObject* moved_object = new MouseMovedGameObject(flo);
                        prefabsToPaint.push_back(moved_object);
                    }

                    if (prefabToPaint->type == GameObjectType::Water) {
                        WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                        wat->position = sf::Vector2f(xx + 8, yy + 8);
                        wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                        wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                        MouseMovedGameObject* moved_object = new MouseMovedGameObject(wat);
                        prefabsToPaint.push_back(moved_object);
                    }


                }
            }
        }
    }

    void clear() {

        for (auto& prefab : prefabsToPaint) {
            delete prefab->_object;
            delete prefab;
        }
        prefabsToPaint.clear();
    }

    void addGameObjectsToMapAndLists(std::vector <MouseMovedGameObject*>& prefabsToPaint, bool selectGameObjects) {

        if (selectGameObjects) {
            unselectGameObjects();
        }

        Chunk* chunk;
        sf::Vector2f pos;

        for (auto& prefab : prefabsToPaint) {

            pos = prefab->_object->position;
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

    void update() {

        if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
            clear();
            mouseSelection();
        }
        else if (prefabToPaint != nullptr) {

            clear();

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
                        dynamic_cast<Unit*>(prefab->_object)->idling();
                    }
                    else {
                        prefab->update();
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
                    dynamic_cast<Unit*>(prefab->_object)->idling();
                }
                else {
                    prefab->update();
                    prefab->_object->mouseIsHover = false;

                }
            }

        }

    }

    void draw() {

        if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
            window->draw(selectArea);

        }
        else {
            for (auto& p : prefabsToPaint) {
                p->draw();
            }
        }
    }

    
};

extern Painter* painter;