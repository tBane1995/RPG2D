﻿#include "Items.h"
#include "Window.h"
#include "Textures.h"
#include <iostream>

std::vector < Item* > items;

Item::Item(std::string name, itemType type, std::wstring description) {
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

	if (item->attributes[attribute::ATTACK])
		description += L"ATTACK " + std::to_wstring(item->attributes[attribute::ATTACK]) + L"\n";

	if (item->attributes[attribute::DEFEND])
		description += L"DEFEND " + std::to_wstring(item->attributes[attribute::DEFEND]) + L"\n";

	if (item->attributes[attribute::STRENGTH])
		description += L"STRENGTH " + std::to_wstring(item->attributes[attribute::STRENGTH]) + L"\n";

	if (item->attributes[attribute::DEXTERITY])
		description += L"DEXTERITY " + std::to_wstring(item->attributes[attribute::DEXTERITY]) + L"\n";

	if (item->attributes[attribute::INTELLIGENCE])
		description += L"INTELLIGENCE " + std::to_wstring(item->attributes[attribute::INTELLIGENCE]) + L"\n";

	if (item->attributes[attribute::HP])
		description += L"HP " + std::to_wstring(item->attributes[attribute::HP]) + L"\n";

	if (item->attributes[attribute::HP_max])
		description += L"HP_max " + std::to_wstring(item->attributes[attribute::HP_max]) + L"\n";

	if (item->attributes[attribute::MP])
		description += L"MP " + std::to_wstring(item->attributes[attribute::MP]) + L"\n";

	if (item->attributes[attribute::MP_max])
		description += L"MP_max " + std::to_wstring(item->attributes[attribute::MP_max]) + L"\n";

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

	item = new Item("items/axe", itemType::weapon, L"do rąbania głów");
	item->attributes[attribute::ATTACK] = 50;
	items.push_back(item);

	item = new Item("items/iron club", itemType::weapon, L"żelazna pałka");
	item->attributes[attribute::ATTACK] = 45;
	items.push_back(item);
	
	item = new Item("items/wide blade", itemType::weapon, L"szerokie ostrze");
	item->attributes[attribute::ATTACK] = 40;
	items.push_back(item);

	item = new Item("items/long sword", itemType::weapon, L"długi miecz");
	item->attributes[attribute::ATTACK] = 35;
	items.push_back(item);
	
	item = new Item("items/curved sword", itemType::weapon, L"zakrzywiony miecz");
	item->attributes[attribute::ATTACK] = 30;
	items.push_back(item);

	item = new Item("items/club", itemType::weapon, L"pałka");
	item->attributes[attribute::ATTACK] = 20;
	items.push_back(item);

	item = new Item("items/stone hammer", itemType::weapon, L"prymitywna broń");
	item->attributes[attribute::ATTACK] = 15;
	items.push_back(item);

	item = new Item("items/gladius", itemType::weapon, L"ceniony przez wojowników");
	item->attributes[attribute::ATTACK] = 15;
	items.push_back(item);

	item = new Item("items/sword", itemType::weapon, L"miecz");
	item->attributes[attribute::ATTACK] = 10;
	items.push_back(item);

	item = new Item("items/dagger", itemType::weapon, L"zdradziecka broń");
	item->attributes[attribute::ATTACK] = 8;
	items.push_back(item);

	item = new Item("items/hatchet", itemType::weapon, L"zazwyczaj służy do rąbania drewna");
	item->attributes[attribute::ATTACK] = 5;
	items.push_back(item);

	item = new Item("items/knife", itemType::weapon, L"zwykly nóż");
	item->attributes[attribute::ATTACK] = 3;
	items.push_back(item);


	item = new Item("items/wooden club", itemType::weapon, L"drewniana pałka");
	item->attributes[attribute::ATTACK] = 2;
	items.push_back(item);

	// SHIELDS

	item = new Item("items/shield", itemType::shield, L"zwyczajna tarcza");
	item->attributes[attribute::DEFEND] = 2;
	items.push_back(item);

	
	// ARMORS

	item = new Item("items/plate armor", itemType::armor, L"zbroja płytowa");
	item->attributes[attribute::DEFEND] = 20;
	items.push_back(item);

	item = new Item("items/chain mail", itemType::armor, L"kolczuga");
	item->attributes[attribute::DEFEND] = 10;
	items.push_back(item);

	item = new Item("items/skin jacket", itemType::armor, L"skórzana kurtka");
	item->attributes[attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item("items/wool shirt", itemType::armor, L"wełniana koszula");
	item->attributes[attribute::DEFEND] = 2;
	items.push_back(item);

	item = new Item("items/torn shirt", itemType::armor, L"podarta koszula");
	item->attributes[attribute::DEFEND] = 1;
	items.push_back(item);

	// PANTS

	item = new Item("items/chain mail pants", itemType::pants, L"nogawice kolcze");
	item->attributes[attribute::DEFEND] = 10;
	items.push_back(item);

	item = new Item("items/skin pants", itemType::pants, L"skórzane spodnie");
	item->attributes[attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item("items/wool pants", itemType::pants, L"wełniane spodnie");
	item->attributes[attribute::DEFEND] = 2;
	items.push_back(item);

	// HELMETS

	item = new Item("items/skin helmet", itemType::helmet, L"skórzany helm");
	item->attributes[attribute::DEFEND] = 2;
	items.push_back(item);

	item = new Item("items/wool hat", itemType::helmet, L"wełniana czapka");
	item->attributes[attribute::DEFEND] = 1;
	items.push_back(item);

	

	// HERBS
	
	item = new Item("items/health plant", itemType::herb, L"roślina życia");
	item->attributes[attribute::HP] = 50;
	items.push_back(item);

	item = new Item("items/mana plant", itemType::herb, L"roślina many");
	item->attributes[attribute::MP] = 50;
	items.push_back(item);

	item = new Item("items/health root", itemType::herb, L"korzeń życia");
	item->attributes[attribute::HP] = 25;
	items.push_back(item);

	item = new Item("items/health herb", itemType::herb, L"zioło życia");
	item->attributes[attribute::HP] = 15;
	items.push_back(item);

	item = new Item("items/mushroom", itemType::herb, L"grzyb");
	item->attributes[attribute::HP] = 5;
	items.push_back(item);

	// POTIONS
	item = new Item("items/potion", itemType::potion, L"mikstura");
	item->attributes[attribute::HP] = 30;
	items.push_back(item);

	// FOOD
	item = new Item("items/roasted meat", itemType::food, L"pieczone mięso");
	item->attributes[attribute::HP] = 20;
	items.push_back(item);

	item = new Item("items/raw meat", itemType::food, L"surowe mięso");
	item->attributes[attribute::HP] = 10;
	items.push_back(item);

	// OTHERS
	item = new Item("items/bone", itemType::other, L"kość");
	items.push_back(item);

	item = new Item("items/tooth", itemType::other, L"kieł zwierza");
	items.push_back(item);

	item = new Item("items/spike", itemType::other, L"kolec zwierza");
	items.push_back(item);

	item = new Item("items/wolf skin", itemType::other, L"skóra wilka");
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
