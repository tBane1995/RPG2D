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

    virtual void update(bool hover_action = true);
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
    virtual void update(bool hover_action = true) override;
    virtual void draw() override;
};

enum class MenuBarType { MapEditor, BuildingEditor };

class MenuBar {
public:

    MenuBarType type;

    sf::Sprite logo;
    sf::RectangleShape bar;

    MenuButton* fileBtn;
    MenuButton* renderBtn;
    MenuButton* helpBtn;

    ButtonWithText* newWorldBtn;
    ButtonWithText* loadWorldBtn;
    ButtonWithText* saveWorldBtn;

    ButtonWithText* newBuildingBtn;
    ButtonWithText* loadBuildingBtn;
    ButtonWithText* saveBuildingBtn;
    ButtonWithText* closeBuildingBtn;

    OptionButton* bordersBtn;
    OptionButton* coordsBtn;
    OptionButton* tilesBordersBtn;
    OptionButton* actionRangeBtn;
    OptionButton* viewRangeBtn;
    OptionButton* collidersBtn;
    OptionButton* meshesBtn;
    OptionButton* monsterBasesBtn;

    ButtonWithText* instructionsMEBtn;
    ButtonWithText* instructionsBEBtn;
    ButtonWithText* aboutMEBtn;
    ButtonWithText* aboutBEBtn;
    ButtonWithText* settingsMEBtn;
    ButtonWithText* settingsBEBtn;

    std::vector < MenuButton* > menu;
    MenuButton* clickedMenuButton;

    MenuBar(MenuBarType type);
    ~MenuBar();
    void createButtons();
    void createMenu();
    bool bar_is_hover();
    void handleEvent(sf::Event& event);
    void update();
    void draw();


};

extern MenuBar* menu_bar;