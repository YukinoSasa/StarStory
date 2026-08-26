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
#include "Menu/MenuPause.h"
#include "../Input/Keyboard.h"
#include "../Sound/SoundManager.h"

SceneMain::SceneMain()
	:m_current_stage_num(2), m_is_story(false), m_is_config(false), m_is_pause(false), m_is_goal(false)
{
	m_p_player = std::make_shared<Player>(m_game_data.m_spawn_pos);
	m_p_enemy_manager = std::make_shared<EnemyManager>(m_current_stage_num);
	m_p_background = std::make_shared<BackGround>();
	m_p_collision_manager = std::make_shared<CollisionManager>();
	m_p_stage = std::make_shared<Stage>(m_current_stage_num);
	m_p_camera = std::make_shared<Camera>();
	m_p_gimmick_manager = std::make_shared<GimmickManager>(m_current_stage_num);
	m_p_item_manager = std::make_shared<ItemManager>(m_current_stage_num);
	m_p_menu_pause = std::make_shared<MenuPause>();

	m_p_player->SetStage(m_p_stage);

	// エネミーそれぞれにステージポインタをセット
	for (auto& enemy : m_p_enemy_manager->GetEnemies())
	{
		enemy->SetStage(m_p_stage);
	}
	m_p_camera->SetPlayer(m_p_player);
	m_p_stage->SetCamera(m_p_camera);
	
	m_collect_bg_handle = LoadGraph("Data/UI/collect_background.png");
	m_piece_ui_handle = LoadGraph("Data/UI/piece_ui.png");
	m_collect_font_handle = CreateFontToHandle("クラフト明朝", 64, -1);
}

SceneMain::~SceneMain()
{
	DeleteGraph(m_collect_bg_handle);
	DeleteFontToHandle(m_collect_font_handle);
	DeleteFontToHandle(m_piece_ui_handle);
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
	m_p_menu_pause->Init();
	m_config.Init();
}

