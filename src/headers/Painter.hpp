#ifndef Painter_hpp
#define Painter_hpp

void clearPrefabsFromPainter() {

    prefabsToPaint.clear();
}

void painterUpdate() {

    if (GUIwasHover || GUIwasClicked) {
        clearPrefabsFromPainter();
        return;
    }
    else if (tool == toolType::Cursor && selection_state == true) {
        mouseSelection();
    }
    else if (prefabToPaint != nullptr) {

        if (prefabToPaint->type == GameObjectType::Terrain || prefabToPaint->type == GameObjectType::Floor || prefabToPaint->type == GameObjectType::Water) {

            clearPrefabsFromPainter();

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

            if (prefabsToPaint.size() == 0 || prefabsToPaint[0]!=prefabToPaint) {

                if (prefabsToPaint.size() != 0 && prefabsToPaint[0] != prefabToPaint)
                    clearPrefabsFromPainter();
                    
                prefabsToPaint.push_back(prefabToPaint);
                
            }
            else{
                for (auto& prefab : prefabsToPaint) {
                    prefab->setPosition(sf::Vector2f(x, y));
                }
                
            }
            
            for (auto& prefab : prefabsToPaint) {
                if (prefab->type == GameObjectType::Unit || prefab->type == GameObjectType::Monster || prefab->type == GameObjectType::Character) {
                    dynamic_cast<Unit*>(prefab)->idling(dt);
                }
                else {
                    prefab->update(dt);
                    prefab->mouseIsHover = false;

                }
            }

        }

    }
    else {
        clearPrefabsFromPainter();
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

    if (prefabToPaint->type == GameObjectType::Nature) {

        Nature* nature = new Nature(prefabToPaint, x, y);
        gameObjects.push_back(nature);
        natures.push_back(nature);
    }

    if (prefabToPaint->type == GameObjectType::Object) {

        Object* object = new Object(prefabToPaint, x, y);
        gameObjects.push_back(object);
        objects.push_back(object);
    }

    if (prefabToPaint->type == GameObjectType::Monster) {

        Monster* monster = new Monster(prefabToPaint, x, y);
        gameObjects.push_back(monster);
        monsters.push_back(monster);
    }

    if (prefabToPaint->type == GameObjectType::ItemOnMap) {

        ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
        gameObjects.push_back(item);
        itemsOnMap.push_back(item);
    }

    if (prefabToPaint->type == GameObjectType::FlatObject) {

        FlatObject* flat = new FlatObject(prefabToPaint, x, y);
        gameObjects.push_back(flat);
        flatObjects.push_back(flat);
    }

    if (prefabToPaint->type == GameObjectType::SmallObject) {

        SmallObject* object= new SmallObject(prefabToPaint, x, y);
        gameObjects.push_back(object);
        smallObjects.push_back(object);
    }

    if (prefabToPaint->type == GameObjectType::Furniture) {

        Furniture* furniture = new Furniture(prefabToPaint, x, y);
        gameObjects.push_back(furniture);
        furnitures.push_back(furniture);
    }

    if (prefabToPaint->type == GameObjectType::Wall) {
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

        if (prefab->type == GameObjectType::Nature) {

            Nature* nature = new Nature(prefab, x, y);
            nature->isInTheMainList = true;
            gameObjects.push_back(nature);
            natures.push_back(nature);
            chunk->_natures.push_back(nature);
        }

        if (prefab->type == GameObjectType::Object) {

            Object* object = new Object(prefab, x, y);
            object->isInTheMainList = true;
            gameObjects.push_back(object);
            objects.push_back(object);
            chunk->_objects.push_back(object);
        }

        if (prefab->type == GameObjectType::Monster) {

            Monster* monster = new Monster(prefab, x, y);
            monster->isInTheMainList = true;
            gameObjects.push_back(monster);
            monsters.push_back(monster);
            chunk->_monsters.push_back(monster);
        }

        if (prefab->type == GameObjectType::ItemOnMap) {

            ItemOnMap* item = new ItemOnMap(prefab, x, y);
            item->isInTheMainList = true;
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
            chunk->_items.push_back(item);
        }

        if (prefab->type == GameObjectType::FlatObject) {

            FlatObject* flat = new FlatObject(prefab, x, y);
            flat->isInTheMainList = true;
            gameObjects.push_back(flat);
            flatObjects.push_back(flat);
            chunk->_flatObjects.push_back(flat);
        }

        if (prefab->type == GameObjectType::SmallObject) {

            SmallObject* object = new SmallObject(prefab, x, y);
            object->isInTheMainList = true;
            gameObjects.push_back(object);
            smallObjects.push_back(object);
            chunk->_smallObjects.push_back(object);
        }

        if (prefab->type == GameObjectType::Door) {
            Door* door = new Door(prefab, x, y);
            door->isInTheMainList = true;
            gameObjects.push_back(door);
            doors.push_back(door);
            chunk->_doors.push_back(door);
        }

    }
}

#endif // ! Painter_hpp
