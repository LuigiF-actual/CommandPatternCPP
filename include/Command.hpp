#pragma once

#include <stack>
#include <memory>

#include <raylib.h>
#include "TileGrid.hpp"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class PaintTileCmd : public Command
{
public:
	PaintTileCmd(Tile& tile, Color newColor)
		: mp_ChangedTile(&tile),
		m_NewColor(newColor),
		m_OriginalColor(tile.color) 
	{
	}

	void execute() override
	{
		if (mp_ChangedTile)
		{
			mp_ChangedTile->color = m_NewColor;
		}
	}

	void undo() override
	{
		if(mp_ChangedTile)
		{
			mp_ChangedTile->color = m_OriginalColor;
		}
	}
private:
	Color m_OriginalColor = BLANK;
	Color m_NewColor = BLANK;
	Tile* mp_ChangedTile = nullptr;
};

class CommandManager
{
public:
	void execute(Tile& tile, Color color)
	{
		if (!ColorIsEqual(tile.color, color)) {
			auto paintCommand = std::make_unique<PaintTileCmd>(tile,color);

			paintCommand->execute();

			m_UndoStack.push(std::move(paintCommand));
		}
	}
	void undo()
	{
		if(!m_UndoStack.empty())
		{
			m_UndoStack.top()->undo();
			m_RedoStack.push(std::move(m_UndoStack.top()));
			m_UndoStack.pop();
		}
	}
	void redo()
	{
		if (!m_RedoStack.empty())
		{
			m_RedoStack.top()->execute();
			m_UndoStack.push(std::move(m_RedoStack.top()));
			m_RedoStack.pop();
		}
	}

private:
	std::stack<std::unique_ptr<Command>> m_UndoStack;
	std::stack<std::unique_ptr<Command>> m_RedoStack;
};