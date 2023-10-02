#pragma once
#include <string>
#include <iostream>
#include "Statistics.h"
#include <cmath>
#include <vector>
#include <numeric>

class AngleStatistics : public Statistics
{
public:
	AngleStatistics(std::string const& name)
		: Statistics(name)
	{
	}

	void AddValue(double value) override
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_angles.push_back(value);
	}

protected:
	//Можно хранить сумму синусоы и косинусов
	double GetAvg() const override
	{
		double scalingFactor = 2 * PI / MAX_ANGLE;

		std::vector<double> sines;
		std::vector<double> cosines;

		double radians;
		for (auto const& angle : m_angles)
		{
			radians = angle * scalingFactor;
			sines.push_back(std::sin(radians));
			cosines.push_back(std::cos(radians));
		}

		double atan = std::atan2(GetVectorMedian(sines), GetVectorMedian(cosines));
		double result = atan / scalingFactor;

		return result < 0 ? result + MAX_ANGLE : result;
	}

private:
	double GetVectorMedian(std::vector<double> v) const
	{
		double sum = 0;
		for (auto& el : v)
		{
			sum += el;
		}
		return sum / v.size();
	}

private:
	const double PI = 3.14159265358979323846;
	const double MAX_ANGLE = 360;
	std::string m_name;
	std::vector<double> m_angles = {};
};