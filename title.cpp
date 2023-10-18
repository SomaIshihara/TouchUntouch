//======================================================
//
//�^�C�g���V�[��[title.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "texture.h"
#include "title.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "object2D.h"

//�ÓI�����o�ϐ�

//=================================
//�R���X�g���N�^
//=================================
CTitle::CTitle()
{
	m_pFade = nullptr;
	m_pStart = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CTitle::~CTitle()
{
}

//=================================
//������
//=================================
HRESULT CTitle::Init(void)
{
	//�^�C�g�����S
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 300.0f, 0.0f), CManager::VEC3_ZERO, 1180.0f, 244.0f, CObject::PRIORITY_UI)->BindTexture(0);

	//�X�^�[�g����
	m_pStart = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_UI);
	m_pStart->BindTexture(1);

	return S_OK;
}

//=================================
//�I��
//=================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll();
}

//=================================
//�X�V
//=================================
void CTitle::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�Q�[���p�b�h�ڑ�
		m_pStart->BindTexture(2);
	}
	else
	{//���ڑ�
		m_pStart->BindTexture(1);
	}

	if (m_pFade == nullptr && CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{//�X�y�[�X�����ꂽ
		m_pFade = CFade::Create(CScene::MODE_GAME);
	}
}

//=================================
//�`��
//=================================
void CTitle::Draw(void)
{
}
