//======================================================
//
//キャラクター処理[character.cpp]
//Author:石原颯馬
//
//======================================================
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "Culc.h"
#include "file.h"
#include "block3D.h"
#include "switch.h"
#include "item.h"
#include "collision.h"
#include "teleport.h"
#include "tutorialobj.h"
#include "debugproc.h"

//静的メンバ変数
CCharacter* CCharacter::m_aChara[] = { nullptr,nullptr };
const float CCharacter::CHARA_SPEED = 3.7f;
const float CCharacter::CHARA_JUMP_POW = 6.0f;
const float CCharacter::CHARA_RESPAWN_HEIGHT = -500.0f;

//=================================
//コンストラクタ
//=================================
CCharacter::CCharacter(int nPriority) : CObject(nPriority)
{
	m_ppModel = nullptr;
	m_nNumModel = CManager::INT_ZERO;
	m_pos = CManager::VEC3_ZERO;
	m_posOld = CManager::VEC3_ZERO;
	m_posLastLanding = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_bJump = false;
	m_nCounterJumpTime = CManager::INT_ZERO;
	m_fJumpPower = CManager::FLT_ZERO;
	m_type = TYPE_MAX;
	m_pCollider = nullptr;
}

//=================================
//デストラクタ
//=================================
CCharacter::~CCharacter()
{
}

//=================================
//初期化
//=================================
HRESULT CCharacter::Init(void)
{
	SetModel();
	SetType(TYPE_CHARACTER);
	m_posOld = m_pos;
	m_pCollider = CBoxCollider::Create(this);
	m_pCollider->SetType(CBoxCollider::TYPE_COLLISION);
	return S_OK;
}

//=================================
//終了
//=================================
void CCharacter::Uninit(void)
{
	//モーション破棄
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{//一つずつ消す
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Uninit();
				delete m_ppModel[cnt];
				m_ppModel[cnt] = nullptr;
			}
		}
		delete[] m_ppModel;	//配列そのものを破棄
	}

	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	m_aChara[m_type] = nullptr;

	Release();
}

//=================================
//更新
//=================================
void CCharacter::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_posOld = m_pos;	//前の位置設定

	if (m_controllInterface->GetType() == m_type)
	{
		if (m_controllInterface->GetPress() == DIK_A)
		{
			m_move.x -= CHARA_SPEED;
		}
		else if (m_controllInterface->GetPress() == DIK_D)
		{
			m_move.x += CHARA_SPEED;
		}
	}

	//ジャンプカウンタ増やす
	m_nCounterJumpTime++;

	//重力加速度によるYの移動量変更
	m_move.y = m_fJumpPower - (ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS);

	//当たり判定
	m_pCollider->CollisionCheck();

	//ボタンは押す・アイテムは拾う
	for (int cnt = 0; cnt < m_pCollider->GetResult().collList.size(); cnt++)
	{
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_SWITCH)
		{
			CSwitch* pSwitch = CSwitch::GetTop();
			while (pSwitch != nullptr)
			{
				if (pSwitch->GetMove() == m_pCollider->GetResult().collList[cnt])
				{
					pSwitch->Push();
					break;
				}
				pSwitch = pSwitch->GetNext();
			}
		}
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_ITEM)
		{
			CItem* pItem = CItem::GetTop();
			while (pItem != nullptr)
			{
				if (pItem == m_pCollider->GetResult().collList[cnt])
				{
					pItem->Get();
					break;
				}
				pItem = pItem->GetNext();
			}
		}
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_TELEPORT)
		{
			CTeleportCollision* pTeleport = CTeleportCollision::GetTop();
			while (pTeleport != nullptr)
			{
				if (pTeleport == m_pCollider->GetResult().collList[cnt])
				{
					m_pos = pTeleport->GetFromPos();
					break;
				}
				pTeleport = pTeleport->GetNext();
			}
		}
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_TUTORIALOBJ)
		{
			CTutorialObj* pTutorialObj = CTutorialObj::GetTop();
			while (pTutorialObj != nullptr)
			{
				if (pTutorialObj == m_pCollider->GetResult().collList[cnt])
				{
					pTutorialObj->Popup();
					break;
				}
				pTutorialObj = pTutorialObj->GetNext();
			}
		}
	}

	if (m_pCollider->GetResult().bHit[1] == true)
	{//着地した
		m_bJump = false;
		m_nCounterJumpTime = 0;
		m_fJumpPower = 0.0f;
		m_posLastLanding = m_pos;
	}
	else
	{
		m_bJump = true;
	}
	
	//ジャンプ
	if (m_bJump == false && m_controllInterface->GetType() == m_type && m_controllInterface->IsJump() == true)
	{//ジャンプ処理
		m_bJump = true;
		m_nCounterJumpTime = 0;
		m_fJumpPower = CHARA_JUMP_POW;
	}

	//リスポーン判定
	if (m_pos.y <= CHARA_RESPAWN_HEIGHT)
	{
		m_pos = m_posLastLanding;
		m_pos.y += 30.0f;
	}

	//移動量減衰
	m_move.x = CManager::FLT_ZERO;
	m_move.z = CManager::FLT_ZERO;

	//モデル設定
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Update();
			}
		}
	}

	//モーションがある
	if (m_pMotion != nullptr)
	{
		//モーション更新
		m_pMotion->Update();
	}
}

