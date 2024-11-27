#ifndef MapEditorPalette_hpp
#define MapEditorPalette_hpp
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

toolType tool;
short brushSize;
sf::Texture tileset;



enum class PaletteType { MapEditor, BuildingEditor };

class PaletteButton : public ButtonWithImage {
public:

    GameObject* object;
    sf::Sprite sprite;

    PaletteButton(sf::Vector2f position) : ButtonWithImage(getSingleTexture("GUI/slot2"), position) {
        object = nullptr;
    }

    void setGameObject(GameObject* object) {
        this->object = object;

        sprite = sf::Sprite();

        if (object != nullptr) {

            if (object->type != GameObjectType::Water) {
                sprite.setTexture(*object->texture->texture);
            }
            else
                sprite.setTexture(*dynamic_cast<WaterPrefab*>(object)->terrain->texture->texture);

            if (object->type == GameObjectType::Terrain || object->type == GameObjectType::Water) {


                sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
                sprite.setOrigin(8, 8);
                sprite.setScale(3.0f, 3.0f);
            }
            else if (object->type != GameObjectType::ItemOnMap) {

                sf::Vector2f o; // origin
                o.x = sprite.getTexture()->getSize().x / 2.0f;
                o.y = sprite.getTexture()->getSize().y / 2.0f;
                sprite.setOrigin(o);

                sf::Vector2f s; // scale

                if (sprite.getLocalBounds().getSize().x > sprite.getLocalBounds().getSize().y) {
                    s.x = 64.0f / float(sprite.getTexture()->getSize().x) * 0.75f;
                    s.y = 64.0f / float(sprite.getTexture()->getSize().x) * 0.75f;
                }
                else if (sprite.getLocalBounds().getSize().x < sprite.getLocalBounds().getSize().y) {
                    s.x = 64.0f / float(sprite.getTexture()->getSize().y) * 0.75f;
                    s.y = 64.0f / float(sprite.getTexture()->getSize().y) * 0.75f;
                }
                else {
                    s.x = 64.0f / float(sprite.getTexture()->getSize().x) * 0.75f;
                    s.y = 64.0f / float(sprite.getTexture()->getSize().x) * 0.75f;
                }

                sprite.setScale(s);
            }
            else {
                // Items
                sprite.setOrigin(28, 28);
                sprite.setTextureRect(sf::IntRect(4, 4, 56, 56));

                
            }

            hover_func = [this]() {
                if (tip == nullptr || tip->btn != this) {
                    sf::Vector2f pos;
                    pos.x = this->position.x - sprite.getTexture()->getSize().x / 2.0f;
                    pos.y = this->position.y + sprite.getTexture()->getSize().y / 4.0f;
                    tip = new Tip(ConvertUtf8ToWide(this->object->name),pos, this);       // TO-DO delete convert and use std::wstring
                }
                   
                };

            onclick_func = [this]() {
                tool = toolType::AddGameObject;
                prefabToPaint = this->object;
                };
        }
        
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        
    }

    virtual void update(float dt) {
        ButtonWithImage::update(dt);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    }

    virtual void draw() {
        ButtonWithImage::draw();
        
        if (object != nullptr) {
            if (object->type == GameObjectType::Water) {
                window->draw(sprite,dynamic_cast< WaterPrefab* >(object)->shader->shader);
            }
            else
                window->draw(sprite);
        }
          
            
        
    }
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

    Palette(PaletteType type) {
        this->type = type;
        
        createPaletteButtons(5,7);
        createToolsButtons();
        createNavButtons();
        createGroupButtons();


        if(type == PaletteType::MapEditor)        selectedGroupButton = btnGroupTerrain;
        if(type == PaletteType::BuildingEditor)   selectedGroupButton = btnGroupFloors;
        
        selectedToolButton = btnToolsCursor;
        selectedPaletteButton = nullptr;

        if(type == PaletteType::MapEditor)       setTerrainObjectsToPalette();
        if(type == PaletteType::BuildingEditor)  setFloorsObjectsToPalette();

        loadPalette();

        ///////////////////////

        tool = toolType::Cursor;
        brushSize = 0;
    }

    void deletePaletteButtons() {
        if (paletteButtons.size() > 0) {
            for (int i = 0; i < paletteButtons.size(); i++) {
                delete paletteButtons[i];
            }

            paletteButtons.clear();
        }
    }

    void deleteNavButtons() {
        if (buttonUp != nullptr) {
            delete buttonUp;
            buttonUp = nullptr;
        }

        if (buttonDown != nullptr) {
            delete buttonDown;
            buttonDown = nullptr;
        }
    }

