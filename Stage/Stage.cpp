#include <DxLib.h>
#include "../GameConst.h"
#include "../Object/Character/Camera.h"
#include "Mapchip.h"
#include "Stage.h"

Stage::Stage() :
	m_stage_height(0.0f), m_is_goal(false)
{
	// csv読み込み
	m_map_data = LoadMap("csv/Stage1.csv");
	m_collision_data = LoadCollision("csv/MapCollision.csv");
	// 画像データ読み込み
	LoadDivGraph("Data/newtileset.png", 190, 18, 11, 16, 16, m_handle_array);

	// マップチップをインスタンス化、vectorに格納
	for (int y = 0; y < (int)m_map_data.size(); y++)
	{
		for (int x = 0; x < (int)m_map_data[y].size(); x++)
		{
			// マップチップのワールド座標(マップチップの中心座標)を求める
			float world_x = (x * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);
			float world_y = (y * Game::MAPCHIP_SIZE) + (Game::MAPCHIP_SIZE * 0.5f);

			std::shared_ptr<Mapchip> p_mapchip = std::make_shared<Mapchip>(
				world_x, world_y, m_map_data[y][x], m_collision_data[m_map_data[y][x]]);
			m_p_mapchips.push_back(p_mapchip);
		}
	}
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
	// ステージの全長を計算
	m_stage_height = (int)m_map_data.size() * Game::MAPCHIP_SIZE;

	for (auto& mapchip : m_p_mapchips)
	{
		mapchip->Init();
	}
}

void Stage::Update()
{

}

void Stage::Draw(Vec2 camera_pos)
{
	for (auto& mapchip : m_p_mapchips)
	{
		mapchip->Draw(camera_pos, m_handle_array);
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

bool Stage::IsCollisionX(const Rect& rect, Rect& chip_rect)
{
	for (auto& mapchip : m_p_mapchips)
	{
		// 当たり判定がないマップチップは飛ばす
		if (!mapchip->GetIsCollision())
		{
			continue;
		}

		// 走査中のマップチップrect
		const Rect& target = mapchip->GetRect();

		// y方向に重なっていなければ、x移動による衝突ではない
		if (rect.GetBottomEdge() <= target.GetTopEdge() || rect.GetTopEdge() >= target.GetBottomEdge())
		{
			continue;
		}

		// x方向で当たっている場合、その矩形を保存
		if (rect.GetRightEdge() > target.GetLeftEdge() && rect.GetLeftEdge() < target.GetRightEdge())
		{
			chip_rect = target;

			return true;
		}
	}

	return false;
}

bool Stage::IsCollisionY(const Rect& rect, Rect& chip_rect)
{
	for (auto& mapchip : m_p_mapchips)
	{
		// 当たり判定がないマップチップは飛ばす
		if (!mapchip->GetIsCollision())
		{
			continue;
		}

		// 走査中のマップチップrect
		const Rect& target = mapchip->GetRect();

		// x方向に重なっていなければ、y移動による衝突ではない
		if (rect.GetRightEdge() <= target.GetLeftEdge() || rect.GetLeftEdge() >= target.GetRightEdge())
		{
			continue;
		}

		// y方向で当たっている場合、その矩形を保存
		if (rect.GetBottomEdge() > target.GetTopEdge() && rect.GetTopEdge() < target.GetBottomEdge())
		{
			chip_rect = target;

			return true;
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
				if (m_map_data[y][x] == 7)
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