#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


using MapData = std::vector<std::vector<int>>;

// CSVファイルを読み込みマップデータを返す
MapData LoadMap(const std::string& file_path);