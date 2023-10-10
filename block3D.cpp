//======================================================
//
//�u���b�N����(3D)[block3D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "block3D.h"
#include "xmodel.h"

//�ÓI�����o�ϐ�
CBlock3D* CBlock3D::m_pTop = nullptr;
CBlock3D* CBlock3D::m_pCur = nullptr;
int CBlock3D::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CBlock3D::CBlock3D()
{
	//�N���A
	CObjectX::SetPos(CManager::VEC3_ZERO);
	CObjectX::SetRot(CManager::VEC3_ZERO);
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

		CXModel* pModel = CXModel::Load("data\\MODEL\\OBJECT\\block_univ.x");
		pBlock->SetModel(pModel);

		D3DXVECTOR3 vtxMin, vtxMax;
		pModel->GetCollision().GetVtx(&vtxMin, &vtxMax);
		pBlock->m_fWidth = vtxMax.x - vtxMin.x;
		pBlock->m_fHeight = vtxMax.y - vtxMin.y;
		pBlock->m_fDepth = vtxMax.z - vtxMin.z;

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
