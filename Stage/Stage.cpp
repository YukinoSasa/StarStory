#include <DxLib.h>
#include "../GameConst.h"
#include "Stage.h"
#include "../Character/Camera.h"

namespace
{
	// 地面ブロックの画像サイズ
	float BLOCK_SIZE = 64.0f;
}

Stage::Stage() :
	m_stage_height(0.0f), m_is_goal(false)
{
	m_map_data = LoadMap("csv/Stage1.csv");
	m_handle1 = LoadGraph("Data/ground_kari.png");
	m_handle2 = LoadGraph("Data/ashiba.png");
	m_handle4 = LoadGraph("Data/piece_kari.png");
}

Stage::~Stage()
{
	DeleteGraph(m_handle1);
	DeleteGraph(m_handle2);
	DeleteGraph(m_handle4);
}

void Stage::Init()
{
	m_stage_height = (int)m_map_data.size() * BLOCK_SIZE;
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
			{
				break;
			}

			case 1:
			{
				// マップチップのワールド座標(マップチップの中心座標)を求める
				float world_x = (x * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);
				float world_y = (y * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);

				// DrawGraphは左上基準なので中心基準から左上にずらす
				float screen_x = world_x - camera_pos.x + Game::SCREEN_HALF_WIDTH - (BLOCK_SIZE * 0.5f);
				float screen_y = world_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT - (BLOCK_SIZE * 0.5f);

				DrawGraphF(screen_x, screen_y, m_handle1, true);
				break;
			}

			case 2:
			{
				float width = 0.0f;
				float height = 0.0f;
				GetGraphSizeF(m_handle2, &width, &height);

				// マップチップのワールド座標(マップチップの中心座標)を求める
				float world_x = (x * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);
				float world_y = (y * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);

				// DrawGraphは左上基準なので中心基準から左上にずらす
				float screen_x = world_x - camera_pos.x + Game::SCREEN_HALF_WIDTH - (BLOCK_SIZE * 0.5f);
				float screen_y = world_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT - (BLOCK_SIZE * 0.5f);

				DrawGraphF(screen_x, screen_y, m_handle2, true);
				break;
			}

			case 3:
				break;

			case 4:
			{
				// マップチップのワールド座標(マップチップの中心座標)を求める
				float world_x = (x * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);
				float world_y = (y * BLOCK_SIZE) + (BLOCK_SIZE * 0.5f);

				// DrawGraphは左上基準なので中心基準から左上にずらす
				float screen_x = world_x - camera_pos.x + Game::SCREEN_HALF_WIDTH - (BLOCK_SIZE * 0.5f);
				float screen_y = world_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT - (BLOCK_SIZE * 0.5f);

				DrawGraphF(screen_x, screen_y, m_handle4, true);
				break;
			}
			}
		}
	}

	//DrawFormatString(0, 30, GetColor(255, 255, 255), "cameraX : %f", camera_pos.x);
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "screenW : %d", Game::SCREEN_WIDTH);
	float width1, height1;
	GetGraphSizeF(m_handle1, &width1, &height1);

	DrawFormatString(0, 90, GetColor(255, 255, 255), "block w x h : %f x %f", width1, height1);

	if (m_is_goal)
	{
		DrawFormatString(1200, 50, GetColor(0, 255, 255), "GOAL!!!");
	}
}

bool Stage::IsCollision(const Rect& rect, Rect& chip_rect)
{
	for (int y = 0; y < (int)m_map_data.size(); y++)
	{
		for (int x = 0; x < (int)m_map_data[y].size(); x++)
		{
			// マップチップ0,3(ゴール),4(かけら)は当たり判定がないので飛ばす
			if (m_map_data[y][x] == 0 || m_map_data[y][x] == 3 || m_map_data[y][x] == 4)
			{
				continue;
			}
			
			// マップチップ1(床),2(足場)の時当たり判定の矩形を持つ
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

bool Stage::IsTrigger(const Rect& rect, Rect& chip_rect)
{
	for (int y = 0; y < (int)m_map_data.size(); y++)
	{
		for (int x = 0; x < (int)m_map_data[y].size(); x++)
		{
			// マップチップ0,1(床),2(足場)はTrigger判定がないので飛ばす
			if (m_map_data[y][x] == 0 || m_map_data[y][x] == 1 || m_map_data[y][x] == 2)
			{
				continue;
			}

			// マップチップ3(ゴール),4(足場)の時当たり判定の矩形を持つ
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

				// ゴールと接触時は当たり判定処理を行わない
				if (m_map_data[y][x] == 3)
				{
					chip_rect.SetIsObject(false);
					m_is_goal = true;
				}

				// アイテムと接触時は当たり判定処理を行わない
				if (m_map_data[y][x] == 4)
				{
					chip_rect.SetIsObject(false);
				}

				return true;
			}
		}
	}

	return false;
}