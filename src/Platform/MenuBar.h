#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Buttons.h"
class CheckBox;

class OptionButton : public ButtonWithText {
public:
    CheckBox* checkbox;

    OptionButton(std::string text) : ButtonWithText(text) {

        this->position = position;
        checkbox = nullptr;
    }

    virtual void update(float dt);
    virtual void draw();
};

class MenuButton : public ButtonWithText {
public:
    std::vector < ButtonWithText* > options;
    bool isOpen;

    MenuButton(std::string text) : ButtonWithText(text) {
        isOpen = false;
        options.clear();
    }

    void addOption(ButtonWithText* btn);

    virtual void draw() override;

    virtual void update(float dt) override {
        ButtonWithText::update(dt);
    }
};

extern sf::Sprite logo;
extern sf::RectangleShape bar;

extern MenuButton* fileBtn;
extern MenuButton* renderBtn;
extern MenuButton* helpBtn;

extern ButtonWithText* newWorldBtn;
extern ButtonWithText* loadWorldBtn;
extern ButtonWithText* saveWorldBtn;

extern ButtonWithText* newBuildingBtn;
extern ButtonWithText* loadBuildingBtn;
extern ButtonWithText* saveBuildingBtn;

extern OptionButton* bordersBtn;
extern OptionButton* coordsBtn;
extern OptionButton* tilesBordersBtn;
extern OptionButton* actionRangeBtn;
extern OptionButton* viewRangeBtn;
extern OptionButton* collidersBtn;
extern OptionButton* meshesBtn;
extern OptionButton* monsterBasesBtn;

extern ButtonWithText* instructionsMEBtn;
extern ButtonWithText* instructionsBEBtn;
extern ButtonWithText* aboutMEBtn;
extern ButtonWithText* aboutBEBtn;

extern std::vector < MenuButton* > menu;
extern MenuButton* clickedMenuButton;

void createMenuBar();
void createMapEditorMenuBar();
void createBuildingEditorMenuBar();
void updateMenuBar();
void drawMenuBar();
