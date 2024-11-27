#include "BuildingsManager.h"


Building::Building(int width, int height) : GameObject("empty", 0, 0)
{
    type = GameObjectType::Building;
    size.x = width;
    size.y = height;

    position.x = size.x * 16 / 2;
    position.y = size.y * 16;

    floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);

    loadCollider();
}

virtual Building::~Building()
{
    delete _door;
    delete floors;

    for (auto& item : _items)
        delete item;

    for (auto& furniture : _furnitures)
        delete furniture;

    for (auto& wall : _walls)
        delete wall;
}

void Building::addGameObject(GameObject* object)
{
    if (object->type == GameObjectType::Wall) {
        Wall* wall = new Wall(object, object->position.x, object->position.y);
        _walls.push_back(wall);
    }

    if (object->type == GameObjectType::ItemOnMap) {
        ItemOnMap* item = new ItemOnMap(object, object->position.x, object->position.y);
        _items.push_back(item);
    }

    if (object->type == GameObjectType::Furniture) {
        Furniture* furniture = new Furniture(object, object->position.x, object->position.y);
        _furnitures.push_back(furniture);
    }
}

void Building::deleteGameObject(GameObject* object) {

    if (object->type == GameObjectType::Wall) {
        auto it = std::find(_walls.begin(), _walls.end(), object);
        if (it != _walls.end())
            _walls.erase(it);
    }

    if (object->type == GameObjectType::ItemOnMap) {
        auto it = std::find(_items.begin(), _items.end(), object);
        if (it != _items.end())
            _items.erase(it);
    }

    if (object->type == GameObjectType::Furniture) {
        auto it = std::find(_furnitures.begin(), _furnitures.end(), object);
        if (it != _furnitures.end())
            _furnitures.erase(it);
    }

}

bool Building::playerInside() {

    short x3, y3, rx3, ry3;
    x3 = player->position.x;
    y3 = player->position.y;
    rx3 = (player->colliders[0]->width / 2.0f);
    ry3 = (player->colliders[0]->length) / 2.0f;

    if (intersectionRectangleWithElipse((x1 + x2) / 2, (y1 + y2) / 2, x2 - x1, y2 - y1, x3, y3, rx3, ry3))
        return true;
    else
        return false;
}

