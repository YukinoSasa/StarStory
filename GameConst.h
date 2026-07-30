#pragma once

namespace Game
{
	// スクリーンサイズ
	constexpr int SCREEN_WIDTH = 1920;
	constexpr int SCREEN_HEIGHT = 1080;

	// スクリーンサイズ(半分)
	constexpr float SCREEN_HALF_WIDTH = SCREEN_WIDTH * 0.5f;
	constexpr float SCREEN_HALF_HEIGHT = SCREEN_HEIGHT * 0.5f;

	// マップチップサイズ
	constexpr float MAPCHIP_SIZE = 64.0f;

	// 重力パラメーター
	constexpr float GRAVITY = 0.3f;

	// 重力を受ける関数
	inline void Gravity(float& move_y)
	{
		move_y += GRAVITY;
	}
}