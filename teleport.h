//======================================================
//
//テレポート処理のヘッダ[teleport.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TELEPORT_H_
#define _TELEPORT_H_

//必要なのインクルード
#include "manager.h"
#include "object.h"
#include "interface.h"
#include "collision.h"

//テレポート当たり判定クラス
class CTeleportCollision : public CObject, public ICollisionReader
{
public:
	//コンストラクタ・デストラクタ
	CTeleportCollision(int nPriority = CObject::PRIORITY_DEFAULT);
	~CTeleportCollision();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CTeleportCollision* Create(const D3DXVECTOR3 pos, const int nID);

	//取得
	D3DXVECTOR3 GetCollisionPos(void) { return m_pos; }	//当たり判定の位置
	D3DXVECTOR3 GetFromPos(void);						//紐づくテレポート先の位置
	static CTeleportCollision* GetTop(void) { return m_pTop; }
	CTeleportCollision* GetNext(void) { return m_pNext; }

	//インターフェース
	D3DXVECTOR3 GetMove(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetPosOld(void) { return m_pos; }
	void SetPos(const D3DXVECTOR3 pos) {}
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

	//除外
	void Exclusion(void);

private:
	//リスト
	static CTeleportCollision* m_pTop;	//リストの最初
	static CTeleportCollision* m_pCur;	//リストの終端
	CTeleportCollision* m_pNext;		//次
	CTeleportCollision* m_pPrev;		//前
	static int m_nNumAll;				//テレポート当たり判定総数

	CBoxCollider* m_pCollider;			//当たり判定

	D3DXVECTOR3 m_pos;						//位置
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ
	int m_nID;								//テレポート先ID
};

//テレポート先
class CTeleportPos : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CTeleportPos(int nPriority = CObject::PRIORITY_DEFAULT);
	~CTeleportPos();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CTeleportPos* Create(const D3DXVECTOR3 pos, const int nID);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static CTeleportPos* GetTop(void) { return m_pTop; }
	CTeleportPos* GetNext(void) { return m_pNext; }
	int GetID(void) { return m_nID; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//除外
	void Exclusion(void);

private:
	//リスト
	static CTeleportPos* m_pTop;	//リストの最初
	static CTeleportPos* m_pCur;	//リストの終端
	CTeleportPos* m_pNext;			//次
	CTeleportPos* m_pPrev;			//前
	static int m_nNumAll;			//テレポート先総数

	D3DXVECTOR3 m_pos;				//位置
	int m_nID;						//テレポート先ID
};

#endif // !_TELEPORT_H_
