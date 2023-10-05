//======================================================
//
//タイトルシーンのヘッダ[title.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "manager.h"

//前方宣言

//タイトルクラス
class CTitle : public CScene
{
public:
	//コンストラクタ・デストラクタ
	CTitle();
	~CTitle();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif // !_TITLE_H_
