#include "Textures.h"
#include <iostream>
#include <fstream>
#include <initializer_list>
#include "Utils.h"


bool areImagesEqual(sf::Image& img1, sf::Image& img2) {
	if (img1.getSize() != img2.getSize()) {
		return false; // Rozmiary są różne
	}

	// Porównaj każdy piksel
	for (unsigned int y = 0; y < img1.getSize().y; y++) {
		for (unsigned int x = 0; x < img1.getSize().x; x++) {
			if (img1.getPixel(x, y) != img2.getPixel(x, y)) {
				return false; // Piksele są różne
			}
		}
	}
	return true; // Wszystkie piksele są identyczne
}

Texture::Texture(std::string pathfile, TextureType type, float cx, float cy) {
	name = "";
	if (pathfile != "")
	{
		name = pathfile.substr(0, pathfile.size() - 4);
	}
	
	this->type = type;
	this->cx = cx;
	this->cy = cy;
}

SingleTexture::SingleTexture(std::string pathfile, float cx, float cy) : Texture(pathfile, TextureType::Single, cx, cy)
{
	TTextureEntry* Info = getSingleTextureInfo(pathfile);
	if (Info)
	{
		texture = singleTextures[Info->MapIndex]->texture;
		TextureAllocated = false;
		IndexToMapFiles = Info->MapIndex;
		this->Info = Info;
	}
	else
	{
		texture = new sf::Texture;
		texture->loadFromFile("assets/" + pathfile);
		texture->setRepeated(true);
		TextureAllocated = true;
		IndexToMapFiles = -1;
		this->Info = nullptr;
	}
	//cout << "load texture: " << pathfile << " as: " << name << endl;
}

SingleTexture::SingleTexture(std::string name, sf::Image image) : Texture(name, TextureType::Single)
{
	TTextureEntry* Info = getSingleTextureInfo(name);
	if (Info)
	{
		texture = singleTextures[Info->MapIndex]->texture;
		TextureAllocated = false;
		IndexToMapFiles = Info->MapIndex;
		this->Info = Info;
		cx = Info->Width / 2;
		cy = Info->Height / 2;
	}
	else
	{
		texture = new sf::Texture;
		texture->loadFromImage(image);
		texture->setRepeated(true);
		TextureAllocated = true;
		IndexToMapFiles = -1;
		this->Info = nullptr;
		cx = texture->getSize().x / 2;
		cy = texture->getSize().y / 2;
	}

	//cout << "load texture from set as: " << name << endl;
}

SingleTexture::~SingleTexture()
{
	if (TextureAllocated && texture)
	{
		delete texture;
		texture = nullptr;
	}
}

sf::Vector2u SingleTexture::getSize()
{
	if (Info)
	{
		return sf::Vector2u(Info->Width, Info->Height);
	}
	return texture->getSize();
}

sf::Vector2u SingleTexture::GetTexturePosInMap()
{
	if (Info)
	{
		return sf::Vector2u(Info->x, Info->y);
	}
	return sf::Vector2u(0, 0);
}

sf::Texture* SingleTexture::CutTexture()
{
	sf::Image Image, ImageMap;
	int Left, Top;
	int Width, Height;

	if (Info)
	{
		Left = Info->x;
		Top = Info->y;
		Width = Info->Width;
		Height = Info->Height;
	}
	else
	{
		Left = 0;
		Top = 0;
		Width = texture->getSize().x;
		Height = texture->getSize().y;
	}
	ImageMap = texture->copyToImage();
	Image.create(Width, Height, sf::Color::Transparent);
	Image.copy(ImageMap, 0, 0, sf::IntRect(Left, Top, Width, Height));
	sf::Texture* Tex = new sf::Texture();
	Tex->loadFromImage(Image);
	return Tex;
}

void SingleTexture::SetTextureForSprite(sf::Sprite* Sprite, SingleTexture* Texture)
{
	Sprite->setTexture(*Texture->texture);
	if (Texture->Info)
	{
		TTextureEntry* Info = Texture->Info;
		Sprite->setTextureRect(sf::IntRect(Info->x, Info->y, Info->Width, Info->Height));
	}
	else
	{
		Sprite->setTextureRect(sf::IntRect(0, 0, Texture->texture->getSize().x, Texture->texture->getSize().y));
	}
}

std::vector < SingleTexture* > singleTextures;

