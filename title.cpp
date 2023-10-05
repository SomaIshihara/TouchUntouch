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
#include "button3D.h"
#include "sound.h"
#include "objectX.h"
#include "meshsky.h"
#include "meshField.h"

//マクロ
#define TITLE_CAMERA_ROT	(CAMERA_MOU_ROT_SPEED * 0.15f)

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
	
}

//=================================
//描画
//=================================
void CTitle::Draw(void)
{
}
