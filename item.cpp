//======================================================
//
//アイテム処理[item.cpp]
//Author:石原颯馬
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "item.h"
#include "xmodel.h"

//静的メンバ変数
CXModel* CItem::m_pModel = nullptr;
int CItem::m_nNumAll = 0;

//************************************************
//アイテム弾クラス
//************************************************
//=================================
//コンストラクタ（デフォルト）
//=================================
CItem::CItem()
{
	//値クリア
	m_nScore = CManager::INT_ZERO;
}

//=================================
//コンストラクタ（オーバーロード 位置幅高さ）
//=================================
CItem::CItem(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) : CObjectX(pos, rot, m_pModel)
{
	//値クリア
	m_nScore = CManager::INT_ZERO;
}

//=================================
//デストラクタ
//=================================
CItem::~CItem()
{
}

//=================================
//初期化
//=================================
HRESULT CItem::Init(void)
{
	SetType(TYPE_ITEM);
	return CObjectX::Init();
}

//=================================
//終了
//=================================
void CItem::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//更新
//=================================
void CItem::Update(void)
{
	CObjectX::Update();
}

//=================================
//描画
//=================================
void CItem::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//生成処理
//=================================
CItem* CItem::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CItem* pItem = NULL;

	if (pItem == NULL)
	{
		//オブジェクトアニメーション2Dの生成
		pItem = new CItem;

		//初期化
		pItem->Init();

		//データ設定
		pItem->m_nScore = 100;	//仮
		pItem->SetPos(pos);
		pItem->SetRot(rot);

		//モデル設定
		pItem->SetModel(CXModel::Load("data\\MODEL\\OBJECT\\item.x"));

		return pItem;
	}
	else
	{
		return NULL;
	}
}