void Building::loadTexture2(std::ifstream& file) {

    // check the size
    //cout << size.x << " " << size.y << "\n";

    short walls_height = 3;

    // variables for generate roof
    float tiles_rows = size.y / 2;
    float tiles_columns = size.x / 2;
    float tile_width = float(size.x) / 4.0f * 32.0f / tiles_columns;
    float tile_height = float(size.y / 4.0f + 2) * 32.0f / tiles_rows;
    float tile_border = 1;

    sf::Color color_outside = sf::Color::Black; //sf::Color(51, 38, 21);
    sf::Color color_inside = sf::Color(128, 24, 24);

    // create basic image to render house
    sf::Image house_image;
    house_image.create(size.x * 16 + tile_width, (walls_height + size.x / 2.0f) * 16.0f + tiles_rows * tile_height + tile_height * 0.75f, sf::Color::Transparent);

    // DRAWING A WALLS
    sf::Image walls_image;
    walls_image.create(32, 32, sf::Color::Transparent);
    walls_image = walls->texture->copyToImage();

    for (short y = 2; y <= walls_height; y++) {
        for (short x = 0; x < size.x / 2; x++) {
            house_image.copy(walls_image, x * 2 * 16 + tile_width / 2.0f, house_image.getSize().y - y * 2 * 16);
        }
    }

    sf::Image bottom_walls_image;
    bottom_walls_image.create(32, 32, sf::Color::Transparent);
    bottom_walls_image = bottom_walls->texture->copyToImage();

    for (short x = 0; x < size.x / 2; x++) {
        house_image.copy(bottom_walls_image, x * 2 * 16 + tile_width / 2.0f, house_image.getSize().y - 2 * 16);
    }

    // top_walls
    sf::Image top_walls_image;
    top_walls_image.create(32, 32, sf::Color::Transparent);
    top_walls_image = top_walls->texture->copyToImage();

    short width = size.x / 2;
    short start_x;
    short end_x;

    for (int y = 0; y <= size.x/4; y+=2) {
        start_x = y;
        end_x = width - y - 1;

        for (int x = 0; x < width; x++) {
            if (x >= start_x && x <= end_x) {
                house_image.copy(top_walls_image, x * 2 * 16 + tile_width / 2.0f, house_image.getSize().y - (y/2 + walls_height + 1) * 2 * 16);
            }
        }
    }

    // DRAWING A SHAPE OF ROOF
    sf::Color color = sf::Color::Black;

    sf::Vector2f p1(0, walls_height*32.0f - tile_height/4.0f);
    sf::Vector2f p2(tile_width/2.0f + size.x/4.0f * 32.0f, (walls_height + size.x/8.0f) * 32.0f); //
    sf::Vector2f p3(tile_width + size.x/2.0f * 32.0f, walls_height * 32.0f - tile_height/4.0f);
    sf::Vector2f p4(tile_width + size.x/2.0f * 32.0f, walls_height * 32.0f + tiles_rows * tile_height - tile_height/4.0f);
    sf::Vector2f p5(tile_width/2.0f + size.x/4.0f * 32.0f, (walls_height + size.x/8.0f) * 32.0f + tiles_rows * tile_height); //
    sf::Vector2f p6(0, walls_height * 32.0f + tiles_rows * tile_height - tile_height/4.0f);

    sf::VertexArray left_quad(sf::Quads, 4);
    left_quad[0].position = p1;
    left_quad[1].position = p2;
    left_quad[2].position = p5;
    left_quad[3].position = p6;

    for (short i = 0; i < 4; i++)
        left_quad[i].color = color;

    sf::VertexArray right_quad(sf::Quads, 4);
    right_quad[0].position = p2;
    right_quad[1].position = p3;
    right_quad[2].position = p4;
    right_quad[3].position = p5;

    for (short i = 0; i < 4; i++)
        right_quad[i].color = color;

    sf::RenderTexture rtex;
    rtex.create(house_image.getSize().x, house_image.getSize().y);
    rtex.draw(left_quad);
    rtex.draw(right_quad);


    // CREATE A TILES
    sf::RenderStates rstate(getSingleTexture("buildings/parts/roof")->texture);

    // LEFT SIDE OF ROOF
    // even tiles
    for (float x = 0; x < tiles_columns; x += 2) {
        // bottom tiles
        sf::Vector2f bottom_pos(x * tile_width, walls_height * 32.0f + x * tile_width/2);
        sf::VertexArray bottom_tile(sf::Quads, 4);
        bottom_tile[0].position = sf::Vector2f(bottom_pos.x + tile_border, bottom_pos.y + tile_border - tile_height/4.0f);
        bottom_tile[1].position = sf::Vector2f(bottom_pos.x + tile_width - tile_border, bottom_pos.y + tile_border + tile_height/8.0f);
        bottom_tile[2].position = sf::Vector2f(bottom_pos.x + tile_width - tile_border, bottom_pos.y - tile_border + tile_height/2.0f + tile_height/8.0f);
        bottom_tile[3].position = sf::Vector2f(bottom_pos.x + tile_border, bottom_pos.y - tile_border + tile_height/2.0f - tile_height/4.0f);

        bottom_tile[0].color = sf::Color(255, 255, 255, 196);
        bottom_tile[1].color = sf::Color(255, 255, 255, 196);
        bottom_tile[2].color = sf::Color(255, 255, 255, 196);
        bottom_tile[3].color = sf::Color(255, 255, 255, 196);

        bottom_tile[0].texCoords = sf::Vector2f(0, 0);
        bottom_tile[1].texCoords = sf::Vector2f(tile_width, 0);
        bottom_tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
        bottom_tile[3].texCoords = sf::Vector2f(0, tile_height);
            
        rtex.draw(bottom_tile, rstate);

        // center tiles
        for (float y = 1; y < tiles_rows; y += 1) {
            sf::Vector2f quad_pos(x * tile_width, walls_height * 32.0f + y * tile_height - tile_height/2.0f + x * tile_width/2);
            sf::VertexArray tile(sf::Quads, 4);
            tile[0].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y + tile_border - tile_height/4.0f);
            tile[1].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y + tile_border + tile_height/8.0f);
            tile[2].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y - tile_border + tile_height + tile_height/8.0f);
            tile[3].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y - tile_border + tile_height - tile_height/4.0f);

            tile[0].color = sf::Color(255, 255, 255, 196);
            tile[1].color = sf::Color(255, 255, 255, 196);
            tile[2].color = sf::Color(255, 255, 255, 196);
            tile[3].color = sf::Color(255, 255, 255, 196);

            tile[0].texCoords = sf::Vector2f(0, 0);
            tile[1].texCoords = sf::Vector2f(tile_width, 0);
            tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
            tile[3].texCoords = sf::Vector2f(0, tile_height);

            rtex.draw(tile, rstate);
        }

        // top tiles
        sf::Vector2f top_pos(x* tile_width, walls_height * 32.0f + tiles_rows * tile_height + x * tile_width / 2 - tile_height / 2.0f);
        sf::VertexArray top_tile(sf::Quads, 4);

        top_tile[0].position = sf::Vector2f(top_pos.x + tile_border, top_pos.y + tile_border - tile_height / 4.0f);
        top_tile[1].position = sf::Vector2f(top_pos.x + tile_width - tile_border, top_pos.y + tile_border + tile_height / 8.0f);
        top_tile[2].position = sf::Vector2f(top_pos.x + tile_width - tile_border, top_pos.y - tile_border + tile_height / 2.0f + tile_height / 8.0f);
        top_tile[3].position = sf::Vector2f(top_pos.x + tile_border, top_pos.y - tile_border + tile_height / 2.0f - tile_height / 4.0f);

        top_tile[0].color = sf::Color(255, 255, 255, 196);
        top_tile[1].color = sf::Color(255, 255, 255, 196);
        top_tile[2].color = sf::Color(255, 255, 255, 196);
        top_tile[3].color = sf::Color(255, 255, 255, 196);

        top_tile[0].texCoords = sf::Vector2f(0, 0);
        top_tile[1].texCoords = sf::Vector2f(tile_width, 0);
        top_tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
        top_tile[3].texCoords = sf::Vector2f(0, tile_height);

        rtex.draw(top_tile, rstate);
    }

    // odd tiles
    for (float x = 1; x < tiles_columns; x += 2) {
        for (float y = 0; y < tiles_rows; y += 1) {
            sf::Vector2f quad_pos(x * tile_width, walls_height * 32.0f + y * tile_height + x * tile_width/2.0f);

            sf::VertexArray tile(sf::Quads, 4);
            tile[0].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y + tile_border - tile_height / 4.0f);
            tile[1].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y + tile_border + tile_height/8.0f);
            tile[2].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y - tile_border + tile_height + tile_height/8.0f);
            tile[3].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y - tile_border + tile_height - tile_height / 4.0f);

            tile[0].color = sf::Color(255, 255, 255, 196);
            tile[1].color = sf::Color(255, 255, 255, 196);
            tile[2].color = sf::Color(255, 255, 255, 196);
            tile[3].color = sf::Color(255, 255, 255, 196);

            tile[0].texCoords = sf::Vector2f(0, 0);
            tile[1].texCoords = sf::Vector2f(tile_width, 0);
            tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
            tile[3].texCoords = sf::Vector2f(0, tile_height);

            rtex.draw(tile, rstate);
        }
    }

    // RIGHT SIDE OF ROOF - ODD TILES
    for (float x = 0; x < tiles_columns; x += 2) {
        for (float y = 0; y < tiles_rows; y += 1) {
            sf::Vector2f quad_pos(size.x/4.0f*32.0f + tile_width + x*tile_width, walls_height*32.0f + size.x/4.0f*16.0f + y*tile_height - x*tile_width/2.0f - tile_width/2.0f);
            sf::VertexArray tile(sf::Quads, 4);

            tile[0].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y + tile_border + tile_height / 8.0f);
            tile[1].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y + tile_border - tile_height / 4.0f);
            tile[2].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y - tile_border + tile_height - tile_height / 4.0f);
            tile[3].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y - tile_border + tile_height + tile_height / 8.0f);
                
            tile[0].texCoords = sf::Vector2f(0, 0);
            tile[1].texCoords = sf::Vector2f(tile_width, 0);
            tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
            tile[3].texCoords = sf::Vector2f(0, tile_height);

            rtex.draw(tile, rstate);
        }
    }

    // RIGHT SIDE OF ROOF - EVEN TILES
    for (float x = 1; x < tiles_columns; x += 2) {
        // bottom tile
        sf::Vector2f bottom_pos(size.x / 4.0f * 32.0f + tile_width + x * tile_width, walls_height * 32.0f + size.x / 4.0f * 16.0f - x * tile_width / 2.0f - tile_width / 2.0f);
        sf::VertexArray bottom_tile(sf::Quads, 4);

        bottom_tile[0].position = sf::Vector2f(bottom_pos.x + tile_border, bottom_pos.y + tile_border + tile_height / 8.0f);
        bottom_tile[1].position = sf::Vector2f(bottom_pos.x + tile_width - tile_border, bottom_pos.y + tile_border - tile_height / 4.0f);
        bottom_tile[2].position = sf::Vector2f(bottom_pos.x + tile_width - tile_border, bottom_pos.y - tile_border + tile_height / 2.0f - tile_height / 4.0f);
        bottom_tile[3].position = sf::Vector2f(bottom_pos.x + tile_border, bottom_pos.y - tile_border + tile_height / 2.0f + tile_height / 8.0f);

        bottom_tile[0].texCoords = sf::Vector2f(0, 0);
        bottom_tile[1].texCoords = sf::Vector2f(tile_width, 0);
        bottom_tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
        bottom_tile[3].texCoords = sf::Vector2f(0, tile_height);

        rtex.draw(bottom_tile, rstate);

        for (float y = 1; y < tiles_rows; y += 1) {
            sf::Vector2f quad_pos(size.x / 4.0f * 32.0f + tile_width + x * tile_width, walls_height * 32.0f + size.x / 4.0f * 16.0f + y * tile_height - x * tile_width / 2.0f - tile_width / 2.0f - tile_height / 2.0f);
            sf::VertexArray tile(sf::Quads, 4);

            tile[0].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y + tile_border + tile_height / 8.0f);
            tile[1].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y + tile_border - tile_height / 4.0f);
            tile[2].position = sf::Vector2f(quad_pos.x + tile_width - tile_border, quad_pos.y - tile_border + tile_height - tile_height / 4.0f);
            tile[3].position = sf::Vector2f(quad_pos.x + tile_border, quad_pos.y - tile_border + tile_height + tile_height / 8.0f);

            tile[0].texCoords = sf::Vector2f(0, 0);
            tile[1].texCoords = sf::Vector2f(tile_width, 0);
            tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
            tile[3].texCoords = sf::Vector2f(0, tile_height);

            rtex.draw(tile, rstate);
        }

        // top tiles
        sf::Vector2f top_pos(size.x / 4.0f * 32.0f + tile_width + x * tile_width, walls_height * 32.0f + size.x / 4.0f * 16.0f + tiles_rows * tile_height - x * tile_width / 2.0f - tile_width / 2.0f - tile_height / 2.0f);
        sf::VertexArray top_tile(sf::Quads, 4);

        top_tile[0].position = sf::Vector2f(top_pos.x + tile_border, top_pos.y + tile_border + tile_height / 8.0f);
        top_tile[1].position = sf::Vector2f(top_pos.x + tile_width - tile_border, top_pos.y + tile_border - tile_height / 4.0f);
        top_tile[2].position = sf::Vector2f(top_pos.x + tile_width - tile_border, top_pos.y - tile_border + tile_height / 2.0f - tile_height / 4.0f);
        top_tile[3].position = sf::Vector2f(top_pos.x + tile_border, top_pos.y - tile_border + tile_height / 2.0f + tile_height / 8.0f);

        top_tile[0].texCoords = sf::Vector2f(0, 0);
        top_tile[1].texCoords = sf::Vector2f(tile_width, 0);
        top_tile[2].texCoords = sf::Vector2f(tile_width, tile_height);
        top_tile[3].texCoords = sf::Vector2f(0, tile_height);

        rtex.draw(top_tile, rstate);
    }

    // CENTER TILES
    // shape
    sf::VertexArray beam(sf::Quads, 4);
    sf::Vector2f pos;

    pos.x = size.x/2.f*16.0f + tile_width/2.0f;
    pos.y = (walls_height + size.x/8.0f)*32.0f - tile_height/8.0f;

    beam[0].position = sf::Vector2f(pos.x - tile_width/2.0f, pos.y);
    beam[1].position = sf::Vector2f(pos.x + tile_width/2.0f, pos.y);
    beam[2].position = sf::Vector2f(pos.x + tile_width/2.0f, pos.y + tiles_rows * tile_height);
    beam[3].position = sf::Vector2f(pos.x - tile_width/2.0f, pos.y + tiles_rows * tile_height);

    for (short i = 0; i < 4; i++)
        beam[i].color = sf::Color::Black;

    rtex.draw(beam);

    // bottom tile
    sf::VertexArray tile(sf::Quads, 4);
    pos.x = size.x / 2.0f * 16.0f;
    pos.y = (walls_height + size.x/8.0f)*32.0f;
    tile[0].position = sf::Vector2f(pos.x + tile_border, pos.y + tile_border - tile_height/8.0f);
    tile[1].position = sf::Vector2f(pos.x + tile_width - tile_border, pos.y + tile_border - tile_height/8.0f);
    tile[2].position = sf::Vector2f(pos.x + tile_width - tile_border, pos.y + tile_height/2.0f - tile_border - tile_height/8.0f);
    tile[3].position = sf::Vector2f(pos.x + tile_border, pos.y + tile_height/2.0f - tile_border - tile_height/8.0f);

    for (short i = 0; i < 4; i++)
        beam[i].color = sf::Color(128,128,128);

    for (short i = 0; i < 4; i++)
        tile[i].texCoords = beam[i].position;
        
    rtex.draw(tile, rstate);

    // center tiles
    for (float y = 0; y < tiles_rows-1; y += 1) {
        pos.x = size.x/2.0f*16.0f;
        pos.y = (walls_height+ size.x/8.0f)*32.0f + y*tile_height + tile_height/2.0f;
        tile[0].position = sf::Vector2f(pos.x + tile_border, pos.y + tile_border - tile_height/8.0f);
        tile[1].position = sf::Vector2f(pos.x + tile_width - tile_border, pos.y + tile_border - tile_height/8.0f);
        tile[2].position = sf::Vector2f(pos.x + tile_width - tile_border, pos.y + tile_height - tile_border - tile_height/8.0f);
        tile[3].position = sf::Vector2f(pos.x + tile_border, pos.y + tile_height - tile_border - tile_height/8.0f);

        for (short i = 0; i < 4; i++)
            tile[i].texCoords = beam[i].position;

        rtex.draw(tile, rstate);
    }

    // top tile
    pos.x = size.x / 2.0f * 16.0f;
    pos.y = (walls_height + size.x / 8.0f) * 32.0f + tiles_rows*tile_height - tile_height/2.0f;
    tile[0].position = sf::Vector2f(pos.x + tile_border, pos.y + tile_border - tile_height / 8.0f);
    tile[1].position = sf::Vector2f(pos.x + tile_width - tile_border, pos.y + tile_border - tile_height / 8.0f);
    tile[2].position = sf::Vector2f(pos.x + tile_width - tile_border, pos.y + tile_height / 2.0f - tile_border - tile_height / 8.0f);
    tile[3].position = sf::Vector2f(pos.x + tile_border, pos.y + tile_height / 2.0f - tile_border - tile_height / 8.0f);

    for (short i = 0; i < 4; i++)
        tile[i].texCoords = beam[i].position;

    rtex.draw(tile, rstate);

    // BEAM UNDER ROOF
       
    // top-center quad
    pos.x = size.x/2.f * 16.0f + tile_width/2.0f;
    pos.y = (walls_height + size.x/8.0f)*32.0f - tile_height/8.0f;

    beam[0].position = sf::Vector2f(pos.x - tile_width/2.0f, pos.y - tile_height/4.0f);
    beam[1].position = sf::Vector2f(pos.x + tile_width/2.0f, pos.y - tile_height/4.0f);
    beam[2].position = sf::Vector2f(pos.x + tile_width/2.0f, pos.y);
    beam[3].position = sf::Vector2f(pos.x - tile_width/2.0f, pos.y);

    for (short i = 0; i < 4; i++)
        beam[i].texCoords = beam[i].position;

    rtex.draw(beam, rstate);

    // top-left quad
    beam[0].position = sf::Vector2f(pos.x - tiles_columns*tile_width - tile_width/2.0f, pos.y - size.x/4.0f*16.0f);
    beam[1].position = sf::Vector2f(pos.x - tiles_columns*tile_width - tile_width/2.0f, pos.y - size.x/4.0f*16.0f-tile_height/4.0f);
    beam[2].position = sf::Vector2f(pos.x-tile_width/2.0f, pos.y-tile_height/4.0f);
    beam[3].position = sf::Vector2f(pos.x-tile_width/2.0f, pos.y);

    for (short i = 0; i < 4; i++)
        beam[i].texCoords = beam[i].position;

    rtex.draw(beam, rstate);

    // top-right quad
    beam[0].position = sf::Vector2f(pos.x + tiles_columns*tile_width + tile_width/2.0f, pos.y - size.x/4.0f*16.0f - tile_height/4.0f);
    beam[1].position = sf::Vector2f(pos.x + tiles_columns*tile_width + tile_width/2.0f, pos.y - size.x/4.0f*16.0f);
    beam[2].position = sf::Vector2f(pos.x + tile_width/2.0f, pos.y);
    beam[3].position = sf::Vector2f(pos.x + tile_width/2.0f, pos.y-tile_height/4.0f);

    for (short i = 0; i < 4; i++)
        beam[i].texCoords = beam[i].position;

    rtex.draw(beam, rstate);


    // SHADOWS UNDER THE ROOF
    // left shadow
    sf::VertexArray shadow(sf::Quads, 4);
    shadow[0].position = sf::Vector2f(pos.x-size.x/4.0f*32.0f, pos.y - size.x/4.0f*16.0f);
    shadow[1].position = sf::Vector2f(pos.x-size.x/4.0f*32.0f, pos.y - size.x/4.0f*16.0f - tile_height);
    shadow[2].position = sf::Vector2f(pos.x, pos.y - tile_height);
    shadow[3].position = sf::Vector2f(pos.x, pos.y);

    for (short i = 0; i < 4; i++) {
        shadow[i].color = sf::Color(0,0,0,64);
        shadow[i].texCoords = shadow[i].position;
    }
            
    rtex.draw(shadow, rstate);

    // right shadow
    shadow[0].position = sf::Vector2f(pos.x, pos.y);
    shadow[1].position = sf::Vector2f(pos.x, pos.y - tile_height);
    shadow[2].position = sf::Vector2f(pos.x + size.x / 4.0f * 32.0f, pos.y - size.x / 4.0f * 16.0f - tile_height);
    shadow[3].position = sf::Vector2f(pos.x + size.x / 4.0f * 32.0f, pos.y - size.x / 4.0f * 16.0f);

    for (short i = 0; i < 4; i++) {
        shadow[i].color = sf::Color(0, 0, 0, 64);
        shadow[i].texCoords = shadow[i].position;
    }

    rtex.draw(shadow, rstate);

    // COPY THE ROOF TO IMAGE
    sf::Image roof_image = rtex.getTexture().copyToImage();
    house_image.copy(roof_image, 0, 0, sf::IntRect(0, 0, 0, 0), true);

    // RENDER EMPTY PLACE FOR THE DOOR
    if (_door != nullptr) {
        sf::RectangleShape door(sf::Vector2f(_door->sprite.getTexture()->getSize()));

        for (short y = 0; y < door.getSize().y - 1; y++)
            for (short x = 0; x < door.getSize().x; x++) {
                sf::Vector2i pos;
                pos.x = float(size.x) / 2.0f * 16.0f - door.getSize().x / 2.0f + tile_width / 2.0f + x;
                pos.y = rtex.getSize().y - 1 - y;
                house_image.setPixel(pos.x, pos.y, sf::Color(0, 0, 0, 0));
            }
    }

    // RENDER WINDOWS
    if ((size.x / 2 - 1) > 2 && (size.x / 4 - 1) % 2 == 1) {
        sf::Texture win_tex = *windows->texture;
        sf::Image window_image = win_tex.copyToImage();

        short left_window_pos;
        short right_window_pos;
        short pos_y = house_image.getSize().y - 64;

        for (short i = 1; i < size.x / 4 - 1; i += 2) {

            left_window_pos = tile_width / 2.0f + i * 32;
            right_window_pos = tile_width / 2.0f + (size.x / 4 + i + 1) * 32;

            house_image.copy(window_image, left_window_pos, pos_y, sf::IntRect(0, 0, 0, 0));
            house_image.copy(window_image, right_window_pos, pos_y, sf::IntRect(0, 0, 0, 0));
        }
    }


    // create main tex
    sf::Texture* tex = new sf::Texture();
    tex->loadFromImage(house_image);

    // create the sprite
    sprite = sf::Sprite();
    sprite.setTexture(*tex);
    sprite.setOrigin(tex->getSize().x/2, tex->getSize().y);
    sprite.setPosition(position);
}


