#include "Map.h"

#include "Borders.h"
#include "BuildingsManager.h"
#include "Character.h"
#include "FlatObjects.h"
#include "Items.h"
#include "Monsters.h"
#include "Natures.h"
#include "Objects.h"
#include "SmallObjects.h"
#include "TerrainAndFloors.h"
#include "Water.h"
#include "Fonts.h"
#include "Theme.h"
#include "Doors.h"
#include "Furnitures.h"
#include "RenderParameters.h"
#include "Walls.h"
#include "Window.h"
#include "Camera.h"
#include "GameObjectsManager.h"
#include "Prefabs.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

Chunk::Chunk(short x, short y)
{
    coords.x = x;
    coords.y = y;

    terrain = new Terrain(x * 16, y * 16, 16, 16);
    water = new Water(x * 16, y * 16, 16, 16);
    borders = new Borders();

    short frameWidth = 2;
    frame = sf::RectangleShape(sf::Vector2f(256 - 2 * frameWidth, 256 - 2 * frameWidth));
    frame.setPosition(x * 256, y * 256);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color(128, 48, 48, 128));
    frame.setOutlineThickness(frameWidth);

    coordsText = sf::Text();
    coordsText.setFont(basicFont);
    coordsText.setCharacterSize(16);
    coordsText.setString(std::to_string(coords.x) + " x " + std::to_string(coords.y));
    coordsText.setFillColor(dialoguesColor);
    coordsText.setPosition(coords.x * 256, coords.y * 256);

    visible = false;
}

Chunk::~Chunk()
{
    // Usuń i zwolnij pamięć dla wszystkich elementów w wektorach
    for (auto& nature : _natures)
        delete nature;
    _natures.clear();

    for (auto& object : _objects)
        delete object;
    _objects.clear();

    for (auto& item : _items)
        delete item;
    _items.clear();

    for (auto& inventory : _inventories)
        delete inventory;
    _inventories.clear();

    for (auto& flat : _flatObjects)
        delete flat;
    _flatObjects.clear();

    for (auto& monster : _monsters)
        delete monster;
    _monsters.clear();

    for (auto& smallObject : _smallObjects)
        delete smallObject;
    _smallObjects.clear();

    for (auto& door : _doors)
        delete door;
    _doors.clear();

    for (auto& character : _characters)
        delete character;
    _characters.clear();

    for (auto& building : _buildings)
        delete building;
    _buildings.clear();



    delete terrain;
    delete water;
}

void Chunk::addGameObjectsToMainLists() {
    // Add all GameObjects of Chunk to Main Lists

    for (auto& nature : _natures) {
        nature->isInTheMainList = true;
        gameObjects.push_back(nature);
        natures.push_back(nature);
    }

    for (auto& object : _objects) {
        object->isInTheMainList = true;
        gameObjects.push_back(object);
        objects.push_back(object);
    }

    for (auto& item : _items) {
        item->isInTheMainList = true;
        gameObjects.push_back(item);
        itemsOnMap.push_back(item);
    }

    for (auto& inventory : _inventories) {
        inventory->isInTheMainList = true;
        gameObjects.push_back(inventory);
        inventoriesOnMap.push_back(inventory);
    }

    for (auto& flat : _flatObjects) {
        flat->isInTheMainList = true;
        gameObjects.push_back(flat);
        flatObjects.push_back(flat);
    }

    for (auto& monster : _monsters) {
        monster->isInTheMainList = true;
        gameObjects.push_back(monster);
        monsters.push_back(monster);
    }

    for (auto& smallObject : _smallObjects) {
        smallObject->isInTheMainList = true;
        gameObjects.push_back(smallObject);
        smallObjects.push_back(smallObject);
    }

    for (auto& door : _doors) {
        door->isInTheMainList = true;
        gameObjects.push_back(door);
        doors.push_back(door);
    }

    for (auto& character : _characters) {
        character->isInTheMainList = true;
        gameObjects.push_back(character);
        characters.push_back(character);
    }

    for (auto& building : _buildings) {
        building->isInTheMainList = true;
        gameObjects.push_back(building);
        buildings.push_back(building);

        building->_door->isInTheMainList = true;
        doors.push_back(building->_door);
        gameObjects.push_back(building->_door);

        for (auto& item : building->_items) {
            item->isInTheMainList = true;
            itemsOnMap.push_back(item);
            gameObjects.push_back(item);
        }


        for (auto& furniture : building->_furnitures) {
            furniture->isInTheMainList = true;
            furnitures.push_back(furniture);
            gameObjects.push_back(furniture);
        }


        for (auto& wall : building->_walls) {
            wall->isInTheMainList = true;
            walls.push_back(wall);
            gameObjects.push_back(wall);
        }

    }
}

