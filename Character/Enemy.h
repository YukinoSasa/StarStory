#pragma once
#include "CharacterBase.h"

/// <summary>
/// キャラクタークラスを継承したエネミークラス
/// </summary>
class Enemy : public CharacterBase
{
public:
	Enemy();

	~Enemy() override;

	// 初期化
	void Init() override;

	// 更新
	void Update() override;

	// 描画
	void Draw(Vec2 camera_pos) override;
};