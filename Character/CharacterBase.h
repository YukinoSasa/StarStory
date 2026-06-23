#pragma once
#include "../Math/Vec2.h"
#include "../Math/Rect.h"

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

private:
	// 重力を受ける計算
	void Gravity();

protected:
	// 画像を読み込む変数
	int m_Handle;

	// 画像の幅を保存するポインタ変数
	int m_HandleWidth;

	// 画像の高さを保存するポインタ変数
	int m_HandleHeight;

	// キャラクターが右向きかどうか
	bool m_IsRight;

	// キャラクターの中心座標
	Vec2 m_Pos;
	// キャラクターの移動量
	Vec2 m_Move;

	// 接地しているかどうか
	bool m_IsGround;

	// 当たり判定用矩形
	Rect m_Rect;
};