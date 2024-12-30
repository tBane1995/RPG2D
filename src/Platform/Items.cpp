﻿#include "Items.h"
#include "Window.h"
#include "Textures.h"
#include <iostream>

std::vector < Item* > items;

Item::Item(std::string name, ItemType type, std::wstring description) {
	this->name = name;
	this->type = type;
	this->description = description;
	this->texture = getSingleTexture(name);
}

Item* getItem(std::string location) {
	for (auto& item : items) {
		if (item->name == location)
			return item;
	}

	return nullptr;
}

std::wstring getItemDescription(Item* item) {
	
	std::wstring description = item->description + L"\n\n";

	if (item->attributes[Attribute::ATTACK])
		description += L"ATTACK " + std::to_wstring(item->attributes[Attribute::ATTACK]) + L"\n";

	if (item->attributes[Attribute::DEFEND])
		description += L"DEFEND " + std::to_wstring(item->attributes[Attribute::DEFEND]) + L"\n";

	if (item->attributes[Attribute::STRENGTH])
		description += L"STRENGTH " + std::to_wstring(item->attributes[Attribute::STRENGTH]) + L"\n";

	if (item->attributes[Attribute::DEXTERITY])
		description += L"DEXTERITY " + std::to_wstring(item->attributes[Attribute::DEXTERITY]) + L"\n";

	if (item->attributes[Attribute::INTELLIGENCE])
		description += L"INTELLIGENCE " + std::to_wstring(item->attributes[Attribute::INTELLIGENCE]) + L"\n";

	if (item->attributes[Attribute::HP])
		description += L"HP " + std::to_wstring(item->attributes[Attribute::HP]) + L"\n";

	if (item->attributes[Attribute::HP_max])
		description += L"HP_max " + std::to_wstring(item->attributes[Attribute::HP_max]) + L"\n";

	if (item->attributes[Attribute::MP])
		description += L"MP " + std::to_wstring(item->attributes[Attribute::MP]) + L"\n";

	if (item->attributes[Attribute::MP_max])
		description += L"MP_max " + std::to_wstring(item->attributes[Attribute::MP_max]) + L"\n";

	return description;
}



ItemOnMap::ItemOnMap(Item* item, float x, float y, short count) : GameObject(item->name, x, y, 16, 8, 32, true, ColliderType::Elipse) {
	type = GameObjectType::ItemOnMap;
	this->item = item;
	this->count = count;
	collected = false;

	texture = getSingleTexture(item->name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(x, y);
	sprite.setScale(0.75f, 0.75f);
}

ItemOnMap::ItemOnMap(GameObject* object, float x, float y) : GameObject(object, x, y) {
	type = GameObjectType::ItemOnMap;
	this->item = getItem(object->name);
	this->count = 1;
	collected = false;

	texture = getSingleTexture(item->name);
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);
	sprite.setScale(0.75f, 0.75f);
}

void ItemOnMap::draw() {

	window->draw(sprite);

	if (mouseIsHover) {

		GameObject::draw();
		window->draw(textname);
	}
}

std::vector < ItemOnMap* > itemsOnMap;

