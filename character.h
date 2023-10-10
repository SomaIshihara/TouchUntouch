//======================================================
//
//キャラクター処理のヘッダ[character.h]
//Author:石原颯馬
//
//======================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//必要なのインクルード
#include "object.h"

//前方宣言
class CModel;
class CShadow;
class CMotion;

//キャラクタークラス
class CCharacter : public CObject
{
public:
	//当たり判定用float3つ
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//キャラクタータイプ列挙
	enum TYPE
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	};

	//コンストラクタ・デストラクタ
	CCharacter();
	~CCharacter();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CCharacter* Create(const TYPE type);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//除外（必要なし）
	void Exclusion(void){}

	//当たり判定
	bool CollisionBlock(D3DXVECTOR3* pPos);

private:
	void SetModel(void);
	bool CollisionAxis(ColFloat source, const float fPosMainOld,ColFloat dest);

	static CCharacter* m_aChara[TYPE_MAX];	//種類別のキャラポインタ

	D3DXMATRIX m_mtxWorld;		//ワールドマトリ
	CModel** m_ppModel;			//モデル（動的確保）
	int m_nNumModel;			//モデル数
	CMotion* m_pMotion;			//モーションポインタ

	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//向き
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ

	bool m_bJump;				//ジャンプ中か
	int m_nCounterJumpTime;		//ジャンプ時間

	//CShadow* m_pShadow;			//影オブジェクトポインタ
	TYPE m_type;				//種類
};

#endif // !_CHARACTER_H_
