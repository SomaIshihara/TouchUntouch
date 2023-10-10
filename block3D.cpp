//======================================================
//
//ブロック処理(3D)[block3D.cpp]
//Author:石原颯馬
//
//======================================================
#include "block3D.h"
#include "xmodel.h"

//静的メンバ変数
CBlock3D* CBlock3D::m_pTop = nullptr;
CBlock3D* CBlock3D::m_pCur = nullptr;
int CBlock3D::m_nNumAll = 0;

//=================================
//コンストラクタ
//=================================
CBlock3D::CBlock3D()
{
	//クリア
	CObjectX::SetPos(CManager::VEC3_ZERO);
	CObjectX::SetRot(CManager::VEC3_ZERO);
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
	m_nNumAll++;
}

//=================================
//デストラクタ
//=================================
CBlock3D::~CBlock3D()
{
}

//=================================
//初期化
//=================================
HRESULT CBlock3D::Init(void)
{
	CObjectX::Init();
	return S_OK;
}

//=================================
//終了
//=================================
void CBlock3D::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//更新
//=================================
void CBlock3D::Update(void)
{
	CObjectX::Update();
}

//=================================
//描画
//=================================
void CBlock3D::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//生成
//=================================
CBlock3D* CBlock3D::Create(const D3DXVECTOR3 pos, const TYPE type)
{
	CBlock3D* pBlock = nullptr;

	if (pBlock == nullptr)
	{
		//オブジェクト2Dの生成
		pBlock = new CBlock3D;

		//初期化
		pBlock->Init();

		//データ設定
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
//除外
//=================================
void CBlock3D::Exclusion(void)
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

	CObjectX::Exclusion();	//親オブジェの除外も行う
}
