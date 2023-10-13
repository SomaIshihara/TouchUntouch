//======================================================
//
//スイッチ処理[switch.cpp]
//Author:石原颯馬
//
//======================================================
#include "switch.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"

//静的メンバ変数
CXModel* CSwitch::m_pModelBase = nullptr;
CXModel* CSwitch::m_pModelMove = nullptr;
CSwitch* CSwitch::m_pTop = nullptr;
CSwitch* CSwitch::m_pCur = nullptr;
int CSwitch::m_nNumAll = 0;

//=================================
//コンストラクタ
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
	{//最後尾がいない（すなわち先頭もいない）
		m_pTop = this;			//俺が先頭
		m_pPrev = nullptr;		//前後誰もいない
		m_pNext = nullptr;
	}
	else
	{//最後尾がいる
		m_pPrev = m_pCur;		//最後尾が自分の前のオブジェ
		m_pCur->m_pNext = this;	//最後尾の次のオブジェが自分
		m_pNext = nullptr;		//自分の次のオブジェはいない
	}
	m_pCur = this;				//俺が最後尾
	m_nNumAll++;
}

//=================================
//デストラクタ
//=================================
CSwitch::~CSwitch()
{
}

//=================================
//初期化
//=================================
HRESULT CSwitch::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CSwitch::Uninit(void)
{
	//モデル破棄
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
//更新
//=================================
void CSwitch::Update(void)
{
	if (m_bPush == true)
	{
		CManager::GetDebProc()->Print("プチプチ\n");
	}

	m_bPush = false;	//いったん押されていない状態にする（状況に応じてキャラクターが押す）
}

//=================================
//描画
//=================================
void CSwitch::Draw(void)
{
	//必要なし
}

//=================================
//生成
//=================================
CSwitch* CSwitch::Create(const D3DXVECTOR3 pos, const TYPE type)
{
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{
		//オブジェクト2Dの生成
		pSwitch = new CSwitch;

		//初期化
		pSwitch->Init();

		//データ設定
		pSwitch->m_pos = pos;
		pSwitch->m_type = type;

		//モデルが読み込まれてなければ読み込み
		if (m_pModelBase == nullptr)
		{//土台がぬるぽ
			m_pModelBase = CXModel::Load("data\\MODEL\\OBJECT\\switch\\switch_01.x");
		}
		if (m_pModelMove == nullptr)
		{//土台がぬるぽ
			m_pModelMove = CXModel::Load("data\\MODEL\\OBJECT\\switch\\switch_02.x");
		}

		//モデル生成
		pSwitch->m_pObjBase = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::VEC3_ZERO, m_pModelBase);
		pSwitch->m_pObjMove = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, 10.0f, 0.0f), CManager::VEC3_ZERO, m_pModelMove);

		return pSwitch;
	}

	return nullptr;
}

//=================================
//除外
//=================================
void CSwitch::Exclusion(void)
{
	if (m_pPrev != nullptr)
	{//前にオブジェがいる
		m_pPrev->m_pNext = m_pNext;	//前のオブジェの次のオブジェは自分の次のオブジェ
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//次のオブジェの前のオブジェは自分の前のオブジェ
	}

	if (m_pCur == this)
	{//最後尾でした
		m_pCur = m_pPrev;	//最後尾を自分の前のオブジェにする
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//先頭を自分の次のオブジェにする
	}

	//成仏
	m_nNumAll--;	//総数減らす
}
