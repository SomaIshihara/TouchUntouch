//======================================================
//
//テクスチャ保存クラスのヘッダ[texture.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define MAX_STR		(256)
#define MAX_TEXTURE	(128)	//テクスチャ数

//テクスチャ保存クラス
class CTexture
{
public:
	//事前読み込みテクスチャ列挙
	enum PRELOAD
	{
		PRELOAD_00_TITLELOGO = 0,
		PRELOAD_01_STARTKB,
		PRELOAD_02_STARTGP,
		PRELOAD_03_NUMBER,
		PRELOAD_04_TIMERSTR,
		PRELOAD_05_SCORESTR,
		PRELOAD_06_BONUSSTR,
		PRELOAD_07_SCENERANKKB,
		PRELOAD_08_SCENERANKGP,
		PRELOAD_09_RANKSTR,
		PRELOAD_10_RANK_01,
		PRELOAD_11_RANK_02,
		PRELOAD_12_RANK_03,
		PRELOAD_13_RANK_04,
		PRELOAD_14_RANK_05,
		PRELOAD_15_SCENETITLEKB,
		PRELOAD_16_SCENETITLEGP,
		PRELOAD_MAX
	};

	//パターンテクスチャ構造体定義
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	//テクスチャポインタ
		int nPatternWidth;				//パターン幅
		int nPatternHeight;				//パターン高さ
	} PatternTexture;
	//コンストラクタ・デストラクタ
	CTexture();
	~CTexture();

	//全読み込み・破棄
	HRESULT Load(const char* pPath);	//あらかじめ読み込みたいテクスチャ読み込み
	void Unload(void);					//追加した分も含めてすべて破棄

	int Regist(const char* pPath, const int nPatWidth = 1, const int nPatHeight = 1);	//追加する分の読み込み
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);											//テクスチャ取得
	int GetPatWidth(int nIdx);					//パターン幅取得
	int GetPatHeight(int nIdx);					//パターン高さ取得

private:
	PatternTexture m_apTexture[MAX_TEXTURE];		//テクスチャポインタ
	char m_aFilepath[MAX_TEXTURE][MAX_STR];			//テクスチャパス
	static int m_nNumAll;							//テクスチャ総数
};

#endif // !_TEXTURE_H_
