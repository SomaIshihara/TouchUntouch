//======================================================
//
//ポーズ画面のヘッダ[game.h]
//Author:石原颯馬
//
//======================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//前方宣言

//タイトルクラス
class CPause
{
public:
	//コンストラクタ・デストラクタ
	CPause();
	~CPause();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif // !_GAME_H_
