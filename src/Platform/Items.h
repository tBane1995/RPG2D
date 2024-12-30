#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "GameObjects.h"


// TO-DO
enum class Attribute { ATTACK, DEFEND, HP, MP, HP_max, MP_max, STRENGTH, DEXTERITY, INTELLIGENCE };
enum class ItemType { herb, potion, food, weapon, helmet, armor, pants, shield, other };

class SingleTexture;

class Item {
public:
	std::string name;
	SingleTexture* texture;
	ItemType type;
	std::map < Attribute, short > attributes;		// TO-DO
	std::wstring description;

	Item(std::string name, ItemType type, std::wstring description);
};

extern std::vector < Item* > items;

Item* getItem(std::string location);
std::wstring getItemDescription(Item* item);

class ItemOnMap : public GameObject {
public:
	Item* item;
	sf::Sprite sprite;
	short count;
	bool collected;

	ItemOnMap(Item* item, float x, float y, short count = 1);
	ItemOnMap(GameObject* object, float x, float y);

	virtual ~ItemOnMap() {
	}

	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) override {

		
	}

	virtual void draw() override;

};

extern std::vector < ItemOnMap* > itemsOnMap;

void loadItems();


class Inventory {
public:
	std::vector < Item* > items;
	std::vector < short > counts;
	short id;

	Inventory() {

		this->id = -1;

		items.clear();
		counts.clear();
	}

	Inventory(short id) {

		this->id = id;

		items.clear();
		counts.clear();
	}

	void addItem(std::string location, short count = 1);
	void addItem(Item* item, short count = 1);
	bool hasItemsInInventory(std::string location, short count = 1);
	void removeItem(std::string name, short count = 1);
	void removeItem(Item* item, short count = 1);
};

extern std::vector < Inventory* > inventories;

void loadInventories();
Inventory* getInventory(short id);

class InventoryOnMap : public GameObject {
public:
	sf::Sprite sprite;
	bool collected;
	Inventory* inventory;

	InventoryOnMap(Inventory* inventory, float x, float y);
	
	virtual void setPosition(sf::Vector2f position) override {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual ~InventoryOnMap() override {

	}

	virtual void update(float dt) override {

	}

	virtual void draw() override;

};

extern std::vector < InventoryOnMap* > inventoriesOnMap;

void transferItem(Item* item, Inventory*& from, Inventory*& to);
