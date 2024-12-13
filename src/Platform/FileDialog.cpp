
#include "FileDialog.h"
#include "Buttons.h"
#include "Scrollbar.h"
#include "TextArea.h"
#include <iostream>
#include "Camera.h"
#include "Fonts.h"

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


FileDialog::FileDialog(DialogType type, std::wstring title, std::string acceptable_extension) : Dialog(type) {
    rect_height = 0;
    rect_width = 512;
    margin_vert = 4;
    margin_hor = 4;
    line_height = 30;

    this->acceptable_extensions = acceptable_extension;

    // TITLE BAR
    titlebar = sf::RectangleShape(sf::Vector2f(512, line_height));
    titlebar.setFillColor(panelColor_medium);
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
    selectedFilenameRect.setFillColor(panelColor_dark);

    selectedFilenameText = new TextArea(L"");
    selectedFilenameText->setCharacterSize(17);
    selectedFilenameText->setTextColor(dialoguesColor);
    selectedFilenameText->setRectColor(sf::Color::Transparent);
    selectedFilenameText->generateRect();

    selectButton = (type == DialogType::OpenFile) ? new ButtonWithText("open", 17) : new ButtonWithText("save", 17);
    cancelButton = new ButtonWithText("cancel", 17);

    submitbar = sf::RectangleShape(sf::Vector2f(rect_width, selectedFilenameRect.getSize().y + 3 * margin_vert + selectButton->rect.getSize().y));
    submitbar.setFillColor(panelColor_medium);

    rect_height += submitbar.getSize().y;

    //////////

    rect_height += 2 * borderWidth;

    /////////////////


    rect = sf::RectangleShape(sf::Vector2f(512.0f, rect_height - 2.0f*borderWidth));
    rect.setFillColor(panelColor_normal);
    rect.setOutlineThickness(borderWidth);
    rect.setOutlineColor(panelColor_dark);

    // POSITIONING /////////////
    sf::Vector2f pos;

    // title bar
    sf::Vector2f p = sf::Vector2f(position.x - rect_width/2.0f, + position.y - rect_height/2.0f);
    rect.setPosition(p.x + cam->position.x+borderWidth, p.y + cam->position.y+borderWidth);

    titlebar.setPosition(p.x + cam->position.x+borderWidth, p.y + cam->position.y+borderWidth);
    titleText->setPosition(sf::Vector2f(p.x + margin_vert+borderWidth, p.y + titleText->getLineHeight() / 4.0f + borderWidth));

    // filenames and scrollbar
    pos.x = cam->position.x + position.x - rect_width/2.0f + borderWidth;
    pos.y = cam->position.y + position.y - rect_height/2.0f + titlebar.getSize().y + borderWidth;
    filenamesRect.setPosition(pos);

    pos.x = position.x - rect_width/2.0f + borderWidth + (titleText->texts[0].getPosition().x - titleText->rect.getPosition().x);
    for (short i = 0; i < 7; i++) {

        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + borderWidth + i * line_height;

        icons[i].setPosition(pos.x + cam->position.x, pos.y + cam->position.y);
        filenamesRects[i].setPosition(pos.x + cam->position.x + 30, pos.y + cam->position.y);
        filenames[i]->setPosition(sf::Vector2f(pos.x + 30, pos.y + filenames[i]->getLineHeight() / 4.0f));
    }

    pos.x = position.x + rect_width/2.0f + borderWidth - scrollbar->size.x;
    pos.y = position.y - rect_height/2.0f + titlebar.getSize().y + borderWidth;
    scrollbar->setPosition(pos);

    // submit bar
    pos.x = position.x - rect_width/2.0f + cam->position.x + borderWidth;
    pos.y = position.y - rect_height/2.0f + cam->position.y + titlebar.getSize().y + 7 * line_height + borderWidth;
    submitbar.setPosition(pos);

    pos.x = position.x - rect_width/2.0f + margin_vert + borderWidth;
    pos.y = position.y - rect_height/2.0f + titlebar.getSize().y + 7.0f * line_height + filenameInfo->getLineHeight() / 4.0f + margin_vert + borderWidth;
    filenameInfo->setPosition(pos);

    pos.x = position.x - rect_width/2.0f + filenameInfo->getSize().x + 2.0f * margin_hor + borderWidth;
    pos.y = position.y - rect_height/2.0f + titlebar.getSize().y + 7.0f * line_height + margin_vert + borderWidth;

    selectedFilenameRect.setPosition(pos.x + cam->position.x, pos.y + cam->position.y);
    selectedFilenameText->setPosition(sf::Vector2f(pos.x, pos.y + selectedFilenameText->getLineHeight() / 4.0f));

    pos.x = position.x + rect_width/2.0f - cancelButton->rect.getSize().x - margin_hor + borderWidth;
    pos.y = position.y + rect_height/2.0f - cancelButton->rect.getSize().y - margin_vert - borderWidth;
    cancelButton->setPosition(pos);

    pos.x = pos.x - selectButton->rect.getSize().x - margin_hor;
    selectButton->setPosition(pos);
    ///////////////////////////

    fileSelected = false;
}