void Building::loadSize(std::ifstream& file)
{
    std::string line;
    std::string objectType;

    std::getline(file, line);
    std::istringstream lineStream(line);
    lineStream >> objectType;
    lineStream >> size.x >> size.y;
}

void Building::loadCollider()
{
    if (!colliders.empty()) {
        delete colliders[0];
        colliders.clear();
    }
            
    colliders.push_back(new Collider(size.x * 16, size.y * 16, position, ColliderType::Rectangle));
    colliders[0]->shape->setPosition(position.x, position.y - size.y / 2 * 16);
}

void Building::loadDoor(std::ifstream& file) {

    std::string line;

    std::getline(file, line);

    if (_door != nullptr)
    {
        delete _door;
    }
    _door = new Door(getPrefab("doors/door_0"), position.x, position.y);
}

void Building::loadWalls(std::ifstream& file) {
        
    std::string line;
    std::string fragment;

    // top_walls
    std::getline(file, line);
        
    size_t  start = line.find("\"");
    size_t end = line.find_last_of("\"");
    if (start != std::string::npos && end != std::string::npos && start < end)
        fragment = line.substr(start + 1, end - start - 1);

    if (fragment == "")
        fragment = "walls/wooden_wall";

    top_walls = getSingleTexture(fragment);
    if (top_walls == nullptr)
        top_walls = getSingleTexture("walls/wooden_wall");

    // walls
    std::getline(file, line);

    start = line.find("\"");
    end = line.find_last_of("\"");
    if (start != std::string::npos && end != std::string::npos && start < end)
        fragment = line.substr(start + 1, end - start - 1);

    walls = getSingleTexture(fragment);
    if (walls == nullptr)
        walls = getSingleTexture("walls/stone_wall");

    // bottom_walls
    std::getline(file, line);

    start = line.find("\"");
    end = line.find_last_of("\"");
    if (start != std::string::npos && end != std::string::npos && start < end)
        fragment = line.substr(start + 1, end - start - 1);

    bottom_walls = getSingleTexture(fragment);
    if (bottom_walls == nullptr)
        bottom_walls = getSingleTexture("walls/stone_wall");
}

