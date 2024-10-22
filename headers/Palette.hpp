#ifndef MapEditorPalette_hpp
#define MapEditorPalette_hpp

sf::Vector2f paletteButtonSize = sf::Vector2f(80.0f, 80.0f);
sf::Vector2f palettePosition;
std::vector < GameObject* > availableGameObjects;
std::vector < GameObject* > terrainGameObjects;
std::vector < GameObject* > floorGameObjects;
std::vector < GameObject* > buildingGameObjects;

short paletteScroll;
short paletteCols;
short paletteRows;

/*
    idle = normal state
    hover - button is hover by cursor
    pressed - button is pressed by click
*/

class Button {
public:

    sf::Vector2f position;
    sf::Sprite sprite;
    buttonState state;
    std::function<void()> func;
    sf::Time clickTime;

    Button() {
        sprite = sf::Sprite();
        state = buttonState::idle;
        func = { };
        
        clickTime = currentTime;
    }

    Button(Button* btn) {

        this->position = btn->position;
        this->sprite = btn->sprite;
        state = buttonState::idle;
        this->func = btn->func;

        clickTime = currentTime;
    }

    Button(Button* btn, sf::Vector2f position) {


        this->position = position;
        this->sprite = btn->sprite;
        state = buttonState::idle;
        this->func = btn->func;

        clickTime = currentTime;
    }

    Button(Texture* texture, sf::Vector2f position) {
        this->position = position;

        sprite = sf::Sprite();

        state = buttonState::idle;

        if (texture != nullptr) {
            sprite.setTexture(*texture->texture);
            sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
        }

        func = { };

        clickTime = currentTime;
    }

    virtual void setTexture(Texture* texture) {
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
    }

    virtual void setPosition(sf::Vector2f position) {
        this->position = position;
        sprite.setPosition(position);
    }

    virtual void changeColor() {

        if (state == buttonState::pressed) {
            sprite.setColor(spritePressedColor);
        }
        else if (state == buttonState::hover) {
            sprite.setColor(spriteHoverColor);
        }
        else {
            sprite.setColor(spriteIdleColor);
        }
            
    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {
            state = buttonState::idle;
            changeColor();
        }
            
    }

    virtual void hover() {
        if (state != buttonState::pressed) {

            float w = sprite.getTexture()->getSize().x;
            float h = sprite.getTexture()->getSize().y;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                state = buttonState::hover;
                changeColor();
                GUIwasHover = true;
            }
        }
        else {
            // GUI WAS PRESSED
            GUIwasHover = true;
        }
    }

    virtual void click() {
        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {
            
            state = buttonState::pressed;
            changeColor();
            GUIwasClicked = true;
            clickTime = currentTime;

            if (func)
                func();
    
        }

    }

    virtual void update(float dt) {
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
    }

    virtual void draw() {

        window->draw(sprite);
    }
};

Button* buttonUp;
Button* buttonDown;

Button* btnGroupEmpty;
Button* btnGroupTerrain;
Button* btnGroupFloors;
Button* btnGroupFurnitures;
Button* btnGroupWalls;
Button* btnGroupMonsters;
Button* btnGroupPaths;
Button* btnGroupItems;
Button* btnGroupNatures;

Button* btnToolsCursor;
Button* btnToolsBrush;
Button* btnToolsRectBrush;
Button* btnToolsIncrease;
Button* btnToolsDecrease;
Button* btnToolsRectangle;
Button* btnToolsElipse;
Button* btnToolsFill;
Button* btnToolsEraser;

Button* selectedGroupButton;
Button* selectedPaletteButton;
Button* selectedTool;

toolType tool;
short brushSize;

class PaletteButton : public Button {
public:

    sf::Sprite objectSprite;
    GameObject* object;

    PaletteButton() : Button() {

        sprite.setTexture(*getTexture("GUI/slot2")->texture);
        sprite.setOrigin(40, 40);
        
        object = nullptr;
        
        state = buttonState::idle;
    }

    virtual void changeColor() {

        if (state == buttonState::pressed) {
            sprite.setColor(spritePressedColor);
            objectSprite.setColor(spritePressedColor);
        }
        else if (state == buttonState::hover) {
            sprite.setColor(spriteHoverColor);
            objectSprite.setColor(spriteHoverColor);
        }
        else {
            sprite.setColor(spriteIdleColor);
            objectSprite.setColor(spriteIdleColor);
        }

    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {

            state = buttonState::idle;
            changeColor();

        }

    }

