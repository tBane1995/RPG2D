#ifndef MenuBar_hpp
#define MenuBar_hpp

class OptionButton : public TextButtonWithLeftAlignment {
public:
    CheckBox* checkbox;

    OptionButton(string text) : TextButtonWithLeftAlignment(text) {

        this->position = position;
        checkbox = nullptr;
    }

    virtual void update(float dt) {
        TextButtonWithLeftAlignment::update(dt);

        if (checkbox)
            checkbox->update(dt);
    }

    virtual void draw() {
        TextButtonWithLeftAlignment::draw();
        if (checkbox)
            checkbox->draw();
    }
};

class MenuButton : public TextButtonWithLeftAlignment {
public:
    std::vector < TextButtonWithLeftAlignment* > options;
    bool isOpen;

    MenuButton(string text) : TextButtonWithLeftAlignment(text) {
        isOpen = false;
        options.clear();
    }

    void addOption(TextButtonWithLeftAlignment* btn) {

        options.push_back(btn);

        // width alignment
        float max_width = 0;

        for (auto& o : options) {
            float wdt = o->text.getLocalBounds().getSize().x + 2 * o->margin;
            
            if (dynamic_cast<OptionButton*>(o))
                wdt += o->rect.getSize().y;

            if (wdt > max_width)
                max_width = wdt;
        }

        // SET THE WIDTH FOR ANY BUTTON
        for (auto& o : options) {
            o->rect.setSize(sf::Vector2f(max_width, o->rect.getSize().y));
        }

        // positioning pos Y
        float pos_y = -screenHeight / 2;
        for (int i = 0; i < options.size(); i++) {
            float pos_y2 = rect.getSize().y;
            for (int j = 0; j < i; j++) {
                pos_y2 += options[j]->rect.getSize().y;
            }
            options[i]->setPosition(sf::Vector2f(position.x, pos_y + pos_y2));
        }

        // positioning checkboxes
        for (auto& o : options) {
            OptionButton* ob = dynamic_cast<OptionButton*>(o);
            if (ob != nullptr && ob->checkbox!=nullptr) {
                sf::Vector2f size = sf::Vector2f(o->rect.getSize().y, o->rect.getSize().y);
                sf::Vector2f pos2;
                pos2.x = position.x + max_width - size.x/2.0f;
                pos2.y = o->position.y + size.y/2.0f;
                ob->checkbox->edit(size, pos2);
            }
        }
        
    }

    virtual void update(float dt) {
        
        TextButtonWithLeftAlignment::update(dt);


        
    }

    virtual void draw() {
        TextButtonWithLeftAlignment::draw();

        if(isOpen)
            for (auto& o : options)
                o->draw();
    }
};

sf::RectangleShape bar;

MenuButton* fileBtn;
MenuButton* renderBtn;
MenuButton* helpBtn;

TextButtonWithLeftAlignment* newWorldBtn;
TextButtonWithLeftAlignment* loadWorldBtn;
TextButtonWithLeftAlignment* saveWorldBtn;

TextButtonWithLeftAlignment* newBuildingBtn;
TextButtonWithLeftAlignment* loadBuildingBtn;
TextButtonWithLeftAlignment* saveBuildingBtn;

OptionButton* bordersBtn;
OptionButton* coordsBtn;
OptionButton* actionRangeBtn;
OptionButton* viewRangeBtn;
OptionButton* collidersBtn;
OptionButton* monsterBasesBtn;

TextButtonWithLeftAlignment* instructionsMEBtn;
TextButtonWithLeftAlignment* instructionsBEBtn;
TextButtonWithLeftAlignment* aboutMEBtn;
TextButtonWithLeftAlignment* aboutBEBtn;

std::vector < MenuButton* > menu;
MenuButton* clickedMenuButton;

