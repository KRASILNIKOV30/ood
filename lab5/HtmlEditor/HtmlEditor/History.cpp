#include <cassert>
#include "History.h"
#include "ICommand.h"

namespace
{
	constexpr int HISTORY_MAX_SIZE = 10;
}

bool History::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool History::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void History::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute(); // может выбросить исключение
		--m_nextCommandIndex;
	}
}

void History::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute(); // может выбросить исключение
		++m_nextCommandIndex;
	}
}

void History::AddAndExecuteCommand(ICommandPtr&& command)
{
	if (m_nextCommandIndex < m_commands.size()) // Не происходит расширения истории команд
	{
		command->Execute(); // может бросить исключение
		++m_nextCommandIndex;
		m_commands.resize(m_nextCommandIndex); // исключение выброшено не будет, т.к. размер <= текущему
		m_commands.back() = std::move(command);
	}
	else // будет происходить расширение истории команд
	{
		assert(m_nextCommandIndex == m_commands.size());
		// резервируем место по добавляемую команду
		m_commands.emplace_back(nullptr); // может выбросить исключение, но мы еще ничего не трогали

		try
		{
			command->Execute(); // может выбросить исключение
			// заменяем команду-заглушку
			m_commands.back() = std::move(command); // не бросает исключений
			if (m_nextCommandIndex == HISTORY_MAX_SIZE)
			{
				m_commands.pop_front();
			}
			else
			{
				++m_nextCommandIndex; // теперь можно обновить индекс следующей команды
			}
		}
		catch (...)
		{
			// удаляем заглушку, т.к. команда не исполнилась
			m_commands.pop_back(); // не бросает исключений
			// перевыбрасываем пойманное исключение вверх (кем бы оно ни было),
			// т.к. команду выполнить не смогли
			throw;
		}
	}
}