#ifndef MapEditor_hpp
#define MapEditor_hpp

#include "Platform/Platform.h"

enum class MapEditorStates { Start, Editor };
MapEditorStates mapEditorState;

void editTiles();
void MapEditorEventRightClick(sf::Event& event);

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

    clearAllMainListsOfGameObjects();

    createTerrainPrefabs();
    createFloorsPrefabs();
    createWaterPrefabs();

    selectedGameObjects.clear();
    mouse_state = MouseState::Idle;

    palette = new Palette(PaletteType::MapEditor);
    menu_bar = new MenuBar(MenuBarType::MapEditor);
    tip = nullptr;
    painter = new Painter();
    context_menu = nullptr;
    clipboard = new Clipboard();

    mapa = new Mapa();
    mapa->load();
    mapa->mapVisiblings();

    updateGameObjects();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

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
        }

        GUIwasHover = false;
        GUIwasClicked = false;
        GUIwasOpen = false;

        for (auto& dialog : dialogs)
            dialog->update();

        palette->update();
        menu_bar->update();
        clipboard->update();

        if (context_menu != nullptr) {
            context_menu->update();

            if (context_menu->_state == ContextMenuState::Close) {
                delete context_menu;
                context_menu = nullptr;
            }
        }

        if (tip != nullptr && tip->btn != nullptr && tip->btn->state != ButtonState::Hover) {
            delete tip;
            tip = nullptr;
        }

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            //std::cout << "cursor on " << worldMousePosition.x << " " << worldMousePosition.y << "\n";

            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (!dialogs.empty()) {

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

                    delete dialogs.back();
                    dialogs.pop_back();
                }
                else if (dialogs.size() >= 2 && dialogs.back()->type == DialogType::Confirm && dialogs[dialogs.size() - 2]->type == DialogType::SaveFile) {
                    Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs[dialogs.size() - 2]);
                    confirm->handleEvent(event);

                    if (confirm->value != ConfirmValue::Undefinded) {
                        if (confirm->value == ConfirmValue::True) {
                            mapa->save(dial->getPathfile());
                            delete confirm;
                            delete dial;
                            dialogs.pop_back();
                            dialogs.pop_back();
                        }
                        else if (confirm->value == ConfirmValue::False) {
                            dial->state = FileDialogState::Idle;
                            delete confirm;
                            dialogs.pop_back();
                        }
                    }

                }
                else if (dialogs.back()->type == DialogType::SaveFile) {
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                    dial->handleEvent(event);

                    if (dial->state == FileDialogState::Canceled) {
                        delete dial;
                        dialogs.pop_back();
                    }
                    else if (dial->state == FileDialogState::FileSelected) {
                        std::wstring filename = getShortName(ConvertUtf8ToWide(dial->getPathfile()));
                        dialogs.push_back(new Confirm(L"Plik " + getShortName(filename) + L" już istnieje. Czy chcesz go zamienić?"));
                        dial->state = FileDialogState::Idle;
                        dial->selectButton->state = ButtonState::Idle;
                        dial->selectButton->changeColor();
                    }

                }
                else if (dialogs.back()->type == DialogType::OpenFile) {
                    FileDialog* dial = dynamic_cast<FileDialog*>(dialogs.back());
                    dial->handleEvent(event);

                    if (dial->cancelButton->state == ButtonState::Pressed) {
                        delete dial;
                        dialogs.pop_back();
                    }
                    else if (dial->state == FileDialogState::FileSelected) {
                        dial->selectButton->state = ButtonState::Idle;
                        mapa->load(dial->getPathfile());
                        delete dial;
                        dialogs.pop_back();
                    }

                }
                else if (dialogs.back()->type == DialogType::ScrollableText) {
                    ScrollableText* scrolltext = dynamic_cast<ScrollableText*>(dialogs.back());
                    scrolltext->handleEvent(event);
                }
                else if (dialogs.back()->type == DialogType::Confirm) {
                    Confirm* confirm = dynamic_cast<Confirm*>(dialogs.back());
                    confirm->handleEvent(event);

                    if (confirm->value != ConfirmValue::Undefinded) {
                        delete dialogs.back();
                        dialogs.pop_back();
                    }
                }
                else if (dialogs.back()->type == DialogType::Panel) {
                    dialogs.back()->handleEvent(event);
                }

            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                if (context_menu != nullptr) {
                    context_menu->handleEvent(event);

                }
                else {
                    palette->handleEvent(event);
                    menu_bar->handleEvent(event);

                    if (!GUIwasHover && !GUIwasClicked) {
                        if (mouse_state == MouseState::MovingGameObjects) {
                            std::cout << "end of moving\n";
                        }
                        else if (painter->tool == toolType::AddGameObject) {
                            painter->addGameObjectsToMapAndLists(painter->prefabsToPaint, false);
                        }
                        else if (mouse_state == MouseState::Selecting) {
                            selectGameObjects();
                        }

                    }

                }

                mouse_state = MouseState::Click;
                mouse_state = MouseState::Idle;


            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                MapEditorEventRightClick(event);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                if (painter->tool == toolType::Cursor || painter->tool == toolType::Rectangle || painter->tool == toolType::Elipse) {
                    if (!GUIwasOpen && !GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork
                        if (mouse_state == MouseState::Idle) {

                            GameObject* clickedObject = nullptr;
                            for (auto& go : gameObjects) {
                                if (go->mouseIsHover) {

                                    if (isPartOfBuilding(go) != nullptr) {
                                        clickedObject = isPartOfBuilding(go);
                                        break;
                                    }
                                    else {
                                        clickedObject = go;
                                        break;
                                    }
                                }
                            }

                            if (clickedObject != nullptr) {
                                // MOVING GAMEOBJECTS

                                sf::Vector2f center(0, 0);
                                for (auto& obj : selectedGameObjects)
                                    center += obj->_object->position;

                                center.x /= selectedGameObjects.size();
                                center.y /= selectedGameObjects.size();

                                sf::Vector2f offset;
                                for (auto& obj : selectedGameObjects) {
                                    offset = obj->_object->position - worldMousePosition;
                                    obj->setOffset(offset);
                                }

                                mouse_state = MouseState::MovingGameObjects;
                            }
                            else if (clipboard->_state == ClipboardState::Idle) {
                                // SELECTING
                                mouse_state = MouseState::Selecting;
                                mouse_start_time = currentTime;
                                startMousePosition = mousePosition;
                                startWorldMousePosition = worldMousePosition;

                            }



                        }

                    }
                }

            }
            else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                    exit(0);
                }

                if (event.key.code == sf::Keyboard::F5) {
                    mapa->save();
                }

                if (event.key.code == sf::Keyboard::F6) {
                    mapa->load();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                    // TO-DO - UNDO ACTION
                }

                if (event.key.code == sf::Keyboard::Space) {
                    // DO NOTHING
                }

            }
        } // events

        
        // TO-DO

        // drawing a terrain
        if (dialogs.empty()) {
            if (!GUIwasHover && !GUIwasClicked) {
                if (!(menu_bar->clickedMenuButton != nullptr && menu_bar->clickedMenuButton->isOpen)) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (painter->prefabToPaint != nullptr) {
                            if (painter->tool == toolType::Brush || painter->tool == toolType::RectBrush) {
                                if (painter->prefabToPaint->type == GameObjectType::Terrain || painter->prefabToPaint->type == GameObjectType::Water)
                                    editTiles();
                            }
                        }
                        else if (mouse_state == MouseState::MovingGameObjects) {
                            for (auto& obj : selectedGameObjects)
                                obj->update();
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



        if (context_menu == nullptr && mouse_state == MouseState::Selecting) {
            selectGameObjects();
        }

        updateGameObjects();
        sortGameObjects();

        painter->update();

        if (tip != nullptr)
            tip->update();

        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        mapa->draw();
        mapa->drawStatistics();

        drawGameObjects();
        painter->draw();
        palette->draw();
        menu_bar->draw();

        for (auto& dial : dialogs)
            dial->draw();

        if (context_menu != nullptr)
            context_menu->draw();

        if (tip != nullptr)
            tip->draw();

        window->display();

    }

    delete window;
}



void editTiles() {

    for(auto& prefab : painter->prefabsToPaint) {

        if (prefab->_object->type == GameObjectType::Terrain) {
            
            TerrainPrefab* tp = dynamic_cast<TerrainPrefab*>(prefab->_object);
            //std::cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Chunk* chunk = mapa->getChunk(tp->position);
            if (chunk != nullptr) {

                chunk->terrain->edit(tp->position, tp->id);
                chunk->water->edit(tp->position, -1);
               
                mapa->generateBorders(chunk);

                //
            }
        }

        if (prefab->_object->type == GameObjectType::Water) {

            WaterPrefab* wp = dynamic_cast<WaterPrefab*>(prefab->_object);
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

void MapEditorEventRightClick(sf::Event& event) {

    if (menu_bar->clickedMenuButton != nullptr && menu_bar->clickedMenuButton->isOpen) {
        menu_bar->handleEvent(event);
        return;
    }

    GameObject* clickedObject = nullptr;
    for (auto& go : gameObjects) {
        if (go->mouseIsHover) {

            if (isPartOfBuilding(go) != nullptr) {
                clickedObject = isPartOfBuilding(go);
            }
            else {
                clickedObject = go;
            }
        }
    }

    if (clickedObject != nullptr) {
        if (clickedObject->isSelected == false) {
            clickedObject->isSelected = true;
            unselectGameObjects();
            selectedGameObjects.push_back(new MouseMovedGameObject(clickedObject));
        }
        context_menu = new ContextMenu(clickedObject);
        return;
    }

    if (!selectedGameObjects.empty()) {

        startMousePosition = mousePosition;
        startWorldMousePosition = worldMousePosition;

        mouseSelection();
        selectGameObjects();
        return;
    }

    if (!painter->prefabsToPaint.empty()) {
        palette->unselectPaletteButton();
        painter->prefabToPaint = nullptr;
        painter->clear();
        painter->tool = toolType::Cursor;
        return;
    }

    if (context_menu != nullptr)
        delete context_menu;

    context_menu = new ContextMenu(nullptr);

}
#endif