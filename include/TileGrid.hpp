#pragma once


#include <iostream>
#include <array>

#include <raylib.h>

struct Tile
{
	Color color;
	Rectangle body;
};

class TileGrid
{
public:
	TileGrid()
	{
		for (size_t row = 0; row < m_GridH; row++)
		{
			for (size_t column = 0; column < m_GridW; column++)
			{
				m_TileGrid.at(row * m_GridW + column).body = Rectangle{ float(column * 100 + 300), float(row * 100 + 200), 100, 100 };
				m_TileGrid.at(row * m_GridW + column).color = RED;
			}
		}
	}

	void draw() const
	{
		for (auto& tile : m_TileGrid)
		{
			DrawRectangleRec(tile.body, tile.color);
			DrawRectangleLinesEx(tile.body, 1.0f, BLACK);
		}
	}

	Tile& at(unsigned int column, unsigned int row)
	{
		return m_TileGrid.at(column * m_GridW + row); 
	}

	auto& getArr()
	{
		return m_TileGrid;
	}

	Tile* findTile(Vector2 position)
	{
		for (auto& tile : m_TileGrid)
		{
			if (CheckCollisionPointRec(position, tile.body))
			{
				return &tile;
			}
		}
		return nullptr;
	}

private:

	static constexpr unsigned int m_GridH = 4;
	static constexpr unsigned int m_GridW = 4;
	static constexpr unsigned int m_GridSize = m_GridH * m_GridW;

	std::array<Tile, m_GridSize > m_TileGrid;
};