    void deleteToolsButtons() {
        if (toolsButtons.size() > 0) {
            for (int i = 0; i < toolsButtons.size(); i++) {
                delete toolsButtons[i];
            }

            toolsButtons.clear();
        }

        cout << "delete Tools Buttons\n";
    }

    void deleteGroupButtons() {
        if (groupButtons.size() > 0) {
            for (int i = 0; i < groupButtons.size(); i++) {
                delete groupButtons[i];
            }

            groupButtons.clear();
        }
    }

    void createPaletteButtons(short size_x, short size_y) {

        deletePaletteButtons();
        
        size.x = size_x;
        size.y = size_y;

        sf::Vector2f start_pos; // left bottom 
        start_pos.x = 0;
        start_pos.x = screenWidth/2.0f - size.x*64 + 32;
        start_pos.y = screenHeight/2.0f - 37 - 32;

        for (short y = 0; y < size.y; y++) {
            for (short x = 0; x < size.x; x++) {

                sf::Vector2f pos;
                pos.x = start_pos.x + x * 64;
                pos.y = start_pos.y - (size.y -1 - y) * 64;

                PaletteButton* btn = new PaletteButton(pos);
                paletteButtons.push_back(btn);
            }
        }
        


    }

    void setTerrainObjectsToPalette() {

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

        
        short id  = countOfBasicTerrain;
        // SET - SANDS_WATER
        id += 8;    // skip the SET - SANDS_WATER
        id += 8;    // skip the SET - WATER_SANDS
        
        // SET - SANDS_GRASS
        availableGameObjects.push_back(terrainGameObjects[id + 0]);
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
        
        
    }

    void setFloorsObjectsToPalette() {

        availableGameObjects.clear();

        for (auto& floor : floorGameObjects)
            availableGameObjects.push_back(floor);

    }

