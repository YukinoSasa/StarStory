#include "LoadCsv.h"
#include "../Math/Vec2.h"

MapData LoadMap(const std::string& file_path)
{
	MapData map_data;
	std::ifstream file(file_path);

	// ファイルが読み込めない場合、以降の処理を行わない
	if (!file)
	{
		return map_data;
	}

	std::string line;

	while (std::getline(file, line))
	{
		// 空行を飛ばす
		if (line.empty())
		{
			continue;
		}

		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ','))
		{
			// Windows環境の'\r'を除去
			if (!cell.empty() && cell.back() == '\r')
			{
				cell.pop_back();
			}

			row.push_back(std::stoi(cell));
		}

		map_data.push_back(row);
	}

	return map_data;
}

EnemyDatas LoadEnemy(const std::string& file_path)
{
	EnemyDatas enemy_datas;
	std::ifstream file(file_path);

	// ファイルが読み込めない場合、以降の処理を行わない
	if (!file)
	{
		return enemy_datas;
	}

	std::string line;

	// 1行目ヘッダ部分を読み込む
	std::getline(file, line);
	
	// 2行目以降をデータとして読み込む
	while (std::getline(file, line))
	{
		EnemyData enemy_data{ 0, Vec2(0.0f, 0.0f), 0.0f, "graph_data" };

		// 空行を飛ばす
		if (line.empty())
		{
			continue;
		}

		std::vector<std::string> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ','))
		{
			// Windows環境の'\r'を除去
			if (!cell.empty() && cell.back() == '\r')
			{
				cell.pop_back();
			}

			row.push_back(cell);
		}
		
		// データをエネミー構造体に変換
		enemy_data.m_stage = std::stoi(row[0]);
		enemy_data.m_spawn.x = std::stof(row[1]);
		enemy_data.m_spawn.y = std::stof(row[2]);
		enemy_data.m_size = std::stof(row[3]);
		enemy_data.m_file_pass = row[4];

		enemy_datas.push_back(enemy_data);
	}

	return enemy_datas;
}

GimmickDatas LoadGimmick(const std::string& file_path)
{
	GimmickDatas gimmick_datas;
	std::ifstream file(file_path);

	// ファイルが読み込めない場合、以降の処理を行わない
	if (!file)
	{
		return gimmick_datas;
	}

	std::string line;

	// 1行目ヘッダ部分を読み込む
	std::getline(file, line);

	// 2行目以降をデータとして読み込む
	while (std::getline(file, line))
	{
		GimmickData gimmick_data{ 0, 0, Vec2(0.0f, 0.0f), 0.0f, "graph_data" };

		// 空行を飛ばす
		if (line.empty())
		{
			continue;
		}

		std::vector<std::string> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ','))
		{
			// Windows環境の'\r'を除去
			if (!cell.empty() && cell.back() == '\r')
			{
				cell.pop_back();
			}

			row.push_back(cell);
		}

		// データをエネミー構造体に変換
		gimmick_data.m_stage = std::stoi(row[0]);
		gimmick_data.m_gimmick_type = std::stoi(row[1]);
		gimmick_data.m_spawn.x = std::stof(row[2]);
		gimmick_data.m_spawn.y = std::stof(row[3]);
		gimmick_data.m_size = std::stof(row[4]);
		gimmick_data.m_file_pass = row[5];

		gimmick_datas.push_back(gimmick_data);
	}

	return gimmick_datas;
}

ItemDatas LoadItem(const std::string& file_path)
{
	ItemDatas item_datas;
	std::ifstream file(file_path);

	// ファイルが読み込めない場合、以降の処理を行わない
	if (!file)
	{
		return item_datas;
	}

	std::string line;

	// 1行目ヘッダ部分を読み込む
	std::getline(file, line);

	// 2行目以降をデータとして読み込む
	while (std::getline(file, line))
	{
		ItemData item_data{ 0, Vec2(0.0f, 0.0f), 0.0f, "graph_data" };

		// 空行を飛ばす
		if (line.empty())
		{
			continue;
		}

		std::vector<std::string> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ','))
		{
			// Windows環境の'\r'を除去
			if (!cell.empty() && cell.back() == '\r')
			{
				cell.pop_back();
			}

			row.push_back(cell);
		}

		// データをエネミー構造体に変換
		item_data.m_stage = std::stoi(row[0]);
		item_data.m_spawn.x = std::stof(row[1]);
		item_data.m_spawn.y = std::stof(row[2]);
		item_data.m_size = std::stof(row[3]);
		item_data.m_file_pass = row[4];

		item_datas.push_back(item_data);
	}

	return item_datas;
}