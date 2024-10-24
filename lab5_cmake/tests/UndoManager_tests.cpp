#include "../history/UndoManager.h"

#include <catch.hpp>

using namespace undo;

class TestEdit final : public AbstractUndoableEdit
{
public:
	explicit TestEdit(int& destroyCounter)
		: m_destroyCounter(destroyCounter)
	{
	}

	[[nodiscard]] bool IsExecuted() const override
	{
		return AbstractUndoableEdit::IsExecuted();
	}

	~TestEdit() override
	{
		++m_destroyCounter;
		AbstractUndoableEdit::~AbstractUndoableEdit();
	}

private:
	int& m_destroyCounter;
};

SCENARIO("history basic functions")
{
	GIVEN("An empty undo list")
	{
		UndoManager history;

		THEN("The undo list is empty")
		{
			CHECK_FALSE(history.CanRedo());
			CHECK_FALSE(history.CanUndo());
			CHECK(history.GetEditCount() == 0);
			CHECK(history.GetCurrentEditIndex() == 0);

			WHEN("add edit to history")
			{
				int destroyCounter;
				const auto edit = std::make_shared<TestEdit>(destroyCounter);
				CHECK(edit->IsExecuted());

				history.AddEdit(edit);

				THEN("the undo list is not empty")
				{
					CHECK_FALSE(history.CanRedo());
					CHECK(history.CanUndo());
					CHECK(history.GetEditCount() == 1);
					CHECK(history.GetCurrentEditIndex() == 1);
				}

				AND_WHEN("undo edit")
				{
					history.Undo();

					THEN("edit was undone")
					{
						CHECK(history.CanRedo());
						CHECK_FALSE(history.CanUndo());
						CHECK(history.GetEditCount() == 1);
						CHECK(history.GetCurrentEditIndex() == 0);
					}
				}
			}
		}
	}
}

SCENARIO("history remove unreachable edits")
{
	GIVEN("An empty undo list")
	{
		UndoManager history;

		WHEN("add 3 edits to history")
		{
			int destroyCounter = 0;
			history.AddEdit(std::make_shared<TestEdit>(destroyCounter));
			history.AddEdit(std::make_shared<TestEdit>(destroyCounter));
			history.AddEdit(std::make_shared<TestEdit>(destroyCounter));

			AND_WHEN("undo 2 edits")
			{
				history.Undo();
				history.Undo();

				THEN("edits was not destroyed")
				{
					CHECK(destroyCounter == 0);
					CHECK(history.GetEditCount() == 3);
				}

				WHEN("add another one edit")
				{
					history.AddEdit(std::make_shared<TestEdit>(destroyCounter));

					THEN("2 edits was destroyed")
					{
						CHECK(history.GetEditCount() == 2);
						CHECK(destroyCounter == 2);
					}
				}
			}
		}
	}
}

SCENARIO("test history limit")
{
	GIVEN("history with 5 edits")
	{
		UndoManager history;
		int destroyCounter = 0;
		history.AddEdit(std::make_shared<TestEdit>(destroyCounter));
		history.AddEdit(std::make_shared<TestEdit>(destroyCounter));
		history.AddEdit(std::make_shared<TestEdit>(destroyCounter));
		history.AddEdit(std::make_shared<TestEdit>(destroyCounter));
		history.AddEdit(std::make_shared<TestEdit>(destroyCounter));

		THEN("the undo list has 5 edits")
		{
			CHECK(history.GetEditCount() == 5);
		}

		WHEN("add another one edit")
		{
			history.AddEdit(std::make_shared<TestEdit>(destroyCounter));

			THEN("the undo list has 5 edits and")
			{
				CHECK(history.GetEditCount() == 5);
			}

			AND_THEN("one edit was destroyed")
			{
				CHECK(destroyCounter == 1);
			}
		}
	}
}