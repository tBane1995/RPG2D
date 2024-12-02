#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "GameObjects.h"

class TerrainPrefab;
class Shader;

class WaterPrefab : public GameObject {
public:
	short id;
	TerrainPrefab* terrain;
	Shader* shader;

	WaterPrefab(std::string name, short id, TerrainPrefab* terrain);

	virtual ~WaterPrefab() {

	}

	virtual void update(float dt) override;
	virtual void draw() override;
};

class Water : public sf::Drawable, public sf::Transformable {
public:
	int width, height;				// normal is a 16x16
	sf::Vector2i coords;			// multiply by 16x16
	sf::VertexArray vertexes;		// vertexes of water
	std::vector < short > tiles;	// tiles

	Water(int x, int y, int width, int height);

	void edit(int x, int y, short value = -1) {
		tiles[y*width + x] = value;
	}

	void edit(sf::Vector2f worldMousePosition, short value = -1);

	void update();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern std::vector < WaterPrefab* > waterGameObjects;
extern short countOfBasicWater;

void createWaterPrefabs();
