add_executable(HtmlEditor
        menu/Menu.h
        document/IDocument.h
        history/IUndoableEdit.h
        history/IUndoableEdit_fwd.h
        history/AbstractUndoableEdit.h
        history/AbstractUndoableEdit.h
        history/AbstractUndoableEdit.cpp
        history/CompoundEdit.h
        history/CompoundEdit.cpp
        history/UndoManager.h
        history/UndoManager.cpp
        fileStorage/FileEntity.h
        fileStorage/Path.h
        fileStorage/FolderEntity.h
        fileStorage/FileRef.h
        fileStorage/FileStorage.h
        documentItems/DocumentItem.h
        documentItems/IParagraph.h
        documentItems/IImage.h
        documentItems/Image.h
        documentItems/Paragraph.h
        edits/EditSink.h
        edits/ResizeImageEdit.h
        edits/ReplaceTextEdit.h
        document/Document.cpp
        document/Document.h
        document/IDocument.h
        edits/InsetrtItemEdit.h
        edits/DeleteItemEdit.h
        edits/ChangeTitleEdit.h
        main.cpp
)

add_executable(HtmlEditor_tests
        menu/Menu.h
        document/IDocument.h
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
        fileStorage/FileRef.h
        fileStorage/FileStorage.h
        documentItems/DocumentItem.h
        documentItems/IParagraph.h
        documentItems/IImage.h
        documentItems/Image.h
        documentItems/Paragraph.h
        edits/EditSink.h
        edits/ResizeImageEdit.h
        tests/Edits_tests.cpp
        edits/ReplaceTextEdit.h
        document/Document.cpp
        document/Document.h
        document/IDocument.h
        edits/InsetrtItemEdit.h
        edits/DeleteItemEdit.h
        edits/ChangeTitleEdit.h
        tests/Document_tests.cpp
)

target_link_libraries(HtmlEditor_tests PUBLIC catch2)
add_test(NAME HtmlEditor_tests COMMAND HtmlEditor_tests)

