#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "../Object/Character/EnemyManager.h"
#include "../Gimmick/GimmickManager.h"

// マップデータのvector配列
using MapData = std::vector<std::vector<int>>;

// csvファイルを読み込みマップデータを返す
MapData LoadMap(const std::string& file_path);

//// エネミーデータのvector配列
//using EnemyDatas = std::vector<EnemyData>;

// csvファイルを読み込みエネミーデータを返す
EnemyDatas LoadEnemy(const std::string& file_path);

// csvファイルを読み込みギミックデータを返す
GimmickDatas LoadGimmick(const std::string& file_path);