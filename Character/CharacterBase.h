#pragma once
#include "../Math/Vec2.h"

/// <summary>
/// キャラクターのベースクラス
/// </summary>
class CharacterBase
{
public:
	CharacterBase();

	virtual ~CharacterBase();

	// 初期化
	virtual void Init();

	// 更新
	virtual void Update();

	// 描画
	virtual void Draw();

protected:
	// 画像を読み込む変数
	int m_Handle;

	// キャラクターの座標
	Vec2 m_Pos;
	// キャラクターの移動量
	Vec2 m_Move;
};