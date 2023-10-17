//======================================================
//
//�Q�[���V�[��[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "game.h"
#include "ranking.h"
#include "pause.h"
#include "result.h"
#include "texture.h"
#include "meshField.h"
#include "score.h"
#include "timer.h"
#include "objectX.h"
#include "meshsky.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "bg.h"
#include "sound.h"
#include "block3D.h"
#include "character.h"
#include "xmodel.h"
#include "switch.h"
#include "player.h"
#include "goal.h"
#include "item.h"

//UI�n
#include "timer.h"
#include "score.h"

//�ÓI�����o�ϐ�
const int CGame::CDSTART_TIME = MAX_FPS;

//=================================
//�R���X�g���N�^
//=================================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pTimer = nullptr;
	m_pScore = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CGame::~CGame()
{
}

//=================================
//������
//=================================
HRESULT CGame::Init(void)
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
	}

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//UI-------------------------------------------
	//�X�R�A�i�����j
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH + 8.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pScore->BindTexture(3);
	CItem::SetScoreInterface(m_pScore);

	//�X�R�A�i�����j
	CObject2D* pObj2D = CObject2D::Create(D3DXVECTOR3(988.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_UI);
	pObj2D->BindTexture(5);

	//�^�C�}�[����
	pObj2D = CObject2D::Create(D3DXVECTOR3(68.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_UI);
	pObj2D->BindTexture(4);

	//�^�C�}�[�i�����j
	m_pTimer = CTimer::Create(D3DXVECTOR3(264.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pTimer->BindTexture(3);

	//UI-------------------------------------------


	//���u��
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->ResetPos();
	CBlock3D::Create(D3DXVECTOR3(0.0f,-70.0f,0.0f), CBlock3D::TYPE_NORMAL);
	CSwitch::Create(D3DXVECTOR3(-80.0f, -20.0f, 0.0f),CSwitch::TYPE_A);
	CCharacter::Create(D3DXVECTOR3(20.0f,50.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(-20.0f, 50.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);
	CGoal::Create(D3DXVECTOR3(150.0f, -20.0f, 0.0f));
	CItem::Create(D3DXVECTOR3(150.0f, 50.0f, 0.0f), CManager::VEC3_ZERO);
	return S_OK;
}

//=================================
//�I��
//=================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll();
	CManager::GetInstance()->GetSound()->Stop();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

//=================================
//�X�V
//=================================
void CGame::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}
}

//=================================
//�`��
//=================================
void CGame::Draw(void)
{
	//���i�͂��ׂ�CObject�N���X�p�����Ă���̂������Ă���̂Ŏ����`��
	//�|�[�Y�̒��g�����ׂ�CObject�N���X�p�����Ă�̂Ŏ����`��
	//����Ă����ł��邱�Ƃ͂Ȃ�
}