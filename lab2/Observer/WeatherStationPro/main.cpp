#include "WeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, { Measurement::Temperature, Measurement::Pressure });

	wd.SetMeasurements(3, 0.7, 760, 10, 210);
	std::cout << std::endl << std::endl;
	wd.SetMeasurements(4, 0.8, 761, 20, 180);

	wd.RemoveObserver(display, { Measurement::Pressure });

	std::cout << std::endl << std::endl;
	wd.SetMeasurements(5, 0.9, 762, 30, 90);

	return 0;
}