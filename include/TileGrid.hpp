#pragma once


#include <iostream>
#include <vector>

#include <raylib.h>



struct Tile
{
	Color color;
	Rectangle body;
};

class TileGrid
{
public:
	TileGrid(size_t columnNums, size_t rowNums, Vector2 gridOffSet)
		: m_GridW(columnNums),
		  m_GridH(rowNums),
		  m_GridOffSet(gridOffSet)
	{
		for (size_t row = 0; row < m_GridH; row++)
		{
			for (size_t column = 0; column < m_GridW; column++)
			{
				m_TileGrid.emplace_back(
					Tile
					{
						RED,
						Rectangle{float(column * m_TileSize.x + m_GridOffSet.x), float(row * m_TileSize.y + m_GridOffSet.y), m_TileSize.x, m_TileSize.y}

					}
				);
			}
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



	size_t m_GridH = 0;
	size_t m_GridW = 0;
	Vector2 m_GridOffSet = { 0.0f,0.0f };

	Vector2 m_TileSize = { 100.0f,100.0f };

	std::vector<Tile> m_TileGrid;
};

class TileRenderer
{
public:
	TileRenderer() = default;

	void draw(TileGrid& mp_GridToDraw) const
	{
		for (auto& tile : mp_GridToDraw.getArr())
		{
			DrawRectangleRec(tile.body, tile.color);
			DrawRectangleLinesEx(tile.body, 1.0f, BLACK);
		}
	}

};
