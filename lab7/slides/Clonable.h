#pragma once
#include <memory>

// убрать лишние шаблоны
template <typename Base, typename CloneInterface, typename Impl, typename... Args>
class Clonable : public Base
{
public:
	// using Base::Base;
	Clonable(Args&&... args)
		: Base(std::forward<Args>(args)...)
	{}
	std::shared_ptr<CloneInterface> Clone()const override
	{
		return std::make_shared<Impl>(*static_cast<Impl const*>(this));
	}
};
