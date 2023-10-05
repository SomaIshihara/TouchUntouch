//======================================================
//
//�e�N�X�`���ۑ��N���X�̃w�b�_[texture.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define MAX_STR		(256)
#define MAX_TEXTURE	(128)	//�e�N�X�`����

//�e�N�X�`���ۑ��N���X
class CTexture
{
public:
	//�p�^�[���e�N�X�`���\���̒�`
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`���|�C���^
		int nPatternWidth;				//�p�^�[����
		int nPatternHeight;				//�p�^�[������
	} PatternTexture;
	//�R���X�g���N�^�E�f�X�g���N�^
	CTexture();
	~CTexture();

	//�S�ǂݍ��݁E�j��
	HRESULT Load(const char* pPath);	//���炩���ߓǂݍ��݂����e�N�X�`���ǂݍ���
	void Unload(void);					//�ǉ����������܂߂Ă��ׂĔj��

	int Regist(const char* pPath, const int nPatWidth = 1, const int nPatHeight = 1);	//�ǉ����镪�̓ǂݍ���
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);											//�e�N�X�`���擾
	int GetPatWidth(int nIdx);					//�p�^�[�����擾
	int GetPatHeight(int nIdx);					//�p�^�[�������擾

private:
	PatternTexture m_apTexture[MAX_TEXTURE];		//�e�N�X�`���|�C���^
	char m_aFilepath[MAX_TEXTURE][MAX_STR];			//�e�N�X�`���p�X
	static int m_nNumAll;							//�e�N�X�`������
};

#endif // !_TEXTURE_H_
