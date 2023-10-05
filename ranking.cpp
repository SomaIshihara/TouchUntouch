//======================================================
//
//ランキングシーン[ranking.cpp]
//Author:石原颯馬
//
//======================================================
#include "precompile.h"
#include "texture.h"
#include "ranking.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "sound.h"

//静的メンバ変数
const int CRanking::MAX_RANK = 5;

//=================================
//コンストラクタ
//=================================
CRanking::CRanking()
{
}

//=================================
//デストラクタ
//=================================
CRanking::~CRanking()
{
}

//=================================
//初期化
//=================================
HRESULT CRanking::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CRanking::Uninit(void)
{
	CObject::ReleaseAll();
}

//=================================
//更新
//=================================
void CRanking::Update(void)
{
	
}

//=================================
//描画
//=================================
void CRanking::Draw(void)
{
}

//=================================
//ランキング設定
//=================================
void CRanking::Set(const int nScore)
{
	
}

//=================================
//ランキング読み込み
//=================================
void CRanking::Load(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != nullptr)
	{//ランキングファイルがある（読み込み）
		fread(&pRanking[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);	//閉じる
	}
	else
	{//ランキングファイルがない（新規作成）
		for (int cnt = 0; cnt < MAX_RANK; cnt++)
		{
			pRanking[cnt] = 0;	//とりあえず0で埋める
		}
		Save(pRanking);
	}
}

//=================================
//ランキング書き込み
//=================================
void CRanking::Save(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "wb");

	assert(("書き込みモードで開けなかったよ！奇跡だね！", pFile != nullptr));

	//開けた体で進める
	fwrite(pRanking, sizeof(long long), MAX_RANK, pFile);	//書き込み

	fclose(pFile);	//閉じる
}
