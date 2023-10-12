//======================================================
//
//�^�C�g���V�[��[title.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "precompile.h"
#include "texture.h"
#include "title.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "sound.h"

//�ÓI�����o�ϐ�

//=================================
//�R���X�g���N�^
//=================================
CTitle::CTitle()
{
	
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
	if (m_pFade == nullptr && CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE))
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
