#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Platform/Window.h"
#include "Platform/Time.h"
#include "Platform/Camera.h"
#include "Platform/Mouse.h"
#include "Platform/Theme.h"

#include "Platform/Fonts.h"
#include "Platform/Textures.h"
#include "Platform/Shaders.h"
#include "Platform/Point.h"
#include "Platform/Collisions.h"

#include "Platform/GameStates.h"
#include "Platform/RenderParameters.h"     // bools of the render value for example renderCoords, renderBorders

#include "Platform/GameObjects.h"
#include "Platform/TerrainAndFloors.h"     // Terrain and Floors
#include "Platform/Water.h"
#include "Platform/Borders.h"
#include "Platform/Pathfinding.h"

#include "Platform/HitTexts.h"             // Hit texts
#include "Platform/Items.h"                // manage of items, itemsOnMap, Inventory and InventoryOnMap
#include "Platform/UnitStates.h"           // states for Units
#include "Platform/Player.h"               // manage of Player
#include "Platform/Units.h"                // manage of Units 
#include "Platform/Monsters.h"             // manage of Monster (dziobak, kolcorozec, bies, etc.)
#include "Platform/Natures.h"              // manage of Natures (tree, rock, boulder, etc.)
#include "Platform/Objects.h"              // manage of Objects (palisade, etc.)
#include "Platform/Furnitures.h"           // manage of Furnitures (barel, table, chest, etc.)
#include "Platform/FlatObjects.h"          // manage of Flat Objects (flat plants, flat rocks, etc.)
#include "Platform/Walls.h"                // manage of Walls 
#include "Platform/Doors.h"                // manage of Doors
#include "Platform/Plants.h"               // manage of Plants ( TO-DO - TEST )
#include "Platform/SmallObjects.h"         // manage of small objects (grass, etc.)
#include "Platform/Dialogues.h"            
#include "Platform/Character.h"            // manage of Characters
#include "Platform/Prefabs.h"              // manage of all prefabs
#include "Platform/BuildingsManager.h"     // manage of Buildings
#include "Platform/GameObjectsManager.h"   // manage of GameObjects - update/sort/render/
#include "Platform/Map.h"
#include "Platform/Quests.h"

#include "Platform/GUI.h"
#include "Platform/PrefabToPaint.h"
#include "Platform/BrushSizes.h"

#include "Platform/TextArea.h"
#include "Platform/EditableTextArea.h"
#include "Platform/Buttons.h"
#include "Platform/Scrollbar.h"
#include "Platform/Dialog.h"
#include "Platform/Message.h"
#include "Platform/Panel.h"
#include "Platform/ScrollableText.h"
#include "Platform/FileDialog.h"
#include "Platform/Confirm.h"
#include "Platform/CheckBox.h"

#include "Platform/Tips.h"
#include "Platform/MenuBar.h"
#include "Platform/Tools.h"
#include "Platform/Palette.h"
#include "Platform/Painter.h"

#include "Platform/ControlsPanel.h"
#include "Platform/InventoryPanel.h"
#include "Platform/TradePanel.h"
#include "Platform/JournalPanel.h"
#include "Platform/StatsPanel.h"


void initPlatform();
