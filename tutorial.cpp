//======================================================
//
//チュートリアルシーン[game.cpp]
//Author:石原颯馬
//
//======================================================
#include "tutorial.h"
#include "input.h"
#include "texture.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"
#include "character.h"
#include "player.h"
#include "objloader.h"
#include "switchmanager.h"
#include "block3D.h"

//シーン系
#include "result.h"

//UI系
#include "fade.h"

//仮
#include "goal.h"

//=================================
//コンストラクタ
//=================================
CTutorial::CTutorial()
{
	m_pPlayer = nullptr;
	m_pSwitchManager = nullptr;
	m_pFade = nullptr;
}

//=================================
//デストラクタ
//=================================
CTutorial::~CTutorial()
{
}

//=================================
//初期化
//=================================
HRESULT CTutorial::Init(void)
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
	CObjLoader::LoadData("data\\tut_mapdata_tutorial.ismd");
	
	//キャラ生成
	CCharacter::Create(D3DXVECTOR3(100.0f,150.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);
	return S_OK;
}

//=================================
//終了
//=================================
void CTutorial::Uninit(void)
{
	//オブジェ全破棄
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}

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
void CTutorial::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボード取得
	CGoal* pGoal = CGoal::GetTop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	bool bGoal = false;

	//終了判定
	if (pGoal != nullptr)
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

	//チュートリアルスキップ
	if (pKeyboard->GetTrigger(DIK_P) == true)
	{
		bGoal = true;
	}

	if (bGoal == true)
	{//ゴールした
		m_pPlayer->SetControll(false);
		if (m_pFade == nullptr)
		{
			//フェード出す
			m_pFade = CFade::Create(CScene::MODE_GAME);

			//BGM再生
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_OUT);
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
void CTutorial::Draw(void)
{
	//普段はすべてCObjectクラス継承してるものが動いているので自動描画
	//ポーズの中身もすべてCObjectクラス継承してるので自動描画
	//よってここですることはない
}