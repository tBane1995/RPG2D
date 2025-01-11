#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

struct Triangle {
    sf::Vector2f a, b, c;
};

// Funkcja pomocnicza sprawdzająca, czy punkt P leży wewnątrz trójkąta ABC
bool isPointInTriangle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f P);
// Funkcja sprawdzająca, czy trójkąt (A, B, C) jest uchem
bool isEar(const std::vector<sf::Vector2f>& vertices, int i, int prev, int next);
// Funkcja do triangulacji wielokąta metodą Ear Clipping
std::vector<Triangle> triangulate(std::vector<sf::Vector2f>& vertices);

void Explode(char ExplodeChar, std::string String, std::vector<std::string>& Items);
