//======================================================
//
//�^�C�g���V�[���̃w�b�_[title.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "manager.h"

//�O���錾

//�^�C�g���N���X
class CTitle : public CScene
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTitle();
	~CTitle();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif // !_TITLE_H_
