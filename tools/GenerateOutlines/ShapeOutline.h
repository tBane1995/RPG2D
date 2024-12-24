#pragma once
#include <vector>

struct TShapeEdge
{
	float m_StartX, m_StartY;
	float m_EndX, m_EndY;
};

// Constants for indexes of arrays in TShapeCell
constexpr const int NORTH = 0;
constexpr const int SOUTH = 1;
constexpr const int EAST = 2;
constexpr const int WEST = 3;

struct TShapeCell
{
	int m_EdgeId[4];
	bool m_EdgeExists[4];
	bool m_Exists = false;
};

class TShape
{
public:
	std::vector<TShapeCell> m_Cells;
	std::vector<TShapeEdge> m_Edges;

	int m_WorldWidth;
	int m_WorldHeight;
	int m_BlockSize;

	TShape(int Width, int Height, int BlockSize = 16) : m_WorldWidth(Width), m_WorldHeight(Height), m_BlockSize(BlockSize), m_Cells(Width * Height)
	{
	}

	~TShape()
	{
	}

	void ConvertTileMapToPolyMap(int sx, int sy, int w, int h, float BlockSize, int Pitch);
};
