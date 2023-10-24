//======================================================
//
//�`���[�g���A���V�[���̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "manager.h"

//�O���錾
class CPlayer;
class CSwitchManager;
class CFade;

//��
class CGoal;

//�^�C�g���N���X
class CTutorial : public CScene
{
public:
	//�ÓIconst
	static const int CDSTART_TIME;	//�J�E���g�_�E���J�n����

	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial();
	~CTutorial();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPlayer* m_pPlayer;	//�v���C���[�|�C���^
	CSwitchManager* m_pSwitchManager;	//�X�C�b�`�}�l
	CFade* m_pFade;		//�t�F�[�h
};

#endif // !_TUTORIAL_H_
