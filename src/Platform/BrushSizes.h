#pragma once

#include <vector>

extern std::vector<std::vector<std::vector<bool>>> brushes;
extern std::vector<std::vector<bool>> brush;

inline void setBrushSize(short size)
{
    brush = brushes[size];  // Przypisanie odpowiedniego pędzla
}

void coutBrush();
