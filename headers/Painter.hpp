#ifndef Painter_hpp
#define Painter_hpp

void clearPrefabs() {

    for (auto& prefab : prefabsToPaint) {
        delete prefab;
    }

    prefabsToPaint.clear();
}

void painterUpdate() {

    if (GUIwasHover || GUIwasClicked) {
        return;
    }
    else if (tool == toolType::Cursor && selection_state == true) {
        mouseSelection();
    }
    else if (prefabToPaint != nullptr) {

        if (prefabToPaint->type == gameObjectType::Terrain || prefabToPaint->type == gameObjectType::Floor) {    

            clearPrefabs();

            // RECTANGLE    ///////////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::Rectangle) {
                if (selection_state == true) {
                    generateRectangle();
                }
            }

            // ELIPSE   ///////////////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::Elipse) {
                if (selection_state == true) {
                    generateElipse();
                }
            }

            //  BRUSH   ////////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::Brush) {
                generateBrush();
            }

            //  RECT BRUSH  ////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::RectBrush) {
                generateRectBrush();
            }

        }
        else {
            // prefab is a GameObject

            float x = short(worldMousePosition.x) / short(tileSide) * short(tileSide);
            float y = short(worldMousePosition.y) / short(tileSide) * short(tileSide);

            if (prefabsToPaint.empty() || prefabsToPaint[0]!=prefabToPaint) {

                if (!prefabsToPaint.empty())
                    clearPrefabs();

                if (prefabToPaint->type == gameObjectType::Nature) {
                    Nature* nature = new Nature(prefabToPaint, x, y);
                    prefabsToPaint.push_back(nature);
                }

                if (prefabToPaint->type == gameObjectType::Monster) {
                    Monster* monster = new Monster(prefabToPaint, x, y);
                    prefabsToPaint.push_back(monster);
                }

                if (prefabToPaint->type == gameObjectType::ItemOnMap) {
                    ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
                    prefabsToPaint.push_back(item);
                }

                if (prefabToPaint->type == gameObjectType::Path) {
                    Path* path = new Path(prefabToPaint, x, y);
                    prefabsToPaint.push_back(path);
                }

                if (prefabToPaint->type == gameObjectType::Furniture) {
                    Furniture* furniture = new Furniture(prefabToPaint, x, y);
                    prefabsToPaint.push_back(furniture);
                }

                if (prefabToPaint->type == gameObjectType::Wall) {
                    Wall* wall = new Wall(prefabToPaint, x, y);
                    prefabsToPaint.push_back(wall);
                }
            }
            else{
                for (auto& prefab : prefabsToPaint) {
                    prefab->setPosition(sf::Vector2f(x, y));
                }
                
            }
            
            for (auto& prefab : prefabsToPaint) {
                if (prefab->type == gameObjectType::Unit || prefab->type == gameObjectType::Monster || prefab->type == gameObjectType::Character) {
                    dynamic_cast<Unit*>(prefab)->idling(dt);

                }
                else {
                    prefab->update(dt);
                    prefab->mouseIsOver = false;

                }
            }

        }

    }
    else {
        clearPrefabs();
    }

}

void painterDraw() {

    if (tool == toolType::Cursor && selection_state == true) {
        window->draw(selectArea);

    } else {
        for (auto& p : prefabsToPaint) {
            p->draw();
        }
    }
    

}

void addPrefabToLists() {

    short x = short(worldMousePosition.x) / short(tileSide) * short(tileSide);
    short y = short(worldMousePosition.y) / short(tileSide) * short(tileSide);
    // cout << "cursor at position: " << xx << " " << yy << "\n"

    if (prefabToPaint->type == gameObjectType::Nature) {

        Nature* nature = new Nature(prefabToPaint, x, y);
        gameObjects.push_back(nature);
        natures.push_back(nature);
    }

    if (prefabToPaint->type == gameObjectType::Monster) {

        Monster* monster = new Monster(prefabToPaint, x, y);
        gameObjects.push_back(monster);
        monsters.push_back(monster);
    }

    if (prefabToPaint->type == gameObjectType::ItemOnMap) {

        ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
        gameObjects.push_back(item);
        itemsOnMap.push_back(item);
    }

    if (prefabToPaint->type == gameObjectType::Path) {

        Path* path = new Path(prefabToPaint, x, y);
        gameObjects.push_back(path);
        paths.push_back(path);
    }

    if (prefabToPaint->type == gameObjectType::Furniture) {

        Furniture* furniture = new Furniture(prefabToPaint, x, y);
        gameObjects.push_back(furniture);
        furnitures.push_back(furniture);
    }

    if (prefabToPaint->type == gameObjectType::Wall) {
        Wall* wall = new Wall(prefabToPaint, x, y);
        gameObjects.push_back(wall);
        walls.push_back(wall);
    }
}


void addPrefabsToMapAndLists() {

    
    Chunk* chunk = mapa->getChunk(worldMousePosition);

    if (chunk == nullptr)
        return;

    for (auto& prefab : prefabsToPaint) {

        float x = prefab->position.x;
        float y = prefab->position.y;

        if (prefab->type == gameObjectType::Nature) {

            Nature* nature = new Nature(prefab, x, y);
            gameObjects.push_back(nature);
            natures.push_back(nature);
            chunk->_natures.push_back(nature);
        }

        if (prefab->type == gameObjectType::Monster) {

            Monster* monster = new Monster(prefab, x, y);
            gameObjects.push_back(monster);
            monsters.push_back(monster);
            chunk->_monsters.push_back(monster);
        }

        if (prefab->type == gameObjectType::ItemOnMap) {

            ItemOnMap* item = new ItemOnMap(prefab, x, y);
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
            chunk->_items.push_back(item);
        }

        if (prefab->type == gameObjectType::Path) {

            Path* path = new Path(prefab, x, y);
            gameObjects.push_back(path);
            paths.push_back(path);
            chunk->_paths.push_back(path);
        }

    }
}

#endif // ! Painter_hpp
