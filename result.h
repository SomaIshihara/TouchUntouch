//======================================================
//
//リザルトシーンのヘッダ[result.h]
//Author:石原颯馬
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//前方宣言
class CBG;
class CButton2D;
class CFade;

//リザルトクラス
class CResult
{
public:
	//コンストラクタ・デストラクタ
	CResult();
	~CResult();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CResult* Create(void);

private:

};

#endif // !_RESULT_H_
