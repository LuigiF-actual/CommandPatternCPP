#pragma once

#include <raylib.h>
#include "TileGrid.hpp"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class Paint : public Command
{
public:
	void execute(Tile& tile, Color newColor)
	{
		m_StoredColor = newColor;
		tile.color = m_StoredColor;
	}
private:
	Color m_StoredColor = BLACK;
};