#pragma once
#include <array>
#include <cassert>
#include "Geom.h"

#include <cstdint>

class Tile
{
public:
	// Размер тайла 8*8 пикселей.
	constexpr static int SIZE = 8;

	// Конструктор по умолчанию. Заполняет тайл указанным цветом.
	explicit Tile(const uint32_t color = ' ') noexcept
	{
		m_data.fill(color);
		// -------------- не удалять ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
		// -------------- не удалять ------------
	}

	Tile(const Tile& other)
	{
		/* Реализуйте недостающий код самостоятельно. */
		m_data = other.m_data;
		// -------------- не удалять ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
		// -------------- не удалять ------------
	}

	~Tile()
	{
		// -------------- не удалять ------------
		--m_instanceCount; // Уменьшаем счётчик тайлов.
		assert(m_instanceCount >= 0);
		// -------------- не удалять ------------
	}

	/**
	 * Изменяет цвет пикселя тайла.
	 * Если координаты выходят за пределы тайла, метод ничего не делает.
	 */
	void SetPixel(const Point p, const uint32_t color) noexcept
	{
		if (IsPointInTile(p))
		{
			m_data[SIZE * p.y + p.x] = color;
		}
	}

	/**
	 * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
	 */
	[[nodiscard]] uint32_t GetPixel(const Point p) const noexcept
	{
		if (!IsPointInTile(p))
		{
			return ' ';
		}
		return m_data[SIZE * p.y + p.x];
	}

	// Возвращает количество экземпляра класса Tile в программе.
	static int GetInstanceCount() noexcept
	{
		// -------------- не удалять ------------
		return m_instanceCount;
		// -------------- не удалять ------------
	}

private:
	[[nodiscard]] static bool IsPointInTile(Point const p) noexcept
	{
		return IsPointInSize(p, {SIZE, SIZE});
	}

private:
	// -------------- не удалять ------------
	inline static int m_instanceCount = 0;
	// -------------- не удалять ------------

	/* Разместите здесь поля для хранения пикселей тайла. */
	std::array<uint32_t, SIZE * SIZE> m_data{};
};
