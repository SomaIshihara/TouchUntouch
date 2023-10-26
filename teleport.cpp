//======================================================
//
//テレポート処理[teleport.cpp]
//Author:石原颯馬
//
//======================================================
#include "teleport.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"

//静的メンバ変数
CTeleportCollision* CTeleportCollision::m_pTop = nullptr;
CTeleportCollision* CTeleportCollision::m_pCur = nullptr;
int CTeleportCollision::m_nNumAll = 0;
CTeleportPos* CTeleportPos::m_pTop = nullptr;
CTeleportPos* CTeleportPos::m_pCur = nullptr;
int CTeleportPos::m_nNumAll = 0;

//*********************************
//テレポート当たり判定クラス
//*********************************
//=================================
//コンストラクタ
//=================================
CTeleportCollision::CTeleportCollision(int nPriority) : CObject(nPriority)
{
	m_pos = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;

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
	m_pCollider = nullptr;
	m_nNumAll++;
}

//=================================
//デストラクタ
//=================================
CTeleportCollision::~CTeleportCollision()
{
}

//=================================
//初期化
//=================================
HRESULT CTeleportCollision::Init(void)
{
	SetType(TYPE_TELEPORT);
	return S_OK;
}

//=================================
//終了
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
//更新
//=================================
void CTeleportCollision::Update(void)
{
	//必要なし
}

//=================================
//描画
//=================================
void CTeleportCollision::Draw(void)
{
	//必要なし
}

//=================================
//生成
//=================================
CTeleportCollision* CTeleportCollision::Create(const D3DXVECTOR3 pos, const int nID)
{
	CTeleportCollision* pTeleportCollision = nullptr;

	if (pTeleportCollision == nullptr)
	{
		//オブジェクト2Dの生成
		pTeleportCollision = new CTeleportCollision;

		//初期化
		pTeleportCollision->Init();

		//データ設定
		pTeleportCollision->m_pos = pos;
		pTeleportCollision->m_nID = nID;
		pTeleportCollision->m_fWidth = 100.0f;
		pTeleportCollision->m_fHeight = 100.0f;
		pTeleportCollision->m_fDepth = 100.0f;

		//当たり判定設定
		pTeleportCollision->m_pCollider = CBoxCollider::Create(pTeleportCollision);
		pTeleportCollision->m_pCollider->SetTag(CBoxCollider::TAG_UNIV);
		pTeleportCollision->m_pCollider->SetType(CBoxCollider::TYPE_TRIGGER);

		return pTeleportCollision;
	}

	return nullptr;
}

//=================================
//紐づくテレポート先の取得
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
//除外
//=================================
void CTeleportCollision::Exclusion(void)
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

//*********************************
//テレポート先クラス
//*********************************
//=================================
//コンストラクタ
//=================================
CTeleportPos::CTeleportPos(int nPriority) : CObject(nPriority)
{
	m_pos = CManager::VEC3_ZERO;

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
CTeleportPos::~CTeleportPos()
{
}

//=================================
//初期化
//=================================
HRESULT CTeleportPos::Init(void)
{
	SetType(TYPE_NONE);
	return S_OK;
}

//=================================
//終了
//=================================
void CTeleportPos::Uninit(void)
{
	Release();
}

//=================================
//更新
//=================================
void CTeleportPos::Update(void)
{
	//必要なし
}

//=================================
//描画
//=================================
void CTeleportPos::Draw(void)
{
	//必要なし
}

//=================================
//生成
//=================================
CTeleportPos* CTeleportPos::Create(const D3DXVECTOR3 pos, const int nID)
{
	CTeleportPos* pTeleportPos = nullptr;

	if (pTeleportPos == nullptr)
	{
		//オブジェクト2Dの生成
		pTeleportPos = new CTeleportPos;

		//初期化
		pTeleportPos->Init();

		//データ設定
		pTeleportPos->m_pos = pos;
		pTeleportPos->m_nID = nID;

		return pTeleportPos;
	}

	return nullptr;
}

//=================================
//除外
//=================================
void CTeleportPos::Exclusion(void)
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
