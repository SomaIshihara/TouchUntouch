//======================================================
//
//アイテム処理のヘッダ[item.h]
//Author:石原颯馬
//
//======================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "objectX.h"

//前方宣言
class CPictoTaxi;
class CXModel;

//優先順位
#define ITEM_PRIORITY	(PRIORITY_DEFAULT)

//アイテム弾クラス
class CItem : public CObjectX
{
public:
	//コンストラクタ・デストラクタ
	CItem();
	CItem(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	~CItem();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//設定
	static void SetModel(CXModel* nModel) { m_pModel = nModel; }

	//取得
	int GetNum(void) { return m_nScore; }

private:
	static int m_nNumAll;
	int m_nScore;
	static CXModel* m_pModel;
};

#endif // !_BLOCK_H_
