#include <DxLib.h>
#include "../../csv/LoadCsv.h"
#include "GimmickBase.h"
#include "Box.h"
#include "MovingPlatform.h"
#include "SavePoint.h"
#include "Spring.h"
#include "GimmickManager.h"

GimmickManager::GimmickManager(int current_stage_num)
{
	// csv読み込み
	m_gimmick_datas = LoadGimmick("csv/Gimmick.csv");

	for (auto& gimmick_data : m_gimmick_datas)
	{
		// 現在のステージのギミックのみ生成する
		if (gimmick_data.m_stage != current_stage_num)
		{
			continue;
		}

		std::shared_ptr<GimmickBase> gimmick = nullptr;

		// 各ギミックのポインタを生成する
		switch (gimmick_data.m_gimmick_type)
		{
		// セーブポイント
		case 0:
		{
			gimmick = std::make_shared<SavePoint>(gimmick_data);
			break;
		}
		// 箱
		case 1:
		{
			gimmick = std::make_shared<Box>(gimmick_data);
			break;
		}
		// 動く床(縦)
		case 2:
		{
			gimmick = std::make_shared<MovingPlatform>(gimmick_data);
			break;
		}
		// 動く床(横)
		case 3:
		{
			gimmick = std::make_shared<MovingPlatform>(gimmick_data);
			break;
		}
		// スプリング
		case 4:
		{
			gimmick = std::make_shared<Spring>(gimmick_data);
			break;
		}
		}

		m_p_gimmicks.push_back(gimmick);
	}
}

void GimmickManager::Init()
{
	for (auto& gimmick : m_p_gimmicks)
	{
		gimmick->Init();
	}
}

void GimmickManager::Update(Rect player_rect, Vec2 player_move)
{
	for (auto& gimmick : m_p_gimmicks)
	{
		gimmick->Update(player_rect, player_move);
	}
}

void GimmickManager::Draw(Vec2 camera_pos)
{
	for (auto& gimmick : m_p_gimmicks)
	{
		gimmick->Draw(camera_pos);
	}
}