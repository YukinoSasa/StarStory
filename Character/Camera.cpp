#include "Camera.h"
#include "Player.h"

Camera::Camera() :
	m_Pos(0.0f, 0.0f)
{

}

Camera::~Camera()
{

}

void Camera::Init()
{

}

void Camera::Update()
{
	UpdateCameraPos();
}

void Camera::UpdateCameraPos()
{
	m_Pos.m_x = 960.0f;
	// プレイヤーのy座標を元にカメラのy座標を決定
	m_Pos.m_y = m_pPlayer->GetPlayerPos().m_y;
}