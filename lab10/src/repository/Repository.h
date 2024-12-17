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
	void Insert(std::string const& id, std::unique_ptr<T>&& item, size_t position = GetSize());
	std::optional<size_t> Remove(std::string const& id);
	void ForEach(std::function<bool(const T* item)> callback) const;
	std::optional<const T*> Find(std::string const& id) const;

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
void Repository<T>::Insert(std::string const& id, std::unique_ptr<T>&& item, size_t position)
{
	m_items.insert(m_items.begin() + position, std::move(item));

	try
	{
		if (!m_itemsMap.emplace(id, position).second)
		{
			m_items.erase(m_items.begin() + position);
		}
	}
	catch (std::exception&)
	{
		m_items.erase(m_items.begin() + position);
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