FileDialog::~FileDialog() {
    delete titleText;
    delete filenameInfo;
    delete selectedFilenameText;
    delete selectButton;
    delete cancelButton;

    for (auto& t : filenames)
        delete t;

    delete scrollbar;
}

void FileDialog::loadDirectory() {
    paths.clear();
    if (std::filesystem::exists(current_path) && std::filesystem::is_directory(current_path)) {

        if (acceptable_extensions != "") {
            
            for (auto& entry : std::filesystem::directory_iterator(current_path)) {
                if (entry.is_directory()) {
                    paths.push_back(entry);
                }
                else {
                    std::string extension = entry.path().extension().string();
                    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });

                    std::cout << extension << "\n";

                    if (extension == acceptable_extensions) {
                        paths.push_back(entry);
                    }
                }
                    
                
                
              
            }
                
        }
        else {
            for (auto& entry : std::filesystem::directory_iterator(current_path))
                paths.push_back(entry);
        }
    }
    std::sort(paths.begin(), paths.end(), sortkey);

    for (auto& p : paths)
        std::cout << p.path().filename() << "\n";

    paths.emplace(paths.begin(), current_path.parent_path());
}

void FileDialog::loadScrollbar() {
    sf::Vector2f scrollbarSize = sf::Vector2f(16, 7 * line_height + 1);
    sf::Vector2f scrollbarPos;
    scrollbarPos.x = position.x + rect_width / 2.0f - scrollbarSize.x + borderWidth;
    scrollbarPos.y = position.y - rect_height / 2.0f + titlebar.getSize().y + borderWidth;
    if (scrollbar != nullptr)
        delete scrollbar;
    scrollbar = new Scrollbar(scrollbarSize,scrollbarPos, 0, paths.size()-1, 0, 7);

}

void FileDialog::createFilenamesTexts() {

    float filename_rect_width = rect_width - scrollbar->size.x - 30 - 2 * margin_vert;

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

void FileDialog::setFilenamesTexts() {

    std::cout << "scrollVal: " << scrollbar->scroll_value << "\n";

    for (short i = 0; i < 7; i++) {

        if (short(scrollbar->scroll_value)+i < paths.size()) {
            if (short(scrollbar->scroll_value)+i == 0) {
                filenames[i]->setWstring(L"..");
            }
            else {
                filenames[i]->setWstring(paths[+short(scrollbar->scroll_value)+i].path().filename().wstring());
            }
            filenames[i]->generateRect();

            std::string extension = paths[short(scrollbar->scroll_value)+i].path().extension().string();
            if(paths[i+short(scrollbar->scroll_value)].is_directory())
                SingleTexture::SetTextureForSprite(&icons[i], getSingleTexture("GUI/icons/dictionary"));
            else
            {
                SingleTexture::SetTextureForSprite(&icons[i], getSingleTexture("GUI/icons/file"));
            }
        }
        else {
            filenames[i]->setWstring(L"");
            SingleTexture::SetTextureForSprite(&icons[i], getSingleTexture("GUI/icons/empty"));
        }
    }
}

std::string FileDialog::getPathfile() {
    std::string pathfile = current_path.string() + "\\" + selectedFilenameText->texts[0].getString();
    std::cout << pathfile << "\n";
    return pathfile;
}

void FileDialog::update(sf::Event& event) {
    scrollbar->update(event);

    selectButton->unclick();
    cancelButton->unclick();

    selectButton->hover();
    cancelButton->hover();

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
      
                        // LOAD THE DIRECTORY
                        if (i + short(scrollbar->scroll_value) < paths.size()) {

                            if (!paths[i + short(scrollbar->scroll_value)].is_directory()) {
                                std::cout << "is file";
                                selectedFilenameText->setWstring(filenames[i]->s);
                            }
                            else {
                                current_path = std::filesystem::path(paths[i + short(scrollbar->scroll_value)].path().wstring());
                                selectedFilenameText->setWstring(L"");
                                loadDirectory();
                                loadScrollbar();
                               
                            }

                        }

                    }
                }
            }




        }
    }

    setFilenamesTexts();

    selectButton->update();
    cancelButton->update();
}

void FileDialog::draw() {
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
 
    filenameInfo->draw();
    window->draw(selectedFilenameRect);
    selectedFilenameText->draw();
    selectButton->draw();
    cancelButton->draw();
}
