#pragma once
#include "Observer.h"
#include "SWeatherInfo.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(CWeatherData& inStation, CWeatherData& outStation)
		: m_inStation(inStation)
		, m_outStation(outStation)
	{}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable& subject) override
	{
		if (&subject == &m_inStation)
		{
			std::cout << "Weather inside:" << std::endl;
		}
		if (&subject == &m_outStation)
		{
			std::cout << "Weather outside:" << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CWeatherData& m_inStation;
	CWeatherData& m_outStation;
};

