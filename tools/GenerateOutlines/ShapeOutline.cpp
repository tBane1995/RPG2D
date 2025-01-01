#include "ShapeOutline.h"
#include <map>
#include <tuple>
#include <iostream>

void TShape::ConvertTileMapToPolyMap(int sx, int sy, int w, int h, float BlockSize, int Pitch)
{
	m_Edges.clear();

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			for (int j = 0; j < 4; ++j)
			{
				int i = (y + sy) * Pitch + (x + sx);
				m_Cells[i].m_EdgeExists[j] = false;
				m_Cells[i].m_EdgeId[j] = 0;
			}
		}
	}

	for (int y = 1; y < h - 1; ++y)
	{
		for (int x = 1; x < w - 1; ++x)
		{
			// Create some convenient indices
			int i = (y + sy) * Pitch + (x + sx); // This Cell
			int n = (y + sy - 1) * Pitch + (x + sx); // Northern Neighbour
			int s = (y + sy + 1) * Pitch + (x + sx); // Southern Neighbour
			int w = (y + sy) * Pitch + (x + sx - 1); // Western Neighbour
			int e = (y + sy) * Pitch + (x + sx + 1); // Eastern Neighbour

			// if this cell exists, check if it needs edges
			if (m_Cells[i].m_Exists)
			{
				// if this cell has no western neighbour, it needs a western edge
				if (!m_Cells[w].m_Exists)
				{
					// It can either extend it from its northern neighbour if they have
					// one, or it can start a new one
					if (m_Cells[n].m_EdgeExists[WEST])
					{
						// Northern neighbour has a western edge, so grow it downwards
						m_Edges[m_Cells[n].m_EdgeId[WEST]].m_EndY += BlockSize;
						m_Cells[i].m_EdgeId[WEST] = m_Cells[n].m_EdgeId[WEST];
					}
					else
					{
						// Northern neighbour does not have a western edge, so start a new one
						TShapeEdge Edge;
						Edge.m_StartX = (x + sx) * BlockSize;
						Edge.m_StartY = (y + sy) * BlockSize;
						Edge.m_EndX = Edge.m_StartX;
						Edge.m_EndY = Edge.m_StartY + BlockSize;
						int EdgeId = m_Edges.size();
						m_Edges.push_back(Edge);
						m_Cells[i].m_EdgeId[WEST] = EdgeId;
					}
					m_Cells[i].m_EdgeExists[WEST] = true;
				}

				// if this cell has no northern neighbour, it needs a northern edge
				if (!m_Cells[n].m_Exists)
				{
					// It can either extend it from its western neighbour if they have
					// one, or it can start a new one
					if (m_Cells[w].m_EdgeExists[NORTH])
					{
						// Western neighbour has a northern edge, so grow it right
						m_Edges[m_Cells[w].m_EdgeId[NORTH]].m_EndX += BlockSize;
						m_Cells[i].m_EdgeId[NORTH] = m_Cells[w].m_EdgeId[NORTH];
					}
					else
					{
						// Western neighbour does not have a northern edge, so start a new one
						TShapeEdge Edge;
						Edge.m_StartX = (x + sx) * BlockSize;
						Edge.m_StartY = (y + sy) * BlockSize;
						Edge.m_EndX = Edge.m_StartX + BlockSize;
						Edge.m_EndY = Edge.m_StartY;
						int EdgeId = m_Edges.size();
						m_Edges.push_back(Edge);
						m_Cells[i].m_EdgeId[NORTH] = EdgeId;
					}
					m_Cells[i].m_EdgeExists[NORTH] = true;
				}

				// if this cell has no eastern neighbour, it needs a eastern edge
				if (!m_Cells[e].m_Exists)
				{
					// It can either extend it from its northern neighbour if they have
					// one, or it can start a new one
					if (m_Cells[n].m_EdgeExists[EAST])
					{
						// Northern neighbour has a eastern edge, so grow it downwards
						m_Edges[m_Cells[n].m_EdgeId[EAST]].m_EndY += BlockSize;
						m_Cells[i].m_EdgeId[EAST] = m_Cells[n].m_EdgeId[EAST];
					}
					else
					{
						// Northern neighbour does not have a eastern edge, so start a new one
						TShapeEdge Edge;
						Edge.m_StartX = (x + sx + 1) * BlockSize;
						Edge.m_StartY = (y + sy) * BlockSize;
						Edge.m_EndX = Edge.m_StartX;
						Edge.m_EndY = Edge.m_StartY + BlockSize;
						int EdgeId = m_Edges.size();
						m_Edges.push_back(Edge);
						m_Cells[i].m_EdgeId[EAST] = EdgeId;
					}
					m_Cells[i].m_EdgeExists[EAST] = true;
				}

				// if this cell has no southern neighbour, it needs a southern edge
				if (!m_Cells[s].m_Exists)
				{
					// It can either extend it from its western neighbour if they have
					// one, or it can start a new one
					if (m_Cells[w].m_EdgeExists[SOUTH])
					{
						// Western neighbour has a northern edge, so grow it right
						m_Edges[m_Cells[w].m_EdgeId[SOUTH]].m_EndX += BlockSize;
						m_Cells[i].m_EdgeId[SOUTH] = m_Cells[w].m_EdgeId[SOUTH];
					}
					else
					{
						// Western neighbour does not have a southern edge, so start a new one
						TShapeEdge Edge;
						Edge.m_StartX = (x + sx) * BlockSize;
						Edge.m_StartY = (y + sy + 1) * BlockSize;
						Edge.m_EndX = Edge.m_StartX + BlockSize;
						Edge.m_EndY = Edge.m_StartY;
						int EdgeId = m_Edges.size();
						m_Edges.push_back(Edge);
						m_Cells[i].m_EdgeId[SOUTH] = EdgeId;
					}
					m_Cells[i].m_EdgeExists[SOUTH] = true;
				}
			}
		}
	}
}

