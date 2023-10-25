//======================================================
//
//ポーズ画面[game.cpp]
//Author:石原颯馬
//
//======================================================
#include "pause.h"
#include "texture.h"
#include "input.h"
#include "bg.h"
#include "object2D.h"
#include "fade.h"
#include "sound.h"

//=================================
//コンストラクタ
//=================================
CPause::CPause()
{
	m_pBG = nullptr;
	m_pPauseStr = nullptr;

	for (int cnt = 0; cnt < MODE_MAX; cnt++)
	{
		m_apSelect[cnt] = nullptr;
	}

	m_bScreenShot = false;
}

//=================================
//デストラクタ
//=================================
CPause::~CPause()
{
}

//=================================
//初期化
//=================================
HRESULT CPause::Init(void)
{
	//背景
	m_pBG = CBG::Create(CObject::PRIORITY_UI);
	m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	m_pBG->BindTexture(-1);

	//文字
	m_pPauseStr = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 90.0f, 0.0f), CManager::VEC3_ZERO, 608.0f, 162.0f, CObject::PRIORITY_UI);
	m_pPauseStr->BindTexture(CTexture::PRELOAD_21_PAUSE_STR);

	//選択部
	for (int cnt = 0; cnt < MODE_MAX - 1; cnt++)
	{
		m_apSelect[cnt] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 270.0f + (180.0f * cnt), 0.0f), CManager::VEC3_ZERO, 584.0f, 126.0f, CObject::PRIORITY_UI);
		m_apSelect[cnt]->BindTexture(CTexture::PRELOAD_22_PAUSE_RESUME + cnt);
	}

	//スクショ部のみ別のところに置く
	m_apSelect[MODE_SCREENSHOT] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 131.0f, 114.0f, 0.0f), CManager::VEC3_ZERO, 132.5f, 100.0f, CObject::PRIORITY_UI);
	m_apSelect[MODE_SCREENSHOT]->BindTexture(CTexture::PRELOAD_25_PAUSE_SCREENSHOT);

	return S_OK;
}

//=================================
//終了
//=================================
void CPause::Uninit(void)
{
	if (m_pBG != nullptr)
	{
		m_pBG->Uninit();
		m_pBG = nullptr;
	}
	if (m_pPauseStr != nullptr)
	{
		m_pPauseStr->Uninit();
		m_pPauseStr = nullptr;
	}

	//選択部
	for (int cnt = 0; cnt < MODE_MAX; cnt++)
	{
		if (m_apSelect[cnt] != nullptr)
		{
			m_apSelect[cnt]->Uninit();
			m_apSelect[cnt] = nullptr;
		}
	}
}

//=================================
//更新
//=================================
void CPause::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//ゲームパッド
		//移動
		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{//上（-）
			m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
		}
		else if (pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//下（+）
			m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
		}
	}
	else
	{//キーボード
		//移動
		if (pKeyboard->GetTrigger(DIK_W) == true)
		{//上（-）
			m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
		}
		else if (pKeyboard->GetTrigger(DIK_S) == true)
		{//下（+）
			m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
		}
	}

	if (m_bScreenShot == false)
	{//通常
		if (pGamepad != nullptr && pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			Select();
		}
		else if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			Select();
		}

		//常時表示部は不透明
		m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		m_pPauseStr->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//いったんすべて半透明
		for (int cnt = 0; cnt < MODE_MAX; cnt++)
		{
			m_apSelect[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		//選択されているところだけ明るく
		m_apSelect[m_mode]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//スクショモード
		//ポーズで使うやつすべて透明
		m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pPauseStr->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		for (int cnt = 0; cnt < MODE_MAX; cnt++)
		{
			m_apSelect[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		//スクショモード解除
		if (pGamepad != nullptr && pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			m_bScreenShot = false;
		}
		else if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			m_bScreenShot = false;
		}
	}
}

//=================================
//描画
//=================================
void CPause::Draw(void)
{
	//CObjectを親にしているから勝手に描画される
}

//=================================
//選択して実行
//=================================
void CPause::Select(void)
{
	switch (m_mode)
	{
	case CPause::MODE_RESUME:
		CManager::GetInstance()->SetEnableUpdate(true);
		break;
	case CPause::MODE_RESTART:
		CManager::GetInstance()->SetEnableUpdate(true);
		CFade::Create(CScene::MODE_GAME);
		break;
	case CPause::MODE_EXIT:
		CManager::GetInstance()->SetEnableUpdate(true);
		CFade::Create(CScene::MODE_TITLE);
		break;
	case CPause::MODE_SCREENSHOT:
		m_bScreenShot = true;
		break;
	default:
		break;
	}
}
