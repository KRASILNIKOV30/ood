#pragma once
#include <functional>

//Хранить счетчик внутри лямбда функции (Исправлено)
using FlyStrategy = std::function<void()>;
using QuackStrategy = std::function<void()>;
using DanceStrategy = std::function<void()>;