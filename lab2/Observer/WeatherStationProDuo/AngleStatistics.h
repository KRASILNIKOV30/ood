#pragma once
#include <string>
#include <iostream>
#include "Statistics.h"
#include <cmath>
#include <vector>

class AngleStatistics final : public Statistics
{
public:
	explicit AngleStatistics(std::string const& name)
		: Statistics(name)
	{
	}

	void AddValue(const double value) override
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
	double GetAvg() const override
	{
		const double scalingFactor = 2 * PI / MAX_ANGLE;

		std::vector<double> sines;
		std::vector<double> cosines;

		for (auto const& angle : m_angles)
		{
			const double radians = angle * scalingFactor;
			sines.push_back(std::sin(radians));
			cosines.push_back(std::cos(radians));
		}

		const double atan = std::atan2(GetVectorMedian(sines), GetVectorMedian(cosines));
		const double result = atan / scalingFactor;

		return result < 0 ? result + MAX_ANGLE : result;
	}

private:
	double GetVectorMedian(std::vector<double> const& v) const
	{
		double sum = 0;
		for (const auto& el : v)
		{
			sum += el;
		}
		return sum / v.size();
	}

	const double PI = 3.14159265358979323846;
	const double MAX_ANGLE = 360;
	std::string m_name;
	std::vector<double> m_angles = {};
};