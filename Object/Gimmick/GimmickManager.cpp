#include "GimmickManager.h"
#include "../../csv/LoadCsv.h"
#include "GimmickBase.h"
#include "Box.h"
#include "MovingPlatform.h"
#include <DxLib.h>

GimmickManager::GimmickManager()
{
	// csv読み込み
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
	DrawFormatString(0, 60, GetColor(255, 255, 255), "Platpos_x : %f", m_p_gimmicks[3]);
	//DrawFormatString(0, 90, GetColor(255, 255, 255), "Platpos_x : %f", m_p_gimmicks[3]->GetGimmickMove().x);

}