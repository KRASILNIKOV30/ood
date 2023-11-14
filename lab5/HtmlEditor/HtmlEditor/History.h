#pragma once
#include <deque>
#include "ICommand.h"

class History
{
public:
	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command);

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