void Building::loadWindows(std::ifstream& file) {

    std::string line;
    std::string fragment;

    std::getline(file, line);

    size_t start = line.find("\"");
    size_t end = line.find_last_of("\"");

    if (start != std::string::npos && end != std::string::npos && start < end)
        fragment = line.substr(start + 1, end - start - 1);

    windows = getSingleTexture(fragment);

    if (windows == nullptr)
        windows = getSingleTexture("buildings/parts/window");
}

void Building::loadFloors(std::ifstream& file) {

    if (floors != nullptr)
        delete floors;

    floors = new Floors(position.x / 16 - size.x / 2, position.y / 16 - size.y, size.x, size.y);

    short value;
    for (short y = 0; y < size.y; y++) {
        for (short x = 0; x < size.x; x++) {
            file >> value;
            floors->edit(x, y, value);
        }
    }
}

void Building::loadGameObjects(std::ifstream& file) {

    std::string line;
    std::string objectType;
    std::string objectName;

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::istringstream lineStream(line);
        lineStream >> objectType;
        //cout << line << "\n";

        if (objectType == "Item") {

            short x, y;
            getline(lineStream, objectName, '"');
            getline(lineStream, objectName, '"');
            lineStream >> x;
            lineStream >> y;

            x = x - (size.x * 16 / 2) + position.x;
            y = y - (size.y * 16) + position.y;

            Item* item = getItem(objectName);
            if (item != nullptr) {
                ItemOnMap* itemOnMap = new ItemOnMap(item, x, y);
                _items.push_back(itemOnMap);
            }

        }

        if (objectType == "Furniture") {
            string name;
            short x, y, id;

            getline(lineStream, objectName, '"');
            getline(lineStream, objectName, '"');
            lineStream >> x;
            lineStream >> y;
            lineStream >> id;

            x = x - (size.x * 16 / 2) + position.x;
            y = y - (size.y * 16) + position.y;

            GameObject* prefab = getPrefab(objectName);
            if (prefab != nullptr) {
                Furniture* furniture = new Furniture(prefab, x, y);
                furniture->inventory = getInventory(id);
                _furnitures.push_back(furniture);
            }

        }

        if (objectType == "Wall") {
            string name;
            short x, y;

            getline(lineStream, objectName, '"');
            getline(lineStream, objectName, '"');
            lineStream >> x;
            lineStream >> y;

            x = x - (size.x * 16 / 2) + position.x;
            y = y - (size.y * 16) + position.y;

            GameObject* prefab = getPrefab(objectName);
            if (prefab != nullptr) {
                Wall* wall = new Wall(prefab, x, y);
                _walls.push_back(wall);
            }

        }

    }
}