void TShape::RemoveInnerEdges()
{
	std::map<int, std::pair<int, int>> OuterX; // MinX and MaxX values for given row
	std::map<int, std::pair<int, int>> OuterY;  // MinY and MaxY values for given column

	// Initialize all X values
	for (int column = 0; column < m_WorldWidth; ++column)
	{
		OuterX[column].first = INT_MAX; // MinX
		OuterX[column].second = -1; // MaxX
	}
	// Initialize all Y values
	for (int row = 0; row < m_WorldHeight; ++row)
	{
		OuterY[row].first = INT_MAX; // MinY
		OuterY[row].second = -1; // MaxY
	}

	// Traverse each column
	for (int x = 0; x < m_WorldWidth; ++x)
	{
		for (int y = 0; y < m_WorldHeight; ++y)
		{
			int i = y * m_WorldWidth + x;
			// if the cell has at least one edge
			if (m_Cells[i].m_Exists && (m_Cells[i].m_EdgeExists[0] || m_Cells[i].m_EdgeExists[1] || m_Cells[i].m_EdgeExists[2] || m_Cells[i].m_EdgeExists[3]))
			{
				// Update MinY and MaxY appropriately
				if (OuterY[x].first > y) OuterY[x].first = y;
				if (OuterY[x].second < y) OuterY[x].second = y;
				// Update MinX and MaxX appropriately
				if (OuterX[y].first > x) OuterX[y].first = x;
				if (OuterX[y].second < x) OuterX[y].second = x;
			}
		}
	}

	/*
	for (int row = 0; row < m_WorldWidth; ++row)
	{
		std::cout << "Row=" << row << ": MinX=" << OuterX[row].first << " MaxX=" << OuterX[row].second << std::endl;
	}
	// Initialize all Y values
	for (int column = 0; column < m_WorldHeight; ++column)
	{
		std::cout << "Column=" << column << ": MinY=" << OuterY[column].first << " MaxY=" << OuterY[column].second << std::endl;
	}
	*/

	// Traverse column again and remove inner edges (shapes/islands inside outside outline)
	for (int x = 0; x < m_WorldWidth; ++x)
	{
		for (int y = 0; y < m_WorldHeight; ++y)
		{
			int i = y * m_WorldWidth + x;
			// if the cell has at least one edge
			if (m_Cells[i].m_Exists && (m_Cells[i].m_EdgeExists[0] || m_Cells[i].m_EdgeExists[1] || m_Cells[i].m_EdgeExists[2] || m_Cells[i].m_EdgeExists[3]))
			{
				// if this is not outside outline the remove it, from polyline
				if ((x > OuterX[y].first && x < OuterX[y].second) && (y > OuterY[x].first && y < OuterY[x].second))
				{
					m_Cells[i].m_Exists = false;
					for (int j = 0; j < 4; ++j)
					{
						m_Cells[i].m_EdgeExists[j] = false;
					}
				}
			}
		}
	}
}

