#pragma once
#include <memory>
#include "../csv/LoadCsv.h"
#include "../Math/Rect.h"

class Camera;

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

	// カメラポインタのセッタ
	void SetCamera(std::shared_ptr<Camera> p_camera) { m_p_camera = p_camera; }

private:
	// マップのデータ
	MapData m_map_data;

	// 地面(csvの1)の画像データ
	int m_handle1;

	// 足場(csvの2)の画像データ
	int m_handle2;

	// かけら(csvの4)の画像データ
	int m_handle4;

	// カメラのポインタ
	std::shared_ptr<Camera> m_p_camera;

	// ステージの高さ
	float m_stage_height;

	// ゴールしたかどうか
	bool m_is_goal;
};