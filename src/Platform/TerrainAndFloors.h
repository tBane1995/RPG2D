#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
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
	SingleTexture* tileset;			// main texture
	std::vector < short > tiles;// tile values

	Terrain(short x, short y, short width, short height);

	void edit(short x, short y, short value);
	void edit(sf::Vector2f worldMousePosition, short value);


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw tiles - terrain
		states.transform *= getTransform();
		states.texture = &*tileset->texture;	// TO-DO
		target.draw(vertexes, states);
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
