#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


bool areImagesEqual(sf::Image& img1, sf::Image& img2);

enum class TextureType { Single, Set };

struct TTextureEntry
{
	std::string Path;
	int x;
	int y;
	int Width;
	int Height;
};

class Texture {
public:
	std::string name;
	TextureType type;
	float cx, cy;	// coordinates of center on the texture

	Texture(std::string pathfile, TextureType type, float cx, float cy);

	Texture(std::string name, TextureType type) {
		this->name = name;
		this->type = type;
		cx = cy = 0;
	}
};

class SingleTexture : public Texture {
public:
	sf::Texture* texture;
	
	SingleTexture(std::string pathfile, float cx, float cy) : Texture(pathfile, TextureType::Single, cx, cy) {

		texture = new sf::Texture;
		texture->loadFromFile("assets/" + pathfile);
		texture->setRepeated(true);

		//cout << "load texture: " << pathfile << " as: " << name << endl;
	}

	SingleTexture(std::string name, sf::Image image) : Texture(name, TextureType::Single) {
		
		texture = new sf::Texture;
		texture->loadFromImage(image);
		texture->setRepeated(true);

		cx = texture->getSize().x / 2;
		cy = texture->getSize().y / 2;
		
		//cout << "load texture from set as: " << name << endl;
	}
private:
	bool TextureAllocated;
};

extern std::vector < SingleTexture* > singleTextures;
extern std::vector<TTextureEntry> TextureMapInfo;

void loadSingleTexture(std::string pathfile, float cx, float cy);
void loadTextureSets(std::string pathfile, int tile_width, int tile_height);
void loadTextures();
SingleTexture* getSingleTexture(std::string name);
TTextureEntry* getSingleTextureInfo(std::string name);
std::vector < SingleTexture* > getTexturesSet(std::string name);
void loadTextureMapInfo();