//=================================
//描画
//=================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイス取得
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();			//テクスチャオブジェクト取得
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//計算用
	D3DMATERIAL9 matDef;												//現在のマテリアル保存用

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//モデル取得
	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//アルファテスト有効化
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
	pRenderer->SetEnableAlplaTest(true);

	//モデル描画
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Draw();
			}
		}
	}

	//アルファテスト無効化
	pRenderer->SetEnableAlplaTest(false);
	
	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=================================
//生成
//=================================
CCharacter* CCharacter::Create(const D3DXVECTOR3 pos, const TYPE type, IControllStat* player)
{
	if (m_aChara[type] == nullptr)
	{
		CCharacter* pChara = nullptr;

		if (pChara == nullptr)
		{
			//オブジェクト2Dの生成
			pChara = new CCharacter;

			//データ設定
			pChara->m_type = type;
			pChara->m_pos = pos;
			pChara->m_controllInterface = player;

			//初期化
			pChara->Init();

			//当たり判定タグ設定
			if (type == TYPE_A)
			{
				pChara->m_pCollider->SetTag(CBoxCollider::TAG_TYPE_A);
			}
			else if (type == TYPE_B)
			{
				pChara->m_pCollider->SetTag(CBoxCollider::TAG_TYPE_B);
			}
			else
			{
				assert(false);
			}

			//いるよ
			m_aChara[type] = pChara;

			return pChara;
		}
	}

	return nullptr;
}

//=================================
//モデル設定
//=================================
void CCharacter::SetModel(void)
{
	//モーション生成・初期化
	m_pMotion = new CMotion;
	m_pMotion->Init();

	//モーションビューアのファイルを読み込み
	if (m_type == TYPE_A)
	{
		LoadMotionViewerFile("data\\motion_kei.txt", &m_ppModel, m_pMotion, &m_nNumModel);
	}
	else if (m_type == TYPE_B)
	{
		LoadMotionViewerFile("data\\motion_rei.txt", &m_ppModel, m_pMotion, &m_nNumModel);
	}

	m_fWidth = 60.0f;
	m_fHeight = 150.0f;
	m_fDepth = 60.0f;

	//モーション補正
	m_ppModel[0]->SetPosOffset(m_ppModel[0]->GetPosOffset() - D3DXVECTOR3(0.0f, 75.0f, 0.0f));

	//モーション設定
	m_pMotion->Set(0);
}