    virtual void hover() {
        if (state != buttonState::pressed) {

            float w = sprite.getTexture()->getSize().x;
            float h = sprite.getTexture()->getSize().y;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                changeColor();
                state = buttonState::hover;
                GUIwasHover = true;
            }
        }
        else {
            // GUI IS PRESSED
            GUIwasHover = true;
        }
    }

    void click(){
        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {
            
            changeColor();
            state = buttonState::pressed;
            GUIwasClicked = true;
            clickTime = currentTime;

            if (selectedPaletteButton == this) {
                
                selectedPaletteButton = nullptr;
                prefabToPaint = nullptr;
                tool = toolType::Cursor;
                selectedTool = btnToolsCursor;
            }
            else {
                
                if (object!=nullptr) {
                    selectedPaletteButton = this;
                    prefabToPaint = object;
                    if (prefabToPaint != nullptr && (prefabToPaint->type == gameObjectType::Terrain || prefabToPaint->type == gameObjectType::Floor))
                    {
                        if (!(tool == toolType::Brush || tool == toolType::RectBrush || tool == toolType::Rectangle || tool == toolType::Elipse || tool == toolType::Fill)) {
                            selectedTool = btnToolsBrush;
                            brushSize = 2;
                            tool = toolType::Brush;
                        }
                    }
                    else {
                        tool = toolType::AddGameObject;
                    }
                }

            }
                
        }

    }

    void setObject(GameObject* object) {

        this->object = object;

        if (object != nullptr) {
            objectSprite.setTexture(*getTexture(object->name)->texture);

            float tw = getTexture(object->name)->texture->getSize().x;
            float th = getTexture(object->name)->texture->getSize().y;
            objectSprite.setOrigin(tw / 2.0f, th / 2.0f);

            float scaleX = (paletteButtonSize.x - 16.0f) / tw; // 80px-16px ( 64px x 64px )
            float scaleY = (paletteButtonSize.y - 16.0f) / th; // 80px-16px ( 64px x 64px )
            objectSprite.setScale(scaleX, scaleY);
        }
    }

    void setPosition(sf::Vector2f position) {
        
        this->position = position;

        sprite.setPosition(position);
        objectSprite.setPosition(position);
    }

    void update(float dt) {

       
    }

    void draw() {
        window->draw(sprite);
        window->draw(objectSprite);
    }

};

std::vector < Button* > groupButtons;
std::vector < Button* > tools;
std::vector < PaletteButton* > palette;

void setTerrainObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& terrain : terrainGameObjects)
        availableGameObjects.push_back(terrain);

}

void setFloorsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& floor : floorGameObjects)
        availableGameObjects.push_back(floor);
}

void setFurnituresObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Furniture)
            availableGameObjects.push_back(p);
    }
}

void setMonstersObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Monster)
            availableGameObjects.push_back(p);
    }
}

void setPathsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Path)
            availableGameObjects.push_back(p);
    }
}

void setWallsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Wall)
            availableGameObjects.push_back(p);
    }
}

void setItemsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& i : items)
        availableGameObjects.push_back(getPrefab(i->name));
}

void setNaturesObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Nature)
            availableGameObjects.push_back(p);
    }
}

void scrollUp() {

    GUIwasClicked = true;

    if (paletteScroll > 0)
        paletteScroll -= 1;
}

void scrollDown() {
    GUIwasClicked = true;

    short maxValue = availableGameObjects.size() - paletteCols * paletteRows;
    if (maxValue < 0)
        maxValue = 0;

    if (paletteScroll * paletteRows < maxValue)
        paletteScroll += 1;
}

