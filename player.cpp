//======================================================
//
//プレイヤー処理[player.cpp]
//Author:石原颯馬
//
//======================================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "camera.h"

//=================================
//コンストラクタ
//=================================
CPlayer::CPlayer()
{

}

//=================================
//デストラクタ
//=================================
CPlayer::~CPlayer()
{}

//=================================
//初期化
//=================================
HRESULT CPlayer::Init(void)
{
	m_controllType = CCharacter::TYPE_A;
	return S_OK;
}

//=================================
//終了
//=================================
void CPlayer::Uninit(void)
{
	
}

//=================================
//更新
//=================================
void CPlayer::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボード取得
	
	//移動
	if (pKeyboard->GetPress(DIK_A) == true)
	{//Aキーが押されている
		m_nPressMove = DIK_A;
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{//Dキーが押されている
		m_nPressMove = DIK_D;
	}
	else
	{//何も押されていない
		m_nPressMove = 0;
	}

	//ジャンプ
	m_bPressJump = (pKeyboard->GetTrigger(DIK_SPACE) == true) ? true : false;

	//キャラ切替
	if (pKeyboard->GetTrigger(DIK_S) == true)
	{
		m_controllType = (m_controllType == CCharacter::TYPE_A) ? CCharacter::TYPE_B : CCharacter::TYPE_A;
	}
}

//=================================
//移動
//=================================
void CPlayer::Move(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボード取得
	CCamera* pCamera = CManager::GetInstance()->CManager::GetInstance()->GetCamera();					//カメラ取得
	D3DXVECTOR3 move = CManager::VEC3_ZERO;
	D3DXVECTOR3 rot = pCamera->GetRot();
	//移動
	if (pKeyboard->GetPress(DIK_A) == true)
	{
		move.x += -cosf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += -sinf(rot.y) * CAMERA_MOVE_SPEED;
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{
		move.x += cosf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += sinf(rot.y) * CAMERA_MOVE_SPEED;
	}

	if (pKeyboard->GetPress(DIK_W) == true)
	{
		move.x += -sinf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += cosf(rot.y) * CAMERA_MOVE_SPEED;
	}
	else if (pKeyboard->GetPress(DIK_S) == true)
	{
		move.x += sinf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += -cosf(rot.y) * CAMERA_MOVE_SPEED;
	}

	//移動
	
}