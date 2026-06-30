#pragma once
#include <cmath>

/// <summary>
/// 2次元ベクトルを表すクラス
/// </summary>
class Vec2
{
public:
	Vec2() : x(0.0f), y(0.0f)
	{

	}

	Vec2(float pos_x, float pos_y) : x(pos_x), y(pos_y)
	{

	}

	// 単項演算子+ Vec2 = +Vec2
	Vec2 operator+() const
	{
		return *this;
	}

	// 単項演算子- Vec2 = -Vec2
	Vec2 operator-() const
	{
		return Vec2{ -x, -y };
	}

	// 足し算
	Vec2 operator+(Vec2 vec) const
	{
		return Vec2{ x + vec.x, y + vec.y };
	}
	// Vec2 += Vec2
	Vec2 operator+=(Vec2 vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	// 引き算
	Vec2 operator-(Vec2 vec) const
	{
		return Vec2{ x - vec.x, y - vec.y };
	}
	// Vec2 -= Vec2
	Vec2 operator-=(Vec2 vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	// 掛け算
	Vec2 operator*(float scale) const
	{
		return Vec2{ x * scale, y * scale };
	}

	// Vec2 *= float
	Vec2 operator*=(float scale)
	{
		x *= scale;
		y *= scale;

		return *this;
	}

	// 割り算
	Vec2 operator/(float scale) const
	{
		return Vec2{ x / scale, y / scale };
	}

	// Vec2 /= float
	Vec2 operator/=(float scale)
	{
		x /= scale;
		y /= scale;

		return *this;
	}

	// ベクトルの長さの2乗
	float SqLength() const
	{
		return x * x + y * y;
	}

	// ベクトルの長さ
	float Length() const
	{
		return sqrtf(SqLength());
	}

	// 自身の正規化
	void Normalize()
	{
		float len = Length();

		if (len > 0.0f)
		{
			x /= len;
			y /= len;
		}

		// 長さ0の場合は何もしない
	}

	// 自身を正規化したベクトルを取得
	Vec2 Normalized() const
	{
		float len = Length();

		if (len > 0.0f)
		{
			return Vec2{ x / len, y / len };
		}

		// 長さが0の場合
		return Vec2{ 0.0f, 0.0f };
	}

public:
	float x;
	float y;
};