void Chunk::removeGameObjectsFromMainLists()
{

    // delete natures ////////////////////////////////////////////////////////////
    for (auto& nature : _natures)
        nature->isInTheMainList = false;

    std::erase_if(natures, [](const auto& nature) { return !nature->isInTheMainList; });

    // delete objects ////////////////////////////////////////////////////////////
    for (auto& object : _objects)
        object->isInTheMainList = false;

    std::erase_if(objects, [](const auto& object) { return !object->isInTheMainList; });

    // delete items ////////////////////////////////////////////////////////////
    for (auto& item : _items)
        item->isInTheMainList = false;

    std::erase_if(itemsOnMap, [](const auto& item) { return !item->isInTheMainList; });

    // delete inventories ////////////////////////////////////////////////////////////
    for (auto& inventory : _inventories)
        inventory->isInTheMainList = false;

    std::erase_if(inventoriesOnMap, [](const auto& inventory) { return !inventory->isInTheMainList; });

    // delete flatObjects ////////////////////////////////////////////////////////////
    for (auto& flat : _flatObjects)
        flat->isInTheMainList = false;

    std::erase_if(flatObjects, [](const auto& flat) { return !flat->isInTheMainList; });

    // delete monsters ////////////////////////////////////////////////////////////
    for (auto& monster : _monsters)
        monster->isInTheMainList = false;

    std::erase_if(monsters, [](const auto& monster) { return !monster->isInTheMainList; });

    // delete smallObjects ////////////////////////////////////////////////////////////
    for (auto& object : _smallObjects)
        object->isInTheMainList = false;

    std::erase_if(smallObjects, [](const auto& object) { return !object->isInTheMainList; });

    // delete doors ////////////////////////////////////////////////////////////
    for (auto& door : _doors)
        door->isInTheMainList = false;

    std::erase_if(doors, [](const auto& door) { return !door->isInTheMainList; });

    // delete characters ////////////////////////////////////////////////////////////
    for (auto& character : _characters)
        character->isInTheMainList = false;

    std::erase_if(characters, [](const auto& character) { return !character->isInTheMainList; });

    // delete buildings ////////////////////////////////////////////////////////////
    for (auto& building : _buildings) {
        building->isInTheMainList = false;

        // delete building - doors
        building->_door->isInTheMainList = false;
        std::erase_if(doors, [](const auto& door) { return !door->isInTheMainList; });

        // delete building - items
        for (auto& item : building->_items)
            item->isInTheMainList = false;

        std::erase_if(itemsOnMap, [](const auto& item) { return !item->isInTheMainList; });

        // delete building - furnitures
        for (auto& furniture : building->_furnitures)
            furniture->isInTheMainList = false;

        std::erase_if(furnitures, [](const auto& furniture) { return !furniture->isInTheMainList; });

        // delete building - walls
        for (auto& wall : building->_walls)
            wall->isInTheMainList = false;

        std::erase_if(walls, [](const auto& wall) { return !wall->isInTheMainList; });

    }

    std::erase_if(buildings, [](const auto& building) { return !building->isInTheMainList; });


    // delete GameObjects  /////////////////////////////////////////////////////////////////////
    std::erase_if(gameObjects, [](const auto& go) { return !go->isInTheMainList; });
}

