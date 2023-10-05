//======================================================
//
//�����L���O�V�[��[ranking.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "precompile.h"
#include "texture.h"
#include "ranking.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "sound.h"

//�ÓI�����o�ϐ�
const int CRanking::MAX_RANK = 5;

//=================================
//�R���X�g���N�^
//=================================
CRanking::CRanking()
{
}

//=================================
//�f�X�g���N�^
//=================================
CRanking::~CRanking()
{
}

//=================================
//������
//=================================
HRESULT CRanking::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CRanking::Uninit(void)
{
	CObject::ReleaseAll();
}

//=================================
//�X�V
//=================================
void CRanking::Update(void)
{
	
}

//=================================
//�`��
//=================================
void CRanking::Draw(void)
{
}

//=================================
//�����L���O�ݒ�
//=================================
void CRanking::Set(const int nScore)
{
	
}

//=================================
//�����L���O�ǂݍ���
//=================================
void CRanking::Load(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != nullptr)
	{//�����L���O�t�@�C��������i�ǂݍ��݁j
		fread(&pRanking[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);	//����
	}
	else
	{//�����L���O�t�@�C�����Ȃ��i�V�K�쐬�j
		for (int cnt = 0; cnt < MAX_RANK; cnt++)
		{
			pRanking[cnt] = 0;	//�Ƃ肠����0�Ŗ��߂�
		}
		Save(pRanking);
	}
}

//=================================
//�����L���O��������
//=================================
void CRanking::Save(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "wb");

	assert(("�������݃��[�h�ŊJ���Ȃ�������I��Ղ��ˁI", pFile != nullptr));

	//�J�����̂Ői�߂�
	fwrite(pRanking, sizeof(long long), MAX_RANK, pFile);	//��������

	fclose(pFile);	//����
}
