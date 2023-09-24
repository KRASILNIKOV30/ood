#include "../../../external/catch2/catch.hpp"
#include "../../Observer/WeatherStationDuo/Observer.h"
#include "../../Observer/WeatherStationDuo/CStatsDisplay.h"
#include "../../Observer/WeatherStationDuo/CDisplay.h"
#include "../../Observer/WeatherStationDuo/WeatherData.h"
#include <sstream>

struct CoutBufferFixture
{
	std::stringstream buffer;
	std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	std::string GetOutput()
	{
		return buffer.str();
	}

	std::string ClearOutput()
	{
		buffer.str(std::string());
	}
};

SCENARIO_METHOD(CoutBufferFixture, "In/out stations test")
{
	GIVEN("Two stations and display")
	{
		CWeatherData inStation;
		CWeatherData outStation;

		CDisplay display(inStation, outStation);

		WHEN("Register display in both stations")
		{
			inStation.RegisterObserver(display);
			outStation.RegisterObserver(display);

			AND_WHEN("In station gives new data")
			{
				inStation.SetMeasurements(3, 0.7, 760);

				THEN("Display outputs weather inside")
				{
					CHECK(GetOutput() ==
						"Weather inside:\n"
						"Current Temp 3\n"
						"Current Hum 0.7\n"
						"Current Pressure 760\n"
						"----------------\n"
					);
				}
			}

			AND_WHEN("Out station gives new data")
			{
				outStation.SetMeasurements(3, 0.7, 760);

				THEN("Display outputs weather outside")
				{
					CHECK(GetOutput() ==
						"Weather outside:\n"
						"Current Temp 3\n"
						"Current Hum 0.7\n"
						"Current Pressure 760\n"
						"----------------\n"
					);
				}
			}
		}
	}
}