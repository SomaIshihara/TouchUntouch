//======================================================
//
//ゲームシーンのヘッダ[game.h]
//Author:石原颯馬
//
//======================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "manager.h"

//前方宣言
class CPlayer;
class CMeshField;
class CPause;
class CResult;
class CTimer;
class CScore;
class CMeshSky;
class CBG;

//タイトルクラス
class CGame : public CScene
{
public:
	//静的const
	static const int CDSTART_TIME;	//カウントダウン開始時間

	//コンストラクタ・デストラクタ
	CGame();
	~CGame();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	
};

#endif // !_GAME_H_
