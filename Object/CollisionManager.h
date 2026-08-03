#pragma once

/// <summary>
/// 当たり判定を管理するクラス
/// </summary>
class CollisionManager
{
public:
	CollisionManager();

	~CollisionManager() = default;

	// 初期化
	void Init();

	// 更新
	void Update();
};