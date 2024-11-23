#pragma once
#include "fillStyle/IFillStyle.h"
#include "lineStyle/ILineStyle.h"

#include <functional>

using LineStyleEnumerator = std::function<void(std::function<bool(ILineStylePtr)>)>;
using FillStyleEnumerator = std::function<void(std::function<bool(IFillStylePtr)>)>;