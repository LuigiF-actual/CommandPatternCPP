#pragma once

#include <iostream>
#include <array>

#include <raylib.h>
#include "TileGrid.hpp"
#include "PlayerMouse.hpp"
#include "Command.hpp"
#include "Config.hpp"
#include "KeyboardManager.hpp"


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
		checkKeyboard();
	}


	void checkMouseInput()
	{
		if ((m_PlMouse.isMouseClicked()) && (m_PlMouse.getMousePos().x < 1000))
		{
			Tile* p_Tile = mp_TileGrid->findTile(m_PlMouse.getMousePos());
			if (p_Tile)
			{
				cmd.execute(*p_Tile, m_CurrentColor);
			}
		}
		else
		{
			for (Tile& tile : m_PaintbrushColors)
			{
				if (CheckCollisionPointRec(m_PlMouse.getMousePos(), tile.body))
				{
					m_CurrentColor = tile.color;
					break;
				}
			}
		}
	}

	void checkKeyboard()
	{
		if (keyboard.ctrlZ())
		{
			cmd.undo();
 		}
		if (keyboard.ctrlY())
		{
			cmd.redo();
		}
	}

private:
	PlayerMouse m_PlMouse;
	KeyboardManager keyboard;

	Color m_CurrentColor = BLACK;

	TileGrid* mp_TileGrid;

	std::array<Tile, 4> m_PaintbrushColors;
	CommandManager cmd;
};
