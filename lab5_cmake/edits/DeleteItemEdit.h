#include <utility>
#include "../document/Document.h"
#include "../documentItems/DocumentItem.h"
#include "../history/AbstractUndoableEdit.h"

class DeleteItemEdit final : public undo::AbstractUndoableEdit
{
public:
	DeleteItemEdit(DocumentItem  item, DocumentIterator const& iter, DocumentItems& items)
		: m_item(std::move(item))
		, m_iter(iter)
		, m_items(items)
	{}

	void UndoImpl() override
	{
		m_items.insert(m_iter, m_item);
	}

	void RedoImpl() override
	{
		m_items.erase(m_iter);
	}

private:
	DocumentItem m_item;
	DocumentIterator m_iter;
	DocumentItems& m_items;
};