//======================================================
//
//�u���b�N����(3D)[block3D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "block3D.h"
#include "renderer.h"
#include "collision.h"
#include "xmodel.h"
#include "switchmanager.h"

//�ÓI�����o�ϐ�
CBlock3D* CBlock3D::m_pTop = nullptr;
CBlock3D* CBlock3D::m_pCur = nullptr;
int CBlock3D::m_nNumAll = 0;
CSwitchManager* CBlock3D::m_pSwitchManager = nullptr;

//=================================
//�R���X�g���N�^
//=================================
CBlock3D::CBlock3D(int nPriority) : CObjectX(nPriority)
{
	//�N���A
	CObjectX::SetPos(CManager::VEC3_ZERO);
	CObjectX::SetRot(CManager::VEC3_ZERO);

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
CBlock3D::~CBlock3D()
{
}

//=================================
//������
//=================================
HRESULT CBlock3D::Init(void)
{
	CObjectX::Init();
	SetType(TYPE_BLOCK);

	CObjectX::SetCollider();
	CBoxCollider* pCollider = CObjectX::GetCollider();
	pCollider->SetType(CBoxCollider::TYPE_COLLISION);
	return S_OK;
}

//=================================
//�I��
//=================================
void CBlock3D::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//�X�V
//=================================
void CBlock3D::Update(void)
{
	//�X�C�b�`�ɉ����������蔻��
	if (m_type == TYPE_GIMMICK_01 || m_type == TYPE_GIMMICK_02)
	{//�M�~�b�N�n�̏ꍇ�s��
		if (m_pSwitchManager->IsPush()[m_type - 1] == true)
		{
			this->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
			if (m_type == TYPE_GIMMICK_01)
			{//��
				SetColor(true, D3DXCOLOR(0xffab7fc7));
			}
			else if (m_type == TYPE_GIMMICK_02)
			{//���F
				SetColor(true, D3DXCOLOR(0xfff7ea31));
			}
		}
		else
		{
			this->GetCollider()->SetType(CBoxCollider::TYPE_NONE);
			if (m_type == TYPE_GIMMICK_01)
			{//��
				SetColor(true, D3DXCOLOR(0x66ab7fc7));
			}
			else if (m_type == TYPE_GIMMICK_02)
			{//���F
				SetColor(true, D3DXCOLOR(0x66f7ea31));
			}
		}
	}

	CObjectX::Update();
}

//=================================
//�`��
//=================================
void CBlock3D::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//����
//=================================
CBlock3D* CBlock3D::Create(const D3DXVECTOR3 pos, const TYPE type)
{
	CBlock3D* pBlock = nullptr;

	if (pBlock == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CBlock3D;

		//������
		pBlock->Init();

		//�f�[�^�ݒ�
		pBlock->SetPos(pos);
		pBlock->m_type = type;
		if (type == TYPE_A)
		{
			pBlock->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_A);
			pBlock->SetColor(true, D3DXCOLOR(0x66f39aac));
		}
		else if (type == TYPE_B)
		{
			pBlock->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_B);
			pBlock->SetColor(true, D3DXCOLOR(0x6668c7ec));
		}
		else
		{
			pBlock->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);

			if (type == TYPE_GIMMICK_01)
			{//��
				pBlock->SetColor(true, D3DXCOLOR(0x66ab7fc7));
			}
			else if (type == TYPE_GIMMICK_02)
			{//���F
				pBlock->SetColor(true, D3DXCOLOR(0x66f7ea31));
			}
		}

		pBlock->SetModel(CXModel::Load("data\\MODEL\\block_univ.x"));

		return pBlock;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//���O
//=================================
void CBlock3D::Exclusion(void)
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

	CObjectX::Exclusion();	//�e�I�u�W�F�̏��O���s��
}
