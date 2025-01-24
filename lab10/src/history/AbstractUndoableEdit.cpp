#include "./AbstractUndoableEdit.h"


using namespace std;

bool AbstractUndoableEdit::CanUndo() const
{
	return IsExecuted() && m_isAlive;
}

bool AbstractUndoableEdit::CanRedo() const
{
	return !IsExecuted() && m_isAlive;
}

bool AbstractUndoableEdit::CanBeReplaced() const
{
	return m_canBeReplaced;
}

void AbstractUndoableEdit::Undo()
{
	if (!CanUndo())
	{
		throw std::logic_error("Can't undo");
	}
	SetExecuted(false);
	UndoImpl();
}

void AbstractUndoableEdit::Redo()
{
	if (!CanRedo())
	{
		throw std::logic_error("Can't redo");
	}
	SetExecuted(true);
	SetReplaceable(false);
	RedoImpl();
}

void AbstractUndoableEdit::Destroy() noexcept
{
	if (m_isAlive)
	{
		m_isAlive = false;
		DestroyImpl();
	}
}

bool AbstractUndoableEdit::AddEdit(const IUndoableEditPtr& edit)
{
	if (!m_isAlive)
	{
		throw std::logic_error("UndoableEdit has been destroyed");
	}
	return AddEditImpl(edit);
}

bool AbstractUndoableEdit::ReplaceEdit(const IUndoableEditPtr& edit)
{
	if (!m_isAlive)
	{
		throw std::logic_error("UndoableEdit has been destroyed");
	}
	if (m_canBeReplaced && edit->CanBeReplaced())
	{
		return ReplaceEditImpl(edit);
	}
	return false;
}

std::string AbstractUndoableEdit::GetName() const
{
	return m_name;
}

void AbstractUndoableEdit::SetReplaceable(bool canBeReplaced)
{
	m_canBeReplaced = canBeReplaced;
}

void AbstractUndoableEdit::UndoImpl()
{
}

void AbstractUndoableEdit::RedoImpl()
{
}

void AbstractUndoableEdit::DestroyImpl() noexcept
{
}

bool AbstractUndoableEdit::AddEditImpl(const IUndoableEditPtr& /*edit*/)
{
	return false;
}

bool AbstractUndoableEdit::ReplaceEditImpl(const IUndoableEditPtr& /*edit*/)
{
	return false;
}

bool AbstractUndoableEdit::IsExecuted() const
{
	return m_executed;
}

void AbstractUndoableEdit::SetExecuted(bool executed)
{
	m_executed = executed;
}

void AbstractUndoableEdit::SetName(const std::string& name)
{
	m_name = name;
}

