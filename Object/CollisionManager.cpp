#include "../GameConst.h"
#include "../Stage/Stage.h"
#include "Character/Player.h"
#include "Gimmick/GimmickManager.h"
#include "Gimmick/GimmickBase.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{

}

void CollisionManager::CheckPlayerCollision(
	std::shared_ptr<Player> p_player, std::shared_ptr<Stage> p_stage,
	std::shared_ptr<GimmickManager> p_gimmick_manager)
{
	// 衝突したチップの矩形
	Rect chip_rect;

	// 位置補正後座標
	float pos_x = p_player->GetPlayerPos().x;
	float pos_y = p_player->GetPlayerPos().y;

	// 横移動、コリジョン更新
	p_player->MovePlayerX();

	// 横画面外に行けないようにする
	if (p_player->GetPlayerPos().x < 0.0f + (p_player->GetCollisionWidth() * 0.5f))
	{
		p_player->SetPlayerPosX(p_player->GetCollisionWidth() * 0.5f);
	}
	else if (p_player->GetPlayerPos().x + (p_player->GetCollisionWidth() * 0.5f) > static_cast<float>(Game::SCREEN_WIDTH))
	{
		p_player->SetPlayerPosX(static_cast<float>(Game::SCREEN_WIDTH));
	}

	// 画面外不可処理後、コリジョンの更新
	p_player->UpdateRect();

	// ステージと衝突した場合 //
	if (p_stage->IsCollision(p_player->GetRect(), chip_rect))
	{
		// 横からの衝突をチェック
		if (p_player->GetPlayerMove().x > 0.0f)
		{
			pos_x = chip_rect.GetLeftEdge() - p_player->GetCollisionWidth() * 0.5f;
		}
		else if (p_player->GetPlayerMove().x < 0.0f)
		{
			pos_x = chip_rect.GetRightEdge() + p_player->GetCollisionWidth() * 0.5f;
		}

		p_player->SetPlayerMoveX(0.0f);
		p_player->SetPlayerPosX(pos_x);
		// コリジョン更新
		p_player->UpdateRect();
	}

	// ステージとの接触判定
	p_stage->IsTrigger(p_player->GetRect(), chip_rect);

	// ギミックと衝突した場合 //
	for (auto& gimmick : p_gimmick_manager->GetGimmicks())
	{
		CheckGimmickX(p_player, gimmick);
	}


	// 縦移動の更新、コリジョンの更新
	p_player->MovePlayerY();

	// ステージと衝突した場合 //
	if (p_stage->IsCollision(p_player->GetRect(), chip_rect))
	{
		// 縦からの衝突をチェック
		if (p_player->GetPlayerMove().y > 0.0f)
		{
			pos_y = chip_rect.GetTopEdge() - p_player->GetCollisionHeight() * 0.5f;
			p_player->SetPlayerMoveY(0.0f);
			p_player->SetIsGround(true);
		}
		else if (p_player->GetPlayerMove().y < 0.0f)
		{
			pos_y = chip_rect.GetBottomEdge() + p_player->GetCollisionHeight() * 0.5f;
			p_player->SetPlayerMoveY(p_player->GetPlayerMove().y * -1.0f);
		}

		p_player->SetPlayerPosY(pos_y);
		// コリジョン更新
		p_player->UpdateRect();
	}

	// ステージとの接触判定
	p_stage->IsTrigger(p_player->GetRect(), chip_rect);

	// ギミックと衝突した場合 //
	for (auto& gimmick : p_gimmick_manager->GetGimmicks())
	{
		CheckGimmickY(p_player, gimmick);
	}
}

void CollisionManager::CheckGimmickX(
	std::shared_ptr<Player> p_player, std::shared_ptr<GimmickBase> p_gimmick)
{
	// プレイヤーがギミックに接している場合プレイヤー座標をセット
	if (p_player->GetRect().IsCollision(p_gimmick->GetRect()))
	{
		// 横からの衝突をチェック
		if (p_player->GetPlayerMove().x > 0.0f)
		{
			p_player->SetPlayerPosX(
				p_gimmick->GetRect().GetLeftEdge() - p_player->GetCollisionWidth() * 0.5f);
		}
		else if (p_player->GetPlayerMove().x < 0.0f)
		{
			p_player->SetPlayerPosX(
				p_gimmick->GetRect().GetRightEdge() + p_player->GetCollisionWidth() * 0.5f);
		}
	}
}

void CollisionManager::CheckGimmickY(
	std::shared_ptr<Player> p_player, std::shared_ptr<GimmickBase> p_gimmick)
{
	// プレイヤーがギミックに接している場合プレイヤー座標をセット
	if (p_player->GetRect().IsCollision(p_gimmick->GetRect()))
	{
		// プレイヤーが上から接した場合
		if (p_player->GetPlayerMove().y > 0.0f)
		{
			p_player->SetPlayerPosY(
				p_gimmick->GetRect().GetTopEdge() - p_player->GetCollisionHeight() * 0.5f);

			p_player->SetPlayerMoveY(0.0f);
			p_player->SetIsGround(true);
		}
		// プレイヤーが下から接した場合
		else if (p_player->GetPlayerMove().y < 0.0f)
		{
			p_player->SetPlayerPosY(
				p_gimmick->GetRect().GetBottomEdge() + p_player->GetCollisionHeight() * 0.5f);

			p_player->SetPlayerMoveY(p_player->GetPlayerMove().y * -1.0f);
		}
	}
}

