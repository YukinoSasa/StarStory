#include "LoadCsv.h"

MapData LoadMap(const std::string& filePath)
{
	MapData mapData;
	std::ifstream file(filePath);

	// ファイルが読み込めない場合、以降の処理を行わない
	if (!file)
	{
		return mapData;
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

		mapData.push_back(row);
	}

	return mapData;
}