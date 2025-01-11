#ifndef MeshEditor_hpp
#define MeshEditor_hpp

#include "Platform/Utils.h"

enum class MeshEditorStates { Start, Editor };
MeshEditorStates meshEditorState;

std::vector <sf::Vector2f> points;
std::vector <Triangle> triangles;
sf::Vector2u tex_size;
short frag_size;
sf::Vector2f position;

void MeshEditor() {

    window->setTitle("Mesh Editor");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    meshEditorState = MeshEditorStates::Start;

    sf::Text* welcomeText = new sf::Text("Mesh Editor", basicFont, 32);
    welcomeText->setFillColor(textColor);
    welcomeText->setOrigin(welcomeText->getLocalBounds().width / 2.f, welcomeText->getLocalBounds().height / 2.f);
    welcomeText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* pressText = new sf::Text("press Spacebar to start", basicFont, 16);
    pressText->setFillColor(textColor);
    pressText->setOrigin(pressText->getLocalBounds().width / 2.f, pressText->getLocalBounds().height / 2.f);
    pressText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    bool skip = false;
    while (window->isOpen() && skip == false) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                skip = true;
                break;
            }
        }
        window->setView(cam->view);
        welcomeText->setPosition(cam->position.x, cam->position.y - 50);
        pressText->setPosition(cam->position.x, cam->position.y + 50);

        window->clear(sf::Color::Black);
        window->draw(*welcomeText);
        window->draw(*pressText);
        window->display();

    }

    meshEditorState = MeshEditorStates::Editor;

    // TO-DO
    tex_size = dynamic_cast<Nature*>(getPrefab("natures/tree9"))->texture->getSize();
    (tex_size.x > tex_size.y) ? frag_size = tex_size.x : frag_size = tex_size.y;
    frag_size /= 16;
    //

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        mousePosition = sf::Mouse::getPosition(*window);
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        position.x = short(worldMousePosition.x) / frag_size * frag_size;
        position.y = short(worldMousePosition.y) / frag_size * frag_size;

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    bool pointExists = false;

                    for (auto& p : points) {
                        if (abs(p.x - worldMousePosition.x) < 25.0f && abs(p.y - worldMousePosition.y) < 25.0f)
                            pointExists = true;
                    }

                    if (!pointExists) {

                        points.push_back(position);
                        triangles = triangulate(points);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }

                if (event.key.code == sf::Keyboard::F5) {

                }

                if (event.key.code == sf::Keyboard::F6) {

                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z) {
                    // TO-DO - UNDO ACTION
                }

                if (event.key.code == sf::Keyboard::Space) {
                    // DO NOTHING
                }

            }
        } // events



        // UPDATE ////////////////////////////////////////////////////////////////////////
        cam->update();

        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 64, 64));
        window->setView(cam->view);

        sf::VertexArray mesh(sf::Lines);
        for (auto& tri : triangles) {
            mesh.append(sf::Vertex(tri.a, sf::Color::Red));
            mesh.append(sf::Vertex(tri.b, sf::Color::Red));
            mesh.append(sf::Vertex(tri.b, sf::Color::Red));
            mesh.append(sf::Vertex(tri.c, sf::Color::Red));
            mesh.append(sf::Vertex(tri.c, sf::Color::Red));
            mesh.append(sf::Vertex(tri.a, sf::Color::Red));
        }

        GameObject* prefab = getPrefab("natures/tree9");
        Nature* nature = dynamic_cast<Nature*>(prefab);
        sf::Sprite sprite = nature->sprite;
        //sprite.setOrigin(nature->texture->cx, nature->texture->cy);
        sprite.setOrigin(nature->texture->cx, nature->texture->cy);
        sprite.setScale(2.0f, 2.0f);

        window->draw(sprite);
        window->draw(mesh);

        float radius = 5.0f;

        for (auto& p : points) {
            sf::CircleShape c(radius);
            c.setOrigin(radius / 2.0f, radius / 2.0f);
            c.setPosition(p.x, p.y);
            c.setFillColor(sf::Color::Blue);
            window->draw(c);
        }

        sf::CircleShape cursor(radius);
        cursor.setOrigin(radius / 2.0f, radius / 2.0f);
        cursor.setFillColor(sf::Color::Red);
        cursor.setPosition(position);
        window->draw(cursor);

        window->display();
    }

    delete window;
}

#endif