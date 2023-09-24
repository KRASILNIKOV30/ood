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
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data, IObservable& observable) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CWeatherData& m_inStation, m_outStation;
};

