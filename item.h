//======================================================
//
//�A�C�e�������̃w�b�_[item.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "object2D.h"
#include "objectX.h"

//�O���錾
class CPictoTaxi;
class CXModel;

//�D�揇��
#define ITEM_PRIORITY	(PRIORITY_DEFAULT)

//�A�C�e���N���X
class CItem : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CItem(int nPriority = ITEM_PRIORITY);	//�f�t�H���g
	CItem(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, int nPriority = ITEM_PRIORITY);	//�I�[�o�[���[�h
	~CItem();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CItem* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight);
private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

//�A�C�e���e�N���X
class CItemBullet : public CObjectX
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CItemBullet();
	CItemBullet(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	~CItemBullet();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CItemBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//�ݒ�
	static void SetModel(CXModel* nModel) { m_pModel = nModel; }

	//�擾
	int GetBulletNum(void) { return m_nBulletNum; }
	static CItemBullet* GetItemBullet(const int nIdx) { return m_pItemBullet[nIdx]; }

	//��荞��
	void PickBullet(CPictoTaxi* taxi);

private:
	static CItemBullet* m_pItemBullet[MAX_OBJ];
	int m_nID;
	static int m_nNumAll;
	int m_nBulletNum;	//�e��
	static CXModel* m_pModel;	//�e�򔠃��f���̔ԍ�
};

#endif // !_BLOCK_H_
