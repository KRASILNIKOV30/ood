#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include <iostream>
#include "Statictics.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStats.AddValue(data.temperature);
		m_humidityStats.AddValue(data.humidity);
		m_preassureStats.AddValue(data.pressure);

		m_temperatureStats.Display();
		m_humidityStats.Display();
		m_preassureStats.Display();
	}

	Statistics m_temperatureStats{"Temp"};
	Statistics m_humidityStats{"Humidity"};
	Statistics m_preassureStats{"Preassure"};
};
