#include <DxLib.h>
#include "../GameConst.h"
#include "Stage.h"
#include "../Character/Camera.h"

namespace
{
	// 地面ブロックの画像サイズ
	float BLOCK_SIZE = 64.0f;
}

Stage::Stage()
{
	m_map_data = LoadMap("csv/Stage1.csv");
	m_handle1 = LoadGraph("Data/ground_kari.png");
}

Stage::~Stage()
{
	DeleteGraph(m_handle1);
}

void Stage::Init()
{

}

void Stage::Update()
{

}

void Stage::Draw(Vec2 camera_pos)
{
	for (int y = 0; y < (int)m_map_data.size(); y++)
	{
		for (int x = 0; x < (int)m_map_data[y].size(); x++)
		{
			int tile = m_map_data[y][x];

			switch (tile)
			{
			case 0:
				break;

			case 1:
				// マップチップのワールド座標(マップチップの中心座標)を求める
				float world_x = (x * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);
				float world_y = (y * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);

				// DrawGraphは左上基準なので中心基準から左上にずらす
				float screen_x = world_x - camera_pos.x + Game::SCREEN_HALF_WIDTH - (BLOCK_SIZE * 0.5f);
				float screen_y = world_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT - (BLOCK_SIZE * 0.5f);

				DrawGraphF(screen_x, screen_y, m_handle1, true);
			}
		}
	}
}

bool Stage::IsCollision(const Rect& rect, Rect& chip_rect)
{
	for (int y = 0; y < (int)m_map_data.size(); y++)
	{
		for (int x = 0; x < (int)m_map_data[y].size(); x++)
		{
			// マップチップ0は当たり判定がないので飛ばす
			if (m_map_data[y][x] == 0)
			{
				continue;
			}
			
			// マップチップ1の時当たり判定の矩形を持つ
			Rect check_chip_rect;
			// 矩形の中心座標を計算
			float chip_x = (x * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);
			float chip_y = (y * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);

			// 矩形の端をセット
			check_chip_rect.CalculateEdges(chip_x, chip_y, BLOCK_SIZE, BLOCK_SIZE);
			// 対象の矩形とマップチップの矩形の当たりを調べる
			if (check_chip_rect.IsCollision(rect))
			{
				// ぶつかったマップチップの矩形を設定
				chip_rect.CalculateEdges(chip_x, chip_y, BLOCK_SIZE, BLOCK_SIZE);
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