void createMenuBar() {
    sf::Vector2f position;

    fileBtn = new MenuButton("FILE");
    position.x = -screenWidth / 2;
    position.y = -screenHeight / 2;
    fileBtn->setPosition(position);
    fileBtn->func = []() {
        if (clickedMenuButton != nullptr)
            clickedMenuButton->isOpen = false;

        if (!fileBtn->isOpen) {
            fileBtn->isOpen = true;
            clickedMenuButton = fileBtn;
        }
        else
            fileBtn->isOpen = false;
        };

    renderBtn = new MenuButton("RENDER");
    position.x = -screenWidth / 2 + fileBtn->rect.getLocalBounds().width;
    position.y = -screenHeight / 2;
    renderBtn->setPosition(position);
    renderBtn->func = []() {
        if (clickedMenuButton != nullptr)
            clickedMenuButton->isOpen = false;

        if (!renderBtn->isOpen) {
            renderBtn->isOpen = true;
            clickedMenuButton = renderBtn;
        }
        else
            renderBtn->isOpen = false;
        };

    helpBtn = new MenuButton("HELP");
    position.x = -screenWidth / 2 + fileBtn->rect.getLocalBounds().width + renderBtn->rect.getLocalBounds().width;
    position.y = -screenHeight / 2;
    helpBtn->setPosition(position);
    helpBtn->func = []() {
        if (clickedMenuButton != nullptr)
            clickedMenuButton->isOpen = false;

        if (!helpBtn->isOpen) {
            helpBtn->isOpen = true;
            clickedMenuButton = helpBtn;
        }
        else
            helpBtn->isOpen = false;
        };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    newWorldBtn = new TextButtonWithLeftAlignment("NEW WORLD");
    newWorldBtn->func = []() {
        mapa = new Mapa();
        };

    loadWorldBtn = new TextButtonWithLeftAlignment("LOAD WORLD");
    loadWorldBtn->func = []() {
        
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;
        loadDialogBox = new OpenDialogBox("Load Map");
        };

    saveWorldBtn = new TextButtonWithLeftAlignment("SAVE WORLD");
    saveWorldBtn->func = []() {
        // TO-DO
        mapa->save();
        };

    newBuildingBtn = new TextButtonWithLeftAlignment("NEW BUILDING");
    newBuildingBtn->func = []() {
        createNewBuilding();
        };

    loadBuildingBtn = new TextButtonWithLeftAlignment("LOAD BUILDING");
    loadBuildingBtn->func = []() {
        clickedMenuButton->isOpen = false;
        clickedMenuButton = nullptr;
        loadDialogBox = new OpenDialogBox("Load Building");
        };

    saveBuildingBtn = new TextButtonWithLeftAlignment("SAVE BUILDING");
    saveBuildingBtn->func = []() {
        saveBuildingToFile();
        };

    bordersBtn = new OptionButton("MAPS BORDERS");
    bordersBtn->checkbox = new CheckBox();
    bordersBtn->checkbox->value = renderBorders;
    bordersBtn->func = []() {
        (renderBorders) ? renderBorders = false : renderBorders = true;
        bordersBtn->checkbox->value = renderBorders;
        };

    coordsBtn = new OptionButton("MAPS COORDS");
    coordsBtn->checkbox = new CheckBox();
    coordsBtn->checkbox->value = renderCoords;
    coordsBtn->func = []() {
        (renderCoords) ? renderCoords = false : renderCoords = true;
        coordsBtn->checkbox->value = renderCoords;
        };

    actionRangeBtn = new OptionButton("ACTION RANGE");
    actionRangeBtn->checkbox = new CheckBox();
    actionRangeBtn->checkbox->value = renderActionRange;
    actionRangeBtn->func = []() {
        (renderActionRange) ? renderActionRange = false : renderActionRange = true;
        actionRangeBtn->checkbox->value = renderActionRange;
        };

    viewRangeBtn = new OptionButton("VIEW RANGE");
    viewRangeBtn->checkbox = new CheckBox();
    viewRangeBtn->checkbox->value = renderViewRange;
    viewRangeBtn->func = []() {
        (renderViewRange) ? renderViewRange = false : renderViewRange = true;
        viewRangeBtn->checkbox->value = renderViewRange;
        };

    collidersBtn = new OptionButton("COLLIDERS");
    collidersBtn->checkbox = new CheckBox();
    collidersBtn->checkbox->value = renderColliders;
    collidersBtn->func = []() {
        (renderColliders) ? renderColliders = false : renderColliders = true;
        collidersBtn->checkbox->value = renderColliders;
        };

    monsterBasesBtn = new OptionButton("MONSTERS BASES");
    monsterBasesBtn->checkbox = new CheckBox();
    monsterBasesBtn->checkbox->value = renderMonsterBases;
    monsterBasesBtn->func = []() {
        (renderMonsterBases) ? renderMonsterBases = false : renderMonsterBases = true;
        monsterBasesBtn->checkbox->value = renderMonsterBases;
        };

    instructionsMEBtn = new TextButtonWithLeftAlignment("INSTRUCTIONS");
    instructionsBEBtn = new TextButtonWithLeftAlignment("INSTRUCTIONS");
    aboutMEBtn = new TextButtonWithLeftAlignment("ABOUT");
    aboutBEBtn = new TextButtonWithLeftAlignment("ABOUT");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f barSize = sf::Vector2f(screenWidth, fileBtn->rect.getLocalBounds().height);
    bar = sf::RectangleShape(barSize);
    bar.setPosition(cam->position.x - screenWidth / 2, cam->position.y - screenHeight / 2);
    bar.setFillColor(sf::Color(48, 48, 48));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void createMapEditorMenuBar() {
       
    createMenuBar();

    menu.clear();
    menu.push_back(fileBtn);
    menu.push_back(renderBtn);
    menu.push_back(helpBtn);

    menu[0]->addOption(newWorldBtn);
    menu[0]->addOption(loadWorldBtn);
    menu[0]->addOption(saveWorldBtn);

    menu[1]->addOption(bordersBtn);
    menu[1]->addOption(coordsBtn);
    menu[1]->addOption(actionRangeBtn);
    menu[1]->addOption(viewRangeBtn);
    menu[1]->addOption(collidersBtn);
    menu[1]->addOption(monsterBasesBtn);

    menu[2]->addOption(instructionsMEBtn);
    menu[2]->addOption(aboutMEBtn);

    clickedMenuButton = nullptr;
}

void createBuildingEditorMenuBar() {

    createMenuBar();

    menu.clear();
    menu.push_back(fileBtn);
    menu.push_back(renderBtn);
    menu.push_back(helpBtn);

    menu[0]->addOption(newBuildingBtn);
    menu[0]->addOption(loadBuildingBtn);
    menu[0]->addOption(saveBuildingBtn);

    menu[1]->addOption(collidersBtn);

    menu[2]->addOption(instructionsBEBtn);
    menu[2]->addOption(aboutBEBtn);

    clickedMenuButton = nullptr;
}

void updateMenuBar() {

	bar.setPosition(cam->position.x - screenWidth / 2, cam->position.y - screenHeight / 2);

    for (auto& m : menu)
        m->update(dt);

    if (clickedMenuButton) {
        for (auto& o : clickedMenuButton->options)
            o->update(dt);
            
    }
}

void drawMenuBar() {

	window->draw(bar);

    for (auto& m : menu)
        m->draw();

}

#endif