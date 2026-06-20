#pragma once
#include "../csv/LoadCsv.h"

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

private:
	// マップのデータ
	MapData m_MapData;

	// 地面(csvの1)の画像データ
	int m_Handle1;
};