void TShape::SortCounterClockWise(std::vector<std::pair<int, int>>& Vertices, std::vector<int>& Indices)
{
	int MeanX = 0, SumX = 0, MinX = INT_MAX;
	int MeanY = 0, SumY = 0, MinY = INT_MAX;
	int Count = 0;
	for (int y = 0; y < m_WorldHeight; ++y)
	{
		for (int x = 0; x < m_WorldWidth; ++x)
		{
			int i = y * m_WorldWidth + x;
			// if the cell has at least one edge
			if (m_Cells[i].m_Exists && (m_Cells[i].m_EdgeExists[0] || m_Cells[i].m_EdgeExists[1] || m_Cells[i].m_EdgeExists[2] || m_Cells[i].m_EdgeExists[3]))
			{
				SumX += x;
				SumY += y;
				if (MinX == INT_MAX) MinX = x;
				if (MinY == INT_MAX) MinY = y;
				Count++;
			}
		}
	}

	MeanX = static_cast<int>(static_cast<float>(SumX) / static_cast<float>(Count));
	MeanY = static_cast<int>(static_cast<float>(SumY) / static_cast<float>(Count));
	Vertices.clear();
	Indices.clear();
	Vertices.emplace_back(MeanX, MeanY);
	Indices.push_back(-1);
	bool Exit = false;
	int x = MinX;
	int y = MinY;
	Vertices.emplace_back(MinX, MinY);
	Indices.push_back(MinY * m_WorldWidth + MinX);
	while (!Exit)
	{
		Exit = FindNonDuplicatePixelInOutline(x, y, Vertices, Indices);
	}
}

void TShape::RemoveIndices(std::vector<int>& Indices)
{
	// Traverse column again and remove inner edges (shapes/islands inside outside outline)
	// Skip first elem as this is central point that does not exists in PolyMap
	for (int i = 0; i < m_Cells.size(); ++i)
	{
		if (std::find(Indices.begin(), Indices.end(), i) == Indices.end())
		{
			m_Cells[i].m_Exists = false;
			for (int j = 0; j < 4; ++j)
			{
				m_Cells[i].m_EdgeExists[j] = false;
			}
		}
	}
}

