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
	void Draw();

	// 指定した矩形がマップチップと当たっているかどうか
	bool IsCollision(const Rect& rect, Rect& chipRect);

	// カメラのポインタをセット
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }

private:
	// ステージの描画位置を更新
	void UpdateStagePos();

	// マップのデータ
	MapData m_MapData;

	// 地面(csvの1)の画像データ
	int m_Handle1;

	// カメラのポインタ
	std::shared_ptr<Camera> m_pCamera;
};