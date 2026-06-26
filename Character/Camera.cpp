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
	// プレイヤーの座標を元にカメラの座標を決定
	m_Pos = m_pPlayer->GetPlayerPos();
}