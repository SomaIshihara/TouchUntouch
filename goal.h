//======================================================
//
//�S�[�������̃w�b�_[goal.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//�K�v�Ȃ̃C���N���[�h
#include "object.h"
#include "character.h"

//�O���錾
class CObjectX;
class CSwitch;

//�L�����N�^�[�N���X
class CGoal : public CObject
{
public:
	//�����蔻��pfloat3��
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CGoal(int nPriority = PRIORITY_04);
	~CGoal();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CGoal* Create(const D3DXVECTOR3 pos);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//���O
	void Exclusion(void){}

private:
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g��
	CObjectX* m_pBase;				//�y��
	CSwitch* m_aSwitch[CCharacter::TYPE_MAX];	//�l�����̃X�C�b�`�I�u�W�F

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_rot;				//����
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y
};

#endif // !_CHARACTER_H_