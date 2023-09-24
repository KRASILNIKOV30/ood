#pragma once
#include <string>
#include <iostream>

class Statistics
{
public:
	Statistics(std::string const& name)
		: m_name(name)
	{
	}

	void AddValue(double value)
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_accValue += value;
		m_countAcc++;
	}

	void Display()
	{
		std::cout << "Max " << m_name << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_name << " " << m_minValue << std::endl;
		std::cout << "Average " << m_name << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	std::string m_name;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};
