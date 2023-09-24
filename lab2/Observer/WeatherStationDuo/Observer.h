#pragma once

#pragma once
#include <map>

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void NotifyObservers() = 0;
};

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable& subject) = 0;
	virtual ~IObserver() = default;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority = 0)
	{
		m_observers.push_back(std::make_pair(priority, &observer));
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		Observers observersCopy = m_observers;
		std::sort(observersCopy.begin(), observersCopy.end(), [](auto& left, auto& right)
			{
				return left.first > right.first;
			});

		for (auto& [priority, observer] : observersCopy)
		{
			observer->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType& observer)
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); it++)
		{
			if (it->second == std::addressof(observer))
			{
				m_observers.erase(it);
				return;
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	using ObserverWithPrioriting = std::pair<int, ObserverType*>;
	using Observers = std::vector<ObserverWithPrioriting>;
	Observers m_observers;
};

