add_executable(HtmlEditor_tests
        tests/Menu_tests.cpp
        sources/Menu.cpp
        headers/Menu.h
        headers/IDocument.h
        headers/IUndoableEdit.h
        headers/IUndoableEdit_fwd.h
        headers/AbstractUndoableEdit.h
        headers/AbstractUndoableEdit.h
        sources/AbstractUndoableEdit.cpp
        headers/CompoundEdit.h
        sources/CompoundEdit.cpp
        headers/UndoManager.h
        sources/UndoManager.cpp
        tests/UndoManager_tests.cpp
)

target_link_libraries(HtmlEditor_tests PUBLIC catch2)
add_test(NAME HtmlEditor_tests COMMAND HtmlEditor_tests)

