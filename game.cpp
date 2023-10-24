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
#include "goal.h"
#include "item.h"
#include "objloader.h"
#include "switchmanager.h"
#include "block3D.h"

//シーン系
#include "result.h"

//UI系
#include "timer.h"
#include "score.h"

//仮
#include "goal.h"

//=================================
//コンストラクタ
//=================================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pTimer = nullptr;
	m_pScore = nullptr;
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
	//カメラリセット
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->ResetPos();

	//操作プレイヤーのクラス生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
	}

	//スイッチ管理オブジェ生成と設定
	m_pSwitchManager = CSwitchManager::Create();
	CBlock3D::SetSwitchManager(m_pSwitchManager);

	//UI-------------------------------------------
	//スコア（数字）
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH + 8.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pScore->BindTexture(CTexture::PRELOAD_03_NUMBER);
	CItem::SetScoreInterface(m_pScore);

	//スコア（文字）
	CObject2D* pObj2D = CObject2D::Create(D3DXVECTOR3(988.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_UI);
	pObj2D->BindTexture(CTexture::PRELOAD_05_SCORESTR);

	//タイマー文字
	pObj2D = CObject2D::Create(D3DXVECTOR3(68.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_UI);
	pObj2D->BindTexture(CTexture::PRELOAD_04_TIMERSTR);

	//タイマー（数字）
	m_pTimer = CTimer::Create(D3DXVECTOR3(264.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pTimer->BindTexture(CTexture::PRELOAD_03_NUMBER);
	m_pTimer->Set(120, CTimer::COUNT_DOWN);
	m_pTimer->Start();

	//UI-------------------------------------------
	CObjLoader::LoadData("data\\tut_mapdata_game.ismd");
	
	//キャラ生成
	CCharacter::Create(D3DXVECTOR3(100.0f,150.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);

	//BGM再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_IN);
	return S_OK;
}

//=================================
//終了
//=================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll();
	CManager::GetInstance()->GetSound()->Stop();

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
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボード取得
	CGoal* pGoal = CGoal::GetTop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	bool bGoal = false;

	//時間管理と終了判定
	if (m_pTimer->GetTime() <= 0)
	{//糸冬
		bGoal = true;
	}
	else if (pGoal != nullptr)
	{
		while (pGoal != nullptr)
		{
			if (pGoal->IsGoal() == true)
			{//糸冬
				bGoal = true;
				break;
			}
			pGoal = pGoal->GetNext();
		}
	}

	if (bGoal == true)
	{//ゴールした
		m_pPlayer->SetControll(false);
		if (m_pResult == nullptr)
		{
			m_pTimer->Stop();
			m_pResult = CResult::Create(m_pTimer->GetTime(), m_pScore->GetScore());

			//SE再生
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		else
		{
			m_pResult->Update();
		}
	}
	else
	{//ゴールしてない
		m_pPlayer->SetControll(true);
	}

	//とりあえず回す（有効・無効は上でやる）
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}

	if (pCamera != nullptr)
	{//カメラ移動
		D3DXVECTOR3 posV = pCamera->GetPosV();
		D3DXVECTOR3 posR = pCamera->GetPosR();
		CCharacter** chara = CCharacter::GetChara();

		float posXCenter = (chara[0]->GetPos().x + chara[1]->GetPos().x) * 0.5f;
		float lenXHalf = fabsf(chara[0]->GetPos().x - chara[1]->GetPos().x) * 0.5f;
		float posYCenter = (chara[0]->GetPos().y + chara[1]->GetPos().y) * 0.5f;
		float lenYHalf = fabsf(chara[0]->GetPos().y - chara[1]->GetPos().y) * 0.5f;
		posV.x = posXCenter;
		posR.x = posXCenter;
		posV.y = posYCenter;
		posR.y = posYCenter;

		pCamera->SetPosV(posV);
		pCamera->SetPosR(posR);

		if (lenXHalf * 2.0f >= 900.0f)
		{//仮
			pCamera->SetLength(lenXHalf * 2.0f);
		}
		else
		{
			pCamera->SetLength(900.0f);
		}
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