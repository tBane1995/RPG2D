﻿#include "Tools.h"
#include "Prefabs.h"
#include "PrefabToPaint.h"
#include "Mouse.h"
#include "BrushSizes.h"
#include "TerrainAndFloors.h"
#include "Water.h"
#include <iostream>

TerrainPrefab* ter = nullptr;
FloorPrefab* flo = nullptr;

void generateBrush() {
    int baseX = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
    int baseY = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

    int brushHalfWdt = brush.size() / 2;
    int brushHalfHgh = brush.size() / 2;

    for (int y = 0; y < brush.size(); y++) {
        for (int x = 0; x < brush[y].size(); x++) {
            if (brush[y][x] == true) {

                int xx = baseX + (x - brushHalfWdt) * tileSide;
                int yy = baseY + (y - brushHalfHgh) * tileSide;

                if (prefabToPaint->type == GameObjectType::Terrain) {
                    ter = new TerrainPrefab(prefabToPaint->name, static_cast<TerrainPrefab*>(prefabToPaint)->id);
                    ter->position = sf::Vector2f(xx + 8, yy + 8);
                    ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    prefabsToPaint.push_back(ter);
                }

                if (prefabToPaint->type == GameObjectType::Floor) {
                    flo = new FloorPrefab(prefabToPaint->name, static_cast<FloorPrefab*>(prefabToPaint)->id);
                    flo->position = sf::Vector2f(xx + 8, yy + 8);
                    flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    prefabsToPaint.push_back(flo);
                }

                if (prefabToPaint->type == GameObjectType::Water) {
                    WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                    wat->position = sf::Vector2f(xx + 8, yy + 8);
                    wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    prefabsToPaint.push_back(wat);
                }

            }
        }
    }
}

void generateRectBrush() {
    int baseX = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
    int baseY = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

    int brushHalfWdt = brush.size() / 2;
    int brushHalfHgh = brush.size() / 2;

    for (int y = 0; y < brush.size(); y++) {
        for (int x = 0; x < brush[y].size(); x++) {

            int xx = baseX + (x - brushHalfWdt) * tileSide;
            int yy = baseY + (y - brushHalfHgh) * tileSide;

            if (prefabToPaint->type == GameObjectType::Terrain) {
                TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, dynamic_cast<TerrainPrefab*>(prefabToPaint)->id);
                ter->position = sf::Vector2f(xx + 8, yy + 8);
                ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                prefabsToPaint.push_back(ter);
            }

            if (prefabToPaint->type == GameObjectType::Floor) {
                FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                flo->position = sf::Vector2f(xx + 8, yy + 8);
                flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                prefabsToPaint.push_back(flo);
            }

            if (prefabToPaint->type == GameObjectType::Water) {
                WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                wat->position = sf::Vector2f(xx + 8, yy + 8);
                wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                prefabsToPaint.push_back(wat);
            }

            

        }
    }
}

void generateRectangle() {
    int start_x = std::min((startWorldMousePosition.x / tileSide), (worldMousePosition.x / tileSide));
    int start_y = std::min((startWorldMousePosition.y / tileSide), (worldMousePosition.y / tileSide));
    int end_x = std::max(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
    int end_y = std::max(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));

    std::cout << "start: " << start_x << ", " << start_y << "\n";
    std::cout << "end: " << end_x << ", " << end_y << "\n";
    std::cout << "\n\n";

    for (int y = start_y; y < end_y; y++)
        for (int x = start_x; x < end_x; x++) {
            int xx = x * int(tileSide);
            int yy = y * int(tileSide);

            if (prefabToPaint->type == GameObjectType::Terrain) {
                TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, dynamic_cast<TerrainPrefab*>(prefabToPaint)->id);
                ter->position = sf::Vector2f(xx + 8, yy + 8);
                ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                prefabsToPaint.push_back(ter);
            }

            if (prefabToPaint->type == GameObjectType::Floor) {
                FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                flo->position = sf::Vector2f(xx + 8, yy + 8);
                flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                prefabsToPaint.push_back(flo);
            }

            if (prefabToPaint->type == GameObjectType::Water) {
                WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                wat->position = sf::Vector2f(xx + 8, yy + 8);
                wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                prefabsToPaint.push_back(wat);
            }

        }

}

void generateElipse() {
    int start_x = std::min((startWorldMousePosition.x / tileSide), (worldMousePosition.x / tileSide));
    int start_y = std::min((startWorldMousePosition.y / tileSide), (worldMousePosition.y / tileSide));
    int end_x = std::max(ceil(startWorldMousePosition.x / tileSide), ceil(worldMousePosition.x / tileSide));
    int end_y = std::max(ceil(startWorldMousePosition.y / tileSide), ceil(worldMousePosition.y / tileSide));

    int width = end_x - start_x;
    int height = end_y - start_y;

    // Środek pędzla
    float centerX = (start_x + end_x) / 2.0f;
    float centerY = (start_y + end_y) / 2.0f;

    // Półosie elipsy
    float a = width / 2.0f;
    float b = height / 2.0f;

    // Generowanie elipsy w oparciu o pędzel
    for (int y = start_y; y < end_y; ++y) {
        for (int x = start_x; x < end_x; ++x) {
            // Obliczanie pozycji w stosunku do środka
            float dx = (x - centerX) / a;
            float dy = (y - centerY) / b;

            // Sprawdź, czy pędzel na tej pozycji ma wartość 1
            if (dx * dx + dy * dy <= 0.995f) {
                int xx = x * int(tileSide);
                int yy = y * int(tileSide);

                if (prefabToPaint->type == GameObjectType::Terrain) {
                    TerrainPrefab* ter = new TerrainPrefab(prefabToPaint->name, dynamic_cast<TerrainPrefab*>(prefabToPaint)->id);
                    ter->position = sf::Vector2f(xx + 8, yy + 8);
                    ter->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    ter->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    prefabsToPaint.push_back(ter);
                }

                if (prefabToPaint->type == GameObjectType::Floor) {
                    FloorPrefab* flo = new FloorPrefab(prefabToPaint->name, dynamic_cast<FloorPrefab*>(prefabToPaint)->id);
                    flo->position = sf::Vector2f(xx + 8, yy + 8);
                    flo->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    flo->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    prefabsToPaint.push_back(flo);
                }

                if (prefabToPaint->type == GameObjectType::Water) {
                    WaterPrefab* wat = new WaterPrefab(prefabToPaint->name, dynamic_cast<WaterPrefab*>(prefabToPaint)->id, dynamic_cast<WaterPrefab*>(prefabToPaint)->terrain);
                    wat->position = sf::Vector2f(xx + 8, yy + 8);
                    wat->colliders[0]->shape->setFillColor(sf::Color(129, 48, 48, 128));
                    wat->colliders[0]->shape->setPosition(sf::Vector2f(xx, yy));
                    prefabsToPaint.push_back(wat);
                }


            }
        }
    }
}