    void setWaterObjectsToPalette() {
        
        availableGameObjects.clear();

        for (int i = 0; i < countOfBasicWater-1; i++) {

            // WATER_TERRAIN
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 0]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 2]);

            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 3]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 4]);

            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 3]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 4]);

            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 3]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
            availableGameObjects.push_back(terrainGameObjects[i+1]);
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
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 12]);

            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 11]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 12]);

            availableGameObjects.push_back(waterGameObjects[countOfBasicWater + i * 16 + 11]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
            availableGameObjects.push_back(waterGameObjects[i+1]);
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

    void setFurnituresObjectsToPalette() {
        availableGameObjects.clear();

        for(auto& p : prefabs)
            if(p->type == GameObjectType::Furniture)
                availableGameObjects.push_back(p);
    }

    void setWallsObjectsToPalette() {
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

        availableGameObjects.push_back(getPrefab("walls/mud_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall"));
        availableGameObjects.push_back(getPrefab("walls/mud_wall"));

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
        availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown2"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown"));
        availableGameObjects.push_back(getPrefab("walls/stone_wall_overgrown2"));

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

        availableGameObjects.push_back(getPrefab("walls/wooden_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall"));
        availableGameObjects.push_back(getPrefab("walls/wooden_wall"));

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

        availableGameObjects.push_back(getPrefab("walls/brick_wall"));
        availableGameObjects.push_back(getPrefab("walls/brick_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/brick_wall"));
        availableGameObjects.push_back(getPrefab("walls/brick_wall"));

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

        availableGameObjects.push_back(getPrefab("walls/mulch_wall"));
        availableGameObjects.push_back(getPrefab("walls/mulch_wall"));
        availableGameObjects.push_back(getPrefab("walls/empty_wall"));
        availableGameObjects.push_back(getPrefab("walls/mulch_wall"));
        availableGameObjects.push_back(getPrefab("walls/mulch_wall"));
    }

    void setMonstersObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Monster) {
                availableGameObjects.push_back(p);
            }
        }
    }

    void setFlatObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& f : prefabs) {
            if (f->type == GameObjectType::FlatObject) {
                availableGameObjects.push_back(f);
            }
        }
    }

    void setItemsObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& i : items) {
            availableGameObjects.push_back(getPrefab(i->name));
        }

    }

    void setNaturesObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Nature) {
                availableGameObjects.push_back(p);
            }
        }
    }

    void setObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::Object) {
                availableGameObjects.push_back(p);
            }
        }

        availableGameObjects.push_back(getPrefab("doors/wooden_gate"));
    }

    void setSmallObjectsToPalette() {
        availableGameObjects.clear();

        for (auto& p : prefabs) {
            if (p->type == GameObjectType::SmallObject) {
                availableGameObjects.push_back(p);
            }
        }
    }

    void loadPalette() {
        for (int i = 0; i < paletteButtons.size(); i++) {

            int index = i + scroll * size.x;

            GameObject* object;
            (index < availableGameObjects.size())? object = availableGameObjects[index] : object = nullptr;
            paletteButtons[i]->setGameObject(object);

            if(object!=nullptr)
                if (object->type == GameObjectType::Terrain || object->type == GameObjectType::Floor || object->type == GameObjectType::Water) {
                    // object is a Terrain or Floor
                    auto button = paletteButtons[i];
                    paletteButtons[i]->onclick_func = [this, button]() {
                        prefabToPaint = button->object;
                        selectedPaletteButton = button;

                        if (tool == toolType::Cursor || tool == toolType::AddGameObject) {
                            tool = toolType::Brush;
                            selectedToolButton = btnToolsBrush;
                        }
                            
                        };
                }
                else {
                    // object is not Terrain, Floor or Water
                    auto button = paletteButtons[i];
                    paletteButtons[i]->onclick_func = [this, button]() {
                        prefabToPaint = button->object;
                        selectedPaletteButton = button;

                        tool = toolType::AddGameObject;
                        selectedToolButton = btnToolsEmpty;
                        };
                }

                

                
        }
    }

    void createNavButtons() {

        deleteNavButtons();

        scroll = 0;

        sf::Vector2f pos;
        pos.x = screenWidth / 2.0f - 160;

        pos.y = screenHeight / 2.0f - 37.0f - float(size.y) * 64.0f - 37.0f/2.0f;
        buttonUp = new ButtonWithImage(getSingleTexture("GUI/wideArrowUp2"), pos);
        buttonUp->onclick_func = [this]() {
            scrollUp();
            loadPalette();
            };

        pos.y = screenHeight / 2.0f - 37.0f/2.0f;
        buttonDown = new ButtonWithImage(getSingleTexture("GUI/wideArrowDown2"), pos);
        buttonDown->onclick_func = [this]() {
            scrollDown();
            loadPalette();
            };

    }

    void createToolsButtons() {
        // delete old Tools Buttons
        deleteToolsButtons();

        cout << "create Tools Buttons\n";
        btnToolsEmpty = new ButtonWithImage();
        btnToolsEmpty->setTexture(getSingleTexture("GUI/toolButtons/toolbutton"));

        btnToolsCursor = new ButtonWithImage();
        btnToolsCursor->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-cursor"));
        btnToolsCursor->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsCursor)
                tip = new Tip(L"Cursor", btnToolsCursor);


            };
        btnToolsCursor->onclick_func = [this]() {
            selectedToolButton = btnToolsCursor;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
        };


        btnToolsBrush = new ButtonWithImage();
        btnToolsBrush->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-brush"));
        btnToolsBrush->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsBrush)
                tip = new Tip(L"Brush", btnToolsBrush);


            };
        btnToolsBrush->onclick_func = [this]() {
            selectedToolButton = btnToolsBrush;
            tool = toolType::Brush;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsRectBrush = new ButtonWithImage();
        btnToolsRectBrush->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-rect_brush"));
        btnToolsRectBrush->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsRectBrush)
                tip = new Tip(L"Rectangle Brush", btnToolsRectBrush);


            };
        btnToolsRectBrush->onclick_func = [this]() {
            selectedToolButton = btnToolsRectBrush;
            tool = toolType::RectBrush;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsIncrease = new ButtonWithImage();
        btnToolsIncrease->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-increase"));
        btnToolsIncrease->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsIncrease)
                tip = new Tip(L"Increase", btnToolsIncrease);


            };
        btnToolsIncrease->onclick_func = [this]() {
            if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
                if (brushSize < 5) {
                    brushSize++;
                    setBrushSize(brushSize);

                    coutBrush();
                    //cout << "\n\n";
                }

            }
        };


        btnToolsDecrease = new ButtonWithImage();
        btnToolsDecrease->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-decrease"));
        btnToolsDecrease->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsDecrease)
                tip = new Tip(L"Decrease", btnToolsDecrease);


            };
        btnToolsDecrease->onclick_func = [this]() {
            if (selectedToolButton == btnToolsBrush || selectedToolButton == btnToolsRectBrush || selectedToolButton == btnToolsEraser) {
                if (brushSize > 0) {
                    brushSize--;
                    setBrushSize(brushSize);

                    //coutBrush();
                    //cout << "\n\n";
                }


            }
        };


        btnToolsRectangle = new ButtonWithImage();
        btnToolsRectangle->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-rectangle"));
        btnToolsRectangle->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsRectangle)
                tip = new Tip(L"Rectangle", btnToolsRectangle);


            };
        btnToolsRectangle->onclick_func = [this]() {
            selectedToolButton = btnToolsRectangle;
            tool = toolType::Rectangle;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsElipse = new ButtonWithImage();
        btnToolsElipse->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-elipse"));
        btnToolsElipse->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsElipse)
                tip = new Tip(L"Elipse", btnToolsElipse);


            };
        btnToolsElipse->onclick_func = [this]() {
            selectedToolButton = btnToolsElipse;
            tool = toolType::Elipse;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };


        btnToolsFill = new ButtonWithImage();
        btnToolsFill->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-fill"));
        btnToolsFill->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsElipse)
                tip = new Tip(L"Fill", btnToolsFill);


            };
        btnToolsFill->onclick_func = [this]() {
            selectedToolButton = btnToolsFill;
            tool = toolType::Fill;
        };


        btnToolsEraser = new ButtonWithImage();
        btnToolsEraser->setTexture(getSingleTexture("GUI/toolButtons/toolbutton-eraser"));
        btnToolsEraser->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnToolsEraser)
                tip = new Tip(L"Eraser", btnToolsEraser);


            };
        btnToolsEraser->onclick_func = [this]() {
            selectedToolButton = btnToolsEraser;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            tool = toolType::Eraser;
            if (prefabToPaint == nullptr) {
                prefabToPaint = availableGameObjects[1];
                selectedPaletteButton = paletteButtons[1];
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f sp;    // start position
        sp.x = screenWidth / 2.0f - 10*32 + 16;
        sp.y = -screenHeight/2.0f + 2*52 + 16 + 30;

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



        brushSize = 0;
        setBrushSize(brushSize);
    }

    void createGroupButtons() {

        deleteGroupButtons();

        // create Group Buttons
        btnGroupEmpty = new ButtonWithImage();
        btnGroupEmpty->setTexture(getSingleTexture("GUI/menuButtons/menuButton"));

        btnGroupTerrain = new ButtonWithImage();
        btnGroupTerrain->setTexture(getSingleTexture("GUI/menuButtons/menuButton-terrain"));
        btnGroupTerrain->hover_func = [this]() {
            if (tip == nullptr || tip->btn!=btnGroupTerrain)
                tip = new Tip(L"Terrains", btnGroupTerrain);

            
            };
        btnGroupTerrain->onclick_func = [this]() {
            selectedGroupButton = btnGroupTerrain;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,7);
            createNavButtons();
            createToolsButtons();
            setTerrainObjectsToPalette();
            loadPalette();
            };

        btnGroupFloors = new ButtonWithImage();
        btnGroupFloors->setTexture(getSingleTexture("GUI/menuButtons/menuButton-floors"));
        btnGroupFloors->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupFloors)
               tip = new Tip(L"Floors", btnGroupFloors);
            };
        btnGroupFloors->onclick_func = [this]() {
            selectedGroupButton = btnGroupFloors;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,7);
            createNavButtons();
            createToolsButtons();
            setFloorsObjectsToPalette();
            loadPalette();
            };

        btnGroupWater = new ButtonWithImage();
        btnGroupWater->setTexture(getSingleTexture("GUI/menuButtons/menuButton-water"));
        btnGroupWater->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupWater)
                tip = new Tip(L"Waters", btnGroupWater);
            };
        btnGroupWater->onclick_func = [this]() {
            selectedGroupButton = btnGroupWater;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5, 7);
            createNavButtons();
            createToolsButtons();
            setWaterObjectsToPalette();
            loadPalette();
            };

        btnGroupFurnitures = new ButtonWithImage();
        btnGroupFurnitures->setTexture(getSingleTexture("GUI/menuButtons/menuButton-furnitures"));
        btnGroupFurnitures->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupFurnitures)
                tip = new Tip(L"Furnitures", btnGroupFurnitures);
            };
        btnGroupFurnitures->onclick_func = [this]() {
            selectedGroupButton = btnGroupFurnitures;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setFurnituresObjectsToPalette();
            loadPalette();
            };

        btnGroupWalls = new ButtonWithImage();
        btnGroupWalls->setTexture(getSingleTexture("GUI/menuButtons/menuButton-walls"));
        btnGroupWalls->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupWalls)
                tip = new Tip(L"Walls", btnGroupWalls);
            };
        btnGroupWalls->onclick_func = [this]() {
            selectedGroupButton = btnGroupWalls;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setWallsObjectsToPalette();
            loadPalette();
            };

        btnGroupMonsters = new ButtonWithImage();
        btnGroupMonsters->setTexture(getSingleTexture("GUI/menuButtons/menuButton-monsters"));
        btnGroupMonsters->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupMonsters)
                tip = new Tip(L"Monsters", btnGroupMonsters);
            };
        btnGroupMonsters->onclick_func = [this]() {
            selectedGroupButton = btnGroupMonsters;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setMonstersObjectsToPalette();
            loadPalette();
            };

        btnGroupFlatObjects = new ButtonWithImage();
        btnGroupFlatObjects->setTexture(getSingleTexture("GUI/menuButtons/menuButton-flat_objects"));
        btnGroupFlatObjects->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupFlatObjects)
                tip = new Tip(L"Flat Objects", btnGroupFlatObjects);
            };
        btnGroupFlatObjects->onclick_func = [this]() {
            selectedGroupButton = btnGroupFlatObjects;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setFlatObjectsToPalette();
            loadPalette();
            };

        btnGroupItems = new ButtonWithImage();
        btnGroupItems->setTexture(getSingleTexture("GUI/menuButtons/menuButton-items"));
        btnGroupItems->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupItems)
                tip = new Tip(L"Items", btnGroupItems);
            };
        btnGroupItems->onclick_func = [this]() {
            selectedGroupButton = btnGroupItems;
            tool = toolType::Cursor;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setItemsObjectsToPalette();
            loadPalette();
            };

        btnGroupNatures = new ButtonWithImage();
        btnGroupNatures->setTexture(getSingleTexture("GUI/menuButtons/menuButton-natures"));
        btnGroupNatures->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupNatures)
                tip = new Tip(L"Natures Objects", btnGroupNatures);
            };
        btnGroupNatures->onclick_func = [this]() {
            tool = toolType::Cursor;
            selectedGroupButton = btnGroupNatures;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5,8);
            createNavButtons();
            deleteToolsButtons();
            setNaturesObjectsToPalette();
            loadPalette();
            };

        btnGroupObjects = new ButtonWithImage();
        btnGroupObjects->setTexture(getSingleTexture("GUI/menuButtons/menuButton-objects"));
        btnGroupObjects->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupObjects)
                tip = new Tip(L"Objects", btnGroupObjects);
            };
        btnGroupObjects->onclick_func = [this]() {
            tool = toolType::Cursor;
            selectedGroupButton = btnGroupObjects;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
            createPaletteButtons(5, 8);
            createNavButtons();
            deleteToolsButtons();
            setObjectsToPalette();
            loadPalette();
            };

        btnGroupSmallObjects = new ButtonWithImage();
        btnGroupSmallObjects->setTexture(getSingleTexture("GUI/menuButtons/menuButton-smallObjects"));
        btnGroupSmallObjects->hover_func = [this]() {
            if (tip == nullptr || tip->btn != btnGroupSmallObjects)
                tip = new Tip(L"Small Objects", btnGroupSmallObjects);
            };
        btnGroupSmallObjects->onclick_func = [this]() {
            tool = toolType::Cursor;
            selectedGroupButton = btnGroupSmallObjects;
            selectedPaletteButton = nullptr;
            prefabToPaint = nullptr;
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

    void scrollUp() {
        if(scroll > 0)
            scroll -= 1;
    }

    void scrollDown() {

        short maxScroll = availableGameObjects.size() - size.x * size.y;
        if (maxScroll < 0)
            maxScroll = 0;

        if(scroll*size.x < maxScroll)
            scroll += 1;
    }

    void unclickButtons() {
        for (auto& tool : toolsButtons)
            tool->unclick();

        for (auto& btn : groupButtons)
            btn->unclick();

        for (auto& btn : paletteButtons)
            btn->unclick();

        buttonUp->unclick();
        buttonDown->unclick();
    }

    void hoverButtons() {
        for (auto& tool : toolsButtons)
            tool->hover();

        for (auto& btn : groupButtons)
            btn->hover();

        for (auto& btn : paletteButtons)
            btn->hover();

        buttonUp->hover();
        buttonDown->hover();
    }

    void clickButtons() {

        for (auto& tool : toolsButtons)
            tool->click();

        for (auto& btn : groupButtons)
            btn->click();

        for (auto& btn : paletteButtons)
            btn->click();

        buttonUp->click();
        buttonDown->click();

    }

    void update(float dt) {
        for (auto& tool : toolsButtons)
            tool->update(dt);

        for (auto& btn : groupButtons)
            btn->update(dt);

        for (auto& btn : paletteButtons) 
            btn->update(dt);
            
        buttonUp->update(dt);
        buttonDown->update(dt);
    }

    void draw() {

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
};

Palette* palette = nullptr;

#endif