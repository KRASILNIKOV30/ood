#include "./UndoManager.h"
#include <cassert>

bool UndoManager::CanUndo() const
{
	if (m_inProgress)
	{
		const auto& edit = GetEditToBeUndone();
		return edit && edit->CanUndo();
	}

	return CompoundEdit::CanUndo();
}

bool UndoManager::CanRedo() const
{
	if (m_inProgress)
	{
		const auto& edit = GetEditToBeRedone();
		return edit && edit->CanRedo();
	}

	return CompoundEdit::CanRedo();
}

size_t UndoManager::GetCurrentEditIndex() const
{
	return m_indexOfNextAdd;
}

void UndoManager::Clear()
{
	m_edits.clear();
	m_indexOfNextAdd = 0;
}

IUndoableEditPtr UndoManager::GetEditToBeUndone() const
{
	assert(m_indexOfNextAdd <= m_edits.size());
	return (m_indexOfNextAdd > 0) ? m_edits[m_indexOfNextAdd - 1] : nullptr;
}

IUndoableEditPtr UndoManager::GetEditToBeRedone() const
{
	return (m_indexOfNextAdd < m_edits.size()) ? m_edits[m_indexOfNextAdd] : nullptr;
}

void UndoManager::UndoTo(const IUndoableEditPtr& edit)
{
	IUndoableEditPtr nextEdit;
	do
	{
		assert(m_indexOfNextAdd > 0 && m_indexOfNextAdd <= m_edits.size());
		nextEdit = m_edits[--m_indexOfNextAdd];
		nextEdit->Undo();
	} while (nextEdit != edit);
}

void UndoManager::RedoTo(const IUndoableEditPtr& edit)
{
	IUndoableEditPtr nextEdit;
	do
	{
		assert(m_indexOfNextAdd < m_edits.size());
		nextEdit = m_edits[m_indexOfNextAdd++];
		nextEdit->Redo();
	} while (nextEdit != edit);
}

void UndoManager::TrimEdits(const size_t from, const size_t to)
{
	assert(from <= to);
	assert(to <= m_edits.size());
	auto i = to;
	while (i > from)
	{
		const auto& edit = m_edits[--i];
		edit->Destroy();
	}
	m_edits.erase(m_edits.begin() + from, m_edits.begin() + to);
	if (m_indexOfNextAdd > to)
	{
		m_indexOfNextAdd -= (to - from);
	}
	else if (m_indexOfNextAdd >= from)
	{
		m_indexOfNextAdd = from;
	}
}

void UndoManager::DestroyImpl() noexcept
{
	m_indexOfNextAdd = 0;
	CompoundEdit::DestroyImpl();
}

void UndoManager::SetExecuted(const bool executed)
{
	if (!m_inProgress)
	{
		CompoundEdit::SetExecuted(executed);
	}
}

bool UndoManager::AddEditImpl(const IUndoableEditPtr& edit)
{
	if (m_indexOfNextAdd < m_edits.size())
	{
		m_edits.resize(m_indexOfNextAdd);
	}

	const auto addResult = CompoundEdit::AddEditImpl(edit);

	m_indexOfNextAdd = m_edits.size();

	if (m_edits.size() > HISTORY_LIMIT)
	{
		TrimEdits(0, 1);
	}

	return addResult;
}

void UndoManager::UndoImpl()
{
	if (m_inProgress)
	{
		auto edit = GetEditToBeUndone();

		// TODO: check that edit is not nullptr
		assert(edit);

		UndoTo(edit);
	}
	else
	{
		CompoundEdit::UndoImpl();
	}
}

void UndoManager::RedoImpl()
{
	if (m_inProgress)
	{
		auto edit = GetEditToBeRedone();
		// TODO: check that edit is not nullptr
		assert(edit);
		RedoTo(edit);
	}
	else
	{
		CompoundEdit::RedoImpl();
	}
}

void UndoManager::EndImpl()
{
	TrimEdits(m_indexOfNextAdd, m_edits.size());
}
