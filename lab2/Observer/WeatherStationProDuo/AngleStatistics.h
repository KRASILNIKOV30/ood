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
	double GetAvg() const override
	{
		double best_so_far = 360;
		for (int i = 0; i < m_angles.size(); i++)
		{
			double sum = 0;
			for (int j = 0; j < m_angles.size(); j++)
			{
				sum += std::fmod(std::abs(m_angles[i] - m_angles[j]), 360);
			}
			if (sum < best_so_far)
			{
				best_so_far = sum;
			}
		}

		return best_so_far;
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