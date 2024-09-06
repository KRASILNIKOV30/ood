#pragma once
#include "Observer.h"
#include "SWeatherInfo.h"
#include "../../../external/core/Assert.h"

class CWeatherData final : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	double GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementChanged(Measurement measurement)
	{
		NotifyObservers(measurement);
	}

	void SetMeasurements
	(
		const double temp,
		const double humidity,
		const double pressure,
		const double windSpeed,
		const double windDirection
	)
	{
		if (!isEqual(m_temperature, temp))
		{
			m_temperature = temp;
			MeasurementChanged(Measurement::Temperature);
		}
		if (!isEqual(m_humidity, humidity))
		{
			m_humidity = humidity;
			MeasurementChanged(Measurement::Humidity);
		}
		if (!isEqual(m_pressure, pressure))
		{
			m_pressure = pressure;
			MeasurementChanged(Measurement::Pressure);
		}
		if (!isEqual(m_windSpeed, windSpeed))
		{
			m_windSpeed = windSpeed;
			MeasurementChanged(Measurement::WindSpeed);
		}
		if (!isEqual(m_windDirection, windDirection))
		{
			m_windDirection = windDirection;
			MeasurementChanged(Measurement::WindDirection);
		}
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();

		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	double m_windDirection = 0;
};