void Chunk::deleteGameObject(GameObject* object)
{

    if (object == nullptr)
        return;

    if (object->type == GameObjectType::Nature) {
        auto it = std::find(_natures.begin(), _natures.end(), object);
        if (it != _natures.end())
            _natures.erase(it);
    }

    if (object->type == GameObjectType::Object) {
        auto it = std::find(_objects.begin(), _objects.end(), object);
        if (it != _objects.end())
            _objects.erase(it);
    }

    if (object->type == GameObjectType::ItemOnMap) {
        auto it = std::find(_items.begin(), _items.end(), object);
        if (it != _items.end())
            _items.erase(it);
    }

    if (object->type == GameObjectType::InventoryOnMap) {
        auto it = std::find(_inventories.begin(), _inventories.end(), object);
        if (it != _inventories.end())
            _inventories.erase(it);
    }

    if (object->type == GameObjectType::FlatObject) {
        auto it = std::find(_flatObjects.begin(), _flatObjects.end(), object);
        if (it != _flatObjects.end())
            _flatObjects.erase(it);
    }

    if (object->type == GameObjectType::Monster) {
        auto it = std::find(_monsters.begin(), _monsters.end(), object);
        if (it != _monsters.end())
            _monsters.erase(it);
    }

    if (object->type == GameObjectType::SmallObject) {
        auto it = std::find(_smallObjects.begin(), _smallObjects.end(), object);
        if (it != _smallObjects.end())
            _smallObjects.erase(it);
    }

    if (object->type == GameObjectType::Door) {
        auto it = std::find(_doors.begin(), _doors.end(), object);
        if (it != _doors.end())
            _doors.erase(it);
    }

    if (object->type == GameObjectType::Character) {
        auto it = std::find(_characters.begin(), _characters.end(), object);
        if (it != _characters.end()) {
            std::cout << "delete character\n";
            _characters.erase(it);
        }

    }

    if (object->type == GameObjectType::Building) {
        auto it = std::find(_buildings.begin(), _buildings.end(), object);
        if (it != _buildings.end())
            _buildings.erase(it);
    }
}

void Chunk::draw()
{
    window->draw(*terrain);

    water->update();    // TO-DO
    window->draw(*water);

    if (renderTilesBorders == true)
        window->draw(*borders);
}

void Chunk::drawAllStatistics() {
    if (renderBorders)
        window->draw(frame);

    if (renderCoords)
        window->draw(coordsText);
}



Mapa::Mapa()
{
    chunks.clear();

    width = 32;
    height = 32;

    for (short y = 0; y < height; y++) {
        for (short x = 0; x < width; x++) {
            Chunk* ch = new Chunk(x, y);
            chunks.push_back(ch);
        }
    }
}

Chunk* Mapa::getChunk(short x, short y)
{
    for (auto& chunk : chunks) {
        if (short(chunk->coords.x) == x && short(chunk->coords.y) == y) {
            //cout << chunk->coords.x << " " << chunk->coords.y << "\n";
            return chunk;
        }

    }

    return nullptr;
}

Chunk* Mapa::getChunk(sf::Vector2f position)
{
    float left, right, top, bottom;

    for (auto& chunk : chunks) {

        left = chunk->coords.x * 16 * tileSide;
        right = left + chunk->terrain->width * tileSide;
        top = chunk->coords.y * 16 * tileSide;
        bottom = top + chunk->terrain->height * tileSide;

        if (position.x >= left && position.x < right && position.y >= top && position.y < bottom)
        {
            //cout << m->coords.x << ", " << m->coords.y << "\n";
            return chunk;

        }
    }

    return nullptr;
}

