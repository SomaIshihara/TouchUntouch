//======================================================
//
//���U���g�V�[��[result.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "precompile.h"
#include "manager.h"
#include "result.h"
#include "game.h"
#include "fade.h"
#include "texture.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "button2D.h"
#include "sound.h"

//�ÓI�����o�ϐ�


//=================================
//�R���X�g���N�^
//=================================
CResult::CResult()
{
	
}

//=================================
//�f�X�g���N�^
//=================================
CResult::~CResult()
{
}

//=================================
//������
//=================================
HRESULT CResult::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CResult::Uninit(void)
{
	
}

//=================================
//�X�V
//=================================
void CResult::Update(void)
{
	
}

//=================================
//�`��
//=================================
void CResult::Draw(void)
{
	//����ɂ���Ă����
}

//=================================
//����
//=================================
CResult* CResult::Create(void)
{
	CResult* pResult = nullptr;

	if (pResult == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pResult = new CResult;

		//������
		pResult->Init();

		return pResult;
	}
	else
	{
		return nullptr;
	}
}
