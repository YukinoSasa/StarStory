#pragma once
#include <cmath>

class Vec2
{
public:
	Vec2() : m_x(0.0f), m_y(0.0f)
	{

	}

	Vec2(float posX, float posY) : m_x(posX), m_y(posY)
	{

	}

	// ’P€‰‰Zq+ Vec2 = +Vec2
	Vec2 operator+() const
	{
		return *this;
	}

	// ’P€‰‰Zq- Vec2 = -Vec2
	Vec2 operator-() const
	{
		return Vec2{ -m_x, -m_y };
	}

	// ‘«‚µZ
	Vec2 operator+(Vec2 vec) const
	{
		return Vec2{ m_x + vec.m_x, m_y + vec.m_y };
	}
	// Vec2 += Vec2
	Vec2 operator+=(Vec2 vec)
	{
		m_x += vec.m_x;
		m_y += vec.m_y;

		return *this;
	}

	// ˆø‚«Z
	Vec2 operator-(Vec2 vec) const
	{
		return Vec2{ m_x - vec.m_x, m_y - vec.m_y };
	}
	// Vec2 -= Vec2
	Vec2 operator-=(Vec2 vec)
	{
		m_x -= vec.m_x;
		m_y -= vec.m_y;

		return *this;
	}

	// Š|‚¯Z
	Vec2 operator*(float scale) const
	{
		return Vec2{ m_x * scale, m_y * scale };
	}

	// Vec2 *= float
	Vec2 operator*=(float scale)
	{
		m_x *= scale;
		m_y *= scale;

		return *this;
	}

	// Š„‚èZ
	Vec2 operator/(float scale) const
	{
		return Vec2{ m_x / scale, m_y / scale };
	}

	// Vec2 /= float
	Vec2 operator/=(float scale)
	{
		m_x /= scale;
		m_y /= scale;

		return *this;
	}

	// ƒxƒNƒgƒ‹‚Ì’·‚³‚Ì2æ
	float SqLength() const
	{
		return m_x * m_x + m_y * m_y;
	}

	// ƒxƒNƒgƒ‹‚Ì’·‚³
	float Length() const
	{
		return sqrtf(SqLength());
	}

	// ©g‚Ì³‹K‰»
	void Normalize()
	{
		float len = Length();

		if (len > 0.0f)
		{
			m_x /= len;
			m_y /= len;
		}

		// ’·‚³0‚Ìê‡‚Í‰½‚à‚µ‚È‚¢
	}

	// ©g‚ğ³‹K‰»‚µ‚½ƒxƒNƒgƒ‹‚ğæ“¾
	Vec2 Normalized() const
	{
		float len = Length();

		if (len > 0.0f)
		{
			return Vec2{ m_x / len, m_y / len };
		}

		// ’·‚³‚ª0‚Ìê‡
		return Vec2{ 0.0f, 0.0f };
	}

public:
	float m_x;
	float m_y;
};