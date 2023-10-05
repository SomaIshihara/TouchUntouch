//======================================================
//
//�Q�[���V�[���̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "manager.h"

//�O���錾
class CPlayer;
class CMeshField;
class CPause;
class CResult;
class CTimer;
class CScore;
class CMeshSky;
class CBG;

//�^�C�g���N���X
class CGame : public CScene
{
public:
	//�ÓIconst
	static const int CDSTART_TIME;	//�J�E���g�_�E���J�n����

	//�R���X�g���N�^�E�f�X�g���N�^
	CGame();
	~CGame();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	
};

#endif // !_GAME_H_
