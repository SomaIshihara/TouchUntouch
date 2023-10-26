//======================================================
//
//�e���|�[�g����[teleport.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "teleport.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"

//�ÓI�����o�ϐ�
CTeleportCollision* CTeleportCollision::m_pTop = nullptr;
CTeleportCollision* CTeleportCollision::m_pCur = nullptr;
int CTeleportCollision::m_nNumAll = 0;
CTeleportPos* CTeleportPos::m_pTop = nullptr;
CTeleportPos* CTeleportPos::m_pCur = nullptr;
int CTeleportPos::m_nNumAll = 0;

//*********************************
//�e���|�[�g�����蔻��N���X
//*********************************
//=================================
//�R���X�g���N�^
//=================================
CTeleportCollision::CTeleportCollision(int nPriority) : CObject(nPriority)
{
	m_pos = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;

	if (m_pCur == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_pTop = this;			//�����擪
		m_pPrev = nullptr;		//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_pCur;		//�Ō���������̑O�̃I�u�W�F
		m_pCur->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;		//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_pCur = this;				//�����Ō��
	m_pCollider = nullptr;
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CTeleportCollision::~CTeleportCollision()
{
}

//=================================
//������
//=================================
HRESULT CTeleportCollision::Init(void)
{
	SetType(TYPE_TELEPORT);
	return S_OK;
}

//=================================
//�I��
//=================================
void CTeleportCollision::Uninit(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	Release();
}

//=================================
//�X�V
//=================================
void CTeleportCollision::Update(void)
{
	//�K�v�Ȃ�
}

//=================================
//�`��
//=================================
void CTeleportCollision::Draw(void)
{
	//�K�v�Ȃ�
}

//=================================
//����
//=================================
CTeleportCollision* CTeleportCollision::Create(const D3DXVECTOR3 pos, const int nID)
{
	CTeleportCollision* pTeleportCollision = nullptr;

	if (pTeleportCollision == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pTeleportCollision = new CTeleportCollision;

		//������
		pTeleportCollision->Init();

		//�f�[�^�ݒ�
		pTeleportCollision->m_pos = pos;
		pTeleportCollision->m_nID = nID;
		pTeleportCollision->m_fWidth = 100.0f;
		pTeleportCollision->m_fHeight = 100.0f;
		pTeleportCollision->m_fDepth = 100.0f;

		//�����蔻��ݒ�
		pTeleportCollision->m_pCollider = CBoxCollider::Create(pTeleportCollision);
		pTeleportCollision->m_pCollider->SetTag(CBoxCollider::TAG_UNIV);
		pTeleportCollision->m_pCollider->SetType(CBoxCollider::TYPE_TRIGGER);

		return pTeleportCollision;
	}

	return nullptr;
}

//=================================
//�R�Â��e���|�[�g��̎擾
//=================================
D3DXVECTOR3 CTeleportCollision::GetFromPos(void)
{
	CTeleportPos* pPos = CTeleportPos::GetTop();

	while (pPos != nullptr)
	{
		if (pPos->GetID() == this->m_nID)
		{
			return pPos->GetPos();
		}
		pPos = pPos->GetNext();
	}

	return CManager::VEC3_ZERO;
}

//=================================
//���O
//=================================
void CTeleportCollision::Exclusion(void)
{
	if (m_pPrev != nullptr)
	{//�O�ɃI�u�W�F������
		m_pPrev->m_pNext = m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
	}

	if (m_pCur == this)
	{//�Ō���ł���
		m_pCur = m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
	}

	//����
	m_nNumAll--;	//�������炷
}

//*********************************
//�e���|�[�g��N���X
//*********************************
//=================================
//�R���X�g���N�^
//=================================
CTeleportPos::CTeleportPos(int nPriority) : CObject(nPriority)
{
	m_pos = CManager::VEC3_ZERO;

	if (m_pCur == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_pTop = this;			//�����擪
		m_pPrev = nullptr;		//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_pCur;		//�Ō���������̑O�̃I�u�W�F
		m_pCur->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;		//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_pCur = this;				//�����Ō��
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CTeleportPos::~CTeleportPos()
{
}

//=================================
//������
//=================================
HRESULT CTeleportPos::Init(void)
{
	SetType(TYPE_NONE);
	return S_OK;
}

//=================================
//�I��
//=================================
void CTeleportPos::Uninit(void)
{
	Release();
}

//=================================
//�X�V
//=================================
void CTeleportPos::Update(void)
{
	//�K�v�Ȃ�
}

//=================================
//�`��
//=================================
void CTeleportPos::Draw(void)
{
	//�K�v�Ȃ�
}

//=================================
//����
//=================================
CTeleportPos* CTeleportPos::Create(const D3DXVECTOR3 pos, const int nID)
{
	CTeleportPos* pTeleportPos = nullptr;

	if (pTeleportPos == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pTeleportPos = new CTeleportPos;

		//������
		pTeleportPos->Init();

		//�f�[�^�ݒ�
		pTeleportPos->m_pos = pos;
		pTeleportPos->m_nID = nID;

		return pTeleportPos;
	}

	return nullptr;
}

//=================================
//���O
//=================================
void CTeleportPos::Exclusion(void)
{
	if (m_pPrev != nullptr)
	{//�O�ɃI�u�W�F������
		m_pPrev->m_pNext = m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
	}

	if (m_pCur == this)
	{//�Ō���ł���
		m_pCur = m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
	}

	//����
	m_nNumAll--;	//�������炷
}
