//======================================================
//
//�|�[�Y��ʂ̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//�O���錾

//�^�C�g���N���X
class CPause
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPause();
	~CPause();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif // !_GAME_H_
