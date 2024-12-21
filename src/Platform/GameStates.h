#pragma once

enum class gameStates { start, controls, game, inventory, trade, dialogue, journal, stats };
extern gameStates gameState;
extern bool DebugMode;
