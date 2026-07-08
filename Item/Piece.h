#pragma once
#include <memory>
#include "../Math/Vec2.h"
#include "../Math/Rect.h"

class Stage;

/// <summary>
/// アイテムのピース(かけら)クラス
/// </summary>
class Piece
{
public:
	Piece();

	~Piece();

	// 初期化
	void Init();

	// 描画
	void Draw(Vec2 camera_pos);

	// ステージポインタのセッタ
	void SetStage(std::shared_ptr<Stage> stage) { m_p_stage = stage; }

private:
	// 画像を読み込む変数
	int m_handle;

	// 画像の幅を保存する変数
	int m_handle_width;

	// 画像の高さを保存する変数
	int m_handle_height;

	// アイテムの中心座標
	Vec2 m_pos;

	// 当たり判定用矩形
	Rect m_rect;

	// ステージポインタ
	// いらない？
	std::shared_ptr<Stage> m_p_stage = nullptr;
};