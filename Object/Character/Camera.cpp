#include "../../GameConst.h"
#include "Player.h"
#include "Camera.h"

Camera::Camera() :
	m_pos(Game::SCREEN_HALF_WIDTH, 0.0f)
{

}

void Camera::Init()
{
	m_pos.y = m_p_player->GetPlayerPos().y;
}

void Camera::Update()
{
	UpdateCameraPos();
}

void Camera::UpdateCameraPos()
{
	// x座標は固定し、プレイヤーのy座標を元にカメラのy座標を決定
	m_pos.y = m_p_player->GetPlayerPos().y;
}