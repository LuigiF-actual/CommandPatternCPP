#pragma once

#include <array>

#include <raylib.h>
#include "TileGrid.hpp"
#include "PlayerMouse.hpp"
#include "Config.hpp"


class PaintBrush
{

public:
	PaintBrush(TileGrid& p_TileGrid) 
		: mp_TileGrid(&p_TileGrid)
	{
		for (size_t i = 0; i < m_PaintbrushColors.size(); i++)
		{
			unsigned char mul = static_cast<unsigned char>(i*30); //Changes the collor of the tile every iteration of the loop

			m_PaintbrushColors.at(i).body = Rectangle{ Config::PALETTE_X ,(float)i * Config::TILE_SIZE + Config::GRID_OFFSET_X,Config::TILE_SIZE,Config::TILE_SIZE };
			m_PaintbrushColors.at(i).color = Color{ mul,mul,mul,255};
		}
	}
	
	void apply(unsigned int x, unsigned int y)
	{
		if (mp_TileGrid != nullptr)
		{
			
		}
	}

	void draw()
	{
		for (auto& tile : m_PaintbrushColors)
		{
			DrawRectangleRec(tile.body, tile.color);
		}
	}

	void update()
	{
		draw();
		checkMouseInput();
	}


	void checkMouseInput()
	{
		if (m_PlMouse.isMouseClicked())
		{
			Tile* p_Tile = mp_TileGrid->findTile(m_PlMouse.getMousePos());
			if (p_Tile)
			{
				p_Tile->color = m_CurrentColor;
			}
		}
	}

private:
	PlayerMouse m_PlMouse;

	Color m_CurrentColor = BLACK;

	TileGrid* mp_TileGrid;
	

	std::array<Tile, 4> m_PaintbrushColors;

};
