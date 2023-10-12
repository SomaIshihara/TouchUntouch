//======================================================
//
//�X�C�b�`����[switch.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "switch.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"

//�ÓI�����o�ϐ�
CXModel* CSwitch::m_pModelBase = nullptr;
CXModel* CSwitch::m_pModelMove = nullptr;
CSwitch* CSwitch::m_pTop = nullptr;
CSwitch* CSwitch::m_pCur = nullptr;
int CSwitch::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CSwitch::CSwitch(int nPriority) : CObject(nPriority)
{
	m_pObjBase = nullptr;
	m_pObjMove = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_type = TYPE_MAX;

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
CSwitch::~CSwitch()
{
}

//=================================
//������
//=================================
HRESULT CSwitch::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CSwitch::Uninit(void)
{
	//���f���j��
	if (m_pObjBase != nullptr)
	{
		m_pObjBase->Uninit();
		m_pObjBase = nullptr;
	}
	if (m_pObjMove != nullptr)
	{
		m_pObjMove->Uninit();
		m_pObjMove = nullptr;
	}

	Release();
}

//=================================
//�X�V
//=================================
void CSwitch::Update(void)
{
	if (m_bPush == true)
	{
		CManager::GetDebProc()->Print("�v�`�v�`\n");
	}

	m_bPush = false;	//�������񉟂���Ă��Ȃ���Ԃɂ���i�󋵂ɉ����ăL�����N�^�[�������j
}

//=================================
//�`��
//=================================
void CSwitch::Draw(void)
{
	//�K�v�Ȃ�
}

//=================================
//����
//=================================
CSwitch* CSwitch::Create(const TYPE type)
{
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pSwitch = new CSwitch;

		//������
		pSwitch->Init();

		//�f�[�^�ݒ�
		pSwitch->m_pos = D3DXVECTOR3(80.0f, -20.0f, 0.0f);
		pSwitch->m_type = type;

		//���f�����ǂݍ��܂�ĂȂ���Γǂݍ���
		if (m_pModelBase == nullptr)
		{//�y�䂪�ʂ��
			m_pModelBase = CXModel::Load("data\\MODEL\\OBJECT\\switch\\switch_01.x");
		}
		if (m_pModelMove == nullptr)
		{//�y�䂪�ʂ��
			m_pModelMove = CXModel::Load("data\\MODEL\\OBJECT\\switch\\switch_02.x");
		}

		//���f������
		pSwitch->m_pObjBase = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::VEC3_ZERO, m_pModelBase);
		pSwitch->m_pObjMove = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, 10.0f, 0.0f), CManager::VEC3_ZERO, m_pModelMove);

		return pSwitch;
	}

	return nullptr;
}

//=================================
//���O
//=================================
void CSwitch::Exclusion(void)
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
