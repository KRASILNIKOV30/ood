#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

enum class Measurement
{
	Temperature,
	Humidity,
	Pressure,
	WindSpeed,
	WindDirection,
};

const std::set<Measurement> defaultMeasurements =
{
	Measurement::Temperature,
	Measurement::Humidity,
	Measurement::Pressure,
	Measurement::WindSpeed,
	Measurement::WindDirection,
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
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, std::set<Measurement> measurements, int priority) = 0;
	virtual void NotifyObservers(Measurement measurement) = 0;
	virtual void RemoveObserver(IObserver<T>& observer, std::set<Measurement> measurements) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver
	(
		ObserverType& observer,
		std::set<Measurement> measurements,
		int priority = 0
	) override
	{
		for (auto& measurement : measurements)
		{
			auto measurementObservers = m_observers.find(measurement);
			if (measurementObservers == m_observers.end())
			{
				measurementObservers = m_observers.emplace(measurement, ObserversWithPrioriting{}).first;
			}
			measurementObservers->second.emplace(priority, &observer);
		}
	}

	void NotifyObservers(Measurement measurement) override
	{
		T data = GetChangedData();
		Observers observersCopy = m_observers;

		auto measurementObservers = m_observers.find(measurement);
		if (measurementObservers != m_observers.end())
		{
			for (auto& observer : measurementObservers->second)
			{
				observer.second->Update(data);
			}
		}
	}

	void RemoveObserver
	(
		ObserverType& observer,
		std::set<Measurement> measurements = defaultMeasurements
	) override
	{
		for (auto& measurement : measurements)
		{
			auto measurementObservers = m_observers.find(measurement);
			if (measurementObservers != m_observers.end())
			{
				auto& observers = measurementObservers->second;
				for (auto it = observers.begin(); it != observers.end(); it++)
				{
					if (it->second == std::addressof(observer))
					{
						observers.erase(it);
						break;
					}
				}
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	using ObserversWithPrioriting = std::multimap<int, ObserverType*, std::greater<int>>;
	using Observers = std::unordered_map<Measurement, ObserversWithPrioriting>;
	Observers m_observers;
};