void loadItems() {

	items.clear();
	Item* item;
	
	// WEAPONS

	item = new Item("items/axe", ItemType::weapon, L"do rąbania głów");
	item->attributes[Attribute::ATTACK] = 50;
	items.push_back(item);

	item = new Item("items/iron club", ItemType::weapon, L"żelazna pałka");
	item->attributes[Attribute::ATTACK] = 45;
	items.push_back(item);
	
	item = new Item("items/wide blade", ItemType::weapon, L"szerokie ostrze");
	item->attributes[Attribute::ATTACK] = 40;
	items.push_back(item);

	item = new Item("items/long sword", ItemType::weapon, L"długi miecz");
	item->attributes[Attribute::ATTACK] = 35;
	items.push_back(item);
	
	item = new Item("items/curved sword", ItemType::weapon, L"zakrzywiony miecz");
	item->attributes[Attribute::ATTACK] = 30;
	items.push_back(item);

	item = new Item("items/club", ItemType::weapon, L"pałka");
	item->attributes[Attribute::ATTACK] = 20;
	items.push_back(item);

	item = new Item("items/stone hammer", ItemType::weapon, L"prymitywna broń");
	item->attributes[Attribute::ATTACK] = 15;
	items.push_back(item);

	item = new Item("items/gladius", ItemType::weapon, L"ceniony przez wojowników");
	item->attributes[Attribute::ATTACK] = 15;
	items.push_back(item);

	item = new Item("items/sword", ItemType::weapon, L"miecz");
	item->attributes[Attribute::ATTACK] = 10;
	items.push_back(item);

	item = new Item("items/dagger", ItemType::weapon, L"zdradziecka broń");
	item->attributes[Attribute::ATTACK] = 8;
	items.push_back(item);

	item = new Item("items/hatchet", ItemType::weapon, L"zazwyczaj służy do rąbania drewna");
	item->attributes[Attribute::ATTACK] = 5;
	items.push_back(item);

	item = new Item("items/knife", ItemType::weapon, L"zwykly nóż");
	item->attributes[Attribute::ATTACK] = 3;
	items.push_back(item);


	item = new Item("items/wooden club", ItemType::weapon, L"drewniana pałka");
	item->attributes[Attribute::ATTACK] = 2;
	items.push_back(item);

	// SHIELDS

	item = new Item("items/shield", ItemType::shield, L"zwyczajna tarcza");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);

	
	// ARMORS

	item = new Item("items/plate armor", ItemType::armor, L"zbroja płytowa");
	item->attributes[Attribute::DEFEND] = 20;
	items.push_back(item);

	item = new Item("items/chain mail", ItemType::armor, L"kolczuga");
	item->attributes[Attribute::DEFEND] = 10;
	items.push_back(item);

	item = new Item("items/skin jacket", ItemType::armor, L"skórzana kurtka");
	item->attributes[Attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item("items/wool shirt", ItemType::armor, L"wełniana koszula");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);

	item = new Item("items/torn shirt", ItemType::armor, L"podarta koszula");
	item->attributes[Attribute::DEFEND] = 1;
	items.push_back(item);

	// PANTS

	item = new Item("items/chain mail pants", ItemType::pants, L"nogawice kolcze");
	item->attributes[Attribute::DEFEND] = 10;
	items.push_back(item);

	item = new Item("items/skin pants", ItemType::pants, L"skórzane spodnie");
	item->attributes[Attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item("items/wool pants", ItemType::pants, L"wełniane spodnie");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);

	// HELMETS

	item = new Item("items/skin helmet", ItemType::helmet, L"skórzany helm");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);

	item = new Item("items/wool hat", ItemType::helmet, L"wełniana czapka");
	item->attributes[Attribute::DEFEND] = 1;
	items.push_back(item);

	

	// HERBS
	
	item = new Item("items/health plant", ItemType::herb, L"roślina życia");
	item->attributes[Attribute::HP] = 50;
	items.push_back(item);

	item = new Item("items/mana plant", ItemType::herb, L"roślina many");
	item->attributes[Attribute::MP] = 50;
	items.push_back(item);

	item = new Item("items/health root", ItemType::herb, L"korzeń życia");
	item->attributes[Attribute::HP] = 25;
	items.push_back(item);

	item = new Item("items/health herb", ItemType::herb, L"zioło życia");
	item->attributes[Attribute::HP] = 15;
	items.push_back(item);

	item = new Item("items/mushroom", ItemType::herb, L"grzyb");
	item->attributes[Attribute::HP] = 5;
	items.push_back(item);

	// POTIONS
	item = new Item("items/potion", ItemType::potion, L"mikstura");
	item->attributes[Attribute::HP] = 30;
	items.push_back(item);

	// FOOD
	item = new Item("items/roasted meat", ItemType::food, L"pieczone mięso");
	item->attributes[Attribute::HP] = 20;
	items.push_back(item);

	item = new Item("items/raw meat", ItemType::food, L"surowe mięso");
	item->attributes[Attribute::HP] = 10;
	items.push_back(item);

	// OTHERS
	item = new Item("items/bone", ItemType::other, L"kość");
	items.push_back(item);

	item = new Item("items/tooth", ItemType::other, L"kieł zwierza");
	items.push_back(item);

	item = new Item("items/spike", ItemType::other, L"kolec zwierza");
	items.push_back(item);

	item = new Item("items/wolf skin", ItemType::other, L"skóra wilka");
	items.push_back(item);

}


