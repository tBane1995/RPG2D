#ifndef MapEditor_hpp
#define MapEditor_hpp

#include "Platform/Platform.h"

enum class MapEditorStates { Start, Editor };
MapEditorStates mapEditorState;

void painterUpdate();
void painterDraw();
void addPrefabToLists();
void editTiles();
void MapEditorUnclickButtons();
void MapEditorHoverButtons();
void MapEditorEventLeftClick();
void MapEditorEventRightClick();

Plant* grass;

void MapEditor() {

    window->setTitle("Map Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    mapEditorState = MapEditorStates::Start;

    sf::Text* welcomeText = new sf::Text("Map Editor", basicFont, 32);
    welcomeText->setFillColor(textColor);
    welcomeText->setOrigin(welcomeText->getLocalBounds().width / 2.f, welcomeText->getLocalBounds().height / 2.f);
    welcomeText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* pressText = new sf::Text("press Spacebar to start", basicFont, 16);
    pressText->setFillColor(textColor);
    pressText->setOrigin(pressText->getLocalBounds().width / 2.f, pressText->getLocalBounds().height / 2.f);
    pressText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    bool skip = false;
    while (window->isOpen() && skip == false) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                skip = true;
                break;
            }
        }
            window->setView(cam->view);
            welcomeText->setPosition(cam->position.x, cam->position.y - 50);
            pressText->setPosition(cam->position.x, cam->position.y + 50);

            window->clear(sf::Color::Black);
            window->draw(*welcomeText);
            window->draw(*pressText);
            window->display();
        
    }
    
    mapEditorState = MapEditorStates::Editor;

    initPlatform();

    clearAllMainListsOfGameObjects();

    createTerrainPrefabs();
    createFloorsPrefabs();
    createWaterPrefabs();

    prefabToPaint = nullptr;
    selectedGameObjects.clear();
    selection_state = false;

    createMapEditorMenuBar();
    palette = new Palette(PaletteType::MapEditor);
    tip = nullptr;

    mapa = new Mapa();
    mapa->load();
    mapa->mapVisiblings();
    
    // TO-DO - TEST CREATE PLANTS
    grass = new Plant("grass", 32, 16, 32);
    grass->setPosition(sf::Vector2f(256*4,256*4));
    std::vector < Plant* > plants;

    for (int y = 0; y < 256; y += 64)
        for (int x = 0; x < 256; x += 64) {
            plants.push_back(new Plant(grass, 256 * 4 + x, 256 * 4 + y));
            plants.push_back(new Plant(grass, 256 * 4 + x + 32, 256 * 4 + y + 32));
        }
            

    for (auto& p : plants)
        gameObjects.push_back(p);

    updateGameObjects();
    
    // TO-DO - TEST CONFIRM DIALOG    
    Confirm* conf = new Confirm(L"To jest testowe okno potwierdzenia. W tym oknie można wybrać opcje tak lub nie.");
    dialogs.push_back(conf);
    //

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        if (dialogs.empty()) {
            if (clickedMenuButton == nullptr) {
                palette->unclickButtons();
                palette->hoverButtons();
            }

            MapEditorUnclickButtons();
            MapEditorHoverButtons();
        }

        if (tip!=nullptr && tip->btn!=nullptr && tip->btn->state != ButtonState::Hover) {
            delete tip;
            tip = nullptr;
        }
            

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            std::cout << "cursor on " << worldMousePosition.x << " " << worldMousePosition.y << "\n";

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (!dialogs.empty()) {
                
                if (dialogs.size()>=2 && dialogs.back()->type == DialogType::Confirm) {
                    Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                    confirm->update(event);

                    if (dialogs[dialogs.size() - 2]->type == DialogType::SaveFile) {
                        if (confirm->value != ConfirmValue::Undefinded) {
                            if (confirm->value == ConfirmValue::True) {
                                FileDialog* dial = dynamic_cast<FileDialog*>(dialogs[dialogs.size() - 2]);
                                mapa->save(dial->getPathfile());
                                delete confirm;
                                dialogs.pop_back();
                                delete dial;
                                dialogs.pop_back();
                            }

                            else if (confirm->value == ConfirmValue::False) {
                                delete confirm;
                                dialogs.pop_back();
                                FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                                dial->fileSelected = false;
                            }
                        }
                    }

                }
                else if (dialogs.back()->type == DialogType::SaveFile) {
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                    dial->update(event);

                    if (dial->cancelButton->state == ButtonState::Pressed) {
                        delete dial;
                        dialogs.pop_back();
                    }

                    else if (dial->selectButton->state == ButtonState::Pressed) {
                        if (dial->fileSelected == true) {
                            std::wstring filename = getShortName(ConvertUtf8ToWide(dial->getPathfile()));
                            dialogs.push_back(new Confirm(L"Plik " + filename + L" już istnieje. Czy chcesz go zamienić?"));
                            dial->selectButton->state = ButtonState::Idle;
                            dial->selectButton->changeColor();
                        }
                    }

                }
                else if (dialogs.back()->type == DialogType::OpenFile) {
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());

                    dial->update(event);

                    if (dial->cancelButton->state == ButtonState::Pressed) {
                        delete dial;
                        dialogs.pop_back();
                    }
                    else if (dial->selectButton->state == ButtonState::Pressed) {
                        if (dial->fileSelected == true) {
                            mapa->load(dial->getPathfile());
                            delete dial;
                            dialogs.pop_back();
                        }
                    }

                }
                else if (dialogs.back()->type == DialogType::ScrollableText) {
                    ScrollableText* scrolltext = dynamic_cast<ScrollableText*>(dialogs.back());
                    scrolltext->update(event);
                }
                else if (dialogs.back()->type == DialogType::Confirm) {
                    Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                    confirm->update(event);

                    if (confirm->value != ConfirmValue::Undefinded) {
                        delete dialogs.back();
                        dialogs.pop_back();
                    }
                }
                

            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    if (dialogs.empty()) {
                        
                        MapEditorEventLeftClick();

                        if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                            selection_state = false;
                        }
                    }

                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (dialogs.empty()) {
                        MapEditorEventRightClick();
                    }
                }
            }
                
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (dialogs.empty()) {
                        if (GUIwasHover != true) {
                            if (clickedMenuButton == nullptr) {
                                startMousePosition = sf::Mouse::getPosition(*window);
                                startWorldMousePosition = window->mapPixelToCoords(mousePosition);

                                if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                                    selection_state = true;
                                }
                            }
                        }
                    }
                    
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                    
                if (event.key.code == sf::Keyboard::Escape) {
                    
                    if (dialogs.empty()) {
                        window->close();
                        exit(0);
                    }
                    else {
                        delete dialogs.back();
                        dialogs.pop_back();
                    }
                }

                if (event.key.code == sf::Keyboard::F5) {
                    // TO-DO
                    if (dialogs.empty()) {
                        mapa->save();
                    }
                }

                if (event.key.code == sf::Keyboard::F6) {
                    mapa->load();
                    /*
                    if (loadDialogBox == nullptr) {
                        loadDialogBox = new OpenDialogBox("Load Map");
                    }
                    */
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                    // TO-DO - UNDO ACTION
                }

                if (event.key.code == sf::Keyboard::Space) {
                    // DO NOTHING
                }

            }
        } // events

        

        if (dialogs.empty()) {
            float moveSpeed = 300.0f * dt;

            // moving the view
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                cam->move(0.0f, -moveSpeed);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                cam->move(0.0f, moveSpeed);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                cam->move(-moveSpeed, 0.0f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                cam->move(moveSpeed, 0.0f);

            // drawing a terrain
            if (!GUIwasHover) {
                if (prefabToPaint != nullptr) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (clickedMenuButton == nullptr) {
                            if (tool == toolType::Brush || tool == toolType::RectBrush) {
                                if (prefabToPaint->type == GameObjectType::Terrain || prefabToPaint->type == GameObjectType::Water)
                                    editTiles();
                            }
                        }

                    }
                }

            }
        }


        // UPDATE ////////////////////////////////////////////////////////////////////////
        if (!dialogs.empty())
            dialogs.back()->update();

        updateShaders();

        mapa->mapVisiblings();
        mapa->update(); 

        cam->update();
        updateGameObjects();
        sortGameObjects();

        if (dialogs.empty()) {
            updateMenuBar();
            palette->update(dt);
            painterUpdate();
        }
        
        if(tip!=nullptr)    
            tip->update();

        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        mapa->draw();
        mapa->drawStatistics();
        
        for (auto& building : buildings) {
            window->draw(*building->floors);
            building->draw();
        }
        
        for (auto& go : gameObjects) {
            if (go->type != GameObjectType::FlatObject)
            if (go->isVisible) {
                if (go->mouseIsHover || go->isSelected) {
                    // Obiekt jest najechany kursorem lub zaznaczony - rysuj wszystkie statystyki
                    go->drawAllStatistics();
                }
                else {
                    // Obiekt nie jest najechany ani zaznaczony - rysuj tylko wymagane statystyki
                    go->drawStatistics();
                }
            }
        }

        drawGameObjects();
        painterDraw();
        drawMenuBar();
        palette->draw();
        for (auto& dial : dialogs)
            dial->draw();

        if(tip!=nullptr)
            tip->draw();
        
        window->display();

    }

    delete window;
}



