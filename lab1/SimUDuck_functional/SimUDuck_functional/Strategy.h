#pragma once
#include <functional>

//������� ������� ������ ������ ������� (����������)
using FlyStrategy = std::function<void()>;
using QuackStrategy = std::function<void()>;
using DanceStrategy = std::function<void()>;