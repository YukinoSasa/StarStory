#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "../Character/EnemyManager.h"

// マップデータのvector配列
using MapData = std::vector<std::vector<int>>;

// csvファイルを読み込みマップデータを返す
MapData LoadMap(const std::string& file_path);

//// エネミーデータのvector配列
//using EnemyDatas = std::vector<EnemyData>;

// csvファイルを読み込みエネミーデータを返す
EnemyDatas LoadEnemy(const std::string& file_path);