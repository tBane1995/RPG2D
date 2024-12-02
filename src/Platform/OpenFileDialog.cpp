#include "OpenFileDialog.h"
#include "Buttons.h"
#include "Scrollbar.h"
#include "TextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"
#include "Theme.h"
#include "Mouse.h"
#include "Textures.h"
#include "Time.h"

bool sortkey(std::filesystem::directory_entry first, std::filesystem::directory_entry second) {

    if (first.is_directory() && second.is_directory()) {
        std::string name_1 = first.path().filename().string();
        std::string name_2 = second.path().filename().string();

        std::transform(name_1.begin(), name_1.end(), name_1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(name_2.begin(), name_2.end(), name_2.begin(), [](unsigned char c) { return std::tolower(c); });

        if (name_1 < name_2)
            return true;
        else
            return false;
    }
    else if (first.is_directory() && !second.is_directory()) {
        return true;
    }
    else if (!first.is_directory() && second.is_directory()) {
        return false;
    }
    else {
        // both are file
        std::string name_1 = first.path().filename().string();
        std::string name_2 = second.path().filename().string();

        std::transform(name_1.begin(), name_1.end(), name_1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(name_2.begin(), name_2.end(), name_2.begin(), [](unsigned char c) { return std::tolower(c); });

        if (name_1 < name_2)
            return true;
        else
            return false;
    }
}


OpenFileDialog::OpenFileDialog(std::wstring title) : Dialog(DialogType::OpenFile) {
    rect_height = 0;
    rect_width = 512;
    margin_vert = 4;
    margin_hor = 4;
    line_height = 30;

    // TITLE BAR
    titlebar = sf::RectangleShape(sf::Vector2f(512, line_height));
    titlebar.setFillColor(sf::Color(48, 48, 48));
    rect_height += titlebar.getSize().y;

    titleText = new TextArea(title);
    titleText->setCharacterSize(17);
    titleText->generateRect();
    titleText->setRectColor(sf::Color::Transparent);
    titleText->setTextColor(dialoguesColor);

    ////////////////////////////////////
    // FILENAMES AND SCROLLBAR
    current_path = std::filesystem::current_path();
    loadDirectory();

    loadScrollbar();
    createFilenamesTexts();
    setFilenamesTexts();

    filenamesRect = sf::RectangleShape(sf::Vector2f(titlebar.getSize().x, 7 * line_height));
    filenamesRect.setFillColor(sf::Color::Transparent);

    rect_height += filenamesRect.getSize().y;

    ///////////////////////////////////////
    // SUBMIT BAR

    filenameInfo = new TextArea(L"File name: ");
    filenameInfo->setCharacterSize(17);
    filenameInfo->setTextColor(dialoguesColor);
    filenameInfo->setRectColor(sf::Color::Transparent);
    filenameInfo->generateRect();

    sf::Vector2f size;
    size.x = rect_width - filenameInfo->getSize().x - 3 * margin_vert;
    size.y = line_height;
    selectedFilenameRect = sf::RectangleShape(size);
    selectedFilenameRect.setFillColor(sf::Color(32, 32, 32));

    selectedFilenameText = new TextArea(L"");
    selectedFilenameText->setCharacterSize(17);
    selectedFilenameText->setTextColor(dialoguesColor);
    selectedFilenameText->setRectColor(sf::Color::Transparent);
    selectedFilenameText->generateRect();

    selectButton = new ButtonWithText("select", 17);
    cancelButton = new ButtonWithText("cancel", 17);

    submitbar = sf::RectangleShape(sf::Vector2f(rect_width, selectedFilenameRect.getSize().y + 3 * margin_vert + selectButton->rect.getSize().y));
    submitbar.setFillColor(sf::Color::Transparent);

    rect_height += submitbar.getSize().y;

    /////////////////

    rect = sf::RectangleShape(sf::Vector2f(512, rect_height));
    rect.setFillColor(panelColor);

    // POSITIONING /////////////
    sf::Vector2f pos;

    // title bar
    sf::Vector2f p = sf::Vector2f(position.x - rect_width / 2.0f, +position.y - rect_height / 2.0f);
    rect.setPosition(p.x + cam->position.x, p.y + cam->position.y);

    titlebar.setPosition(p.x + cam->position.x, p.y + cam->position.y);
    titleText->setPosition(sf::Vector2f(p.x + margin_vert, p.y + titleText->getLineHeight() / 4.0f));

    // filenames and scrollbar
    pos.x = cam->position.x + position.x - rect_width / 2.0f;
    pos.y = cam->position.y + position.y - rect_height / 2.0f + titlebar.getSize().y;
    filenamesRect.setPosition(pos);

    pos.x = position.x - rect_width / 2.0f + (titleText->texts[0].getPosition().x - titleText->rect.getPosition().x);
    for (short i = 0; i < 7; i++) {

        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + i * line_height;

        icons[i].setPosition(pos.x + cam->position.x, pos.y + cam->position.y);
        filenamesRects[i].setPosition(pos.x + cam->position.x + 30, pos.y + cam->position.y);
        filenames[i]->setPosition(sf::Vector2f(pos.x + 30, pos.y + filenames[i]->getLineHeight() / 4.0f));
    }

    pos.x = position.x + rect_width / 2.0f - scrollbar->bar.getSize().x;
    pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y;
    scrollbar->setPosition(pos);

    // submit bar
    pos.x = position.x - rect_width / 2.0f + cam->position.x;
    pos.y = position.y - rect_height / 2.0f + cam->position.y + titlebar.getSize().y + 7 * line_height;
    submitbar.setPosition(pos);

    pos.x = position.x - rect_width / 2.0f + margin_vert;
    pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + 7.0f * line_height + filenameInfo->getLineHeight() / 4.0f + margin_vert;
    filenameInfo->setPosition(pos);

    pos.x = position.x - rect_width / 2.0f + filenameInfo->getSize().x + 2.0f * margin_hor;
    pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + 7.0f * line_height + margin_vert;

    selectedFilenameRect.setPosition(pos.x + cam->position.x, pos.y + cam->position.y);
    selectedFilenameText->setPosition(sf::Vector2f(pos.x, pos.y + selectedFilenameText->getLineHeight() / 4.0f));

    pos.x = position.x + rect_width / 2.0f - cancelButton->rect.getSize().x - margin_hor;
    pos.y = position.y + rect_height / 2.0f - cancelButton->rect.getSize().y - margin_vert;
    cancelButton->setPosition(pos);

    pos.x = pos.x - selectButton->rect.getSize().x - margin_hor;
    selectButton->setPosition(pos);
    ///////////////////////////

    fileSelected = false;
}

OpenFileDialog::~OpenFileDialog() {
    delete titleText;
    delete filenameInfo;
    delete selectedFilenameText;
    delete selectButton;
    delete cancelButton;

    for (auto& t : filenames)
        delete t;

    delete scrollbar;
}

void OpenFileDialog::loadDirectory() {
    paths.clear();
    if (std::filesystem::exists(current_path) && std::filesystem::is_directory(current_path)) {

        for (auto& entry : std::filesystem::directory_iterator(current_path)) {
            paths.push_back(entry);
        }
    }
    std::sort(paths.begin(), paths.end(), sortkey);

    paths.emplace(paths.begin(), current_path.parent_path());
}

void OpenFileDialog::loadScrollbar() {
    sf::Vector2f scrollbarSize = sf::Vector2f(16, 7 * line_height + 1);
    scrollbar = new Scrollbar(scrollbarSize, 0, paths.size() - 1, 0, 7);
}

void OpenFileDialog::createFilenamesTexts() {

    float filename_rect_width = rect_width - scrollbar->bar.getSize().x - 30 - 2 * margin_vert;

    for (int i = 0; i < 7; i++) {
        filenamesRects[i] = sf::RectangleShape(sf::Vector2f(filename_rect_width, line_height));
        filenamesRects[i].setFillColor(sf::Color::Transparent);

        filenames[i] = new TextArea(L"");
        filenames[i]->setCharacterSize(17);
        filenames[i]->generateRect();
        filenames[i]->setRectColor(sf::Color::Transparent);
        filenames[i]->setTextColor(dialoguesColor);

        icons[i] = sf::Sprite();
    }

}

void OpenFileDialog::setFilenamesTexts() {
    for (short i = 0; i < 7; i++) {

        if (i + short(scrollbar->scrollValue) < paths.size()) {
            if (i + short(scrollbar->scrollValue) == 0) {
                filenames[i]->setWstring(L"..");
            }
            else {
                filenames[i]->setWstring(paths[i + short(scrollbar->scrollValue)].path().filename().wstring());
            }
            filenames[i]->generateRect();

            std::string extension = paths[i + short(scrollbar->scrollValue)].path().extension().string();
            if (extension == "")
                icons[i].setTexture(*getSingleTexture("GUI/icons/dictionary")->texture);
            else
                icons[i].setTexture(*getSingleTexture("GUI/icons/file")->texture);
        }
        else
            filenames[i]->setWstring(L"");
    }
}

std::string OpenFileDialog::getPathfile() {
    std::string pathfile = current_path.string() + "\\" + selectedFilenameText->texts[0].getString();
    std::cout << pathfile << "\n";
    return pathfile;
}

void OpenFileDialog::update(sf::Event& event) {
    scrollbar->update(event);

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {

            selectButton->click();
            cancelButton->click();

            if (selectButton->state == ButtonState::Pressed) {
                fileSelected = true;
            }
            else {
                for (short i = 0; i < 7; i++) {
                    if (filenames[i]->rect.getGlobalBounds().contains(worldMousePosition)) {
                        cout << "click";
                        // LOAD THE DIRECTORY
                        if (i + short(scrollbar->scrollValue) < paths.size()) {

                            if (!paths[i + short(scrollbar->scrollValue)].is_directory()) {
                                cout << "is file";
                                selectedFilenameText->setWstring(filenames[i]->s);
                            }
                            else {
                                current_path = std::filesystem::path(paths[i + short(scrollbar->scrollValue)].path().wstring());
                                selectedFilenameText->setWstring(L"");
                                loadDirectory();
                                scrollbar->setValue(0);
                                scrollbar->maxValue = paths.size() - 1;
                                scrollbar->update();
                            }

                        }

                    }
                }
            }




        }
    }

    setFilenamesTexts();

    selectButton->update(dt);
    cancelButton->update(dt);
}

void OpenFileDialog::draw() {
    //main rect
    window->draw(rect);

    // tile bar
    window->draw(titlebar);
    titleText->draw();

    // filenames and scrollbar
    window->draw(filenamesRect);
    for (short i = 0; i < 7; i++) {
        window->draw(filenamesRects[i]);
        filenames[i]->draw();
        window->draw(icons[i]);
    }

    scrollbar->draw();

    // submit bar
    window->draw(submitbar);
    window->draw(selectedFilenameRect);
    filenameInfo->draw();
    selectedFilenameText->draw();
    selectButton->draw();
    cancelButton->draw();
}
