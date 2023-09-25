#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include <iostream>
#include "Statistics.h"
#include "WeatherData.h"
#include "AngleStatistics.h"
#include "WeatherDataPro.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(CWeatherData& inStation, CWeatherDataPro& outStation)
		: m_inStation(inStation)
		, m_outStation(outStation)
	{}

private:
	void Update(SWeatherInfo const& data, IObservable& subject)
	{
		m_temperatureStats.AddValue(data.temperature);
		m_humidityStats.AddValue(data.humidity);
		m_preassureStats.AddValue(data.pressure);

		m_temperatureStats.Display();
		m_humidityStats.Display();
		m_preassureStats.Display();

		if (&subject == &m_outStation)
		{
			m_windSpeedStats.AddValue(data.windSpeed);
			m_windDirectionStats.AddValue(data.windDirection);
			m_windSpeedStats.Display();
			m_windDirectionStats.Display();
		}
	}

	Statistics m_temperatureStats{ "Temp" };
	Statistics m_humidityStats{ "Humidity" };
	Statistics m_preassureStats{ "Preassure" };
	Statistics m_windSpeedStats{ "Wind speed" };
	AngleStatistics m_windDirectionStats{ "Wind direction" };

	CWeatherData& m_inStation;
	CWeatherDataPro& m_outStation;

};
