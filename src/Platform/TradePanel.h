#pragma once


enum class activeInventoryPanel { Left, Right };
extern activeInventoryPanel activePanel;

class InventoryPanel;

extern InventoryPanel* inventoryLeft;
extern InventoryPanel* inventoryRight;

void updateTradePanel();
void drawTradePanel();
