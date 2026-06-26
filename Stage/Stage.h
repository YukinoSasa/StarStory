#pragma once
#include "../csv/LoadCsv.h"
#include "../Math/Rect.h"

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

private:
	// ステージの描画位置を更新
	void UpdateStagePos();

	// マップのデータ
	MapData m_MapData;

	// 地面(csvの1)の画像データ
	int m_Handle1;
};