void Mapa::save(std::string filename) {
    std::ofstream file(filename);

    for (auto& chunk : chunks) {
        file << "Chunk ";

        file << "y=" << chunk->coords.y << " ";
        file << "x=" << chunk->coords.x << "\n";

        for (short y = 0; y < 16; y++) {
            for (short x = 0; x < 16; x++) {

                file << chunk->terrain->tiles[y * 16 + x];

                if (x != 15)
                    file << " ";
            }

            file << "\n";
        }

        for (auto& nature : chunk->_natures)
            file << "Nature \"" << nature->name << "\" y=" << int(nature->position.y) << " x=" << int(nature->position.x) << "\n";

        for (auto& object : chunk->_objects)
            file << "Object \"" << object->name << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

        for (auto& item : chunk->_items)
            file << "Item \"" << item->name << "\" y=" << int(item->position.y) << " x=" << int(item->position.x) << "\n";

        for (auto& inventory : chunk->_inventories)
            file << "Inventory \"" << inventory->name << "\" y=" << int(inventory->position.y) << " x=" << int(inventory->position.x) << "\n";

        for (auto& flat : chunk->_flatObjects)
            file << "FlatObject \"" << flat->name << "\" y=" << int(flat->position.y) << " x=" << int(flat->position.x) << "\n";

        for (auto& monster : chunk->_monsters)
            file << "Monster \"" << monster->name << "\" y=" << int(monster->base.y) << " x=" << int(monster->base.x) << "\n";

        for (auto& object : chunk->_smallObjects)
            file << "SmallObject \"" << object->name << "\" y=" << int(object->position.y) << " x=" << int(object->position.x) << "\n";

        for (auto& character : chunk->_characters)
            file << "Character \"" << character->name << "\" y=" << int(character->position.y) << " x=" << int(character->position.x) << "\n";

        for (auto& building : chunk->_buildings)
            file << "Building \"" << building->name << "\" y=" << int(building->position.y) << " x=" << int(building->position.x) << "\n";

        file << "\n";
    }

    file.close();

    std::cout << "saved map\n";
}

