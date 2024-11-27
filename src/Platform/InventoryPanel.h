#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

extern short itemsInRow;
extern short itemsInCol;
extern short slotSide;
extern short cursor;

class Inventory;

class InventoryPanel {
public:

	Inventory* inventory;
	sf::Vector2f position;
	short scroll;

	std::vector < Item* > sortedItems;
	std::vector < short > sortedItemsCounts;

	std::vector < sf::Sprite > slotsSprites;
	std::vector <sf::Sprite > itemsSprites;
	std::vector < sf::Text > counts;
	bool drawSelector;
	sf::Sprite selector;

	InventoryPanel(Inventory* inventory, float position_x = 0, float position_y = 0);

	void update(int cursor);

	void draw();
};

extern InventoryPanel* inventory;

extern sf::Sprite background;
extern sf::Sprite itemSprite;
extern sf::Text itemName;
extern sf::Text itemDescription;
extern bool drawItemStats;

void updateInventoryPanel();
void drawInventoryPanel();
void useItem();
