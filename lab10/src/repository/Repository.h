#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

template <class T>
class Repository
{
public:
	[[nodiscard]] size_t GetSize() const;
	void Insert(std::string const& id, T&& item, std::optional<size_t> position = std::nullopt);
	void Insert(std::string const& id, std::unique_ptr<T>&& item, std::optional<size_t> position = std::nullopt);
	std::optional<size_t> Remove(std::string const& id);
	void ForEach(std::function<bool(const T* item)> callback) const;
	std::optional<const T*> Find(std::string const& id) const;
	std::optional<T*> Find(std::string const& id);

private:
	using ItemsMap = std::unordered_map<std::string, size_t>;
	using Items = std::vector<std::unique_ptr<T>>;

	ItemsMap m_itemsMap;
	Items m_items;
};

template <class T>
size_t Repository<T>::GetSize() const
{
	return m_items.size();
}

template <class T>
void Repository<T>::Insert(std::string const& id, T&& item, const std::optional<size_t> position)
{
	Insert(id, std::make_unique<T>(std::move(item)), position);
}

template <class T>
void Repository<T>::Insert(std::string const& id, std::unique_ptr<T>&& item, const std::optional<size_t> position)
{
	const auto pos = position.has_value()
		? position.value()
		: GetSize();

	m_items.insert(m_items.begin() + pos, std::move(item));

	try
	{
		if (!m_itemsMap.emplace(id, pos).second)
		{
			m_items.erase(m_items.begin() + pos);
		}
	}
	catch (std::exception&)
	{
		m_items.erase(m_items.begin() + pos);
		throw;
	}
}

template <class T>
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
	return position;
}

template <class T>
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
std::optional<T*> Repository<T>::Find(std::string const& id)
{
	auto optVal = const_cast<const Repository*>(this)->Find(id);
	if (!optVal.has_value())
	{
		return std::nullopt;
	}
	return const_cast<T*>(optVal.value());
}
