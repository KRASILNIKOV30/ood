#pragma once
#include "history/IUndoableEdit.h"
#include <functional>

using EditSink = std::function<void(undo::IUndoableEditPtr)>;