void editTiles() {

    for(auto& prefab : prefabsToPaint) {

        if (prefab->type == GameObjectType::Terrain) {
            
            TerrainPrefab* tp = dynamic_cast<TerrainPrefab*>(prefab);
            //std::cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Chunk* chunk = mapa->getChunk(tp->position);
            if (chunk != nullptr) {

                chunk->terrain->edit(tp->position, tp->id);
                chunk->water->edit(tp->position, -1);
               
                mapa->generateBorders(chunk);

                //
            }
        }

        if (prefab->type == GameObjectType::Water) {

            WaterPrefab* wp = dynamic_cast<WaterPrefab*>(prefab);
            //std::cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Chunk* chunk = mapa->getChunk(wp->position);
            if (chunk != nullptr) {
                chunk->terrain->edit(wp->position, wp->terrain->id);
                chunk->water->edit(wp->position, wp->terrain->id);
                
                mapa->generateBorders(chunk);
            }
        }
    }
    
    
    
}

void MapEditorUnclickButtons() {

    for (auto& m : menu) {
        m->unclick();

        if (m->isOpen) {
            for (auto& o : m->options)
                o->unclick();
        }
    }

}

void MapEditorHoverButtons() {

    for (auto& m : menu) {
        m->hover();

        if (m->isOpen) {
            for (auto& o : m->options)
                o->hover();
        }
    }

}

