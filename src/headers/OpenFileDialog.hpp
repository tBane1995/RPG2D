#ifndef OpenFileDialog_hpp
#define OpenFileDialog_hpp

bool sortkey(std::filesystem::directory_entry first, std::filesystem::directory_entry second) {

    if (first.is_directory() && second.is_directory()) {
        string name_1 = first.path().filename().string();
        string name_2 = second.path().filename().string();

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
        string name_1 = first.path().filename().string();
        string name_2 = second.path().filename().string();

        std::transform(name_1.begin(), name_1.end(), name_1.begin(), [](unsigned char c) { return std::tolower(c); });
        std::transform(name_2.begin(), name_2.end(), name_2.begin(), [](unsigned char c) { return std::tolower(c); });

        if (name_1 < name_2)
            return true;
        else
            return false;
    }

}


class OpenFileDialog : public Dialog {
public:
    sf::Vector2f position = sf::Vector2f(0, 0);

    sf::RectangleShape rect;        // main big panel
    float rect_width;
    float rect_height;
    float margin_vert;
    float margin_hor;
    float filenames_line_height;

    sf::RectangleShape titlebar;    // 
    TextArea* titleText;            //  

    sf::Sprite icons[7];
    sf::RectangleShape filenamesRects[7];
    TextArea* filenames[7];

    sf::RectangleShape submitbar;   // 
    TextArea* filenameText;         // "Filename" text
    TextArea* selectedFilenameText; // selected filename
    ButtonWithText* submitButton;       // 

    std::filesystem::path current_path;                     // current path of directory  
    std::vector < std::filesystem::directory_entry > paths; // list of paths

    

    Scrollbar* scrollbar;   // scrollbar          
    bool fileSelected;      // if "submit button" pressed is true

    OpenFileDialog(wstring title) : Dialog(DialogType::OpenFile) {

        rect_height = 0;
        rect_width = 512;
        margin_vert = 4;
        margin_hor = 4;
        filenames_line_height = 28;

        // TITLE
        titlebar = sf::RectangleShape(sf::Vector2f(512, 32)); 
        titlebar.setFillColor(sf::Color(48, 48, 48));
        rect_height += titlebar.getSize().y;

        titleText = new TextArea(title);
        titleText->setCharacterSize(17);
        titleText->generateRect();
        titleText->setRectColor(sf::Color::Transparent);
        titleText->setTextColor(dialoguesColor);

        ////////////////////////////////////
        // TEXTS AND SCROLLBAR
        current_path = std::filesystem::current_path();
        loadDirectory();
 
        loadScrollbar();
        createFilenamesTexts();
        setFilenamesTexts();

        rect_height += 7 * filenames_line_height;

        ///////////////////////////////////////
        sf::Vector2f pos;

        filenameText = new TextArea(L"File name: ");
        filenameText->setCharacterSize(17);
        filenameText->generateRect();
        filenameText->setRectColor(sf::Color::Transparent);
        filenameText->setTextColor(dialoguesColor);
        pos.x = position.x - 256;
        pos.y = position.y + 256 - 128 - filenameText->rect.getSize().y + 4;
        filenameText->setPosition(pos);
        
        selectedFilenameText = new TextArea(L"");
        selectedFilenameText->setCharacterSize(24);
        selectedFilenameText->setRectColor(sf::Color(32, 32, 32));
        selectedFilenameText->setTextColor(dialoguesColor);
        selectedFilenameText->setRectSize(sf::Vector2f(256 + 48 - 4, filenameText->rect.getSize().y));
        pos.x = position.x - 256 + filenameText->getSize().x;
        pos.y = position.y + 256 - 128 - selectedFilenameText->rect.getSize().y + 4;
        selectedFilenameText->setPosition(pos);
       
        submitButton = new ButtonWithText("submit", 23);
        cout << submitButton->rect.getSize().y << "\n";
        pos.x = position.x + 256 - submitButton->rect.getSize().x - 4;
        pos.y = position.y + 256 - 128 - submitButton->rect.getSize().y + 4;
        submitButton->setPosition(pos);

        submitbar = sf::RectangleShape(sf::Vector2f(512, selectedFilenameText->rect.getSize().y + 8));
        submitbar.setFillColor(sf::Color(48, 48, 48));
        submitbar.setPosition(position.x +cam->position.x - 256, position.y + cam->position.y + 256 - 128 - 32 + 1);
        rect_height += submitbar.getSize().y;

        rect = sf::RectangleShape(sf::Vector2f(512, rect_height));
        rect.setFillColor(panelColor);
        

        // POSITIONING /////////////
        sf::Vector2f p = sf::Vector2f(position.x - rect_width/2.0f,+ position.y - rect_height/2.0f);
        rect.setPosition(p.x+cam->position.x, p.y+cam->position.y);
        
        titlebar.setPosition(p.x+cam->position.x, p.y+cam->position.y);
        titleText->setPosition(sf::Vector2f(p.x + margin_vert, p.y+titleText->getLineHeight()/4.0f));

        pos.x = position.x - rect_width/2.0f + (titleText->texts[0].getPosition().x - titleText->rect.getPosition().x);
        for (short i = 0; i < 7; i++) {

            pos.y = position.y - rect_height/2.0f + titlebar.getSize().y + i * filenamesRects[0].getSize().y;

            icons[i].setPosition(pos.x+cam->position.x, pos.y+cam->position.y);
            filenamesRects[i].setPosition(pos.x+cam->position.x+30, pos.y+cam->position.y);
            filenames[i]->setPosition(sf::Vector2f(pos.x+30,pos.y+filenames[i]->getLineHeight()/4.0f));
        }

        pos.x = position.x + rect_width / 2.0f - scrollbar->bar.getSize().x;
        pos.y = position.y - rect_height / 2.0f + titlebar.getSize().y;
        scrollbar->setPosition(pos);
        
        ///////////////////////////

        fileSelected = false;
    }

