#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


bool areImagesEqual(sf::Image& img1, sf::Image& img2);

enum class TextureType { Single, Set };

struct TTextureEntry
{
	std::string Path;
	int MapIndex;
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
	virtual ~Texture() {};
};

class SingleTexture : public Texture {
public:
	sf::Texture* texture;
	
	SingleTexture(std::string pathfile, float cx, float cy);
	SingleTexture(std::string name, sf::Image image);
	virtual ~SingleTexture();

	sf::Vector2u getSize();

	static void SetTextureForSprite(sf::Sprite* Sprite, SingleTexture* Texture);
	static void SetOriginForSprite(sf::Sprite* Sprite, SingleTexture* Texture, float DividerX = 2.0f, float DividerY = 2.0f);

private:
	bool TextureAllocated;
	int IndexToMapFiles;
	TTextureEntry* Info;
};

extern std::vector < SingleTexture* > singleTextures;
extern std::vector<TTextureEntry> TextureMapInfo;

void loadSingleTexture(std::string pathfile, float cx, float cy);
void loadTextureSets(std::string pathfile, int tile_width, int tile_height);
void loadTextures();
SingleTexture* getSingleTexture(std::string name);
TTextureEntry* getSingleTextureInfo(std::string name);
std::vector < SingleTexture* > getTexturesSet(std::string name);
void loadTextureMapInfo(std::string Fname, int Index);
