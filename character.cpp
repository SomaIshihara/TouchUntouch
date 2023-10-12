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

//静的メンバ変数
CCharacter* CCharacter::m_aChara[] = { nullptr,nullptr };

//=================================
//コンストラクタ
//=================================
CCharacter::CCharacter()
{
	m_ppModel = nullptr;
	m_nNumModel = CManager::INT_ZERO;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_bJump = false;
	m_nCounterJumpTime = CManager::INT_ZERO;
	m_type = TYPE_MAX;
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

	Release();
}

//=================================
//更新
//=================================
void CCharacter::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 pos = m_pos;

	if (pKeyboard->GetPress(DIK_A))
	{
		m_move.x -= 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		m_move.x += 2.0f;
	}

	//ジャンプカウンタ増やす
	m_nCounterJumpTime++;

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

	//当たり判定
	pos.x += m_move.x;
	pos.y += m_move.y - (ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS);
	pos.z += m_move.z;

	if (CollisionBlock(&pos))
	{//着地した
		m_bJump = false;
		//ジャンプ
		if (pKeyboard->GetRepeate(DIK_SPACE))
		{//ジャンプ処理
			m_bJump = true;
			m_nCounterJumpTime = 0;
			m_move.y = 5.0f;
		}
	}
	if(CollisionSwitch(&pos))
	{//着地した
		m_bJump = false;
		//ジャンプ
		if (pKeyboard->GetRepeate(DIK_SPACE))
		{//ジャンプ処理
			m_bJump = true;
			m_nCounterJumpTime = 0;
			m_move.y = 5.0f;
		}
	}

	m_pos = pos;


	//移動量減衰
	m_move.x = CManager::FLT_ZERO;
	m_move.z = CManager::FLT_ZERO;
}

//=================================
//描画
//=================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイス取得
	CTexture* pTexture = CManager::GetTexture();						//テクスチャオブジェクト取得
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

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=================================
//生成
//=================================
CCharacter* CCharacter::Create(const TYPE type)
{
	if (m_aChara[type] == nullptr)
	{
		CCharacter* pChara = nullptr;

		if (pChara == nullptr)
		{
			//オブジェクト2Dの生成
			pChara = new CCharacter;

			//初期化
			pChara->Init();

			//データ設定
			pChara->m_type = type;

			//いるよ
			m_aChara[type] = pChara;

			return pChara;
		}
	}

	return nullptr;
}

//=================================
//ブロック当たり判定
//=================================
bool CCharacter::CollisionBlock(D3DXVECTOR3* pPos)
{
	//自分の当たり判定
	float fPlayerWidth = m_fWidth * 0.5f, fPlayerHeight = m_fHeight * 0.5f, fPlayerDepth = m_fDepth * 0.5f;

	//着地結果
	bool bLand = false;

	//X
	ColFloat playerCol;
	playerCol.pPosMain = &pPos->x;
	playerCol.pPosSubA = pPos->y;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerWidth;
	playerCol.fSizeSubA = fPlayerHeight;
	playerCol.fSizeSubB = fPlayerDepth;

	CBlock3D* pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther = pBlock->GetPos();
		otherCol.pPosMain = &posOther.x;
		otherCol.pPosSubA = posOther.y;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pBlock->GetWidth() * 0.5f;
		otherCol.fSizeSubA = pBlock->GetHeight() * 0.5f;
		otherCol.fSizeSubB = pBlock->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.x, otherCol))	//当たり判定
		{
			m_move.x = 0.0f;
		}

		pBlock = pBlock->GetNext();	//次のブロック
	}

	//Y
	playerCol.pPosMain = &pPos->y;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerHeight;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerDepth;

	pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther = pBlock->GetPos();
		otherCol.pPosMain = &posOther.y;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pBlock->GetHeight() * 0.5f;
		otherCol.fSizeSubA = pBlock->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pBlock->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.y, otherCol) == true)	//当たり判定
		{//着地した
			m_move.y = 0.0f;
			m_nCounterJumpTime = 0;
			bLand = true;
		}

		pBlock = pBlock->GetNext();	//次のブロック
	}

	//Z
	playerCol.pPosMain = &pPos->z;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->y;
	playerCol.fSizeMain = fPlayerDepth;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerHeight;

	pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther = pBlock->GetPos();
		otherCol.pPosMain = &posOther.z;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.y;
		otherCol.fSizeMain = pBlock->GetDepth() * 0.5f;
		otherCol.fSizeSubA = pBlock->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pBlock->GetHeight() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.z, otherCol))	//当たり判定
		{
			m_move.z = 0.0f;
		}

		pBlock = pBlock->GetNext();	//次のブロック
	}

	return bLand;
}