void MapEditorEventLeftClick() {

    if (clickedMenuButton != nullptr) {
        bool clickOnMenu = false;

        for (auto& m : menu) {

            if (m->click())
                clickOnMenu = true;

            if (m->isOpen) {
                for (auto& o : m->options)
                    if (o->click())
                        clickOnMenu = true;
            }
        }

        if (clickOnMenu == false) {
            clickedMenuButton->isOpen = false;
            clickedMenuButton = nullptr;
        }
            
    }
    else {

        for (auto& m : menu) {
            if (m->click())
                tool = toolType::Cursor;
        }

        palette->clickButtons();

        if (!GUIwasHover) {

            if (tool == toolType::Cursor) {

                float x = selectArea.getPosition().x;
                float y = selectArea.getPosition().y;
                float w = selectArea.getSize().x;
                float h = selectArea.getSize().y;

                if (w < 16) w = 16;
                if (h < 16) h = 16;

                selectGameObjects(x, y, w, h);

            }

            if (!prefabsToPaint.empty()) {

                if (tool == toolType::AddGameObject) {
                    addPrefabsToMapAndLists();
                }

                if (tool == toolType::Rectangle || tool == toolType::Elipse) {
                    editTiles();
                }
            }

        }
    }   // CLICKED MENU BUTTON
}

void MapEditorEventRightClick() {
    
    if (clickedMenuButton != nullptr) {
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;

    }else if (prefabToPaint == nullptr) {

        if (!selectedGameObjects.empty()) {
            selectGameObjects(0, 0, 0, 0);
            return;
        }

        bool was_delete = false;

        ////////////////////////////////////////////////////////
        
        for (auto it = buildings.begin(); it != buildings.end(); ) {
            Building* b = *it;

            if (b->mouseIsHover == true) {

                deleteGameObjectFromMainLists(b);   // erase

                Chunk* chunk = mapa->getChunk(b->position);  // erase
                if (chunk != nullptr) {
                    chunk->deleteGameObject(b);
                }
                    
                delete b;
                was_delete = true;
                break;
            }
            else
                it++;
        }
       
        if (was_delete == false) {
            for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
                GameObject* go = *it;

                if (go->type != GameObjectType::Building && go->mouseIsHover == true) {

                    deleteGameObjectFromMainLists(go);  // erase

                    Chunk* chunk = nullptr;

                    if (go->type == GameObjectType::Monster)
                        chunk = mapa->getChunk(dynamic_cast<Monster*>(go)->base);
                    else
                        chunk = mapa->getChunk(go->position);

                    if (chunk != nullptr) {
                        chunk->deleteGameObject(go);    // erase
                    }

                    delete go;      // delete
                    
                    was_delete = true;
                    break;
                }
                else
                    it++;
            }
        }


        

    }
    else {
        palette->selectedPaletteButton = nullptr;
        palette->selectedToolButton = palette->btnToolsCursor;
        tool = toolType::Cursor;
        prefabToPaint = nullptr;

    }
}
#endif