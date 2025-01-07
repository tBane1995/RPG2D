#include "Water.h"
#include "Window.h"
#include "Mouse.h"
#include "Shaders.h"
#include "TerrainAndFloors.h"

WaterPrefab::WaterPrefab(std::string name, short id, TerrainPrefab* terrain) : GameObject(name) {
	type = GameObjectType::Water;
		
	this->terrain = terrain;
	this->id = id;
		
	if(terrain!=nullptr)
		texture = terrain->texture;

	shader = getShader("shaders/" + name);

	colliders[0]->shape->setPosition(position);
}

void WaterPrefab::update() {
	sf::Vector2f position;
	position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
	position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
}

void WaterPrefab::draw() {
	window->draw(*colliders[0]->shape);
}


Water::Water(int x, int y, int width, int height) {

	coords.x = x;
	coords.y = y;

	this->width = width;
	this->height = height;

	tiles.resize(width * height, -1);

}

void Water::edit(sf::Vector2f worldMousePosition, short value) {

	short coord_x = (worldMousePosition.x - coords.x * 16) / 16;
	short coord_y = (worldMousePosition.y - coords.y * 16) / 16;

	if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
		return;

	tiles[coord_y*width + coord_x] = value;

}

void Water::update() {

	vertexes.clear();
	vertexes.setPrimitiveType(sf::Triangles);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (tiles[y * width + x] > -1)
			{
				sf::Vertex tile[6];

				int coord_x = (coords.x + x);
				int coord_y = (coords.y + y);

				tile[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				tile[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				tile[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				tile[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				tile[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				tile[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

				short tu = (short(coord_x * tileSide) % 64) + ((tiles[y * width + x]) * 64);
				short tv = (short(coord_y * tileSide) % 64);

				tile[0].texCoords = sf::Vector2f(tu, tv);
				tile[1].texCoords = sf::Vector2f(tu + tileSide, tv);
				tile[2].texCoords = sf::Vector2f(tu, tv + tileSide);
				tile[3].texCoords = sf::Vector2f(tu, tv + tileSide);
				tile[4].texCoords = sf::Vector2f(tu + tileSide, tv);
				tile[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);

				for (int i = 0; i < 6; i++)
				{
					vertexes.append(tile[i]);
				}
			}
		}
	}
}

void Water::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &(*getSingleTexture("tiles/0_tileset")->texture);
	states.shader = &(*getShader("shaders/lake")->shader);
	target.draw(vertexes, states);
	/*
	static bool first = true;
	if (first)
	{
		first = false;
		std::cout << "WATER! " << "coords: " << coords.x << "x" << coords.y << "    size: " << width << "x" << height << std::endl;
		for (int i = 0; i < vertexes.getVertexCount(); i += 6)
		{
			std::cout << "WATER! " << i / 6 << ":  Tile: " << tiles[i / 6] << ":  ";
			std::cout << "(" << vertexes[i + 0].position.x << ", " << vertexes[i + 0].position.y << "  tex: " << vertexes[i + 0].texCoords.x << "x" << vertexes[i + 0].texCoords.y << ")  ";
			std::cout << "(" << vertexes[i + 1].position.x << ", " << vertexes[i + 1].position.y << "  tex: " << vertexes[i + 1].texCoords.x << "x" << vertexes[i + 1].texCoords.y << ")  ";
			std::cout << "(" << vertexes[i + 2].position.x << ", " << vertexes[i + 2].position.y << "  tex: " << vertexes[i + 2].texCoords.x << "x" << vertexes[i + 2].texCoords.y << ")  ";
			std::cout << "(" << vertexes[i + 3].position.x << ", " << vertexes[i + 3].position.y << "  tex: " << vertexes[i + 3].texCoords.x << "x" << vertexes[i + 3].texCoords.y << ")  ";
			std::cout << "(" << vertexes[i + 4].position.x << ", " << vertexes[i + 4].position.y << "  tex: " << vertexes[i + 4].texCoords.x << "x" << vertexes[i + 4].texCoords.y << ")  ";
			std::cout << "(" << vertexes[i + 5].position.x << ", " << vertexes[i + 5].position.y << "  tex: " << vertexes[i + 5].texCoords.x << "x" << vertexes[i + 5].texCoords.y << ")";
			std::cout << std::endl;
		}
	}
	*/
}


std::vector < WaterPrefab* > waterGameObjects;
short countOfBasicWater;

void createWaterPrefabs() {

	waterGameObjects.clear();

	waterGameObjects.push_back(new WaterPrefab("empty", 0, nullptr));
	waterGameObjects.push_back(new WaterPrefab("palette_lake", 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[0])));
	countOfBasicWater = 2;

	/////////////////////////////////////////////////////
	for (int i = 0; i < countOfBasicWater; i++) {

		std::string shader_name = waterGameObjects[i + 1]->name;

		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 0])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 1])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 2])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 3])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 4])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 5])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 6])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 7])));

		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 8])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 9])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 10])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 11])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 12])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 13])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 14])));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i + 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[countOfBasicTerrain + i * 16 + 15])));

	}


}
