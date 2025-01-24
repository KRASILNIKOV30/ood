#pragma once
#include <functional>
#include <gsl/gsl>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

template <typename T>
concept ItemWithId = requires(T const& t) {
	{
		t.GetId()
	} -> std::same_as<std::string>;
};

template <class T>
	requires ItemWithId<T>
class Repository
{
public:
	using PtrType = std::shared_ptr<T>;
	using ConstPtrType = const PtrType;

	[[nodiscard]] size_t GetSize() const;
	void Insert(T const& item, std::optional<size_t> position = std::nullopt);
	void Insert(std::shared_ptr<T> const& item, std::optional<size_t> position = std::nullopt);
	std::optional<size_t> Remove(std::string const& id);
	void ForEach(std::function<bool(ConstPtrType item)> callback, bool reverse = false) const;

	std::optional<ConstPtrType> Find(std::string const& id) const;
	std::optional<PtrType> Find(std::string const& id);
	ConstPtrType Get(std::string const& id) const;
	PtrType Get(std::string const& id);
	ConstPtrType Get(size_t position) const;
	PtrType Get(size_t position);

private:
	void IncreaseIndexes(size_t insertedAt);
	void DecreaseIndexes(size_t removedAt);

private:
	using ItemsMap = std::unordered_map<std::string, size_t>;
	using Items = std::vector<std::shared_ptr<T>>;

	ItemsMap m_itemsMap;
	Items m_items;
};

template <class T>
	requires ItemWithId<T>
size_t Repository<T>::GetSize() const
{
	return m_items.size();
}

template <class T>
	requires ItemWithId<T>
void Repository<T>::Insert(T const& item, const std::optional<size_t> position)
{
	Insert(std::make_shared<T>(item), position);
}

template <class T>
	requires ItemWithId<T>
void Repository<T>::Insert(std::shared_ptr<T> const& item, const std::optional<size_t> position)
{
	bool commit = false;
	const auto pos = position.value_or(GetSize());
	const auto it = m_items.insert(m_items.begin() + pos, item);

	auto finalizer = gsl::finally([&] {
		if (!commit)
		{
			m_items.erase(it);
		}
	});

	if (!m_itemsMap.emplace(it->get()->GetId(), pos).second)
	{
		return;
	}
	commit = true;
	IncreaseIndexes(pos);
}

template <class T>
	requires ItemWithId<T>
std::optional<size_t> Repository<T>::Remove(std::string const& id)
{
	const auto& mapIt = m_itemsMap.find(id);
	if (mapIt == m_itemsMap.end())
	{
		return std::nullopt;
	}
	const auto position = mapIt->second;
	m_items.erase(m_items.begin() + position);
	m_itemsMap.erase(mapIt);

	DecreaseIndexes(position);

	return position;
}

template <class T>
	requires ItemWithId<T>
void Repository<T>::ForEach(std::function<bool(ConstPtrType item)> callback, bool reverse) const
{
	if (reverse)
	{
		for (auto it = m_items.rbegin(); it != m_items.rend(); ++it)
		{
			if (!callback(*it))
			{
				return;
			}
		}
	}
	else
	{
		for (const auto& item : m_items)
		{
			if (!callback(item))
			{
				return;
			}
		}
	}
}

template <class T>
	requires ItemWithId<T>
std::optional<typename Repository<T>::ConstPtrType> Repository<T>::Find(std::string const& id) const
{
	const auto& mapIt = m_itemsMap.find(id);
	if (mapIt == m_itemsMap.end())
	{
		return std::nullopt;
	}
	return m_items.at(mapIt->second);
}

template <class T>
	requires ItemWithId<T>
std::optional<typename Repository<T>::PtrType> Repository<T>::Find(std::string const& id)
{
	auto optVal = const_cast<const Repository*>(this)->Find(id);
	if (!optVal.has_value())
	{
		return std::nullopt;
	}
	return optVal.value();
}
template <class T>
	requires ItemWithId<T>
typename Repository<T>::ConstPtrType Repository<T>::Get(std::string const& id) const
{
	const auto& mapIt = m_itemsMap.find(id);
	if (mapIt == m_itemsMap.end())
	{
		throw std::runtime_error("No such item");
	}
	return m_items.at(mapIt->second);
}

template <class T>
	requires ItemWithId<T>
typename Repository<T>::PtrType Repository<T>::Get(std::string const& id)
{
	return const_cast<const Repository*>(this)->Get(id);
}

template <class T>
	requires ItemWithId<T>
typename Repository<T>::ConstPtrType Repository<T>::Get(size_t position) const
{
	return m_items.at(position);
}

template <class T>
	requires ItemWithId<T>
typename Repository<T>::PtrType Repository<T>::Get(const size_t position)
{
	return const_cast<const Repository*>(this)->Get(position);
}

template <class T>
	requires ItemWithId<T>
void Repository<T>::IncreaseIndexes(const size_t insertedAt)
{
	for (auto i = insertedAt + 1; i < GetSize(); ++i)
	{
		++m_itemsMap[m_items[i]->GetId()];
	}
}

template <class T>
	requires ItemWithId<T>
void Repository<T>::DecreaseIndexes(const size_t removedAt)
{
	for (auto i = removedAt; i < GetSize(); ++i)
	{
		--m_itemsMap[m_items[i]->GetId()];
	}
}
