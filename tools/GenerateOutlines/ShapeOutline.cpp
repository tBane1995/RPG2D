#include "ShapeOutline.h"

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