//======================================================
//
//リザルトシーン[result.cpp]
//Author:石原颯馬
//
//======================================================
#include "precompile.h"
#include "manager.h"
#include "result.h"
#include "game.h"
#include "fade.h"
#include "texture.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "button2D.h"
#include "sound.h"

//静的メンバ変数


//=================================
//コンストラクタ
//=================================
CResult::CResult()
{
	
}

//=================================
//デストラクタ
//=================================
CResult::~CResult()
{
}

//=================================
//初期化
//=================================
HRESULT CResult::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CResult::Uninit(void)
{
	
}

//=================================
//更新
//=================================
void CResult::Update(void)
{
	
}

//=================================
//描画
//=================================
void CResult::Draw(void)
{
	//勝手にやってくれる
}

//=================================
//生成
//=================================
CResult* CResult::Create(void)
{
	CResult* pResult = nullptr;

	if (pResult == nullptr)
	{
		//オブジェクト2Dの生成
		pResult = new CResult;

		//初期化
		pResult->Init();

		return pResult;
	}
	else
	{
		return nullptr;
	}
}
