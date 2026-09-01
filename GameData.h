#pragma once
#include "Math/Vec2.h"

/// <summary>
/// 初期座標などゲームデータを扱う構造体
/// </summary>
struct GameData
{
	// 各ステージの初期スポーン座標
	Vec2 m_init_pos = Vec2(130.0f, 4008.0f);

	// リスポーン座標(セーブポイント通過時に上書き)
	Vec2 m_spawn_pos = Vec2(130.0f, 4008.0f);
};