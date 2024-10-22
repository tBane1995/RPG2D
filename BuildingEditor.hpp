#ifndef BuildingEditor_hpp
#define BuildingEditor_hpp

enum class buildingEditorStates { start, editor };
buildingEditorStates buildingEditorState;

void BuildingEditorUnclickButtons();
void BuildingEditorHoverButtons();
void BuildingEditorEventLeftClick();
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
    welcomeText->setFillColor(titleColor);
    welcomeText->setOrigin(welcomeText->getLocalBounds().width / 2.f, welcomeText->getLocalBounds().height / 2.f);
    welcomeText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* pressText = new sf::Text("press Spacebar to start", basicFont, 16);
    pressText->setFillColor(titleColor);
    pressText->setOrigin(pressText->getLocalBounds().width / 2.f, pressText->getLocalBounds().height / 2.f);
    pressText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    bool skip = false;
    while (window->isOpen() && skip == false) {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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

    loadBuildingFromFile();
    cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);

    loadDialogBox = nullptr;

    prefabToPaint = nullptr;
    selectedGameObjects.clear();
    selection_state = false;

    createBuildingEditorMenuBar();
    createBuildingEditorPalette();

    updateGameObjects();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        if (loadDialogBox == nullptr) {
            BuildingEditorUnclickButtons();
            BuildingEditorHoverButtons();
        }
        

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (loadDialogBox) {
                loadDialogBox->update(event, dt);

                if (loadDialogBox->fileSelected) {
                    
                    loadBuildingFromFile(loadDialogBox->getPathfile()); // TO-DO
                    delete loadDialogBox;
                    loadDialogBox = nullptr;
                    cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);
                }
            }
            
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (loadDialogBox == nullptr) {
                        BuildingEditorEventLeftClick();

                        if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                            selection_state = false;
                        }
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (loadDialogBox == nullptr) {
                        BuildingEditorEventRightClick();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (loadDialogBox == nullptr) {
                        if (!GUIwasHover) {
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    if (loadDialogBox == nullptr) {
                        window->close();
                        exit(0);
                    }
                    else {
                        delete loadDialogBox;
                        loadDialogBox = nullptr;
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                    if (loadDialogBox == nullptr) {
                        saveBuildingToFile();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) {
                    if (loadDialogBox == nullptr) {
                        loadDialogBox = new OpenDialogBox("Load Building");
                    }
                }
            }
        }

        // UPDATE ///////////////////////////////////////////////////////////////////////

        // calculate delta time
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        if (loadDialogBox == nullptr) {
            if (!GUIwasHover) {
                if (prefabToPaint != nullptr) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (tool == toolType::Brush || tool == toolType::RectBrush) {
                            if (prefabToPaint->type == gameObjectType::Floor) {
                                for (auto& prefab : prefabsToPaint) {
                                    building->floors->edit(prefab->position, dynamic_cast<FloorPrefab*>(prefabToPaint));  // TO-DP
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
        if (loadDialogBox == nullptr) {
            updateMenuBar();
            updatePalette();
            painterUpdate();
        }

        // RENDER ////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color::Black);
        window->setView(cam->view);
        window->draw(*terrain);
        
        window->draw(*building->floors);

        for (auto& go : gameObjects) {
            if (go->mouseIsOver || go->isSelected) {
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
        drawMenuBar();
        drawPalette();
        if (loadDialogBox)
            loadDialogBox->draw();
        window->display();
    }
}

void BuildingEditorUnclickButtons() {
    buttonUp->unclick();
    buttonDown->unclick();

    for (auto& mb : groupButtons)
        mb->unclick();
    
    for (auto& p : palette)
        p->unclick();

    for (auto& t : tools)
        t->unclick();

    for (auto& m : menu) {
        m->unclick();

        if (m->isOpen) {
            for (auto& o : m->options)
                o->unclick();
        }
    }
    
}

void BuildingEditorHoverButtons() {
    buttonUp->hover();
    buttonDown->hover();

    for (auto& mb : groupButtons)
        mb->hover();
    
    for (auto& p : palette)
        p->hover();
    
    for (auto& t : tools)
        t->hover();

    for (auto& m : menu) {
        m->hover();

        if (m->isOpen) {
            for (auto& o : m->options)
                o->hover();
        }
    }
}

void BuildingEditorEventLeftClick() {

    
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
        buttonUp->click();
        buttonDown->click();

        for (auto& mb : groupButtons)
            mb->click();

        for (short i = 0; i < paletteCols * paletteRows; i++) {
            palette[i]->click();
        }

        if (selectedGroupButton == btnGroupFloors)
            for (auto& tool : tools)
                tool->click();

        for (auto& m : menu) {
            if (m->click())
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
                    addPrefabToLists();
                }

                if (tool == toolType::Rectangle || tool == toolType::Elipse) {
                    for (auto& prefab : prefabsToPaint) {
                        //floors->edit(prefab->position, dynamic_cast<FloorPrefab*>(prefabToPaint));
                    }
                }
            }

        }
    }

    

}

void BuildingEditorEventRightClick() {
    if (clickedMenuButton != nullptr) {
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;

    }
    else if (prefabToPaint == nullptr) {

        if (!selectedGameObjects.empty()) {
            selectGameObjects(0, 0, 0, 0);
            return;
        }

        bool was_delete = false;

        for (auto& go : gameObjects) {
            if (go->mouseIsOver == true) {
                //cout << "delete: " << go->name << "\n";
                deleteGameObjectFromMainLists(go);  // TO-DO
                was_delete = true;
                break;
            }
        }

        if (was_delete) {
            //deleteGameObjectsFromMainLists();
        }

    }
    else {

        selectedPaletteButton = nullptr;
        selectedTool = btnToolsCursor;
        tool = toolType::Cursor;
        prefabToPaint = nullptr; 
    }
        
}

#endif