void Mapa::load(std::string filename) {
    // clearing chunks
    for (auto& chunk : chunks) {
        delete chunk;
    }

    chunks.clear();

    clearAllMainListsOfGameObjects();

    // create chunks
    short width = 32;
    short height = 32;

    for (short y = 0; y < height; y++) {
        for (short x = 0; x < width; x++) {
            Chunk* ch = new Chunk(x, y);
            chunks.push_back(ch);
        }
    }

    // open file map
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "cant open map: " << filename << "\n";
        return;
    }

    std::cout << "open map: " << filename << "\n";

    std::string line;
    std::string objectType;
    Chunk* chunk = nullptr;

    // loading
    while (std::getline(file, line)) {

        if (line.empty()) {
            //cout << "empty line\n";
            continue;
        }

        std::istringstream lineStream(line);
        lineStream >> objectType;

        if (objectType == "Chunk") {

            // load Chunk
            std::regex chunk_regex(R"(Chunk y=([0-9]+) x=([0-9]+))");
            std::smatch chunk_match;

            if (std::regex_search(line, chunk_match, chunk_regex)) {
                int chunk_y = std::stoi(chunk_match[1]);
                int chunk_x = std::stoi(chunk_match[2]);

                // get chunk
                chunk = getChunk(chunk_x, chunk_y);

                if (chunk == nullptr) {
                    chunk = new Chunk(chunk_x, chunk_y);
                    chunks.push_back(chunk);
                }

                // check the correct of datas
                std::streampos pos = file.tellg(); // Zapisanie pozycji linii
                bool correct_data = true;
                std::string _line;
                int y = 0;
                int x;

                while (std::getline(file, _line) && _line[0] >= '0' && _line[0] <= '9') {

                    std::istringstream iss(_line);
                    int val;
                    x = 0;

                    while (iss >> val)
                        x += 1;

                    if (x != 16) {
                        //cout << x << "\n";
                        correct_data = false;
                    }

                    y += 1;
                };

                if (y != 16) {
                    //cout << y << "\n";
                    correct_data = false;
                }

                // predefine tiles
                std::vector < short > tiles(256, 0);

                if (correct_data == true) {
                    file.seekg(pos); // wczytanie pozycji linii

                    // load tiles
                    short y = 0;
                    while (y < 16 && std::getline(file, line)) {

                        std::istringstream tileStream(line);
                        short value;
                        short x = 0;

                        while (tileStream >> value) {
                            tiles[y * 16 + x] = value;
                            x += 1;
                        }

                        y += 1;
                    }

                    // set the tiles
                    for (short i = 0; i < tiles.size(); i++) {

                        chunk->terrain->edit(i % 16, i / 16, tiles[i]);

                        // TO-DO
                        if (tiles[i] == 0 || (tiles[i] >= countOfBasicTerrain && tiles[i] < countOfBasicTerrain + 16)) {
                            chunk->water->edit(i % 16, i / 16, tiles[i]);
                        }
                        else
                            chunk->water->edit(i % 16, i / 16, -1);

                    }


                }


            }

        }
        else {

            short x, y;
            std::string temp;
            std::string objectName;

            std::getline(lineStream, temp, '"');         // get string to temp to sign "
            std::getline(lineStream, objectName, '"');   // get string to objectName to sign "
            std::getline(lineStream, temp, '=');         // get string to temp to sign =
            lineStream >> y;                        // string to y
            std::getline(lineStream, temp, '=');         // get string to temp to sign =
            lineStream >> x;                        // string to x
            //cout << objectType << " \"" << objectName << "\" " << x << " " << y << "\n";

            chunk = getChunk(sf::Vector2f(x, y));
            if (chunk == nullptr) {
                chunk = new Chunk(x / 256, y / 256);
                chunks.push_back(chunk);
            }

            if (objectType == "Nature") {
                GameObject* prefab = getPrefab(objectName);
                if (prefab != nullptr) {
                    Nature* nature = new Nature(prefab, x, y);
                    chunk->_natures.push_back(nature);
                }
            }

            if (objectType == "Object") {
                GameObject* prefab = getPrefab(objectName);
                if (prefab != nullptr) {
                    Object* object = new Object(prefab, x, y);
                    chunk->_objects.push_back(object);
                }
            }

            if (objectType == "Item") {
                Item* item = getItem(objectName);
                if (item != nullptr) {
                    ItemOnMap* itemOnMap = new ItemOnMap(item, x, y);
                    chunk->_items.push_back(itemOnMap);
                }
            }

            if (objectType == "Inventory") {
                // TO-DO - get Inventory(id)
                Inventory* inventory = getInventory(0);
                if (inventory != nullptr) {
                    InventoryOnMap* inventoryOnMap = new InventoryOnMap(inventory, x, y);
                    chunk->_inventories.push_back(inventoryOnMap);
                }
            }

            if (objectType == "FlatObject") {
                GameObject* prefab = getPrefab(objectName);
                if (prefab != nullptr) {
                    FlatObject* flat = new FlatObject(prefab, x, y);
                    chunk->_flatObjects.push_back(flat);
                }
            }

            if (objectType == "Monster") {
                GameObject* prefab = getPrefab(objectName);
                if (prefab != nullptr) {
                    Monster* monster = new Monster(prefab, x, y);
                    chunk->_monsters.push_back(monster);
                }
            }

            if (objectType == "SmallObject") {
                GameObject* prefab = getPrefab(objectName);
                if (prefab != nullptr) {
                    SmallObject* object = new SmallObject(prefab, x, y);
                    chunk->_smallObjects.push_back(object);
                }
            }

            if (objectType == "Character") {
                // To-DO - get Character
                GameObject* prefab = getPrefab(objectName);
                if (prefab != nullptr) {
                    Character* character = new Character(prefab, x, y);
                    chunk->_characters.push_back(character);
                }
            }

            if (objectType == "Building") {
                // TO-DO
                Building* building = new Building(objectName, x, y);
                chunk->_buildings.push_back(building);
            }

        }


    }

    file.close();

    mapVisiblings();
    generateBorders();
}

