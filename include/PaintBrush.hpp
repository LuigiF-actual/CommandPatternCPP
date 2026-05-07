#pragma once

#include <raylib.h>
#include "TileGrid.hpp"

class PaintBrush
{
public:
	PaintBrush(TileGrid& p_TileGrid) 
		: mp_TileGrid(&p_TileGrid)
	{
		mp_TileGrid->at(0, 0).color = GREEN;
	}
	k
private:
	TileGrid* mp_TileGrid;
};
