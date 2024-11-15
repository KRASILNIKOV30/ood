#pragma once
#include "fillStyle/IFillStyle.h"
#include "lineStyle/ILineStyle.h"

#include <functional>

using LineStyleEnumerator = std::function<void(std::function<bool(ILineStyle*)>)>;
using FillStyleEnumerator = std::function<void(std::function<bool(IFillStyle*)>)>;