bool TShape::FindNonDuplicatePixelInOutline(int& x, int& y, std::vector<std::pair<int, int>>& Vertices, std::vector<int>& Indices)
{
	bool Exit = false;

	while (!Exit)
	{
		int Current = y * m_WorldWidth + x;
		int West = (x < m_WorldWidth) ? (Current - 1) : -1;
		int South = (y < m_WorldHeight) ? (Current + m_WorldWidth) : -1;
		int East = (x > 0) ? (Current + 1) : -1;
		int North = (y > 0) ? (Current - m_WorldWidth) : -1;
		int SW = South - 1;
		int SE = South + 1;
		int NE = North + 1;
		int NW = North - 1;

		std::vector<std::tuple<int, int, int>> ProcessVertices;
		// First check Main Directions
		if (IsNonDuplicatePixelInOutline(x - 1, y, Indices)) // West
		{
			ProcessVertices.emplace_back(West, x - 1, y);
		}
		if (IsNonDuplicatePixelInOutline(x, y + 1, Indices)) // South
		{
			ProcessVertices.emplace_back(South, x, y + 1);
		}
		if (IsNonDuplicatePixelInOutline(x + 1, y, Indices)) // East
		{
			ProcessVertices.emplace_back(East, x + 1, y);
		}
		if (IsNonDuplicatePixelInOutline(x, y - 1, Indices)) // North
		{
			ProcessVertices.emplace_back(North, x, y - 1);
		}

		// if there is no main direction then check mixed ones
		if (ProcessVertices.size() == 0)
		{
			if (!HasPixelEdge(x - 1, y) && !HasPixelEdge(x, y + 1) && IsNonDuplicatePixelInOutline(x - 1, y + 1, Indices)) // South-West
			{
				ProcessVertices.emplace_back(SW, x - 1, y + 1);
			}
			if (!HasPixelEdge(x + 1, y) && !HasPixelEdge(x, y + 1) && IsNonDuplicatePixelInOutline(x + 1, y + 1, Indices)) // South-East
			{
				ProcessVertices.emplace_back(SE, x + 1, y + 1);
			}
			if (!HasPixelEdge(x + 1, y) && !HasPixelEdge(x, y - 1) && IsNonDuplicatePixelInOutline(x + 1, y - 1, Indices)) // North-East
			{
				ProcessVertices.emplace_back(NE, x + 1, y - 1);
			}
			if (!HasPixelEdge(x - 1, y) && !HasPixelEdge(x, y - 1) && IsNonDuplicatePixelInOutline(x - 1, y - 1, Indices)) // North-West
			{
				ProcessVertices.emplace_back(NE, x - 1, y - 1);
			}
		}

		if (ProcessVertices.size() == 1)
		{
			x = std::get<1>(ProcessVertices[0]);
			y = std::get<2>(ProcessVertices[0]);
			Vertices.emplace_back(x, y);
			Indices.push_back(std::get<0>(ProcessVertices[0]));
		}
		else if (ProcessVertices.size() > 1)
		{
			for (int i = 0; i < ProcessVertices.size(); ++i)
			{
				x = std::get<1>(ProcessVertices[i]);
				y = std::get<2>(ProcessVertices[i]);
				Vertices.emplace_back(x, y);
				Indices.push_back(std::get<0>(ProcessVertices[i]));
				Exit = FindNonDuplicatePixelInOutline(x, y, Vertices, Indices);
			}
		}
		else
		{
			Exit = true;
		}
	}

	return Exit;
}

bool TShape::IsNonDuplicatePixelInOutline(int x, int y, std::vector<int>& Indices)
{
	int i = y * m_WorldWidth + x;
	return i >= 0 && i < m_Cells.size()
		&&
		(m_Cells[i].m_Exists && (m_Cells[i].m_EdgeExists[0] || m_Cells[i].m_EdgeExists[1] || m_Cells[i].m_EdgeExists[2] || m_Cells[i].m_EdgeExists[3]))
		&&
		std::find(Indices.begin(), Indices.end(), i) == Indices.end();
}

bool TShape::HasPixelEdge(int x, int y)
{
	int i = y * m_WorldWidth + x;
	return i >= 0 && i < m_Cells.size()
		&&
		(m_Cells[i].m_Exists && (m_Cells[i].m_EdgeExists[0] || m_Cells[i].m_EdgeExists[1] || m_Cells[i].m_EdgeExists[2] || m_Cells[i].m_EdgeExists[3]))
		;
}
