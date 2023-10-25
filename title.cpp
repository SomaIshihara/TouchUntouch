//======================================================
//
//タイトルシーン[title.cpp]
//Author:石原颯馬
//
//======================================================
#include "texture.h"
#include "title.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "object2D.h"

//静的メンバ変数

//=================================
//コンストラクタ
//=================================
CTitle::CTitle()
{
	m_pFade = nullptr;
	m_pStart = nullptr;
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
	//タイトルロゴ
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 300.0f, 0.0f), CManager::VEC3_ZERO, 1180.0f, 244.0f, CObject::PRIORITY_UI)->BindTexture(CTexture::PRELOAD_00_TITLELOGO);

	//スタート文字
	m_pStart = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_UI);
	m_pStart->BindTexture(CTexture::PRELOAD_01_STARTKB);

	//BGM再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_OUT);

	return S_OK;
}

//=================================
//終了
//=================================
void CTitle::Uninit(void)
{
	//音停止
	CManager::GetInstance()->GetSound()->Stop();

	//オブジェ全破棄
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}
}

//=================================
//更新
//=================================
void CTitle::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//ゲームパッド接続
		m_pStart->BindTexture(CTexture::PRELOAD_02_STARTGP);
	}
	else
	{//未接続
		m_pStart->BindTexture(CTexture::PRELOAD_01_STARTKB);
	}

	if (m_pFade == nullptr && CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{//スペース押された
		m_pFade = CFade::Create(CScene::MODE_TUTORIAL);

		//SE再生
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
	}
}

//=================================
//描画
//=================================
void CTitle::Draw(void)
{
}
