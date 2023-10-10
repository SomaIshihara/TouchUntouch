//======================================================
//
//�u���b�N����(3D)�̃w�b�_[block3D.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BLOCK_3D_H_
#define _BLOCK_3D_H_

//�K�v�Ȃ��̃C���N���[�h
#include "objectX.h"

//�u���b�N�N���X
class CBlock3D : public CObjectX
{
public:
	//�u���b�N��ޗ�
	enum TYPE
	{
		TYPE_NORMAL = 0,	//����:�ʏ�i���j
		TYPE_GIMMICK_01,	//����:�M�~�b�N1�i���j
		TYPE_GIMMICK_02,	//����:�M�~�b�N2�i���j
		TYPE_A,				//�ʁi�s���N�j
		TYPE_B,				//�ʁi��F�j
		TYPE_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CBlock3D();
	~CBlock3D();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CBlock3D* Create(const D3DXVECTOR3 pos, const TYPE type);

	//���X�g���O
	virtual void Exclusion(void);

	//�擾
	static CBlock3D* GetTop(void) { return m_pTop; }
	CBlock3D* GetNext(void) { return m_pNext; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
private:
	//���X�g
	static CBlock3D* m_pTop;	//���X�g�̍ŏ�
	static CBlock3D* m_pCur;	//���X�g�̏I�[
	CBlock3D* m_pNext;			//��
	CBlock3D* m_pPrev;			//�O

	//�T�C�Y
	float m_fWidth, m_fHeight, m_fDepth;

	//��
	static int m_nNumAll;

	//�p�����[�^
	TYPE m_type;	//�u���b�N���
};

#endif // !_BLOCK_3D_H_