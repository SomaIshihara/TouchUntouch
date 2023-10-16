//======================================================
//
//�A�C�e�������̃w�b�_[item.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "objectX.h"

//�O���錾
class CPictoTaxi;
class CXModel;

//�D�揇��
#define ITEM_PRIORITY	(PRIORITY_DEFAULT)

//�A�C�e���e�N���X
class CItem : public CObjectX
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CItem();
	CItem(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	~CItem();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//�ݒ�
	static void SetModel(CXModel* nModel) { m_pModel = nModel; }

	//�擾
	int GetNum(void) { return m_nScore; }

private:
	static int m_nNumAll;
	int m_nScore;
	static CXModel* m_pModel;
};

#endif // !_BLOCK_H_
