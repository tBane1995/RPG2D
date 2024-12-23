﻿#pragma once

enum class toolType { Cursor, Brush, RectBrush, Rectangle, Elipse, Fill, Eraser, AddGameObject };

class TerrainPrefab;
class FloorPrefab;

extern TerrainPrefab* ter;
extern FloorPrefab* flo;

void generateBrush();
void generateRectBrush();
void generateRectangle();
void generateElipse();