    ~OpenFileDialog() {

        delete titleText;
        delete filenameText;
        delete selectedFilenameText;
        delete submitButton;

        for (auto& t : filenames)
            delete t;

        delete scrollbar;

    }

    void loadDirectory() {
        paths.clear();
        if (filesystem::exists(current_path) && filesystem::is_directory(current_path)) {

            for (auto& entry : filesystem::directory_iterator(current_path)) {
                paths.push_back(entry);
            }
        }
        std::sort(paths.begin(), paths.end(), sortkey);

        paths.emplace(paths.begin(), current_path.parent_path());

    }

    void loadScrollbar() {

        sf::Vector2f scrollbarSize = sf::Vector2f(16, 7 * filenames_line_height + 1);
        scrollbar = new Scrollbar(scrollbarSize, 0, paths.size() - 1, 0, 7);
         
    }

    void createFilenamesTexts() {

        float filename_rect_width = rect_width - scrollbar->bar.getSize().x - 30 - 2 * margin_vert;

        for (int i = 0; i < 7; i++) {
            filenamesRects[i] = sf::RectangleShape(sf::Vector2f(filename_rect_width, filenames_line_height));
            filenamesRects[i].setFillColor(sf::Color::Transparent);

            filenames[i] = new TextArea(L"");
            filenames[i]->setCharacterSize(17);
            filenames[i]->generateRect();
            filenames[i]->setRectColor(sf::Color::Transparent);
            filenames[i]->setTextColor(dialoguesColor);

            icons[i] = sf::Sprite();
        }

    }

    void setFilenamesTexts() {
        for (short i = 0; i < 7; i++) {

            if (i + short(scrollbar->scrollValue) < paths.size()) {
                if (i + short(scrollbar->scrollValue) == 0) {
                    filenames[i]->setWstring(L"..");
                }
                else {
                    filenames[i]->setWstring(paths[i + short(scrollbar->scrollValue)].path().filename().wstring());
                }
                filenames[i]->generateRect();

                string extension = paths[i + short(scrollbar->scrollValue)].path().extension().string();
                if (extension == "")
                    icons[i].setTexture(*getSingleTexture("GUI/icons/dictionary")->texture);
                else
                    icons[i].setTexture(*getSingleTexture("GUI/icons/file")->texture);
            }
            else
                filenames[i]->setWstring(L"");
        }
    }

    std::string getPathfile() {
        string pathfile = current_path.string() + "\\" + selectedFilenameText->texts[0].getString();
        cout << pathfile << "\n";
        return pathfile;
    }

    void update(sf::Event& event) {
        scrollbar->update(event);

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {

                submitButton->click();

                if (submitButton->state == ButtonState::Pressed) {
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
                                    scrollbar->maxValue = paths.size()-1;
                                    scrollbar->update();
                                }

                            }

                        }
                    }
                }

                

                
            }
        }

        setFilenamesTexts();

        submitButton->update(dt);
    }

    void draw() {
        window->draw(rect);

        window->draw(titlebar);
        titleText->draw();

        window->draw(submitbar);
        filenameText->draw();
        selectedFilenameText->draw();
        submitButton->draw();
        

        for (short i = 0; i < 7; i++) {
            window->draw(filenamesRects[i]);
            filenames[i]->draw();
            window->draw(icons[i]);
        }

        scrollbar->draw();
    }
};

#endif