void createPalette() {

    // NAV BUTTONS

    paletteButtonSize = sf::Vector2f(80, 80);

    sf::Vector2f buttonSize = sf::Vector2f(320, 40);

    Texture* texUp = getTexture("GUI/wideArrowUp2");
    sf::Vector2f positionUp;
    positionUp.x = screenWidth / 2.f - buttonSize.x / 2.0f;
    positionUp.y = -screenHeight / 2.0f + buttonSize.y / 2.0f + paletteButtonSize.y;
    buttonUp = new Button(texUp, positionUp);
    buttonUp->func = scrollUp;

    Texture* texDown = getTexture("GUI/wideArrowDown2");
    sf::Vector2f positionDown;
    positionDown.x = screenWidth / 2.f - buttonSize.x / 2.0f;
    positionDown.y = screenHeight / 2.0f - buttonSize.y / 2.0f;
    buttonDown = new Button(texDown, positionDown);
    buttonDown->func = scrollDown;


    // MENU BUTTONS 
    btnGroupEmpty = new Button();
    btnGroupEmpty->setTexture(getTexture("GUI/menuButtons/menuButton"));

    btnGroupTerrain = new Button();
    btnGroupTerrain->setTexture(getTexture("GUI/menuButtons/menuButton-terrain"));
    btnGroupTerrain->func = []() {
        selectedGroupButton = btnGroupTerrain;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setTerrainObjectsToPalette();
        };

    btnGroupFloors = new Button();
    btnGroupFloors->setTexture(getTexture("GUI/menuButtons/menuButton-floors"));
    btnGroupFloors->func = []() {
        selectedGroupButton = btnGroupFloors;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setFloorsObjectsToPalette();
        };

    btnGroupFurnitures = new Button();
    btnGroupFurnitures->setTexture(getTexture("GUI/menuButtons/menuButton-furnitures"));
    btnGroupFurnitures->func = []() {
        selectedGroupButton = btnGroupFurnitures;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setFurnituresObjectsToPalette();
        };

    btnGroupWalls = new Button();
    btnGroupWalls->setTexture(getTexture("GUI/menuButtons/menuButton-walls"));
    btnGroupWalls->func = []() {
        selectedGroupButton = btnGroupWalls;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setWallsObjectsToPalette();
        };

    btnGroupMonsters = new Button();
    btnGroupMonsters->setTexture(getTexture("GUI/menuButtons/menuButton-monsters"));
    btnGroupMonsters->func = []() {
        selectedGroupButton = btnGroupMonsters;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setMonstersObjectsToPalette();
        };

    btnGroupPaths = new Button();
    btnGroupPaths->setTexture(getTexture("GUI/menuButtons/menuButton-paths"));
    btnGroupPaths->func = []() {
        selectedGroupButton = btnGroupPaths;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setPathsObjectsToPalette();
        };

    btnGroupItems = new Button();
    btnGroupItems->setTexture(getTexture("GUI/menuButtons/menuButton-items"));
    btnGroupItems->func = []() {
        selectedGroupButton = btnGroupItems;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setItemsObjectsToPalette();
        };

    btnGroupNatures = new Button();
    btnGroupNatures->setTexture(getTexture("GUI/menuButtons/menuButton-natures"));
    btnGroupNatures->func = []() {
        tool = toolType::Cursor;
        selectedGroupButton = btnGroupNatures;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setNaturesObjectsToPalette();
        };

    // CREATE EMPTY MENU 
    groupButtons.clear();

    for (short i = 0; i <8; i++) {
        Texture* tex = getTexture("GUI/menuButtons/menuButton");
        sf::Vector2f position;
        position.x = screenWidth/2 -(i%4 * 80) - 40;
        position.y = -screenHeight/2 + (i/4)*40 +20;
        groupButtons.push_back(new Button(btnGroupEmpty, position));
    }

    paletteScroll = 0;
    paletteRows = 4;
    paletteCols = 7;

    // TERRAIN GAMEOBJECTS
    terrainGameObjects.clear();
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_0_grass", terrainType::grass));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_1_sands", terrainType::sands));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_2_water", terrainType::water));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_3_gravel", terrainType::gravel));

    // FLOOR GAMEOBJECTS
    floorGameObjects.clear();
    floorGameObjects.push_back(new FloorPrefab("floors/floor_0", floorType::floor_0));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_1", floorType::floor_1));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_2", floorType::floor_2));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_3", floorType::floor_3));

    // CREATE TOOLS
    
    btnToolsCursor = new Button();
    btnToolsCursor->setTexture(getTexture("GUI/smallButtons/smallbutton-cursor"));
    btnToolsCursor->func = []() {
        selectedTool = btnToolsCursor;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        };
    

    btnToolsBrush = new Button();
    btnToolsBrush->setTexture(getTexture("GUI/smallButtons/smallbutton-brush"));
    btnToolsBrush->func = []() {
        selectedTool = btnToolsBrush;
        tool = toolType::Brush;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };


    btnToolsRectBrush = new Button();
    btnToolsRectBrush->setTexture(getTexture("GUI/smallButtons/smallbutton-rect_brush"));
    btnToolsRectBrush->func = []() {
        selectedTool = btnToolsRectBrush;
        tool = toolType::RectBrush;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    btnToolsIncrease = new Button();
    btnToolsIncrease->setTexture(getTexture("GUI/smallButtons/smallbutton-increase"));
    btnToolsIncrease->func = []() {
        if (selectedTool == btnToolsBrush || selectedTool == btnToolsRectBrush || selectedTool == btnToolsEraser) {
            if (brushSize < 5) {
                brushSize++;
                setBrushSize(brushSize);

                //coutBrush();
                //cout << "\n\n";
            }
                
        }
        };
    

    btnToolsDecrease = new Button();
    btnToolsDecrease->setTexture(getTexture("GUI/smallButtons/smallbutton-decrease"));
    btnToolsDecrease->func = []() {
        if (selectedTool == btnToolsBrush || selectedTool == btnToolsRectBrush || selectedTool == btnToolsEraser) {
            if (brushSize > 0) {
                brushSize--;
                setBrushSize(brushSize);

                //coutBrush();
                //cout << "\n\n";
            }
                
            
        }
        };
    

    btnToolsRectangle = new Button();
    btnToolsRectangle->setTexture(getTexture("GUI/smallButtons/smallbutton-rectangle"));
    btnToolsRectangle->func = []() {
        selectedTool = btnToolsRectangle;
        tool = toolType::Rectangle;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    btnToolsElipse = new Button();
    btnToolsElipse->setTexture(getTexture("GUI/smallButtons/smallbutton-elipse"));
    btnToolsElipse->func = []() {
        selectedTool = btnToolsElipse;
        tool = toolType::Elipse;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    btnToolsFill = new Button();
    btnToolsFill->setTexture(getTexture("GUI/smallButtons/smallbutton-fill"));
    btnToolsFill->func = []() {
        selectedTool = btnToolsFill;
        tool = toolType::Fill;
        };
    

    btnToolsEraser = new Button();
    btnToolsEraser->setTexture(getTexture("GUI/smallButtons/smallbutton-eraser"));
    btnToolsEraser->func = []() {
        selectedTool = btnToolsEraser;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        tool = toolType::Eraser;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    // EMPTY TOOLS
    Button* emptyButton = new Button();
    emptyButton->setTexture(getTexture("GUI/smallButtons/smallbutton"));
    
    //tools.push_back(btnToolsCursor);
    //tools.push_back(btnToolsBrush);
    //tools.push_back(btnToolsIncrease);
    //tools.push_back(btnToolsDecrease);
    //tools.push_back(btnToolsRectangleArea);
    //tools.push_back(btnToolsElipseArea);
    //tools.push_back(btnToolsFill);
    //tools.push_back(btnToolsEraser);

    sf::Vector2f sp;    // start position
    sp.x = screenWidth / 2.0f - paletteRows * paletteButtonSize.x + 20;
    sp.y = - screenHeight / 2.0f + paletteButtonSize.y * 2.0f - 20;

    tools.clear();

    tools.push_back(new Button(btnToolsCursor, sf::Vector2f(sp.x, sp.y)));
    tools.push_back(new Button(btnToolsBrush, sf::Vector2f(sp.x + 40, sp.y)));
    tools.push_back(new Button(btnToolsRectBrush, sf::Vector2f(sp.x + 80, sp.y)));
    tools.push_back(new Button(btnToolsIncrease, sf::Vector2f(sp.x + 120, sp.y)));
    tools.push_back(new Button(btnToolsDecrease, sf::Vector2f(sp.x + 160, sp.y)));
    tools.push_back(new Button(btnToolsRectangle, sf::Vector2f(sp.x + 200, sp.y)));
    tools.push_back(new Button(btnToolsElipse, sf::Vector2f(sp.x + 240, sp.y)));
    //tools.push_back(new Button(btnToolsFill, sf::Vector2f(sp.x + 280, sp.y)));    / /TO-DO
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x + 280, sp.y)));

    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x, sp.y + 40)));
    //tools.push_back(new Button(btnToolsEraser, sf::Vector2f(sp.x, sp.y+40))); // TO-DO
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+40, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+80, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+120, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+160, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+200, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+240, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+280, sp.y+40)));

    brushSize = 0;
    setBrushSize(brushSize);

    // SLOTS AND PREFABS
    palette.clear();
    for (short i = 0; i < paletteCols * paletteRows; i++)
        palette.push_back(new PaletteButton());
}

