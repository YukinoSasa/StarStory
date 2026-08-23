#include "../../csv/LoadCsv.h"
#include "ItemManager.h"
#include "Piece.h"

ItemManager::ItemManager(int current_stage_num)
{
	// csvを読み込む
	m_item_datas = LoadItem("csv/Item.csv");

	for (auto& item_data : m_item_datas)
	{
		// 現在のステージのアイテムのみ生成する
		if (item_data.m_stage != current_stage_num)
		{
			continue;
		}

		// 各アイテムのポインタを生成する
		std::shared_ptr<Piece> piece = std::make_shared<Piece>(item_data);
		m_p_items.push_back(piece);
	}
}

void ItemManager::Init()
{
	for (auto& item : m_p_items)
	{
		item->Init();
	}
}

void ItemManager::Update()
{
	for (auto& item : m_p_items)
	{
		item->Update();
	}
}

void ItemManager::Draw(Vec2 camera_pos)
{
	for (auto& item : m_p_items)
	{
		item->Draw(camera_pos);
	}
}