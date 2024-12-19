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
	{ t.GetId() } -> std::same_as<std::string>;
};

template <class T>
	requires ItemWithId<T>
class Repository
{
public:
	[[nodiscard]] size_t GetSize() const;
	void Insert(T&& item, std::optional<size_t> position = std::nullopt);
	void Insert(std::unique_ptr<T>&& item, std::optional<size_t> position = std::nullopt);
	std::optional<size_t> Remove(std::string const& id);
	void ForEach(std::function<bool(const T* item)> callback) const;

	std::optional<const T*> Find(std::string const& id) const;
	std::optional<T*> Find(std::string const& id);
	const T* Get(std::string const& id) const;
	T* Get(std::string const& id);
	const T* Get(size_t position) const;
	T* Get(size_t position);

private:
	void IncreaseIndexes(size_t insertedAt);
	void DecreaseIndexes(size_t removedAt);

private:
	using ItemsMap = std::unordered_map<std::string, size_t>;
	using Items = std::vector<std::unique_ptr<T>>;

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
void Repository<T>::Insert(T&& item, const std::optional<size_t> position)
{
	Insert(std::make_unique<T>(std::move(item)), position);
}

template <class T>
	requires ItemWithId<T>
void Repository<T>::Insert(std::unique_ptr<T>&& item, const std::optional<size_t> position)
{
	bool commit = false;
	const auto pos = position.value_or(GetSize());
	const auto it = m_items.insert(m_items.begin() + pos, std::move(item));

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
void Repository<T>::ForEach(std::function<bool(const T* item)> callback) const
{
	for (const auto& item : m_items)
	{
		if (!callback(item.get()))
		{
			return;
		}
	}
}

template <class T>
	requires ItemWithId<T>
std::optional<const T*> Repository<T>::Find(std::string const& id) const
{
	const auto& mapIt = m_itemsMap.find(id);
	if (mapIt == m_itemsMap.end())
	{
		return std::nullopt;
	}
	return m_items.at(mapIt->second).get();
}

template <class T>
	requires ItemWithId<T>
std::optional<T*> Repository<T>::Find(std::string const& id)
{
	auto optVal = const_cast<const Repository*>(this)->Find(id);
	if (!optVal.has_value())
	{
		return std::nullopt;
	}
	return const_cast<T*>(optVal.value());
}

template <class T>
	requires ItemWithId<T>
const T* Repository<T>::Get(std::string const& id) const
{
	const auto& mapIt = m_itemsMap.find(id);
	if (mapIt == m_itemsMap.end())
	{
		throw std::runtime_error("No such item");
	}
	return m_items.at(mapIt->second).get();
}

template <class T>
	requires ItemWithId<T>
T* Repository<T>::Get(std::string const& id)
{
	return const_cast<T*>(const_cast<const Repository*>(this)->Get(id));
}

template <class T>
	requires ItemWithId<T>
const T* Repository<T>::Get(size_t position) const
{
	return m_items.at(position).get();
}

template <class T>
	requires ItemWithId<T>
T* Repository<T>::Get(size_t position)
{
	return m_items.at(position).get();
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
