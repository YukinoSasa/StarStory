#pragma once
#include "Math/Vec2.h"

/// <summary>
/// ゲームデータを扱う構造体
/// </summary>
struct GameData
{
	// 各ステージの初期スポーン座標
	Vec2 m_init_pos = Vec2(130.0f, 4008.0f);

	// リスポーン座標(セーブポイント通過時に上書き)
	Vec2 m_spawn_pos = Vec2(130.0f, 4008.0f);

	// ストーリーを開始する星のかけら数
	static constexpr int STORY_ONE = 10;
	static constexpr int STORY_TWO = 35;
	// 星のかけらMAX数
	static constexpr int STAR_MAX = 50;

	// クリア時にプレイヤーが集めたアイテムの個数
	int m_item_result = 0;
};