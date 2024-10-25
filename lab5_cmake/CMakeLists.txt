add_executable(HtmlEditor_tests
        menu/Menu.h
        ./IDocument.h
        history/IUndoableEdit.h
        history/IUndoableEdit_fwd.h
        history/AbstractUndoableEdit.h
        history/AbstractUndoableEdit.h
        history/AbstractUndoableEdit.cpp
        history/CompoundEdit.h
        history/CompoundEdit.cpp
        history/UndoManager.h
        history/UndoManager.cpp
        tests/UndoManager_tests.cpp
        tests/Menu_tests.cpp
        fileStorage/FileEntity.h
        fileStorage/Path.h
        tests/FileStorage_tests.cpp
        fileStorage/FolderEntity.h
)

target_link_libraries(HtmlEditor_tests PUBLIC catch2)
add_test(NAME HtmlEditor_tests COMMAND HtmlEditor_tests)

