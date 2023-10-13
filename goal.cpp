//======================================================
//
//�S�[������[goal.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "goal.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"
#include "switch.h"

//=================================
//�R���X�g���N�^
//=================================
CGoal::CGoal(int nPriority) : CObject(nPriority)
{
	m_aSwitch[0] = nullptr;
	m_aSwitch[1] = nullptr;
	m_pBase = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CGoal::~CGoal()
{
}

//=================================
//������
//=================================
HRESULT CGoal::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CGoal::Uninit(void)
{
	if (m_pBase != nullptr)
	{
		m_pBase->Uninit();
		m_pBase = nullptr;
	}

	for (int cnt = 0; cnt < CCharacter::TYPE_MAX; cnt++)
	{
		if (m_aSwitch[cnt] != nullptr)
		{
			m_aSwitch[cnt]->Uninit();
			m_aSwitch[cnt] = nullptr;
		}
	}
	Release();
}

//=================================
//�X�V
//=================================
void CGoal::Update(void)
{
	bool bPush = true;
	for (int cnt = 0; cnt < CCharacter::TYPE_MAX; cnt++)
	{
		if (m_aSwitch[cnt] != nullptr && m_aSwitch[cnt]->IsPush() == false)
		{
			bPush = false;
			break;
		}
	}

	if (bPush == true)
	{
		CManager::GetDebProc()->Print("�S�[��\n");
	}
}

//=================================
//�`��
//=================================
void CGoal::Draw(void)
{
	//�K�v�Ȃ�
}

//=================================
//����
//=================================
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = nullptr;

	if (pGoal == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pGoal = new CGoal;

		//������
		pGoal->Init();

		//�f�[�^�ݒ�
		pGoal->m_pos = pos;

		//�y�䐶��
		pGoal->m_pBase = CObjectX::Create(pGoal->m_pos, CManager::VEC3_ZERO, CXModel::Load("data\\MODEL\\OBJECT\\Goal_Base.x"));

		//�X�C�b�`����
		pGoal->m_aSwitch[CCharacter::TYPE_A] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(-55.0f, 10.0f, 0.0f), CSwitch::TYPE_A);
		pGoal->m_aSwitch[CCharacter::TYPE_B] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(55.0f,10.0f,0.0f), CSwitch::TYPE_B);

		return pGoal;
	}

	return nullptr;
}