//======================================================
//
//ゲームシーン[game.cpp]
//Author:石原颯馬
//
//======================================================
#include "game.h"
#include "ranking.h"
#include "pause.h"
#include "result.h"
#include "texture.h"
#include "meshField.h"
#include "score.h"
#include "timer.h"
#include "objectX.h"
#include "meshsky.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "bg.h"
#include "sound.h"
#include "block3D.h"
#include "character.h"
#include "xmodel.h"
#include "switch.h"
#include "player.h"

//静的メンバ変数
const int CGame::CDSTART_TIME = MAX_FPS;

//=================================
//コンストラクタ
//=================================
CGame::CGame()
{
	
}

//=================================
//デストラクタ
//=================================
CGame::~CGame()
{
}

//=================================
//初期化
//=================================
HRESULT CGame::Init(void)
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
	}

	CManager::GetCamera()->ResetPos();
	CBlock3D::Create(D3DXVECTOR3(0.0f,-70.0f,0.0f), CBlock3D::TYPE_NORMAL);
	CSwitch::Create(CSwitch::TYPE_A);
	CCharacter::Create(D3DXVECTOR3(20.0f,50.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(-20.0f, 50.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);
	return S_OK;
}

//=================================
//終了
//=================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll();
	CManager::GetSound()->Stop();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

//=================================
//更新
//=================================
void CGame::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();	//キーボード取得

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}
}

//=================================
//描画
//=================================
void CGame::Draw(void)
{
	//普段はすべてCObjectクラス継承してるものが動いているので自動描画
	//ポーズの中身もすべてCObjectクラス継承してるので自動描画
	//よってここですることはない
}