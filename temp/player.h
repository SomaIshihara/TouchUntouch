//======================================================
//
//�v���C���[�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�D�揇��
#define PLAYER_PRIORITY	(4)

class CPlayer : public CObjectAnim2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayer(int nPriority = PLAYER_PRIORITY);	//�f�t�H���g
	CPlayer(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight,
		const int nAnimSpeed, int nPriority = PLAYER_PRIORITY);	//�I�[�o�[���[�h�i�ʒu����and�A�j���[�V�����j
	~CPlayer();

	//����
	static CPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nAnimSpeed);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	void AddDamage(int nDamage);

private:
	//�����蔻��
	void CollisionBlockX(D3DXVECTOR3* pPosNew);
	bool CollisionBlockY(D3DXVECTOR3* pPosNew);
	void CollisionItem(D3DXVECTOR3 * pPosNew);

	//�ϐ�
	int m_nIdxTexture;			//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_move;			//�ړ���
	float m_fBulletRot;			//�e�����p�x
	int m_nLife;				//�̗�
	int m_nCounterJumpTime;		//�W�����v���Ă���̌o�ߎ���
	bool m_bJump;				//�W�����v���Ă��邩�ǂ���
};

#endif // !_PLAYER_H_