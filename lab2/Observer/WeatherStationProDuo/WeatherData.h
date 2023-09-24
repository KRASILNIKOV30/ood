#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "SWeatherInfo.h"
#include "Observer.h"

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		SetDefaultMeasurements(temp, humidity, pressure);
		MeasurementsChanged();
	}

protected:
	void SetDefaultMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
	}

	void InitDefaultInfo(SWeatherInfo& info) const
	{
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
	}

	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		InitDefaultInfo(info);
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
