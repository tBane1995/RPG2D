#ifndef Prefabs_hpp
#define Prefabs_hpp

std::vector < GameObject* > prefabs;

GameObject* getPrefab(string name) {
    for (auto& go : prefabs) {
        if (go->name == name)
            return go;
    }

    std::cout << "error - get Prefab - Prefab: \"" << name << "\" not exists\n";
    return nullptr;
}

void loadPrefabs() {

    prefabs.clear();
 
    // TREES
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/tree1", 36, 18));
    prefabs.push_back(new Nature("natures/tree2", 44, 22));
    prefabs.push_back(new Nature("natures/bush1", 110, 55));

    // ROCKS
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/rocks1", 90, 45));
    prefabs.push_back(new Nature("natures/rocks2", 90, 45));
    prefabs.push_back(new Nature("natures/rocks3", 90, 45));

    // FURNITURES
    prefabs.push_back(new Furniture("furnitures/table1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/bench1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/chest1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/wardrobe1", 64, 32));
    prefabs.push_back(new Furniture("furnitures/bookshelf1", 64, 32));
    prefabs.push_back(new Furniture("furnitures/furnace1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/bed1", 64, 32));
    prefabs.push_back(new Furniture("furnitures/chair1", 16, 16));
    prefabs.push_back(new Furniture("furnitures/barrel1", 16, 16));
    prefabs.push_back(new Furniture("furnitures/lectern1", 24, 16));

    // WALLS
    prefabs.push_back(new Wall("walls/wooden_wall_bottom", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_0", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_1", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_2", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_3", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_4", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_5", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_6", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_7", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_8", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_9", 32, 32));

    prefabs.push_back(new Wall("walls/stone_wall_bottom", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_0", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_1", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_2", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_3", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_4", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_5", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_6", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_7", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_8", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_9", 32, 32));

    prefabs.push_back(new Wall("walls/mud_wall_bottom", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_0", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_1", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_2", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_3", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_4", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_5", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_6", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_7", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_8", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_9", 32, 32));
    

    // PATHS
    // name, width, height
    prefabs.push_back(new Path("paths/stonepath1", 64, 32));
    prefabs.push_back(new Path("paths/stonepath2", 64, 32));

    // ITEMS
    for (auto& i : items) {
        prefabs.push_back(new ItemOnMap(i, 0, 0));
    }

    // CHARACTERS
    // name, bodySet

    Character* character = nullptr;

    character = new Character("characters/jack", "sets/body/woman-blackhaired");
    character->dialogue = getDialogue(1);
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->rightHand = getItem("items/sword");
    character->leftHand = getItem("items/shield");
    prefabs.push_back(character);

    character = new Character("characters/john", "sets/body/boy-brownhaired");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);

    character = new Character("characters/peter", "sets/body/boy-brownhaired");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);

    character = new Character("characters/pit", "sets/body/man-brownhaired");
    character->dialogue = getDialogue(5);
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);


    // MONSTERS
    // name, width, height

    Monster* dziobak = new Monster("monsters/dziobak", 72, 36, 10);
    dziobak->HP = 40;
    dziobak->HP_FULL = 40;
    dziobak->MP = 10;
    dziobak->MP_FULL = 10;
    dziobak->STRENGTH = 4;
    dziobak->DEXTERITY = 2;
    dziobak->INTELLIGENCE = 1;
    prefabs.push_back(dziobak);

    Monster* goblin = new Monster("monsters/goblin", 32, 16, 20);
    goblin->HP = 80;
    goblin->HP_FULL = 80;
    goblin->MP = 10;
    goblin->MP_FULL = 10;
    goblin->STRENGTH = 8;
    goblin->DEXTERITY = 4;
    goblin->INTELLIGENCE = 2;
    prefabs.push_back(goblin);

    Monster* wilczur = new Monster("monsters/wilczur", 70, 35, 50);
    wilczur->HP = 120;
    wilczur->HP_FULL = 120;
    wilczur->MP = 10;
    wilczur->MP_FULL = 10;
    wilczur->STRENGTH = 12;
    wilczur->DEXTERITY = 6;
    wilczur->INTELLIGENCE = 3;
    prefabs.push_back(wilczur);

    Monster* jaszczur = new Monster("monsters/jaszczur", 70, 35, 80);
    jaszczur->HP = 160;
    jaszczur->HP_FULL = 160;
    jaszczur->MP = 10;
    jaszczur->MP_FULL = 10;
    jaszczur->STRENGTH = 16;
    jaszczur->DEXTERITY = 8;
    jaszczur->INTELLIGENCE = 4;
    prefabs.push_back(jaszczur);

    Monster* niedzwiedz = new Monster("monsters/niedzwiedz", 70, 35, 80);
    niedzwiedz->HP = 160;
    niedzwiedz->HP_FULL = 160;
    niedzwiedz->MP = 10;
    niedzwiedz->MP_FULL = 10;
    niedzwiedz->STRENGTH = 16;
    niedzwiedz->DEXTERITY = 8;
    niedzwiedz->INTELLIGENCE = 4;
    prefabs.push_back(niedzwiedz);

    Monster* szpon = new Monster("monsters/szpon", 66, 32, 100);
    szpon->HP = 200;
    szpon->HP_FULL = 200;
    szpon->MP = 10;
    szpon->MP_FULL = 10;
    szpon->STRENGTH = 20;
    szpon->DEXTERITY = 10;
    szpon->INTELLIGENCE = 5;
    prefabs.push_back(szpon);

    Monster* kolcorozec = new Monster("monsters/kolcorozec", 70, 35, 140);
    kolcorozec->HP = 240;
    kolcorozec->HP_FULL = 240;
    kolcorozec->MP = 10;
    kolcorozec->MP_FULL = 10;
    kolcorozec->STRENGTH = 24;
    kolcorozec->DEXTERITY = 12;
    kolcorozec->INTELLIGENCE = 6;
    prefabs.push_back(kolcorozec);

    Monster* golem = new Monster("monsters/golem", 90, 60, 180);
    golem->HP = 280;
    golem->HP_FULL = 280;
    golem->MP = 10;
    golem->MP_FULL = 10;
    golem->STRENGTH = 28;
    golem->DEXTERITY = 14;
    golem->INTELLIGENCE = 7;
    prefabs.push_back(golem);

    Monster* troll = new Monster("monsters/troll", 90, 60, 240);
    troll->HP = 320;
    troll->HP_FULL = 320;
    troll->MP = 10;
    troll->MP_FULL = 10;
    troll->STRENGTH = 32;
    troll->DEXTERITY = 16;
    troll->INTELLIGENCE = 8;
    prefabs.push_back(troll);

    Monster* bies = new Monster("monsters/bies", 90, 60, 300);
    bies->HP = 360;
    bies->HP_FULL = 360;
    bies->MP = 10;
    bies->MP_FULL = 10;
    bies->STRENGTH = 36;
    bies->DEXTERITY = 18;
    bies->INTELLIGENCE = 9;
    prefabs.push_back(bies);
}



#endif