void createMapEditorPalette() {
    
    createPalette();
    setTerrainObjectsToPalette();

    groupButtons[3] = btnGroupTerrain;
    groupButtons[2] = btnGroupNatures;
    groupButtons[1] = btnGroupPaths;
    groupButtons[0] = btnGroupMonsters;

    groupButtons[7] = btnGroupItems;
    groupButtons[6] = new Button(btnGroupEmpty);
    groupButtons[5] = new Button(btnGroupEmpty);
    groupButtons[4] = new Button(btnGroupEmpty);

    selectedGroupButton = btnGroupTerrain;
    selectedPaletteButton = nullptr;
    selectedTool = btnToolsCursor;
    tool = toolType::Cursor;

}

void createBuildingEditorPalette() {
    
    createPalette();
    setFloorsObjectsToPalette();

    groupButtons[3] = btnGroupFloors;
    groupButtons[2] = btnGroupFurnitures;
    groupButtons[1] = btnGroupWalls;
    groupButtons[0] = btnGroupItems;

    groupButtons[7] = new Button(btnGroupEmpty);
    groupButtons[6] = new Button(btnGroupEmpty);
    groupButtons[5] = new Button(btnGroupEmpty);
    groupButtons[4] = new Button(btnGroupEmpty);

    selectedGroupButton = btnGroupFloors;
    selectedPaletteButton = nullptr;
    selectedTool = btnToolsCursor;
    tool = toolType::Cursor;
}

