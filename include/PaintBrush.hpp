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
	PaintBrush(TileGrid& TileGrid_, TileGrid& ColorPallete_) 
		: m_TileGrid(TileGrid_),
		  m_ColorPallete(ColorPallete_)
	{	
		int tempCounter = 0;
		for (auto& tile : m_ColorPallete.getArr())
		{
			unsigned char mul = static_cast<unsigned char>(tempCounter * 30); //Changes the collor of the tile every iteration of the loop

			tile.body = Rectangle{ Config::PALETTE_X ,(float)tempCounter * Config::TILE_SIZE + Config::GRID_OFFSET_X,Config::TILE_SIZE,Config::TILE_SIZE };
			tile.color = Color{ mul,mul,mul,255 };
			tempCounter++;
		}
	}
	

	void update()
	{
		checkMouseInput();
		checkKeyboard();
	}


	void checkMouseInput()
	{
		if ((m_PlMouse.isMouseClicked()) && (m_PlMouse.getMousePos().x < m_ColorPallete.getArr().at(0).body.x))
		{
			Tile* p_Tile = m_TileGrid.findTile(m_PlMouse.getMousePos());
			if (p_Tile)
			{
				cmd.execute(*p_Tile, m_CurrentColor);
			}
		}
		else
		{
			for (Tile& tile : m_ColorPallete.getArr())
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

	TileGrid& m_TileGrid;
	TileGrid& m_ColorPallete;

	CommandManager cmd;
};
