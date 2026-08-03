#include <DxLib.h>
#include "../GameConst.h"
#include "../Object/Character/Camera.h"
#include "Stage.h"

Stage::Stage() :
	m_stage_height(0.0f), m_is_goal(false)
{
	// csv読み込み
	m_map_data = LoadMap("csv/Stage1.csv");
	m_collision_data = LoadCollision("csv/MapCollision.csv");

	LoadDivGraph("Data/newtileset.png", 190, 18, 11, 16, 16, m_handle_array);

}

Stage::~Stage()
{
	for (int i = 0; i < sizeof(m_handle_array) / sizeof(m_handle_array[0]); i++)
	{
		DeleteGraph(m_handle_array[i]);
	}
}

void Stage::Init()
{
	m_stage_height = (int)m_map_data.size() * Game::MAPCHIP_SIZE;
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

			// マップチップのワールド座標(マップチップの中心座標)を求める
			float world_x = (x * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);
			float world_y = (y * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);

			// DrawGraphは左上基準なので中心基準から左上にずらす
			float screen_x = world_x - camera_pos.x + Game::SCREEN_HALF_WIDTH - (Game::MAPCHIP_SIZE * 0.5f);
			float screen_y = world_y - camera_pos.y + Game::SCREEN_HALF_HEIGHT - (Game::MAPCHIP_SIZE * 0.5f);

			DrawExtendGraphF(screen_x, screen_y, screen_x + Game::MAPCHIP_SIZE, screen_y + Game::MAPCHIP_SIZE, m_handle_array[tile], true);
		}
	}


	//DrawFormatString(0, 30, GetColor(255, 255, 255), "cameraX : %f", camera_pos.x);
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "screenW : %d", Game::SCREEN_WIDTH);
	//float width1, height1;
	//GetGraphSizeF(m_handle1, &width1, &height1);

	//DrawFormatString(0, 90, GetColor(255, 255, 255), "block w x h : %f x %f", width1, height1);

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
			// 当たり判定がないマップチップは飛ばす
			if (!IsCollisionChip(m_map_data[y][x]))
			{
				continue;
			}
			
			// 当たり判定の矩形を持つ
			Rect check_chip_rect;
			// 矩形の中心座標を計算
			float chip_x = (x * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);
			float chip_y = (y * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);

			// 矩形の端をセット
			check_chip_rect.CalculateEdges(chip_x, chip_y, Game::MAPCHIP_SIZE, Game::MAPCHIP_SIZE);
			// 対象の矩形とマップチップの矩形の当たりを調べる
			if (check_chip_rect.IsCollision(rect))
			{
				// ぶつかったマップチップの矩形を設定
				chip_rect.CalculateEdges(chip_x, chip_y, Game::MAPCHIP_SIZE, Game::MAPCHIP_SIZE);

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
			float chip_x = (x * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);
			float chip_y = (y * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);

			// 矩形の端をセット
			check_chip_rect.CalculateEdges(chip_x, chip_y, Game::MAPCHIP_SIZE, Game::MAPCHIP_SIZE);
			// 対象の矩形とマップチップの矩形の当たりを調べる
			if (check_chip_rect.IsCollision(rect))
			{
				// ぶつかったマップチップの矩形を設定
				chip_rect.CalculateEdges(chip_x, chip_y, Game::MAPCHIP_SIZE, Game::MAPCHIP_SIZE);

				// ゴールと接触時は当たり判定処理を行わない
				if (m_map_data[y][x] == 3)
				{
					chip_rect.SetIsObject(false);
					m_is_goal = true;
				}
			}
		}
	}
	
	return false;
}

bool Stage::IsGroundFoward(Rect& rect)
{
	// rectの位置に床があるかどうかを確認
	// 当たり判定のあるチップだったらtrueを返す
	// それ以外だったらfalseを返す
	for (int y = 0; y < (int)m_map_data.size(); y++)
	{
		for (int x = 0; x < (int)m_map_data[y].size(); x++)
		{
			// 当たり判定がないマップチップは飛ばす
			if (!IsCollisionChip(m_map_data[y][x]))
			{
				continue;
			}

			// 当たり判定ありのチップの場合矩形をもつ
			Rect check_chip_rect;
			// 矩形の中心座標を計算
			float chip_x = (x * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);
			float chip_y = (y * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);

			// 矩形の端をセット
			check_chip_rect.CalculateEdges(chip_x, chip_y, Game::MAPCHIP_SIZE, Game::MAPCHIP_SIZE);
			
			if (check_chip_rect.IsCollision(rect))
			{
				return true;
			}
		}
	}

	return false;
}

bool Stage::IsCollisionChip(int chip_num)
{
	return m_collision_data[chip_num];
}