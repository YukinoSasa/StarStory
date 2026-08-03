#include "GimmickManager.h"
#include "../../csv/LoadCsv.h"
#include "GimmickBase.h"
#include "Box.h"
#include "MovingPlatform.h"

GimmickManager::GimmickManager()
{
	// csvを読み込む
	m_gimmick_datas = LoadGimmick("csv/Gimmick.csv");

	for (auto& gimmick_data : m_gimmick_datas)
	{
		std::shared_ptr<GimmickBase> gimmick;

		// 各ギミックのポインタを生成する
		switch (gimmick_data.m_gimmick_type)
		{
		// 箱
		case 1:
		{
			gimmick = std::make_shared<Box>(gimmick_data);
			break;
		}
		// 動く床
		case 2:
		{
			gimmick = std::make_shared<MovingPlatform>(gimmick_data);
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

void GimmickManager::Update(Rect player_rect, Vec2 player_last_move)
{
	for (auto& gimmick : m_p_gimmicks)
	{
		gimmick->Update(player_rect, player_last_move);
	}
}

void GimmickManager::Draw(Vec2 camera_pos)
{
	for (auto& gimmick : m_p_gimmicks)
	{
		gimmick->Draw(camera_pos);
	}
}