void updatePalette() {

    // MENU
    for (short i = 0; i < 8; i++) {
        sf::Vector2f position;
        position.x = screenWidth / 2 - (i % 4 * 80) - 40;
        position.y = -screenHeight / 2 + (i / 4) * 40 + 20;
        groupButtons[i]->setPosition(position);

        if (groupButtons[i] == selectedGroupButton) {
            groupButtons[i]->state = buttonState::pressed;
            groupButtons[i]->changeColor();
        }

        groupButtons[i]->update(dt);
    }

    // NAV BUTTONS
    buttonUp->update(dt);
    buttonDown->update(dt);

    // TOOLS
    for (auto& tool : tools) {
        tool->update(dt);
    }

    if (selectedTool != nullptr) {
        selectedTool->state = buttonState::pressed;
        selectedTool->changeColor();
        selectedTool->update(dt);
    }

    // PALETTE SIZE
    (selectedGroupButton == btnGroupTerrain || selectedGroupButton == btnGroupFloors) ? paletteRows = 6 : paletteRows = 7;
    paletteCols = 4;

    // SLOTS AND PREFABS

    float scaleX, scaleY;
    float tw, th; // texture width, texture height

    float dist_x = paletteCols * paletteButtonSize.x - paletteButtonSize.x / 2;
    palettePosition.x = cam->position.x + screenWidth / 2.0f - dist_x;
    palettePosition.y = cam->position.y - screenHeight / 2.0f + paletteButtonSize.y;

    for (short i = 0; i < paletteCols * paletteRows; i++) {

        sf::Vector2f position;
        position.x = palettePosition.x + (i % paletteCols) * paletteButtonSize.x;
        position.y = palettePosition.y + (i / paletteCols) * paletteButtonSize.y + paletteButtonSize.y;
        
        if (selectedGroupButton == btnGroupTerrain || selectedGroupButton == btnGroupFloors)
            position.y += paletteButtonSize.y;

        palette[i]->objectSprite = sf::Sprite();
        palette[i]->sprite.setPosition(position);
        palette[i]->setObject(nullptr);
        palette[i]->changeColor();

        if (i + paletteScroll * paletteCols < availableGameObjects.size()) {

            palette[i]->setObject(availableGameObjects[i + paletteScroll * paletteCols]);
            palette[i]->setPosition(position);

        }

        palette[i]->update(dt);
    }

    if (selectedPaletteButton != nullptr) {
        selectedPaletteButton->state = buttonState::pressed;
        selectedPaletteButton->changeColor();
        selectedPaletteButton->update(dt);
    }

}

void drawPalette() {

    for (short i = 0; i < paletteCols*paletteRows; i++) {
        palette[i]->draw();
    }

    buttonUp->draw();
    buttonDown->draw();

    for (auto& button : groupButtons)
        button->draw();

    if (selectedGroupButton == btnGroupTerrain || selectedGroupButton == btnGroupFloors) {
        for (auto& tool : tools)
            tool->draw();
    }

    
}



#endif