#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "GameObjects.h"
#include "Textures.h"

extern float tileSide;

class SingleTexture;

class TerrainPrefab : public GameObject {
public:
	short id;

	TerrainPrefab(std::string name, short id);

	virtual ~TerrainPrefab() { 
		
	}

	virtual void update(float dt);
	virtual void draw();
	
};

class FloorPrefab : public GameObject {
public:
	short id;

	FloorPrefab(std::string name, short id);

	virtual ~FloorPrefab() { 
		
	}

	virtual void update(float dt);
	virtual void draw();

};

class Terrain : public sf::Drawable, public sf::Transformable {
public:
	short width, height;		// normal is a 16x16
	sf::Vector2i coords;		// multiply by 16x16
	sf::VertexArray vertexes;	// vertexes of tiles
	SingleTexture* tileset;		// main texture
	std::vector<short> tiles;	// tile values

	Terrain(short x, short y, short width, short height);

	void edit(short x, short y, short value);
	void edit(sf::Vector2f worldMousePosition, short value);


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw tiles - terrain
		states.transform *= getTransform();
		states.texture = tileset->texture;	// TO-DO
		target.draw(vertexes, states);
		static bool first = true;
		if (first)
		{
			first = false;
			std::cout << "coords: " << coords.x << "x" << coords.y << "    size: " << width << "x" << height << std::endl;
			for (int i = 0; i < vertexes.getVertexCount(); i += 4)
			{
				std::cout << i / 4 << ":  Tile: " << tiles[i/4] << ":  ";
				std::cout << "(" << vertexes[i + 0].position.x << ", " << vertexes[i + 0].position.y << "  tex: " << vertexes[i + 0].texCoords.x << "x" << vertexes[i + 0].texCoords.y << ")  ";
				std::cout << "(" << vertexes[i + 1].position.x << ", " << vertexes[i + 1].position.y << "  tex: " << vertexes[i + 1].texCoords.x << "x" << vertexes[i + 1].texCoords.y << ")  ";
				std::cout << "(" << vertexes[i + 2].position.x << ", " << vertexes[i + 2].position.y << "  tex: " << vertexes[i + 2].texCoords.x << "x" << vertexes[i + 2].texCoords.y << ")  ";
				std::cout << "(" << vertexes[i + 3].position.x << ", " << vertexes[i + 3].position.y << "  tex: " << vertexes[i + 3].texCoords.x << "x" << vertexes[i + 3].texCoords.y << ")";
				std::cout << std::endl;
			}
		}
	}
};


class Floors : public sf::Drawable, public sf::Transformable {
public:
	short width, height;
	sf::Vector2i coords;

	sf::VertexArray vertexes;
	SingleTexture* floorset;	// TO-DO

	std::vector < short > floors;

	Floors(short x, short y, short width, short height);

	void edit(short x, short y, short value);
	void edit(sf::Vector2f worldMousePosition, short value);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		states.transform *= getTransform();
		states.texture = &*floorset->texture;	// TO-DO
		target.draw(vertexes, states);


	}
};

extern Terrain* terrain;

extern std::vector < TerrainPrefab* > terrainGameObjects;
extern std::vector < FloorPrefab* > floorGameObjects;

extern short countOfBasicTerrain;

void createTerrainPrefabs();
void createFloorsPrefabs();
