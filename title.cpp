//======================================================
//
//タイトルシーン[title.cpp]
//Author:石原颯馬
//
//======================================================
#include "precompile.h"
#include "texture.h"
#include "title.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "sound.h"

//静的メンバ変数

//=================================
//コンストラクタ
//=================================
CTitle::CTitle()
{
	
}

//=================================
//デストラクタ
//=================================
CTitle::~CTitle()
{
}

//=================================
//初期化
//=================================
HRESULT CTitle::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll();
}

//=================================
//更新
//=================================
void CTitle::Update(void)
{
	if (m_pFade == nullptr && CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{//スペース押された
		m_pFade = CFade::Create(CScene::MODE_GAME);
	}
}

//=================================
//描画
//=================================
void CTitle::Draw(void)
{
}
