#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"
#include <filesystem>

class ButtonWithText;
class Scrollbar;
class TextArea;
class EditableTextArea;

bool sortkey(std::filesystem::directory_entry first, std::filesystem::directory_entry second);

enum class FileDialogState { Idle, Canceled, FileSelected };

class FileDialog : public Dialog {
public:
    sf::Vector2f position = sf::Vector2f(0, 0);
       
    FileDialogState state;

    sf::RectangleShape rect;        // main big panel
    float rect_width;
    float rect_height;
    float margin_vert;
    float margin_hor;
    float line_height;

    // title bar
    sf::RectangleShape titlebar;
    TextArea* titleText;

    // filenames 
    sf::RectangleShape filenamesRect;
    sf::Sprite icons[7];
    TextArea* filenames[7];

    // submit bar
    sf::RectangleShape submitbar;
    TextArea* filenameInfo;
    EditableTextArea* selectedFilename;

    ButtonWithText* selectButton;
    ButtonWithText* cancelButton;

    std::string acceptable_extensions;

    std::filesystem::path current_path;                     // current path of directory  
    std::vector < std::filesystem::directory_entry > paths; // list of paths

    Scrollbar* scrollbar = nullptr;

    FileDialog(DialogType type, std::wstring title, std::string acceptable_extension="");
    ~FileDialog();

    void loadDirectory();
    void loadScrollbar();
    void createFilenamesTexts();
    void setFilenamesTexts();

    std::string getPathfile();

    void handleEvent(sf::Event& event);
    void update();
    void draw();
};