void Building::load() {
    std::string filename = name;
    std::ifstream file(filename);

    if (!file.is_open()) {
        cout << "cant open building script: " << filename << "\n";
        return;
    }

    loadName(file);
    loadSize(file);
    loadCollider();
    loadDoor(file);
    loadWalls(file);
    loadWindows(file);
    loadTexture2(file);

    std::string line;

    std::getline(file, line);
    std::getline(file, line);

    loadFloors(file);
    loadGameObjects(file);

    file.close();
}

void Building::loadWithPositioning()
{
    std::string filename = name;
    std::ifstream file(filename);

    if (!file.is_open()) {
        cout << "cant open building script: " << filename << "\n";
        return;
    }

    loadName(file);
        
    loadSize(file);

    position.x = size.x * 16 / 2;
    position.y = size.y * 16;

    loadCollider();
    loadDoor(file);
    loadWalls(file);
    loadWindows(file);

    loadTexture2(file);

    std::string line;

    std::getline(file, line);
    std::getline(file, line);

    loadFloors(file);
    loadGameObjects(file);

    file.close();
}

void Building::save(std::string filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        cout << "cant open file to save building: " << filename << "\n";
        return;
    }

    file << "name \"testBuilding\"\n";
    file << "size " << to_string(floors->width) << " " << to_string(floors->height) << "\n";
    file << "door \"door_0\"\n";

    file << "\n";

    // SAVE FLOORS
    file << "// FLOORS\n";
    for (short y = 0; y < floors->height; y++) {
        for (short x = 0; x < floors->width; x++) {
            file << floors->floors[y * floors->width + x];
            if (x != floors->width - 1)
                file << " ";
        }
        file << "\n";
    }
    file << "\n";

    // SAVE ITEMS
    if (_items.size() > 0)
        file << "// ITEMS\n";
    for (auto& item : _items)
        file << "Item " << char(34) << item->name << char(34) << " " << int(item->position.x) << " " << int(item->position.y) << "\n";
    if (_items.size() > 0)
        file << "\n";


    if (_furnitures.size() > 0)
        file << "// FURNITURES\n";
    for (auto& furniture : _furnitures)
        file << "Furniture " << char(34) << furniture->name << char(34) << " " << int(furniture->position.x) << " " << int(furniture->position.y) << "\n";
    if (_furnitures.size() > 0)
        file << "\n";


    if (_walls.size() > 0)
        file << "// WALLS\n";
    for (auto& wall : _walls)
        file << "Wall " << char(34) << wall->name << char(34) << " " << int(wall->position.x) << " " << int(wall->position.y) << "\n";
    if (_walls.size() > 0)
        file << "\n";


    file.close();

}

