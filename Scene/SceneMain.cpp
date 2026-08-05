#include <DxLib.h>
#include "SceneMain.h"
#include "../Object/Character/Player.h"
#include "../Object/Character/EnemyManager.h"
#include "../Object/Character/Enemy.h"
#include "../Object/Item/Piece.h"
#include "BackGround/BackGround.h"
#include "../Object/CollisionManager.h"
#include "../Stage/Stage.h"
#include "../Object/Character/Camera.h"
#include "../Object/Gimmick/GimmickManager.h"
#include "../Object/Gimmick/GimmickBase.h"
#include "../Object/Item/ItemManager.h"

SceneMain::SceneMain() :
	m_is_goal(false)
{
	m_p_player = std::make_shared<Player>();
	m_p_enemy_manager = std::make_shared<EnemyManager>();
	//m_p_piece = std::make_shared<Piece>();
	m_p_background = std::make_shared<BackGround>();
	m_p_collision_manager = std::make_shared<CollisionManager>();
	m_p_stage = std::make_shared<Stage>();
	m_p_camera = std::make_shared<Camera>();
	m_p_gimmick_manager = std::make_shared<GimmickManager>();
	m_p_item_manager = std::make_shared<ItemManager>();

	//m_p_pieces.resize(10);
	//for (auto& piece : m_p_pieces)
	//{
	//	piece = std::make_shared<Piece>();
	//}

	m_p_player->SetStage(m_p_stage);

	// エネミーそれぞれにステージポインタをセット
	for (auto& enemy : m_p_enemy_manager->GetEnemies())
	{
		enemy->SetStage(m_p_stage);
	}
	//m_p_piece->SetStage(m_p_stage);
	m_p_camera->SetPlayer(m_p_player);
	m_p_stage->SetCamera(m_p_camera);
	
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_p_player->Init();
	m_p_enemy_manager->Init();
	//m_p_piece->Init();
	m_p_background->Init();
	m_p_stage->Init();
	m_p_item_manager->Init();
	m_p_gimmick_manager->Init();
}

void SceneMain::Update()
{
	m_p_gimmick_manager->Update(m_p_player->GetRect(), m_p_player->GetPlayerMove());
	m_p_player->Update();
	m_p_collision_manager->CheckPlayerCollision(m_p_player, m_p_stage, m_p_gimmick_manager);
	m_p_enemy_manager->Update();
	m_p_camera->Update();
	
	// ギミック接触判定
	//for (auto& gimmick : m_p_gimmick_manager->GetGimmicks())
	//{
	//	HitPlayerGimmick(m_p_player->GetRect(), gimmick->GetRect());
	//}

	// アイテム接触判定
	for (auto& item : m_p_item_manager->GetItems())
	{
		HitPlayerItem(m_p_player->GetRect(), item->GetRect(), item);
	}

	// 死亡判定(敵接触)
	for (auto& enemy : m_p_enemy_manager->GetEnemies())
	{
		HitPlayerEnemy(m_p_player->GetRect(), enemy->GetRect());
	}

	// 死亡後シーン遷移のトリガーオン
	if (!m_p_player->GetIsAlive())
	{
		m_scene_result = SceneResult::Gameover;
		m_is_scene_end = true;
	}

	// クリア判定後シーン遷移のトリガーオン
	if (m_p_stage->GetIsGoal())
	{
		m_is_goal = true;
		m_scene_result = SceneResult::Clear;
		m_is_scene_end = true;
	}
}

void SceneMain::Draw()
{
	m_p_background->Draw(m_p_camera->GetCameraPos(), m_p_stage->GetStageHeight());
	m_p_stage->Draw(m_p_camera->GetCameraPos());
	m_p_gimmick_manager->Draw(m_p_camera->GetCameraPos());
	m_p_item_manager->Draw(m_p_camera->GetCameraPos());
	m_p_enemy_manager->Draw(m_p_camera->GetCameraPos());
	m_p_player->Draw(m_p_camera->GetCameraPos());

	

	//for (auto& piece : m_p_pieces)
	//{
	//	piece->Draw(m_p_camera->GetCameraPos());
	//}
}

void SceneMain::HitPlayerEnemy(const Rect& player_rect, const Rect& enemy_rect)
{
	// プレイヤーが敵に接している場合プレイヤー死亡
	if (player_rect.IsCollision(enemy_rect))
	{
		m_p_player->SetIsAlive(false);
	}
}

//void SceneMain::HitPlayerGimmick(const Rect& player_rect, const Rect& gimmick_rect)
//{
//	// プレイヤーがギミックに接している場合プレイヤー座標をセット
//	if (player_rect.IsCollision(gimmick_rect))
//	{
//		// プレイヤーが右から接した場合
//		if (m_p_player->GetPlayerMove().x < 0.0f)
//		{
//			m_p_player->SetPlayerPos(
//				gimmick_rect.GetRightEdge() + m_p_player->GetPlayerWidth() * 0.5f,
//				m_p_player->GetPlayerPos().y);
//		}
//		// プレイヤーが左から接した場合
//		else if (m_p_player->GetPlayerMove().x > 0.0f)
//		{
//			m_p_player->SetPlayerPos(
//				gimmick_rect.GetLeftEdge() - m_p_player->GetPlayerWidth() * 0.5f,
//				m_p_player->GetPlayerPos().y);
//		}
//	}
//
//	if (player_rect.IsCollision(gimmick_rect))
//	{
//		// プレイヤーが上から接した場合
//		if (m_p_player->GetPlayerMove().y > 0.0f)
//		{
//			m_p_player->SetPlayerPos(
//				m_p_player->GetPlayerPos().x,
//				gimmick_rect.GetTopEdge() - m_p_player->GetPlayerHeight() * 0.5f);
//
//			m_p_player->SetPlayerMoveY(0.0f);
//			m_p_player->SetIsGround(true);
//		}
//	}
//}

void SceneMain::HitPlayerItem(const Rect& player_rect, const Rect& item_rect, std::shared_ptr<Piece> item)
{
	// プレイヤーがアイテムに接触した場合取得
	if (player_rect.IsCollision(item_rect))
	{
		item->Collect();
	}
}