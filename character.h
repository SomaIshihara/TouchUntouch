//======================================================
//
//�L�����N�^�[�����̃w�b�_[character.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//�K�v�Ȃ̃C���N���[�h
#include "object.h"

//�O���錾
class CModel;
class CShadow;
class CMotion;

//�L�����N�^�[�N���X
class CCharacter : public CObject
{
public:
	//�����蔻��pfloat3��
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//�L�����N�^�[�^�C�v��
	enum TYPE
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CCharacter();
	~CCharacter();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CCharacter* Create(const TYPE type);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

	//�����蔻��
	bool CollisionBlock(D3DXVECTOR3* pPos);

private:
	void SetModel(void);
	bool CollisionAxis(ColFloat source, const float fPosMainOld,ColFloat dest);

	static CCharacter* m_aChara[TYPE_MAX];	//��ޕʂ̃L�����|�C���^

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g��
	CModel** m_ppModel;			//���f���i���I�m�ہj
	int m_nNumModel;			//���f����
	CMotion* m_pMotion;			//���[�V�����|�C���^

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y

	bool m_bJump;				//�W�����v����
	int m_nCounterJumpTime;		//�W�����v����

	//CShadow* m_pShadow;			//�e�I�u�W�F�N�g�|�C���^
	TYPE m_type;				//���
};

#endif // !_CHARACTER_H_
