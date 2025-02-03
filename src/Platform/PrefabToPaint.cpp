﻿#include "PrefabToPaint.h"

std::vector<std::vector<std::vector<bool>>> brushes = {

    // 0 - 1x1
    {
        {1}
    },

    // 1 - 3x3
    {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    },

    // 2 - 5x5
    {
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0}
    },

    // 3 - 7x7
    {
        {0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 0}
    },

    // 4 - 9x9
    {
        {0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0}
    },

    // 5 - 11x11
    {
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},

    }
};


Painter::Painter() {
    prefabToPaint = nullptr;
    prefabsToPaint.clear();
    tool = toolType::Cursor;
    setBrushSize(2);
}

Painter::~Painter() { }

void Painter::setPrefabToPaint(GameObject* prefab) {
    prefabToPaint = prefab;
}

void Painter::setBrushSize(short size) {
    brushSize = size;
    brush = brushes[size];
}

void Painter::decreaseBrush() {
    if (brushSize > 0) {
        setBrushSize(brushSize - 1);
        coutBrush();
        //cout << "\n\n";
    }
}

void Painter::increaseBrush() {
    if (brushSize < 5) {
        setBrushSize(brushSize + 1);
        coutBrush();
        //cout << "\n\n";
    }
}

void Painter::coutBrush() {

    for (auto& row : brush) {
        for (bool cell : row)
            std::cout << cell << " ";
        std::cout << "\n";
    }
}

void Painter::generateBrush() {
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

void Painter::generateRectBrush() {
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

void Painter::generateRectangle() {
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

void Painter::generateElipse() {
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

void Painter::clear() {

    for (auto& prefab : prefabsToPaint) {
        delete prefab->_object;
        delete prefab;
    }
    prefabsToPaint.clear();
}

void Painter::addGameObjectsToMapAndLists(std::vector <MouseMovedGameObject*>& prefabsToPaint, bool selectGameObjects) {

    if (selectGameObjects) {
        unselectGameObjects();
    }

    Chunk* chunk;
    sf::Vector2f pos;

    for (auto& prefab : prefabsToPaint) {

        GameObject* object = getNewGameObject(prefab->_object);
        object->setPosition(prefab->_object->position);
        std::cout << object->position.x << " " << object->position.y << "\n";
        chunk = mapa->getChunk(object->position);

        if (chunk == nullptr)
            break;

        object->isInTheMainList = true;
        if (selectGameObjects) {
            object->isSelected = true;
            selectedGameObjects.push_back(new MouseMovedGameObject(object));
        }

        chunk->addGameObject(object);
        addGameObjectToMainLists(object);

    }
}

void Painter::addGameObjectsToBuildingAndLists(std::vector <MouseMovedGameObject*>& prefabsToPaint, bool selectGameObjects) {

    if (selectGameObjects) {
        unselectGameObjects();
    }

    sf::Vector2f pos;

    for (auto& prefab : prefabsToPaint) {

        GameObject* object = getNewGameObject(prefab->_object);
        object->setPosition(prefab->_object->position);
        std::cout << object->position.x << " " << object->position.y << "\n";


        object->isInTheMainList = true;
        if (selectGameObjects) {
            object->isSelected = true;
            selectedGameObjects.push_back(new MouseMovedGameObject(object));
        }

        building_to_edit->addGameObject(object);
        addGameObjectToMainLists(object);
        std::cout << "add - position of wall: " << object->position.x << " " << object->position.y << "\n";

    }
}
void Painter::update() {

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

void Painter::draw() {

    if (tool == toolType::Cursor && mouse_state == MouseState::Selecting) {
        window->draw(selectArea);

    }
    else {
        for (auto& p : prefabsToPaint) {
            p->draw();
        }
    }
}

Painter* painter = nullptr;