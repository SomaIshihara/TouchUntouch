//======================================================
//
//チュートリアルシーンのヘッダ[game.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "manager.h"

//前方宣言
class CPlayer;
class CSwitchManager;
class CFade;

//仮
class CGoal;

//タイトルクラス
class CTutorial : public CScene
{
public:
	//静的const
	static const int CDSTART_TIME;	//カウントダウン開始時間

	//コンストラクタ・デストラクタ
	CTutorial();
	~CTutorial();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPlayer* m_pPlayer;	//プレイヤーポインタ
	CSwitchManager* m_pSwitchManager;	//スイッチマネ
	CFade* m_pFade;		//フェード
};

#endif // !_TUTORIAL_H_
