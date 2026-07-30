#include "../../GameConst.h"
#include "Camera.h"
#include "Player.h"

Camera::Camera() :
	m_pos(Game::SCREEN_HALF_WIDTH, 0.0f)
{

}

void Camera::Update()
{
	UpdateCameraPos();
}

void Camera::UpdateCameraPos()
{
	// プレイヤーのy座標を元にカメラのy座標を決定
	m_pos.y = m_p_player->GetPlayerPos().y;
}