void Mapa::mapVisiblings()
{
    sf::Vector2f chunk_position;
    float width = screenWidth * 2.0f;
    float height = screenHeight * 2.0f;
    bool prevVisible;

    for (auto& chunk : chunks) {

        chunk_position.x = (chunk->terrain->coords.x * tileSide) + 8 * tileSide;
        chunk_position.y = (chunk->terrain->coords.y * tileSide) + 8 * tileSide;

        prevVisible = chunk->visible;

        chunk->visible = intersectionTwoRectangles(cam->position.x, cam->position.y, width, height, chunk_position.x, chunk_position.y, 16 * tileSide, 16 * tileSide);

        if (prevVisible == false && chunk->visible == true) {
            chunk->addGameObjectsToMainLists();
        }
        else if (prevVisible == true && chunk->visible == false) {
            chunk->removeGameObjectsFromMainLists();
        }

    }
}

void Mapa::generateBorders(Chunk* chunk) {
    Chunk* centerChunk;
    Chunk* topChunk;
    Chunk* bottomChunk;
    Chunk* leftChunk;
    Chunk* rightChunk;

    Terrain* centerTerrain;
    Terrain* topTerrain;
    Terrain* bottomTerrain;
    Terrain* leftTerrain;
    Terrain* rightTerrain;

    for (short y = -1; y <= 1; y++)
        for (short x = -1; x <= 1; x++) {
            centerChunk = getChunk(chunk->coords.x + x, chunk->coords.y + y);

            if (centerChunk != nullptr) {
                topChunk = getChunk(chunk->coords.x + x, chunk->coords.y + y - 1);
                bottomChunk = getChunk(chunk->coords.x + x, chunk->coords.y + y + 1);
                leftChunk = getChunk(chunk->coords.x + x - 1, chunk->coords.y + y);
                rightChunk = getChunk(chunk->coords.x + x + 1, chunk->coords.y + y);

                centerTerrain = centerChunk->terrain;
                (topChunk != nullptr) ? topTerrain = topChunk->terrain : topTerrain = nullptr;
                (bottomChunk != nullptr) ? bottomTerrain = bottomChunk->terrain : bottomTerrain = nullptr;
                (leftChunk != nullptr) ? leftTerrain = leftChunk->terrain : leftTerrain = nullptr;
                (rightChunk != nullptr) ? rightTerrain = rightChunk->terrain : rightTerrain = nullptr;

                centerChunk->borders->generate(centerTerrain, topTerrain, bottomTerrain, leftTerrain, rightTerrain);
            }

        }
}

void Mapa::generateBorders() {
    Chunk* chunk;
    Chunk* topChunk;
    Chunk* bottomChunk;
    Chunk* leftChunk;
    Chunk* rightChunk;

    Terrain* terrain;
    Terrain* topTerrain;
    Terrain* bottomTerrain;
    Terrain* leftTerrain;
    Terrain* rightTerrain;

    short y, x;

    for (int i = 0; i < chunks.size(); i++) {

        y = chunks[i]->coords.y;
        x = chunks[i]->coords.x;

        //cout << x << " " << y << "\n";

        chunk = getChunk(x, y);
        topChunk = getChunk(x, y - 1);
        bottomChunk = getChunk(x, y + 1);
        leftChunk = getChunk(x - 1, y);
        rightChunk = getChunk(x + 1, y);

        terrain = chunk->terrain;
        (topChunk != nullptr) ? topTerrain = topChunk->terrain : topTerrain = nullptr;
        (bottomChunk != nullptr) ? bottomTerrain = bottomChunk->terrain : bottomTerrain = nullptr;
        (leftChunk != nullptr) ? leftTerrain = leftChunk->terrain : leftTerrain = nullptr;
        (rightChunk != nullptr) ? rightTerrain = rightChunk->terrain : rightTerrain = nullptr;

        chunks[i]->borders->generate(terrain, topTerrain, bottomTerrain, leftTerrain, rightTerrain);
    }
}

void Mapa::draw() {
    for (auto& chunk : chunks) {
        chunk->draw();
    }
}

void Mapa::drawStatistics() {
    for (auto& chunk : chunks) {
        chunk->drawAllStatistics();
    }
}

Mapa* mapa = nullptr;