void Inventory::addItem(std::string location, short count) {

	for (short i = 0; i < items.size(); i++)
		if (items[i]->name == location) {
			counts[i] += count;
			return;
		}

	items.push_back(getItem(location));
	counts.push_back(count);
}

void Inventory::addItem(Item* item, short count) {

	bool addedItem = false;

	for (short i = 0; i < items.size(); i++)
		if (items[i] == item) {
			counts[i] += count;
			return;
		}

	items.push_back(item);
	counts.push_back(count);
}

bool Inventory::hasItemsInInventory(std::string location, short count) {
	for (short i = 0; i < items.size(); i++)
		if (items[i]->name == location) {
				
			if (counts[i] >= count)
				return true;
			else
				return false;
		}

	return false;
}

void Inventory::removeItem(std::string name, short count) {
	for (short i = 0; i < items.size(); i++)
		if (items[i]->name == name) {
			counts[i] -= count;
		}

	// delete zeros (count)
	std::vector < Item* > newItems;
	std::vector < short > newCounts;

	for (short i = 0; i < items.size(); i++) {
		if (counts[i] > 0) {
			newItems.push_back(items[i]);
			newCounts.push_back(counts[i]);
		}
				
	}

	items = newItems;
	counts = newCounts;
}

void Inventory::removeItem(Item* item, short count) {
	for (short i = 0; i < items.size(); i++)
	{
		if (items[i] == item) {
			counts[i] -= count;
		}
	}

	// delete zeros (count)
	std::vector < Item* > newItems;
	std::vector < short > newCounts;

	for (short i = 0; i < items.size(); i++) {
		if (counts[i] > 0) {
			newItems.push_back(items[i]);
			newCounts.push_back(counts[i]);
		}
	}

	items = newItems;
	counts = newCounts;
}

std::vector < Inventory* > inventories;

void loadInventories() {
	inventories.clear();

	Inventory* inventory;

	inventory = new Inventory(0);
	inventory->addItem("items/roasted meat", 3);
	inventories.push_back(inventory);

	inventory = new Inventory(1);
	inventory->addItem("items/wooden club");
	inventory->addItem("items/wool shirt");
	inventory->addItem("items/wool pants");				
	inventories.push_back(inventory);
}

Inventory* getInventory(short id) {

	for (auto& i : inventories)
	{
		if (i->id == id)
		{
			return i;
		}
	}

	std::cout << "Inventory id=" << id << " not exists!\n";
	return nullptr;

}


InventoryOnMap::InventoryOnMap(Inventory* inventory, float x, float y) : GameObject("inventory", x, y, 16, 8, 16, true, ColliderType::Elipse) {
	type = GameObjectType::InventoryOnMap;
	texture = getSingleTexture("items/bag");
	sprite = sf::Sprite();
	SingleTexture::SetTextureForSprite(&sprite, texture);
	sprite.setOrigin(texture->cx, texture->cy);
	sprite.setPosition(position);
	sprite.setScale(0.75f, 0.75f);
	collected = false;
	this->inventory = inventory;
}

void InventoryOnMap::draw() {

	if (mouseIsHover)
	{
		GameObject::draw();
	}
	window->draw(sprite);

}

std::vector < InventoryOnMap* > inventoriesOnMap;

void transferItem(Item* item, Inventory*& from, Inventory*& to) {

	from->removeItem(item);
	to->addItem(item);
}
