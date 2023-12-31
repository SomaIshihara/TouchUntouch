//======================================================
//
//パーティクル処理[particle.cpp]
//Author:石原颯馬
//
//======================================================
#include "particleBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "effectBillboard.h"
#include "Culc.h"

//マクロ
#define ROT_ACCU	(100)	//角度の精度
#define SPEED_ACCU	(100)	//速度の精度
#define PART_EFFECT_LIFE	(20)	//エフェクト用パーティクルの寿命

//=================================
//コンストラクタ（デフォルト）
//=================================
CParticleBillboard::CParticleBillboard()
{
	//パーティクルのクリア
	m_particle.pos = CManager::VEC3_ZERO;
	m_particle.nLife = CManager::INT_ZERO;
	m_particle.nEffeceNum = CManager::INT_ZERO;
	m_particle.fSpeedBace = CManager::FLT_ZERO;
	m_particle.fSpeedDegree = CManager::FLT_ZERO;
	m_particle.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_particle.fWidth = CManager::FLT_ZERO;
	m_particle.fHeight = CManager::FLT_ZERO;
}

//=================================
//デストラクタ
//=================================
CParticleBillboard::~CParticleBillboard()
{
}

//=================================
//初期化
//=================================
HRESULT CParticleBillboard::Init(void)
{
	//できた
	return S_OK;
}

//=================================
//終了
//=================================
void CParticleBillboard::Uninit(void)
{
	//パーティクル管理オブジェクト破棄
	Release();
}

//=================================
//更新
//=================================
void CParticleBillboard::Update(void)
{
	//エフェクト追加処理
	for (int cntEffectNum = 0; cntEffectNum < m_particle.nEffeceNum; cntEffectNum++)
	{
		//位置（パーティクルの位置と同じ）
		//移動量
		float fRotZ = (float)(rand() % (int)(ROT_ACCU * TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
		float fRotY = (float)(rand() % (int)(ROT_ACCU * TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
		float fSpeed = (rand() % (int)(m_particle.fSpeedDegree * SPEED_ACCU)) / SPEED_ACCU + m_particle.fSpeedBace;
		D3DXVECTOR3 move;
		move.x = sinf(fRotZ) * cosf(fRotY) * fSpeed;	//X
		move.y = cosf(fRotZ) * fSpeed;					//Y
		move.z = cosf(fRotZ) * cosf(fRotY) * fSpeed;	//Z

		//幅高さ（パーティクルにある）
		//色（パーティクルにある）
		//寿命（マクロ）

		//エフェクトを出す
		CEffectBillboard* pEffect;
		pEffect = pEffect->Create(m_particle.pos, move, m_particle.fWidth, m_particle.fHeight, m_particle.col, PART_EFFECT_LIFE);
		pEffect->Init();

		//AllEffectのほうのfor文を抜ける
		break;
	}

	//エフェクト寿命管理
	m_particle.nLife--;

	if (m_particle.nLife <= CManager::INT_ZERO)
	{
		Uninit();
	}
}

//=================================
//生成処理
//=================================
CParticleBillboard* CParticleBillboard::Create(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
	const D3DXCOLOR col, const float fWidth, const float fHeight)
{
	CParticleBillboard* pParticle = nullptr;

	if (pParticle == nullptr)
	{
		//パーティクル管理オブジェクト生成
		pParticle = new CParticleBillboard;

		//パーティクル管理オブジェクト初期化
		pParticle->Init();

		//データ設定
		pParticle->m_particle.pos = pos;
		pParticle->m_particle.nLife = nLife;
		pParticle->m_particle.nEffeceNum = nEffeceNum;
		pParticle->m_particle.fSpeedBace = fSpeedBace;
		pParticle->m_particle.fSpeedDegree = fSpeedDegree;
		pParticle->m_particle.col = col;
		pParticle->m_particle.fWidth = fWidth;
		pParticle->m_particle.fHeight = fHeight;

		return pParticle;
	}
	else
	{
		return nullptr;
	}
}