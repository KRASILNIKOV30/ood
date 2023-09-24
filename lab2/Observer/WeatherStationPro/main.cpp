#include "WeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 10, 0);
	wd.SetMeasurements(4, 0.8, 761, 20, 270);
	//wd.SetMeasurements(10, 0.8, 761, 5, 90);
	//wd.SetMeasurements(-10, 0.8, 761, 10, 180);
	return 0;
}