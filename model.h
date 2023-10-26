//======================================================
//
//モデル処理のヘッダ[model.h]
//Author:石原颯馬
//
//======================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//前方宣言
class CMotion;

//モデル（階層構造あり）クラス
class CModel
{
public:
	//コンストラクタ・デストラクタ
	CModel();
	~CModel();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CModel* Create(const char* pPath, const D3DXVECTOR3 posOffset, const D3DXVECTOR3 rotOffset);
	
	//親子設定
	void SetParent(CModel* pModel) { m_pParent = pModel; }

	//取得
	D3DXVECTOR3 GetPosOffset(void) { return m_pos; }
	D3DXVECTOR3 GetRotOffset(void) { return m_rot; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

	//設定
	void SetPosMotioned(D3DXVECTOR3 pos) { m_posMotioned = pos; }
	void SetRotMotioned(D3DXVECTOR3 rot) { m_rotMotioned = rot; }
	void SetPosOffset(D3DXVECTOR3 pos) { m_pos = pos; }

	//読み込み
	HRESULT Load(const char* pPath);

private:
	//モデル
	LPD3DXMESH m_pMesh;			//メッシュ
	LPD3DXBUFFER m_pBuffMat;	//マテリアルポインタ
	DWORD m_dwNumMatModel;		//マテ数
	int* m_pIdxtexture;			//テクスチャ番号（動的確保）

	//位置類
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_posMotioned;	//モーション後の位置
	D3DXVECTOR3 m_rotMotioned;	//モーション後の向き
	D3DXMATRIX m_mtxWorld;		//ワールドマトリ
	CModel* m_pParent;			//親モデルポインタ
};

#endif // !_MODEL_H_
