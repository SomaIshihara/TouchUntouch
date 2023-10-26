//======================================================
//
//�e���|�[�g�����̃w�b�_[teleport.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TELEPORT_H_
#define _TELEPORT_H_

//�K�v�Ȃ̃C���N���[�h
#include "manager.h"
#include "object.h"
#include "interface.h"
#include "collision.h"

//�e���|�[�g�����蔻��N���X
class CTeleportCollision : public CObject, public ICollisionReader
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTeleportCollision(int nPriority = CObject::PRIORITY_DEFAULT);
	~CTeleportCollision();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CTeleportCollision* Create(const D3DXVECTOR3 pos, const int nID);

	//�擾
	D3DXVECTOR3 GetCollisionPos(void) { return m_pos; }	//�����蔻��̈ʒu
	D3DXVECTOR3 GetFromPos(void);						//�R�Â��e���|�[�g��̈ʒu
	static CTeleportCollision* GetTop(void) { return m_pTop; }
	CTeleportCollision* GetNext(void) { return m_pNext; }

	//�C���^�[�t�F�[�X
	D3DXVECTOR3 GetMove(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetPosOld(void) { return m_pos; }
	void SetPos(const D3DXVECTOR3 pos) {}
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

	//���O
	void Exclusion(void);

private:
	//���X�g
	static CTeleportCollision* m_pTop;	//���X�g�̍ŏ�
	static CTeleportCollision* m_pCur;	//���X�g�̏I�[
	CTeleportCollision* m_pNext;		//��
	CTeleportCollision* m_pPrev;		//�O
	static int m_nNumAll;				//�e���|�[�g�����蔻�葍��

	CBoxCollider* m_pCollider;			//�����蔻��

	D3DXVECTOR3 m_pos;						//�ʒu
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y
	int m_nID;								//�e���|�[�g��ID
};

//�e���|�[�g��
class CTeleportPos : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTeleportPos(int nPriority = CObject::PRIORITY_DEFAULT);
	~CTeleportPos();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CTeleportPos* Create(const D3DXVECTOR3 pos, const int nID);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static CTeleportPos* GetTop(void) { return m_pTop; }
	CTeleportPos* GetNext(void) { return m_pNext; }
	int GetID(void) { return m_nID; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//���O
	void Exclusion(void);

private:
	//���X�g
	static CTeleportPos* m_pTop;	//���X�g�̍ŏ�
	static CTeleportPos* m_pCur;	//���X�g�̏I�[
	CTeleportPos* m_pNext;			//��
	CTeleportPos* m_pPrev;			//�O
	static int m_nNumAll;			//�e���|�[�g�摍��

	D3DXVECTOR3 m_pos;				//�ʒu
	int m_nID;						//�e���|�[�g��ID
};

#endif // !_TELEPORT_H_
