#pragma once
#include "WeatherData.h"

class CWeatherDataPro : public CWeatherData
{
public:
	double GetWindSpeed()const
	{
		return m_windSpeed;
	}

	double GetWindDirection()const
	{
		return m_windDirection;
	}

	void SetMeasurements
	(
		double temp,
		double humidity,
		double pressure,
		double windSpeed,
		double windDirection
	)
	{
		SetDefaultMeasurements(temp, humidity, pressure);
		SetProMeasurements(windSpeed, windDirection);

		MeasurementsChanged();
	}

protected:
	void SetProMeasurements(double windSpeed, double windDirection)
	{
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;
	}

	void InitProInfo(SWeatherInfo& info) const
	{
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
	}

	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		InitDefaultInfo(info);
		InitProInfo(info);
		return info;
	}

private:
	double m_windSpeed = 0;
	double m_windDirection = 0;
};