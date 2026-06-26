#include <DxLib.h>
#include "Stage.h"
#include "../Character/Camera.h"

namespace
{
	// 地面ブロックの画像サイズ
	float K_SIZE = 64.0f;
}

Stage::Stage()
{
	m_MapData = LoadMap("csv/Stage1.csv");
	m_Handle1 = LoadGraph("Data/ground_kari.png");
}

Stage::~Stage()
{
	DeleteGraph(m_Handle1);
}

void Stage::Init()
{

}

void Stage::Update()
{

}

void Stage::Draw()
{
	for (int y = 0; y < (int)m_MapData.size(); y++)
	{
		for (int x = 0; x < (int)m_MapData[y].size(); x++)
		{
			int Tile = m_MapData[y][x];

			switch (Tile)
			{
			case 0:
				break;

			case 1:
				// マップチップのワールド座標を求める
				float worldX = (x * K_SIZE) + (K_SIZE / 2);
				float worldY = (y * K_SIZE) + (K_SIZE / 2);

				// 描画するスクリーン座標を求める
				Vec2 screenPos = m_pCamera->GetCameraPos();
				float screenX = worldX - screenPos.m_x + 960.0f;
				float screenY = worldY - screenPos.m_y + 540.0f;
				//DrawGraph(x * K_SIZE, y * K_SIZE + 100, m_Handle1, true);
				DrawGraph(screenX, screenY, m_Handle1, true);
			}
		}
	}
}

bool Stage::IsCollision(const Rect& rect, Rect& chipRect)
{
	for (int y = 0; y < (int)m_MapData.size(); y++)
	{
		for (int x = 0; x < (int)m_MapData[y].size(); x++)
		{
			// マップチップ0は当たり判定がないので飛ばす
			if (m_MapData[y][x] == 0)
			{
				continue;
			}
			
			// マップチップ1の時当たり判定の矩形を持つ
			Rect ChipRect;
			// 矩形の端をセット
			float chipX = (x * K_SIZE) + (K_SIZE / 2);
			float chipY = (y * K_SIZE) + (K_SIZE / 2) + 100;

			ChipRect.SetEdges(chipX, chipY, K_SIZE, K_SIZE);
			// 対象の矩形とマップチップの矩形の当たりを調べる
			if (ChipRect.IsCollision(rect))
			{
				// ぶつかったマップチップの矩形を設定
				chipRect.SetEdges(chipX, chipY, K_SIZE, K_SIZE);
				return true;
			}

		}
	}

	return false;
}

void Stage::UpdateStagePos()
{
	// マップの世界座標 - カメラ座標 + 画面中心
	// 現在は不要？

}