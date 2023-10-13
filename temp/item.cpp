//======================================================
//
//�A�C�e������[item.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "picto.h"
#include "item.h"

//�}�N��
#define ITEMBULLET_MIN		(20)	//�A�C�e���Œ��
#define ITEMBULLET_DEGREE	(80)	//�U�ꕝ

//�ÓI�����o�ϐ�
CItemBullet* CItemBullet::m_pItemBullet[];
CXModel* CItemBullet::m_pModel = nullptr;
int CItemBullet::m_nNumAll = 0;

//************************************************
//[���g�p]2D�A�C�e���N���X
//************************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CItem::CItem(int nPriority) : CObject2D(nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�������j
//=================================
CItem::CItem(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, int nPriority) :CObject2D(pos, CManager::VEC3_ZERO, fWidth, fHeight, nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
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
	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Item_05.png");

	SetType(TYPE_ITEM);	//�^�C�v�ݒ�

	return CObject2D::Init();
}

//=================================
//�I��
//=================================
void CItem::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CItem::Update(void)
{
	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CItem::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//��������
//=================================
CItem* CItem::Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight)
{
	CItem* pItem = NULL;

	if (pItem == NULL)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pItem = new CItem(pos, fWidth, fHeight);

		//������
		pItem->Init();

		//�e�N�X�`���ݒ�
		pItem->BindTexture(pItem->m_nIdxTexture);

		return pItem;
	}
	else
	{
		return NULL;
	}
}

//************************************************
//�A�C�e���e�N���X
//************************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CItemBullet::CItemBullet()
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//���ׂĊm�F
		if (m_pItemBullet[cnt] == NULL)
		{//�����
			m_pItemBullet[cnt] = this;	//�������g�̃|�C���^��o�^
			m_nID = cnt;	//ID�o����
			m_nNumAll++;	//�������₷
			break;
		}
	}
	//�l�N���A
	m_nBulletNum = CManager::INT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�������j
//=================================
CItemBullet::CItemBullet(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) : CObjectX(pos, rot, m_pModel)
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//���ׂĊm�F
		if (m_pItemBullet[cnt] == NULL)
		{//�����
			m_pItemBullet[cnt] = this;	//�������g�̃|�C���^��o�^
			m_nID = cnt;	//ID�o����
			m_nNumAll++;	//�������₷
			break;
		}
	}
	//�l�N���A
	m_nBulletNum = CManager::INT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CItemBullet::~CItemBullet()
{
}

//=================================
//������
//=================================
HRESULT CItemBullet::Init(void)
{
	SetType(TYPE_ITEM);	//�^�C�v�ݒ�
	m_nBulletNum = rand() % (ITEMBULLET_DEGREE + 1) + ITEMBULLET_MIN;	//�e���ݒ�

	return CObjectX::Init();
}

//=================================
//�I��
//=================================
void CItemBullet::Uninit(void)
{
	//�폜
	m_pItemBullet[m_nID] = NULL;

	CObjectX::Uninit();
}

//=================================
//�X�V
//=================================
void CItemBullet::Update(void)
{
	CObjectX::Update();
}

//=================================
//�`��
//=================================
void CItemBullet::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//��������
//=================================
CItemBullet* CItemBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CItemBullet* pItem = NULL;

	if (pItem == NULL)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pItem = new CItemBullet(pos, rot);

		//������
		pItem->Init();

		return pItem;
	}
	else
	{
		return NULL;
	}
}

//=================================
//���W����
//=================================
void CItemBullet::PickBullet(CPictoTaxi * taxi)
{
	taxi->SetBullet(m_nBulletNum);
}
