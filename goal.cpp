//======================================================
//
//ゴール処理[goal.cpp]
//Author:石原颯馬
//
//======================================================
#include "goal.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"
#include "switch.h"

//=================================
//コンストラクタ
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
	m_bGoal = false;
}

//=================================
//デストラクタ
//=================================
CGoal::~CGoal()
{
}

//=================================
//初期化
//=================================
HRESULT CGoal::Init(void)
{
	SetType(TYPE_GOAL);
	return S_OK;
}

//=================================
//終了
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
//更新
//=================================
void CGoal::Update(void)
{
	m_bGoal = true;	//ゴールしてるかもしれないのでいったんtrue
	for (int cnt = 0; cnt < CCharacter::TYPE_MAX; cnt++)
	{
		if (m_aSwitch[cnt] != nullptr && m_aSwitch[cnt]->IsPush() == false)
		{
			m_bGoal = false;	//ゴールしてないわ。falseにする
			break;
		}
	}
}

//=================================
//描画
//=================================
void CGoal::Draw(void)
{
	//必要なし
}

//=================================
//生成
//=================================
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = nullptr;

	if (pGoal == nullptr)
	{
		//オブジェクト2Dの生成
		pGoal = new CGoal;

		//初期化
		pGoal->Init();

		//データ設定
		pGoal->m_pos = pos;

		//土台生成
		pGoal->m_pBase = CObjectX::Create(pGoal->m_pos, CManager::VEC3_ZERO, CXModel::Load("data\\MODEL\\OBJECT\\Goal_Base.x"));

		//スイッチ生成
		pGoal->m_aSwitch[CCharacter::TYPE_A] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(-55.0f, 10.0f, 0.0f), CSwitch::TYPE_A);
		pGoal->m_aSwitch[CCharacter::TYPE_B] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(55.0f,10.0f,0.0f), CSwitch::TYPE_B);

		return pGoal;
	}

	return nullptr;
}