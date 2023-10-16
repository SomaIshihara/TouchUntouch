//======================================================
//
//�A�C�e������[item.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "item.h"
#include "xmodel.h"

//�ÓI�����o�ϐ�
CXModel* CItem::m_pModel = nullptr;
int CItem::m_nNumAll = 0;

//************************************************
//�A�C�e���e�N���X
//************************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CItem::CItem()
{
	//�l�N���A
	m_nScore = CManager::INT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�������j
//=================================
CItem::CItem(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) : CObjectX(pos, rot, m_pModel)
{
	//�l�N���A
	m_nScore = CManager::INT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CItem::~CItem()
{
}

//=================================
//������
//=================================
HRESULT CItem::Init(void)
{
	SetType(TYPE_ITEM);
	return CObjectX::Init();
}

//=================================
//�I��
//=================================
void CItem::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//�X�V
//=================================
void CItem::Update(void)
{
	CObjectX::Update();
}

//=================================
//�`��
//=================================
void CItem::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//��������
//=================================
CItem* CItem::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CItem* pItem = NULL;

	if (pItem == NULL)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pItem = new CItem;

		//������
		pItem->Init();

		//�f�[�^�ݒ�
		pItem->m_nScore = 100;	//��
		pItem->SetPos(pos);
		pItem->SetRot(rot);

		//���f���ݒ�
		pItem->SetModel(CXModel::Load("data\\MODEL\\OBJECT\\item.x"));

		return pItem;
	}
	else
	{
		return NULL;
	}
}