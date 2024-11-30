#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Dialog.h"
#include <filesystem>

class ButtonWithText;
class Scrollbar;
class TextArea;

bool sortkey(std::filesystem::directory_entry first, std::filesystem::directory_entry second);


class OpenFileDialog : public Dialog {
public:
    sf::Vector2f position = sf::Vector2f(0, 0);
    sf::RectangleShape rect;        // main big panel
    sf::RectangleShape titlebar;    // 
    TextArea* titleText;            //  
    sf::RectangleShape submitbar;   // 
    TextArea* filenameText;         // "Filename" text
    TextArea* selectedFilenameText; // selected filename
    ButtonWithText* submitButton;       // 

    std::filesystem::path current_path;                     // current path of directory  
    std::vector < std::filesystem::directory_entry > paths; // list of paths

    sf::RectangleShape textField[7];    // text Field - rects
    TextArea* texts[7];                 // texts - filenames
    sf::Sprite icons[7];                // icons

    Scrollbar* scrollbar;   // scrollbar          
    bool fileSelected;      // if "submit button" pressed is true

    OpenFileDialog(std::wstring title);
    ~OpenFileDialog();

    void clearTexts();
    void loadScrollbar();
    void loadDirectory();

    std::string getPathfile();

    void update(sf::Event& event);
    void draw();
};
