#ifndef MapEditor_hpp
#define MapEditor_hpp

#include "Platform/Platform.h"

enum class MapEditorStates { Start, Editor };
MapEditorStates mapEditorState;

void editTiles();
bool unselectGameObjects();
bool deleteChosenGameObject();
void unselectPaletteButton();
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

    clearAllMainListsOfGameObjects();

    createTerrainPrefabs();
    createFloorsPrefabs();
    createWaterPrefabs();

    prefabToPaint = nullptr;
    selectedGameObjects.clear();
    mouse_state = MouseState::Idle;

    palette = new Palette(PaletteType::BuildingEditor);
    menu_bar = new MenuBar(MenuBarType::MapEditor);
    character_side_menu = nullptr;
    tip = nullptr;

    mapa = new Mapa();
    mapa->load();
    mapa->mapVisiblings();

    updateGameObjects();

    dialogs.push_back(new Panel());

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

        if (character_side_menu != nullptr)
            character_side_menu->update();


        palette->update();
        menu_bar->update();
        
        

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
                        dial->selectButton->state == ButtonState::Idle;
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

                mouse_state = MouseState::Click;

                palette->handleEvent(event);
                menu_bar->handleEvent(event);
                if (character_side_menu != nullptr) {
                    character_side_menu->handleEvent(event);
                    if (character_side_menu->state == CharacterSideMenuState::Close) {
                        delete character_side_menu;
                        character_side_menu = nullptr;
                    }

                }




                if (!GUIwasHover && !GUIwasClicked)
                    if (tool == toolType::AddGameObject) {
                        addPrefabsToMapAndLists();
                    }


                mouse_state = MouseState::Idle;



            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {

                MapEditorEventRightClick();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                    if (!GUIwasHover && !GUIwasClicked) {   // TO-DO - now not nowork

                        if (mouse_state == MouseState::Idle) {

                            mouse_state = MouseState::Selecting;
                            mouse_start_time = currentTime;
                            startMousePosition = mousePosition;
                            startWorldMousePosition = worldMousePosition;

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

        // drawing a terrain
        if (dialogs.empty()) {
            if (!GUIwasHover && !GUIwasClicked) {
                if (prefabToPaint != nullptr) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (tool == toolType::Brush || tool == toolType::RectBrush) {
                            if (prefabToPaint->type == GameObjectType::Terrain || prefabToPaint->type == GameObjectType::Water)
                                editTiles();
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
        if (mouse_state == MouseState::Selecting)
            selectGameObjects();
        updateGameObjects();
        sortGameObjects();
        painterUpdate();



        if (tip != nullptr)
            tip->update();



        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        mapa->draw();
        mapa->drawStatistics();
        drawGameObjects();
        painterDraw();
        palette->draw();
        menu_bar->draw();

        if (character_side_menu != nullptr)
            character_side_menu->draw();

        for (auto& dial : dialogs)
            dial->draw();

        if (tip != nullptr)
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

bool deleteChosenGameObject() {
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

    return was_delete;
}

void unselectPaletteButton() {
    palette->selectedPaletteButton = nullptr;
    palette->selectedToolButton = palette->btnToolsCursor;
    tool = toolType::Cursor;
    prefabToPaint = nullptr;
}

void MapEditorEventRightClick() {

    Character* clicked_character = nullptr;

    for (auto& character : characters)
        if (pointInEllipse(worldMousePosition.x, worldMousePosition.y, character->position.x, character->position.y, character->colliders[0]->width / 2.0f, character->colliders[0]->length / 2.0f)) {
            clicked_character = character;
            break;
        }

    if (clicked_character != nullptr) {

        unselectGameObjects();

        if (character_side_menu != nullptr) {
            delete character_side_menu;
            character_side_menu = nullptr;
        }

        character_side_menu = new CharacterSideMenu(clicked_character);
        selectedGameObjects.push_back(clicked_character);
        clicked_character->isSelected = true;

    }
    else if (unselectGameObjects()) {
        std::cout << "unselect GameObjects\n";
    }
    else if (deleteChosenGameObject()) {
        std::cout << "delete chosen GameObject\n";
    }
    else {
        unselectPaletteButton();
        std::cout << "unselect Palette Button\n";
    }
}
#endif