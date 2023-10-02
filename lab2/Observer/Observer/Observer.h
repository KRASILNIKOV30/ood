#pragma once
#include <map>

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
������������ �������� ����������� ������������������ ������������.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority = -std::numeric_limits<int>::infinity()) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority = 0) override
	{
		m_observers.push_back(std::make_pair(priority, &observer));
	}

	void NotifyObservers() override
	{
		//�������� ����������� � ������ ������
		T data = GetChangedData();
		Observers observersCopy = m_observers;
		std::sort(observersCopy.begin(), observersCopy.end(), [](auto& left, auto& right)
		{
			return left.first > right.first;
		});

		for (auto& [priority, observer] : observersCopy)
		{
			observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
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
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;

private:
	using ObserverWithPrioriting = std::pair<int, ObserverType*>;
	using Observers = std::vector<ObserverWithPrioriting>;
	Observers m_observers;
};
