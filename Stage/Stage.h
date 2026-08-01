#pragma once
#include <memory>
#include "../csv/LoadCsv.h"
#include "../Math/Rect.h"

class Camera;
class Piece;

/// <summary>
/// マップのデータを持つステージクラス
/// </summary>
class Stage
{
public:
	Stage();

	~Stage();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw(Vec2 camera_pos);

	// 指定した矩形がマップチップと衝突しているかどうか
	bool IsCollision(const Rect& rect, Rect& chip_rect);

	// 指定した矩形がマップチップに入っているかどうか
	bool IsTrigger(const Rect& rect, Rect& chip_rect);

	// ステージ高さのゲッタ
	float GetStageHeight() const { return m_stage_height; }

	// ゴールしたかどうかのゲッタ
	bool GetIsGoal() const { return m_is_goal; }

	// カメラポインタのセッタ
	void SetCamera(std::shared_ptr<Camera> p_camera) { m_p_camera = p_camera; }

	// 前方に床があるかどうか
	bool IsGroundFoward(Rect& rect);

private:
	// コリジョンチップかどうか
	bool IsCollisionChip(int chip_num);

	// マップデータ
	MapData m_map_data;

	// コリジョンデータ
	CollisionData m_collision_data;

	// マップチップの画像データ配列
	int m_handle_array[190];

	// カメラのポインタ
	std::shared_ptr<Camera> m_p_camera;

	// ステージの高さ
	float m_stage_height;

	// ゴールしたかどうか
	bool m_is_goal;
};