void SceneMain::Update(GameSetting& game_setting, std::shared_ptr<SoundManager> p_sound_manager)
{
	// ポーズ判定
	if (!m_is_pause && Keyboard::IsTrigger(KEY_INPUT_ESCAPE))
	{
		p_sound_manager->PlaySE(SoundManager::SeType::Cancel);
		m_is_pause = true;
		m_p_menu_pause->SetSelectedItem();
		m_p_menu_pause->SetCurrentStateDefault();
		return;
	}

	// 設定中の場合Update
	if (m_is_config)
	{
		m_config.Update(game_setting, p_sound_manager);

		// 戻る選択がされた場合ポーズメニューに戻る
		if (Keyboard::IsTrigger(KEY_INPUT_ESCAPE) || m_config.GetIsCloseSelected())
		{
			m_config.SetIsCloseSelectedFalse();
			p_sound_manager->PlaySE(SoundManager::SeType::Cancel);
			m_config.SetConfigStateDefault();
			m_p_menu_pause->SetCurrentStateDefault();
			m_is_config = false;

			return;
		}
	}

	// ポーズ中はポーズのみUpdateし、それ以外はUpdateしない
	if (m_is_pause)
	{
		m_p_menu_pause->Update(p_sound_manager);

		// ポーズ中設定が選択された場合、設定を開く
		if (m_p_menu_pause->GetCurrentState() == MenuPause::MenuPauseState::SelectedConfig)
		{
			m_is_config = true;
		}
		// ポーズ中タイトルへ戻るが選択された場合、タイトルシーンへ遷移
		if (m_p_menu_pause->GetCurrentState() == MenuPause::MenuPauseState::SelectedReturnToTitle)
		{
			m_scene_result = SceneResult::None;
			m_is_scene_end = true;
		}
		// ポーズが閉じられたかどうか
		if ((Keyboard::IsTrigger(KEY_INPUT_ESCAPE) ||
			m_p_menu_pause->GetCurrentState() == MenuPause::MenuPauseState::SelectedReturnToGame))
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Cancel);
			m_is_pause = false;
			return;
		}

		return;
	}

	m_p_gimmick_manager->Update(m_p_player->GetRect(), m_p_player->GetPlayerMove());
	m_p_collision_manager->CheckBoxCollisionY(m_p_gimmick_manager, m_p_stage);
	m_p_player->Update();
	m_p_collision_manager->CheckPlayerCollisionX(m_p_player, m_p_stage, m_p_gimmick_manager, m_game_data);
	m_p_collision_manager->CheckPlayerCollisionY(m_p_player, m_p_stage, m_p_gimmick_manager, m_game_data);
	m_p_enemy_manager->Update();
	m_p_item_manager->Update();
	m_p_camera->Update();
	
	// アイテム接触判定
	for (auto& item : m_p_item_manager->GetItems())
	{
		HitPlayerItem(m_p_player->GetRect(), item->GetRect(), item, p_sound_manager);
	}

	// 敵接触判定
	for (auto& enemy : m_p_enemy_manager->GetEnemies())
	{
		// プレイヤーが敵の索敵範囲と接触している場合、敵の追跡処理
		if (m_p_player->GetRect().IsCollision(enemy->GetSearchRange()))
		{
			enemy->TrackPlayer(m_p_player->GetPlayerPos());
		}
		else
		{
			enemy->ReturnToInitPos();
		}

		// 敵本体との接触判定
		HitPlayerEnemy(m_p_player->GetRect(), enemy->GetRect());
	}

	// 死亡後シーン遷移のトリガーオン
	if (!m_p_player->GetIsAlive())
	{
		m_p_player->SetPlayerPosX(m_game_data.m_spawn_pos.x);
		m_p_player->SetPlayerPosY(m_game_data.m_spawn_pos.y);

		m_p_player->SetIsAlive(true);
		//m_scene_result = SceneResult::Gameover;
		//m_is_scene_end = true;
		return;
	}


	// クリア判定後次のステージへ
	if (m_current_stage_num != 2 && m_p_stage->GetIsGoal())
	{
		m_current_stage_num++;
		LoadNextStage();
	}
	// 最終ステージクリア判定後シーン遷移のトリガーオン
	else if (m_current_stage_num == 2 && m_p_stage->GetIsGoal())
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

	// 星のかけらカウントUIの描画
	DrawGraphF(1600.0f, 0.0f, m_collect_bg_handle, true);
	DrawGraphF(1680.0f, 30.0f, m_piece_ui_handle, true);
	DrawFormatStringToHandle(1800.0f, 50.0f, GetColor(0, 105,148), 
		m_collect_font_handle, "%d", m_p_player->GetPlayerCollectItem());

	// ストーリー中の場合ストーリーのテキストboxを描画
	if (m_is_story)
	{
		m_story_manager.Draw();
	}

	// ポーズ中で設定が開かれた場合最前面に設定を描画、それ以外はポーズメニューを描画
	if (m_is_pause)
	{
		if (m_p_menu_pause->GetCurrentState() == MenuPause::MenuPauseState::SelectedConfig)
		{
			m_config.Draw();
		}
		else
		{
			m_p_menu_pause->Draw();
		}
	}
}

void SceneMain::HitPlayerEnemy(const Rect& player_rect, const Rect& enemy_rect)
{
	// プレイヤーが敵に接している場合プレイヤー死亡
	if (player_rect.IsCollision(enemy_rect))
	{
		m_p_player->SetIsAlive(false);
	}
}

void SceneMain::HitPlayerItem(const Rect& player_rect, const Rect& item_rect,
	std::shared_ptr<Piece> item, std::shared_ptr<SoundManager> p_sound_manager)
{
	// プレイヤーがアイテムに接触した場合取得
	if (player_rect.IsCollision(item_rect))
	{
		// カウントを1つずつにするためif文
		if (!item->GetIsCollected())
		{
			p_sound_manager->PlaySE(SoundManager::SeType::Item);
			m_p_player->CountItem();
		}
		item->Collect();
	}
}

void SceneMain::LoadNextStage()
{
	// 新しいステージ、エネミー、ギミックポインタを生成
	m_p_stage = std::make_shared<Stage>(m_current_stage_num);
	m_p_enemy_manager = std::make_shared<EnemyManager>(m_current_stage_num);
	m_p_gimmick_manager = std::make_shared<GimmickManager>(m_current_stage_num);

	// プレイヤーにステージポインタをセット
	m_p_player->SetStage(m_p_stage);

	// エネミーそれぞれにステージポインタをセット
	for (auto& enemy : m_p_enemy_manager->GetEnemies())
	{
		enemy->SetStage(m_p_stage);
	}

	// 初期化
	m_p_stage->Init();
	m_p_enemy_manager->Init();
	m_p_gimmick_manager->Init();

	// プレイヤーをステージの初期スポーンへ移動
	m_p_player->SetPlayerPosX(m_game_data.m_spawn_pos.x);
	m_p_player->SetPlayerPosY(m_game_data.m_spawn_pos.y);
}