bool Building::isPart(GameObject* object) {
    if (object == nullptr)
        return false;

    for (auto& item : _items)
        if (object == item)
            return true;

    for (auto& furniture : _furnitures)
        if (object == furniture)
            return true;

    for (auto& wall : _walls)
        if (object == wall)
            return true;

    return false;
}

virtual void Building::draw()
{
    if (isSelected == true) {
        window->draw(*colliders[0]->shape);
    }

    if (player != nullptr && !playerInside()) {
        window->draw(sprite);
    }

    // TO-DO - OR

    if (player == nullptr) {
        if (GameObject::mouseIsHover == false) {
            window->draw(sprite);
        }
    }

}

std::vector < Building* > buildings;
Building* building = nullptr;

void addGameObjectsToMainLists() {
    doors.push_back(building->_door);
    gameObjects.push_back(building->_door);

    for (auto& item : building->_items) {
        itemsOnMap.push_back(item);
        gameObjects.push_back(item);
    }

    for (auto& furniture : building->_furnitures) {
        furnitures.push_back(furniture);
        gameObjects.push_back(furniture);
    }

    for (auto& wall : building->_walls) {
        walls.push_back(wall);
        gameObjects.push_back(wall);
    }
}

void removeGameObjectsFromMainLists() {
    // delete door
    auto itd = std::find(doors.begin(), doors.end(), building->_door);
    if (itd != doors.end())
        doors.erase(itd);

    auto god = std::find(gameObjects.begin(), gameObjects.end(), building->_door);
    if (god != gameObjects.end())
        gameObjects.erase(god);

    // delete building _items
    for (auto& item : building->_items) {
        auto it = std::find(itemsOnMap.begin(), itemsOnMap.end(), item);
        if (it != itemsOnMap.end())
            itemsOnMap.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), item);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    // delete building _furnitures
    for (auto& furniture : building->_furnitures) {
        auto it = std::find(furnitures.begin(), furnitures.end(), furniture);
        if (it != furnitures.end())
            furnitures.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), furniture);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }

    // delete building _walls
    for (auto& wall : building->_walls) {
        auto it = std::find(walls.begin(), walls.end(), wall);
        if (it != walls.end())
            walls.erase(it);

        auto go = std::find(gameObjects.begin(), gameObjects.end(), wall);
        if (go != gameObjects.end())
            gameObjects.erase(go);
    }
}

void createNewBuilding() {
    if (building) {
        removeGameObjectsFromMainLists();   // TO-DO
        delete building;
        building = nullptr;
    }

    clearAllMainListsOfGameObjects();
    building = new Building(16, 16);
    terrain = new Terrain(0, 0, building->size.x, building->size.y);
    cam->setPosition(building->size.x * 16 / 2 + 160, building->size.y * 16 / 2);

}

void loadBuildingFromFile(string filename) {
    if (building) {
        removeGameObjectsFromMainLists();   // TO-DO
        delete building;
        building = nullptr;
    }

    clearAllMainListsOfGameObjects();
    building = new Building(filename);
    terrain = new Terrain(0, 0, building->size.x, building->size.y);
    addGameObjectsToMainLists();    // TO-DO

}
