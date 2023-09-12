#pragma once
#include <functional>

using FlyStrategy = std::function<void(int flyCounter)>;
using Strategy = std::function<void()>;