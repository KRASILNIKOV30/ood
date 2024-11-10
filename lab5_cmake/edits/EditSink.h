#pragma once
#include "ResizeImageEdit.h"
#include <functional>

using EditSink = std::function<void (IUndoableEditPtr)>;
