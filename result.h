//======================================================
//
//���U���g�V�[���̃w�b�_[result.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//�O���錾
class CBG;
class CButton2D;
class CFade;

//���U���g�N���X
class CResult
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CResult();
	~CResult();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CResult* Create(void);

private:

};

#endif // !_RESULT_H_