void loadSingleTexture(std::string pathfile, float cx, float cy) {
	singleTextures.push_back(new SingleTexture(pathfile, cx, cy));
}

void loadTextureSets(std::string pathfile, int tile_width, int tile_height)
{
	sf::Image image;
	image.loadFromFile("assets/" + pathfile + ".png");

	short image_width = image.getSize().x;
	short image_height = image.getSize().y;

	//cout << image_width << "x" << image_height << "\n";

	int counter = 0;
	int TexIndex = 0;
	// get All map textures to images
	for (short y = 0; y < image_height; y += tile_height)
		for (short x = 0; x < image_width; x += tile_width) {

			// create tile - fragment of texture
			sf::Image tile;
			tile.create(tile_width, tile_height);
			tile.copy(image, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

			// searching - exist doubles or no
			bool existed = false;

			existed = getSingleTextureInfo(pathfile + "_" + std::to_string(counter)) != nullptr;
			if (pathfile.find("tiles/") == 0 && counter == 4)
			{
				existed = true;
			}

			if (!existed)
			{
				if (pathfile.find("walls/") == 0)
				{
					std::initializer_list<short> Duplicates{ 2,3,6,7,8,9,10,11,13,14,15,16,18,19,22,25,26,27,28,29 };
					for (const short* it = Duplicates.begin(); it != Duplicates.end(); ++it)
					{
						if (*it == counter)
						{
							existed = true;
							break;
						}
					}
				}
			}
			/*
			existed = false;
			for (short i = 6; i < singleTextures.size(); i++)
			{
				if (singleTextures[i]->texture->getSize().x < 256)
				{
					sf::Image img = singleTextures[i]->texture->copyToImage();

					if (areImagesEqual(tile, img))
					{
						existed = true;
						img.saveToFile(pathfile + "_" + std::to_string(counter) + ".png");
						std::cout << "exists: " << pathfile + "_" + std::to_string(counter) + ".png" << std::endl;
						break;
					}
				}
			}
			*/

			// if no exist then add
			if (existed == false) {
				SingleTexture* new_texture = new SingleTexture(pathfile + "_" + std::to_string(TexIndex), tile);
				//tile.saveToFile(pathfile + "_" + std::to_string(TexIndex) + "_" + std::to_string(counter) + ".png");
				//cout << "created texture: " << pathfile + "_" + std::to_string(counter) << "\n";
				singleTextures.push_back(new_texture);
				TexIndex += 1;
			}
			counter += 1;
		}
}

void loadTextures()
{

	singleTextures.clear();
	TextureMapInfo.clear();

	// najpierw ladujemy mapy
	loadSingleTexture("TextureMapCharacter.png", 2048, 2048);
	loadTextureMapInfo("assets/TextureMapCharacter.txt", 0);

	loadSingleTexture("TextureMapCharacter1.png", 2048, 2048);
	loadTextureMapInfo("assets/TextureMapCharacter1.txt", 1);

	loadSingleTexture("TextureMapMain.png", 2048, 2048);
	loadTextureMapInfo("assets/TextureMapMain.txt", 2);

	loadSingleTexture("TextureMapMonsters.png", 2048, 2048);
	loadTextureMapInfo("assets/TextureMapMonsters.txt", 3);

	loadSingleTexture("TextureMapMonsters1.png", 2048, 2048);
	loadTextureMapInfo("assets/TextureMapMonsters1.txt", 4);

	loadSingleTexture("TextureMapMonsters2.png", 2048, 2048);
	loadTextureMapInfo("assets/TextureMapMonsters2.txt", 5);

	// NOISE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("noise.png", 256, 256);
	loadSingleTexture("noise2.png", 256, 256);
	loadSingleTexture("empty.png", 32, 32);

	// GUI ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("GUI/slot1.png", 40, 40);
	loadSingleTexture("GUI/slot2.png", 32, 32);
	loadSingleTexture("GUI/selector.png", 40, 40);

	loadSingleTexture("GUI/infoPanel.png", 300, 75);
	loadSingleTexture("GUI/bigPanel.png", 300, 200);

	loadSingleTexture("GUI/wideArrowUp1.png", 80, 20);
	loadSingleTexture("GUI/wideArrowUp2.png", 80, 20);
	loadSingleTexture("GUI/wideArrowDown1.png", 160, 18.5f);
	loadSingleTexture("GUI/wideArrowDown2.png", 160, 18.5f);

	// menu buttons textures
	loadSingleTexture("GUI/menuButtons/menuButton.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-terrain.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-floors.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-water.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-furnitures.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-walls.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-monsters.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-flat_objects.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-items.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-natures.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-smallObjects.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-objects.png", 32, 26);

	// small buttons textures
	loadSingleTexture("GUI/smallButtons/smallbutton.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowUp.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowDown.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowLeft.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowRight.png", 20, 20);

	// tool butttons textures
	loadSingleTexture("GUI/toolButtons/toolbutton.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-cursor.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-brush.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-rect_brush.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-increase.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-decrease.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-rectangle.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-elipse.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-fill.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-eraser.png", 20, 16);

	loadSingleTexture("GUI/spacebutton.png", 80, 20);

	loadSingleTexture("GUI/scrollbar/bar_bottom.png", 8, 8);
	loadSingleTexture("GUI/scrollbar/bar_top.png", 8, 8);
	loadSingleTexture("GUI/scrollbar/bar_center.png", 8, 8);
	loadSingleTexture("GUI/scrollbar/scroll_bottom.png", 8, 8);
	loadSingleTexture("GUI/scrollbar/scroll_top.png", 8, 8);
	loadSingleTexture("GUI/scrollbar/scroll_center.png", 8, 8);

	loadSingleTexture("GUI/checkbox/check.png", 8, 8);

	loadSingleTexture("GUI/hand.png", 8, 8);
	loadSingleTexture("GUI/grey_hand.png", 8, 8);
	loadSingleTexture("GUI/talk.png", 8, 8);

	loadSingleTexture("GUI/icons/MapEditor_small_ico.png", 15, 15);
	loadSingleTexture("GUI/icons/dictionary.png", 15, 15);
	loadSingleTexture("GUI/icons/file.png", 15, 15);
	loadSingleTexture("GUI/icons/empty.png", 15, 15);

	loadSingleTexture("GUI/character_menu/btn_info.png", 16, 16);
	loadSingleTexture("GUI/character_menu/btn_remove.png", 16, 16);
	loadSingleTexture("GUI/character_menu/btn_cancel.png", 16, 16);

	// TILES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("tiles/0_tileset.png", 0, 0);
	loadSingleTexture("tiles/tile_0_water.png", 32, 32);
	loadSingleTexture("tiles/tile_1_sands.png", 32, 32);
	loadSingleTexture("tiles/tile_2_grass.png", 32, 32);
	loadSingleTexture("tiles/tile_3_gravel.png", 32, 32);
	loadSingleTexture("tiles/tile_4_steps.png", 32, 32);
	loadSingleTexture("tiles/tile_5_highlands.png", 32, 32);
	loadSingleTexture("tiles/tile_6.png", 32, 32);
	loadSingleTexture("tiles/tile_7.png", 32, 32);
	loadSingleTexture("tiles/tile_8.png", 32, 32);
	loadSingleTexture("tiles/tile_9.png", 32, 32);
	loadSingleTexture("tiles/tile_10.png", 32, 32);

	loadTextureSets("tiles/set_0_water_sands", 64, 64);
	loadTextureSets("tiles/set_0_sands_water", 64, 64);
	loadTextureSets("tiles/set_1_sands_grass", 64, 64);
	loadTextureSets("tiles/set_1_grass_sands", 64, 64);
	loadTextureSets("tiles/set_2_grass_gravel", 64, 64);
	loadTextureSets("tiles/set_2_gravel_grass", 64, 64);

	// FLOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("floors/0_floorset.png", 0, 0);
	loadSingleTexture("floors/floor_0.png", 32, 32);
	loadSingleTexture("floors/floor_1.png", 32, 32);
	loadSingleTexture("floors/floor_2.png", 32, 32);
	loadSingleTexture("floors/floor_3.png", 32, 32);

	// NATURES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("natures/tree9.png", 129, 213);
	loadSingleTexture("natures/boulder1.png", 66, 72);
	loadSingleTexture("natures/boulder2.png", 65, 78);
	loadSingleTexture("natures/boulder3.png", 60, 80);
	loadSingleTexture("natures/column.png", 65, 85);
	loadSingleTexture("natures/driftwood.png", 59, 77);
	loadSingleTexture("natures/rock1.png", 32, 36);
	loadSingleTexture("natures/rock2.png", 32, 36);
	loadSingleTexture("natures/reed1.png", 32, 54);
	loadSingleTexture("natures/reed2.png", 32, 54);


	// SMALL OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("smallObjects/grass1.png", 33, 32);
	loadSingleTexture("smallObjects/grass2.png", 33, 32);
	loadSingleTexture("smallObjects/grass3.png", 33, 32);

	// OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("objects/palisade.png", 16, 112);
	loadSingleTexture("objects/palisade.png", 16, 112);
	loadSingleTexture("objects/stone_wall.png", 8, 56);
	loadSingleTexture("objects/great_stone_wall.png", 16, 112);
	loadSingleTexture("objects/great_gate.png", 32, 112);
	loadSingleTexture("objects/great_stone_gate.png", 64, 112);
	loadSingleTexture("objects/well.png", 64, 96);
	loadSingleTexture("objects/hunter_tent.png", 128, 175);
	loadSingleTexture("objects/log_with_saw.png", 64, 70);
	loadSingleTexture("objects/pile_of_wood.png", 64, 80);

	loadTextureSets("objects/brazier", 64, 64);

	// FLAT OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("flatObjects/stonepath1.png", 32, 32);
	loadSingleTexture("flatObjects/stonepath2.png", 32, 32);
	loadSingleTexture("flatObjects/sandspath1.png", 32, 32);
	loadSingleTexture("flatObjects/sandspath2.png", 32, 32);

	loadSingleTexture("flatObjects/herb1.png", 33, 32);
	loadSingleTexture("flatObjects/herb2.png", 33, 32);

	loadSingleTexture("flatObjects/small_rock1.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock1.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock2.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock3.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock4.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock5.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock6.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock7.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock8.png", 16, 16);

	// ITEMS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("items/bag.png", 28, 48);

	// WEAPONS
	loadSingleTexture("items/club.png", 32, 32);
	loadSingleTexture("items/knife.png", 32, 32);
	loadSingleTexture("items/hatchet.png", 32, 32);
	loadSingleTexture("items/sword.png", 32, 32);
	loadSingleTexture("items/dagger.png", 32, 32);
	loadSingleTexture("items/wooden club.png", 32, 32);
	loadSingleTexture("items/long sword.png", 32, 32);
	loadSingleTexture("items/curved sword.png", 32, 32);
	loadSingleTexture("items/wide blade.png", 32, 32);
	loadSingleTexture("items/gladius.png", 32, 32);
	loadSingleTexture("items/iron club.png", 32, 32);
	loadSingleTexture("items/axe.png", 32, 32);
	loadSingleTexture("items/stone hammer.png", 32, 32);

	// HELMET
	loadSingleTexture("items/skin helmet.png", 32, 32);
	loadSingleTexture("items/wool hat.png", 32, 32);

	// ARMORS
	loadSingleTexture("items/plate armor.png", 32, 32);
	loadSingleTexture("items/chain mail.png", 32, 32);
	loadSingleTexture("items/skin jacket.png", 32, 32);
	loadSingleTexture("items/torn shirt.png", 32, 32);
	loadSingleTexture("items/wool shirt.png", 32, 32);

	// PANTS
	loadSingleTexture("items/chain mail pants.png", 32, 32);
	loadSingleTexture("items/skin pants.png", 32, 32);
	loadSingleTexture("items/wool pants.png", 32, 32);

	// SHIELDS
	loadSingleTexture("items/shield.png", 32, 32);	// TO-DO to delete

	// HERBS
	loadSingleTexture("items/mana plant.png", 30, 50);
	loadSingleTexture("items/health herb.png", 32, 34);
	loadSingleTexture("items/health root.png", 31, 46);
	loadSingleTexture("items/health plant.png", 30, 44);
	loadSingleTexture("items/mushroom.png", 30, 44);

	// POTIONS
	loadSingleTexture("items/potion.png", 32, 32);

	// FOOD
	loadSingleTexture("items/raw meat.png", 32, 32);
	loadSingleTexture("items/roasted meat.png", 32, 32);

	// OTHERS
	loadSingleTexture("items/bone.png", 32, 32);
	loadSingleTexture("items/bone.png", 40, 40);
	loadSingleTexture("items/tooth.png", 32, 32);
	loadSingleTexture("items/spike.png", 32, 32);
	loadSingleTexture("items/wolf skin.png", 32, 32);

	// DOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("doors/wooden_door_0.png", 32, 32);
	loadSingleTexture("doors/wooden_door_1.png", 32, 32);
	loadSingleTexture("doors/wooden_door_2.png", 32, 32);
	loadSingleTexture("doors/wooden_door_3.png", 32, 32);

	loadSingleTexture("doors/wooden_gate_0.png", 64, 112);
	loadSingleTexture("doors/wooden_gate_1.png", 64, 112);
	loadSingleTexture("doors/wooden_gate_2.png", 64, 112);
	loadSingleTexture("doors/wooden_gate_3.png", 64, 112);

	// MONSTERS
	std::vector < std::string > monsters;

	monsters.push_back("dziobak");
	monsters.push_back("goblin");
	monsters.push_back("wilczur");
	monsters.push_back("jaszczur");
	monsters.push_back("niedzwiedz");
	monsters.push_back("szpon");
	monsters.push_back("kolcorozec");
	monsters.push_back("golem");
	monsters.push_back("troll");
	monsters.push_back("bies");

	for (auto& m : monsters) {
		for (short i = 0; i < 4; i++) {

			loadSingleTexture("monsters/" + m + ".png", 63, 87);

			loadSingleTexture("monsters/" + m + "/idleTop" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/idleRight" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/idleBottom" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/idleLeft" + std::to_string(i) + ".png", 63, 87);

			loadSingleTexture("monsters/" + m + "/attackTop" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/attackRight" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/attackBottom" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/attackLeft" + std::to_string(i) + ".png", 63, 87);

			loadSingleTexture("monsters/" + m + "/runTop" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/runRight" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/runBottom" + std::to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/runLeft" + std::to_string(i) + ".png", 63, 87);

		}
	}

	// FURNITURES
	loadSingleTexture("furnitures/table.png", 32, 32);
	loadSingleTexture("furnitures/table_alchemist.png", 32, 32);
	loadSingleTexture("furnitures/table_alchemist_2.png", 32, 32);
	loadSingleTexture("furnitures/table_herbalist.png", 32, 32);
	loadSingleTexture("furnitures/table_herbalist_2.png", 32, 32);
	loadSingleTexture("furnitures/bench.png", 32, 32);
	loadSingleTexture("furnitures/chest.png", 32, 32);
	loadSingleTexture("furnitures/wardrobe.png", 32, 50);
	loadSingleTexture("furnitures/bookshelf.png", 32, 50);
	loadSingleTexture("furnitures/furnace.png", 32, 50);
	loadSingleTexture("furnitures/bed.png", 32, 50);
	loadSingleTexture("furnitures/chair.png", 34, 38);
	loadSingleTexture("furnitures/barrel.png", 34, 38);
	loadSingleTexture("furnitures/lectern.png", 34, 38);


	// WALLS
	loadSingleTexture("walls/empty_wall.png", 16, 16);
	loadSingleTexture("walls/mud_wall.png", 16, 16);
	loadSingleTexture("walls/stone_wall.png", 16, 16);
	loadSingleTexture("walls/stone_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls/wooden_wall.png", 16, 16);
	loadSingleTexture("walls/brick_wall.png", 16, 16);
	loadSingleTexture("walls/mulch_wall.png", 16, 16);

	loadTextureSets("walls/set_mud_wall", 32, 32);
	loadTextureSets("walls/set_stone_wall", 32, 32);
	loadTextureSets("walls/set_wooden_wall", 32, 32);
	loadTextureSets("walls/set_brick_wall", 32, 32);
	loadTextureSets("walls/set_mulch_wall", 32, 32);


	// BODY SETS
	std::vector < std::string > bodySets;
	bodySets.clear();
	bodySets.push_back("boy-redhaired");		// face without beard
	bodySets.push_back("boy-blackhaired");		// face without beard
	bodySets.push_back("boy-brownhaired");		// face without beard

	bodySets.push_back("man-redhaired");		// face have a beard
	bodySets.push_back("man-blackhaired");		// face have a beard
	bodySets.push_back("man-brownhaired");		// face have a beard

	bodySets.push_back("woman-redhaired");		// face with long hair
	bodySets.push_back("woman-blackhaired");	// face with long hair
	bodySets.push_back("woman-brownhaired");	// face with long hair


	for (auto& set : bodySets) {
		for (short i = 0; i < 4; i++) {

			loadSingleTexture("sets/body/" + set + "/idleTop" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/idleRight" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/idleBottom" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/idleLeft" + std::to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/body/" + set + "/runTop" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/runRight" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/runBottom" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/runLeft" + std::to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/body/" + set + "/attackTop" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/attackRight" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/attackBottom" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/attackLeft" + std::to_string(i) + ".png", 32, 58);
		}
	}


	// ITEMS SETS
	std::vector < std::string > itemSets;
	itemSets.clear();
	itemSets.push_back("skin jacket");
	itemSets.push_back("skin pants");
	itemSets.push_back("skin helmet");
	itemSets.push_back("torn shirt");
	itemSets.push_back("wool shirt");
	itemSets.push_back("wool hat");
	itemSets.push_back("wool pants");
	itemSets.push_back("wooden club");
	itemSets.push_back("axe");
	itemSets.push_back("club");
	itemSets.push_back("iron club");
	itemSets.push_back("stone hammer");
	itemSets.push_back("sword");
	itemSets.push_back("long sword");
	itemSets.push_back("gladius");
	itemSets.push_back("wide blade");
	itemSets.push_back("knife");
	itemSets.push_back("dagger");
	itemSets.push_back("hatchet");
	itemSets.push_back("curved sword");
	itemSets.push_back("chain mail");
	itemSets.push_back("chain mail pants");
	itemSets.push_back("plate armor");
	itemSets.push_back("shield");



	for (auto& set : itemSets) {

		for (short i = 0; i < 4; i++) {

			loadSingleTexture("sets/items/" + set + "/idleTop" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/idleRight" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/idleBottom" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/idleLeft" + std::to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/items/" + set + "/runTop" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/runRight" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/runBottom" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/runLeft" + std::to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/items/" + set + "/attackTop" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/attackRight" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/attackBottom" + std::to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/attackLeft" + std::to_string(i) + ".png", 32, 58);

		}
	}

	// PLANTS
	loadSingleTexture("plants/grass_0.png", 32, 46);
	loadSingleTexture("plants/grass_1.png", 32, 46);

	// BUILDING PARTS
	loadSingleTexture("buildings/parts/logo.png", 16, 16);
	loadSingleTexture("buildings/parts/roof.png", 32, 32);
	loadSingleTexture("buildings/parts/window.png", 16, 16);
	loadSingleTexture("buildings/parts/window_2.png", 16, 16);
	loadSingleTexture("buildings/parts/bar.png", 32, 5);


}

SingleTexture* getSingleTexture(std::string name) {
	for (auto& t : singleTextures) {
		if (t->name == name) {
			return t;
		}
	}

	std::cout << __func__ << ": error - get Texture - Texture: \"" << name << "\" not exists\n";
	return nullptr;
}

TTextureEntry* getSingleTextureInfo(std::string name) {
	for (TTextureEntry& t : TextureMapInfo) {
		if (t.Path == name) {
			return &t;
		}
	}

	std::cout << __func__ << ": error - get Texture - Texture: \"" << name << "\" not exists\n";
	return nullptr;
}

std::vector < SingleTexture* > getTexturesSet(std::string name) {

	std::vector < SingleTexture* > texture_set;
	texture_set.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name) != std::string::npos)
			texture_set.push_back(tex);

	if (texture_set.empty())
		std::cout << "error - get Texture Set - Texture Set: \"" << name << "\" is empty\n";

	return texture_set;
}

std::vector<TTextureEntry> TextureMapInfo;
void loadTextureMapInfo(std::string Fname, int Index)
{
	std::ifstream ifs;
	ifs.open(Fname, std::ios::in || std::ios::beg);
	if (ifs)
	{
		while (!ifs.eof() && !ifs.fail())
		{
			TTextureEntry Item;
			std::string Line;
			std::getline(ifs, Line);
			size_t StartPos = 0UL;
			size_t Pos = Line.find(':');
			if (Pos != std::string::npos)
			{
				// pomijamy czlon "assets\" w nazwie, zeby zachowac zgodnosc z dotychczasowym kodem bez wiekszych zmian
				Item.Path = Line.substr(StartPos + 7, Pos - (StartPos + 7));
				std::vector<std::string> Arr;
				Explode(',', Line.substr(Pos + 1), Arr);
				if (Arr.size() == 4)
				{
					Item.MapIndex = Index;
					Item.x = std::atoi(Arr[0].c_str());
					Item.y = std::atoi(Arr[1].c_str());
					Item.Width = std::atoi(Arr[2].c_str());
					Item.Height = std::atoi(Arr[3].c_str());
					TextureMapInfo.push_back(Item);
				}
			}
		}
		ifs.close();
	}
}