//=================================
//スイッチ当たり判定
//=================================
bool CCharacter::CollisionSwitch(D3DXVECTOR3* pPos)
{
	//自分の当たり判定
	float fPlayerWidth = m_fWidth * 0.5f, fPlayerHeight = m_fHeight * 0.5f, fPlayerDepth = m_fDepth * 0.5f;

	//着地結果
	bool bLand = false;

	//X
	ColFloat playerCol;
	playerCol.pPosMain = &pPos->x;
	playerCol.pPosSubA = pPos->y;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerWidth;
	playerCol.fSizeSubA = fPlayerHeight;
	playerCol.fSizeSubB = fPlayerDepth;

	CSwitch* pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther;

		//可動部
		posOther = pSwitch->GetMove()->GetPos();
		otherCol.pPosMain = &posOther.x;
		otherCol.pPosSubA = posOther.y;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetMove()->GetWidth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetMove()->GetHeight() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetMove()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.x, otherCol))	//当たり判定
		{
			m_move.x = 0.0f;
		}

		//土台
		posOther = pSwitch->GetBase()->GetPos();
		otherCol.pPosMain = &posOther.x;
		otherCol.pPosSubA = posOther.y;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetBase()->GetWidth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetBase()->GetHeight() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetBase()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.x, otherCol))	//当たり判定
		{
			m_move.x = 0.0f;
		}

		pSwitch = pSwitch->GetNext();	//次のスイッチ
	}

	//Y
	playerCol.pPosMain = &pPos->y;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerHeight;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerDepth;

	pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther;

		//可動部
		posOther = pSwitch->GetMove()->GetPos();
		otherCol.pPosMain = &posOther.y;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetMove()->GetHeight() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetMove()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetMove()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.y, otherCol) == true)	//当たり判定
		{//着地した
			m_move.y = 0.0f;
			m_nCounterJumpTime = 0;
			bLand = true;
			pSwitch->Push();
		}

		//土台
		posOther = pSwitch->GetBase()->GetPos();
		otherCol.pPosMain = &posOther.y;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetBase()->GetHeight() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetBase()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetBase()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.y, otherCol) == true)	//当たり判定
		{//着地した
			m_move.y = 0.0f;
			m_nCounterJumpTime = 0;
			bLand = true;
		}

		pSwitch = pSwitch->GetNext();	//次のスイッチ
	}

	//Z
	playerCol.pPosMain = &pPos->z;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->y;
	playerCol.fSizeMain = fPlayerDepth;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerHeight;

	pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther;

		//可動部
		posOther = pSwitch->GetMove()->GetPos();
		otherCol.pPosMain = &posOther.z;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.y;
		otherCol.fSizeMain = pSwitch->GetMove()->GetDepth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetMove()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetMove()->GetHeight() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.z, otherCol))	//当たり判定
		{
			m_move.z = 0.0f;
		}

		//土台
		posOther = pSwitch->GetBase()->GetPos();
		otherCol.pPosMain = &posOther.z;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.y;
		otherCol.fSizeMain = pSwitch->GetBase()->GetDepth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetBase()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetBase()->GetHeight() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.z, otherCol))	//当たり判定
		{
			m_move.z = 0.0f;
		}

		pSwitch = pSwitch->GetNext();	//次のスイッチ
	}

	return bLand;
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
	LoadMotionViewerFile("data\\motion_exithuman.txt", &m_ppModel, m_pMotion, &m_nNumModel);

	//モーション設定
	m_pMotion->Set(0);
}

//=================================
//軸単位での当たり判定
//=================================
bool CCharacter::CollisionAxis(ColFloat source, const float fPosMainOld, ColFloat dest)
{
	bool bCollision = false;

	if (source.pPosSubA - source.fSizeSubA < dest.pPosSubA + dest.fSizeSubA &&
		source.pPosSubA + source.fSizeSubA > dest.pPosSubA - dest.fSizeSubA &&
		source.pPosSubB - source.fSizeSubB < dest.pPosSubB + dest.fSizeSubB &&
		source.pPosSubB + source.fSizeSubB > dest.pPosSubB - dest.fSizeSubB)
	{
		if (fPosMainOld + source.fSizeMain <= *dest.pPosMain - dest.fSizeMain &&
			*source.pPosMain + source.fSizeMain > *dest.pPosMain - dest.fSizeMain)
		{
			*source.pPosMain = *dest.pPosMain - dest.fSizeMain - source.fSizeMain;
			bCollision = true;
		}
		else if (fPosMainOld - source.fSizeMain >= *dest.pPosMain + dest.fSizeMain &&
			*source.pPosMain - source.fSizeMain < *dest.pPosMain + dest.fSizeMain)
		{
			*source.pPosMain = *dest.pPosMain + dest.fSizeMain + source.fSizeMain;
			bCollision = true;
		}
	}

	return bCollision;
}
