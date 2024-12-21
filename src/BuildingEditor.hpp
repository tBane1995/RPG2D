#ifndef BuildingEditor_hpp
#define BuildingEditor_hpp

enum class buildingEditorStates { start, editor };
buildingEditorStates buildingEditorState;

void BuildingEditorEventLeftClick(sf::Event& event);
void BuildingEditorEventRightClick();

void BuildingEditor() {

    window->setTitle("Building Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    buildingEditorState = buildingEditorStates::start;

    sf::Text* welcomeText = new sf::Text("Building Editor", basicFont, 32);
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

    /////////////////////////////////////////////////////////////////////////////////////////////////

    buildingEditorState = buildingEditorStates::editor;

    createTerrainPrefabs();
    createFloorsPrefabs();
    createWaterPrefabs();

    prefabToPaint = nullptr;
    selectedGameObjects.clear();

    
    palette = new Palette(PaletteType::BuildingEditor);
    menu_bar = new MenuBar(MenuBarType::BuildingEditor);
    tip = nullptr;

    loadBuildingFromFile();
    cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);

    updateGameObjects();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        palette->update();
        menu_bar->update();

        GUIwasHover = false;
        GUIwasClicked = false;

        if (tip != nullptr && tip->btn != nullptr && tip->btn->state != ButtonState::Hover) {
            delete tip;
            tip = nullptr;
        }

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (!dialogs.empty()) {
                if (dialogs.back()->type == DialogType::OpenFile) {
                    FileDialog* opendial = dynamic_cast<FileDialog*>(dialogs.back());

                    opendial->handleEvent(event);

                    if (opendial->state == FileDialogState::FileSelected) {
                        loadBuildingFromFile(opendial->getPathfile());
                        delete dialogs.back();
                        dialogs.pop_back();
                    }

                }
                else if (dialogs.back()->type == DialogType::ScrollableText) {
                    ScrollableText* scrolltext = dynamic_cast<ScrollableText*>(dialogs.back());
                    scrolltext->handleEvent(event);
                }


            }
            
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (dialogs.empty()) {
                        BuildingEditorEventLeftClick(event);
                        palette->handleEvent(event);
                        menu_bar->handleEvent(event);

                        if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                            mouse_state = MouseState::Idle;
                        }
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (dialogs.empty()) {
                        BuildingEditorEventRightClick();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (dialogs.empty()) {
                        if (!GUIwasHover) {
                            if (menu_bar->clickedMenuButton == nullptr) {
                                startMousePosition = sf::Mouse::getPosition(*window);
                                startWorldMousePosition = window->mapPixelToCoords(mousePosition);

                                if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                                    mouse_state = MouseState::Selecting;
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
                    if (dialogs.empty()) {
                        saveBuildingToFile();
                    }
                }

                if (event.key.code == sf::Keyboard::F6) {
                    if (dialogs.empty()) {
                        dialogs.push_back(new FileDialog(DialogType::OpenFile, L"Load Building"));
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                    // TO-DO - UNDO ACTION
                }
            }

            

        } // events

        // UPDATE ///////////////////////////////////////////////////////////////////////

        // calculate delta time
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        if (dialogs.empty()) {
            if (!GUIwasHover) {
                if (prefabToPaint != nullptr) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (tool == toolType::Brush || tool == toolType::RectBrush) {
                            if (prefabToPaint->type == GameObjectType::Floor) {
                                for (auto& prefab : prefabsToPaint) {
                                    building->floors->edit(prefab->position, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);  // TO-DP
                                }
                            }
                        }
                    }
                }
            }
        }
        
        for (auto& go : gameObjects)
            go->updateStatistic(dt);

        cam->update();
        updateGameObjects();
        sortGameObjects();

        if (dialogs.empty()) {
            palette->update();
            painterUpdate();
        }

        if (tip != nullptr)
            tip->update();

        // RENDER ////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color::Black);
        window->setView(cam->view);
        window->draw(*terrain);
        
        window->draw(*building->floors);

        for (auto& go : gameObjects) {
            if (go->mouseIsHover || go->isSelected) {
                // Obiekt jest najechany kursorem lub zaznaczony - rysuj wszystkie statystyki
                go->drawAllStatistics();
            }
            else {
                // Obiekt nie jest najechany ani zaznaczony - rysuj tylko wymagane statystyki
                go->drawStatistics();
            }
        }
        
        drawGameObjects();
        painterDraw();
        palette->draw();
        menu_bar->draw();
        for(auto& dial : dialogs)
            dial->draw();

        if (tip != nullptr)
            tip->draw();

        window->display();
    }
}


void BuildingEditorEventLeftClick(sf::Event& event) {

    /*
    if (clickedMenuButton != nullptr) {
        bool clickOnMenu = false;
        
        for (auto& m : menu) {

            if (m->state == ButtonState::Pressed)
                clickOnMenu = true;

            if (m->isOpen) {
                for (auto& o : m->options)
                    if (o->state == ButtonState::Pressed)
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
            if (m->state == ButtonState::Pressed)
                tool = toolType::Cursor;
        }

        if (!GUIwasHover) {

            if (tool == toolType::Cursor) {

                short x = selectArea.getPosition().x;
                short y = selectArea.getPosition().y;
                short w = selectArea.getSize().x;
                short h = selectArea.getSize().y;

                if (w < 16) w = 16;
                if (h < 16) h = 16;

                selectGameObjects(x, y, w, h);

            }

            if (!prefabsToPaint.empty()) {

                if (tool == toolType::AddGameObject) {
                    addPrefabsToBuildingAndLists();
                }

                if (tool == toolType::Rectangle || tool == toolType::Elipse) {
                    for (auto& prefab : prefabsToPaint) {
                        building->floors->edit(prefab->position, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                    }
                }
            }

        }
    }
    */
    

}

void BuildingEditorEventRightClick() {
    if (menu_bar->clickedMenuButton != nullptr) {
        menu_bar->clickedMenuButton->isOpen = false;
        menu_bar->clickedMenuButton = nullptr;

    }
    else if (prefabToPaint == nullptr) {

        if (!selectedGameObjects.empty()) {
            selectGameObjects(0, 0, 0, 0);
            return;
        }

        bool was_delete = false;

        for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
            GameObject* go = *it;

            if (go->mouseIsHover == true) {
                deleteGameObjectFromMainLists(go);
                building->deleteGameObject(go);
                delete go;
                was_delete = true;
                break;
            }
            else
                ++it;
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