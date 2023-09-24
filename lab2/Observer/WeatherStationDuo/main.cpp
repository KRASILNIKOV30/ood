#include "WeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData inStation;
	CWeatherData outStation;

	CDisplay display(inStation, outStation);
	inStation.RegisterObserver(display);
	outStation.RegisterObserver(display);

	CStatsDisplay statsDisplay(inStation, outStation);;
	inStation.RegisterObserver(statsDisplay);
	outStation.RegisterObserver(statsDisplay);

	inStation.SetMeasurements(3, 0.7, 760);
	outStation.SetMeasurements(4, 0.8, 761);

	inStation.RemoveObserver(statsDisplay);

	outStation.SetMeasurements(10, 0.8, 761);
	inStation.SetMeasurements(-10, 0.8, 761);
	return 0;
}