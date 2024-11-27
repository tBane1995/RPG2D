#include "Water.h"

WaterPrefab::WaterPrefab(string name, short id, TerrainPrefab* terrain) : GameObject(name) {
	type = GameObjectType::Water;
		
	this->terrain = terrain;
	this->id = id;
		
	if(terrain!=nullptr)
		texture = terrain->texture;

	shader = getShader("shaders/" + name);

	colliders[0]->shape->setPosition(position);
}


Water::Water(int x, int y, int width, int height) {

	coords.x = x;
	coords.y = y;

	this->width = width;
	this->height = height;

	tiles.resize(width * height, -1);

}

void Water::edit(sf::Vector2f worldMousePosition, short value = -1) {

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

std::vector < WaterPrefab* > waterGameObjects;
short countOfBasicWater;

void createWaterPrefabs() {

	waterGameObjects.clear();

	waterGameObjects.push_back(new WaterPrefab("empty", 0, nullptr));
	waterGameObjects.push_back(new WaterPrefab("palette_lake", 1, dynamic_cast<TerrainPrefab*>(terrainGameObjects[0])));
	countOfBasicWater = 2;

	/////////////////////////////////////////////////////
	for (int i = 0; i < countOfBasicWater; i++) {

		string shader_name = waterGameObjects[i + 1]->name;

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
