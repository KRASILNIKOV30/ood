#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	virtual std::string GetDescription()const override
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino()
		:CCoffee("Cappuccino")
	{}

	double GetCost() const override
	{
		return 80;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte()
		: CCoffee("Latte")
	{}

	double GetCost() const override
	{
		return 90;
	}
};

enum class TeaSort
{	
	MiLanXiang,
	DaHongPao,
	TieGuanYin,
	FengHuangDanCong
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaSort sort)
		: CBeverage("Tea")
		, m_sort(sort)
	{}

    std::string GetDescription()const override
	{
		switch (m_sort)
		{
		case TeaSort::MiLanXiang:
			return "Mi Lan Xiang";
		case TeaSort::DaHongPao:
			return "Da Hong Pao";
		case TeaSort::TieGuanYin:
			return "Tie Guan Yin";
		case TeaSort::FengHuangDanCong:
			return "Feng Huang Dan Cong";
		}

		return "Tea";
	}

	double GetCost() const override
	{
		return 30;
	}

private:
	TeaSort m_sort;
};

enum class PortionSize
{
	Small,
	Standard,
	Big
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(PortionSize size)
		: CBeverage("Milkshake")
		, m_size(size)
	{}

	std::string GetDescription()const override
	{
		switch (m_size)
		{
		case PortionSize::Small:
			return "Small Milkshake";
		case PortionSize::Standard:
			return "Standard Milkshake";
		case PortionSize::Big:
			return "Big Milkshake";
		}

		return "Standard Milkshake";
	}

	double GetCost() const override
	{
		switch (m_size)
		{
		case PortionSize::Small:
			return 50;
		case PortionSize::Standard:
			return 60;
		case PortionSize::Big:
			return 80;
		}

		return 60;
	}

private:
	PortionSize m_size;
};
