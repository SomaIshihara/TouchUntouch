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
#include "button3D.h"
#include "sound.h"
#include "objectX.h"
#include "meshsky.h"
#include "meshField.h"

//�}�N��
#define TITLE_CAMERA_ROT	(CAMERA_MOU_ROT_SPEED * 0.15f)

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
	
}

//=================================
//�`��
//=================================
void CTitle::Draw(void)
{
}
