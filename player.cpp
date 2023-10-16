//======================================================
//
//�v���C���[����[player.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "camera.h"

//=================================
//�R���X�g���N�^
//=================================
CPlayer::CPlayer()
{

}

//=================================
//�f�X�g���N�^
//=================================
CPlayer::~CPlayer()
{}

//=================================
//������
//=================================
HRESULT CPlayer::Init(void)
{
	m_controllType = CCharacter::TYPE_A;
	return S_OK;
}

//=================================
//�I��
//=================================
void CPlayer::Uninit(void)
{
	
}

//=================================
//�X�V
//=================================
void CPlayer::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾
	
	//�ړ�
	if (pKeyboard->GetPress(DIK_A) == true)
	{//A�L�[��������Ă���
		m_nPressMove = DIK_A;
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{//D�L�[��������Ă���
		m_nPressMove = DIK_D;
	}
	else
	{//����������Ă��Ȃ�
		m_nPressMove = 0;
	}

	//�W�����v
	m_bPressJump = (pKeyboard->GetTrigger(DIK_SPACE) == true) ? true : false;

	//�L�����ؑ�
	if (pKeyboard->GetTrigger(DIK_S) == true)
	{
		m_controllType = (m_controllType == CCharacter::TYPE_A) ? CCharacter::TYPE_B : CCharacter::TYPE_A;
	}
}

//=================================
//�ړ�
//=================================
void CPlayer::Move(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾
	CCamera* pCamera = CManager::GetInstance()->CManager::GetInstance()->GetCamera();					//�J�����擾
	D3DXVECTOR3 move = CManager::VEC3_ZERO;
	D3DXVECTOR3 rot = pCamera->GetRot();
	//�ړ�
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

	//�ړ�
	
}