//======================================================
//
//�I�u�W�F�N�g�iX�j����[object3D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "objectX.h"
#include "xmodel.h"
#include <assert.h>

//�}�N��
#define PATH_LENGTH	(256)

//�ÓI�����o�ϐ�
CObjectX* CObjectX::m_pTop = nullptr;
CObjectX* CObjectX::m_pCur = nullptr;
int CObjectX::m_nNumAll = 0;

using namespace std;

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;

	if (m_pCur == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_pTop = this;		//�����擪
		m_pPrev = nullptr;		//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_pCur;		//�Ō���������̑O�̃I�u�W�F
		m_pCur->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;			//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_pCur = this;				//�����Ō��
	m_bExclusion = false;		//�����Ă�
	m_pModel = nullptr;
	m_nNumAll++;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�����j
//=================================
CObjectX::CObjectX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel, int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pos = pos;
	m_rot = rot;

	if (m_pCur == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_pTop = this;		//�����擪
		m_pPrev = nullptr;		//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_pCur;		//�Ō���������̑O�̃I�u�W�F
		m_pCur->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;			//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_pCur = this;				//�����Ō��
	m_bExclusion = false;		//�����Ă�
	m_pModel = pModel;			//���f���ݒ�

	//�T�C�Y�ݒ�
	D3DXVECTOR3 vtxMin, vtxMax;
	m_pModel->GetCollision().GetVtx(&vtxMin, &vtxMax);
	m_fWidth = vtxMax.x - vtxMin.x;
	m_fHeight = vtxMax.y - vtxMin.y;
	m_fDepth = vtxMax.z - vtxMin.z;

	m_nNumAll++;	//�I�u�W�F�N�g�����₷
}

//=================================
//�f�X�g���N�^
//=================================
CObjectX::~CObjectX()
{
}

//========================
//����������
//========================
HRESULT CObjectX::Init(void)
{
	return S_OK;
}

//========================
//�I������
//========================
void CObjectX::Uninit(void)
{
	m_bExclusion = true;		//���O�\��

	//�������g�j��
	Release();
}

//========================
//�X�V����
//========================
void CObjectX::Update(void)
{
	
}

//========================
//�`�揈��
//========================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//�v�Z�p
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;													//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxWorld);

	//�g�k�𔽉f
	//D3DXMatrixScaling(&mtxScall, FENCE_SCALE, FENCE_SCALE, FENCE_SCALE);
	//D3DXMatrixMultiply(&g_aFence[nCount].mtxWorld, &g_aFence[nCount].mtxWorld, &mtxScall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)m_pModel->GetBufMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModel->GetNumMat(); nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_pModel->GetIdxTexture()[nCntMat]));

		//���f���`��
		m_pModel->GetMesh()->DrawSubset(nCntMat);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
//��������
//========================
CObjectX* CObjectX::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel)
{
	CObjectX* pObjX = nullptr;

	if (pObjX == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObjX = new CObjectX(pos, rot, pModel);

		//������
		pObjX->Init();

		return pObjX;
	}
	else
	{
		return nullptr;
	}
}

//========================
//�I�u�W�F�N�g�P�ʏ��O����
//========================
void CObjectX::Delete(CXModel * pTarget)
{
	CObjectX* pObject = m_pTop;	//�擪������

	while (pObject != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CObjectX* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�

		if (pObject->GetModel() == pTarget)
		{
			pObject->Uninit();	//���O
		}

		pObject = pObjectNext;	//��������
	}
}

//========================
//�f�[�^�ǂݍ���
//========================
CObjectX::LOADRESULT CObjectX::LoadData(const char * pPath)
{
	FILE* pFile;
	BINCODE code;
	bool bRead = false;
	char** ppFilePath = nullptr;
	int nReadedModel = 0;

	pFile = fopen(pPath, "rb");

	if (pFile != nullptr)
	{//�J����
		while (1)
		{
			fread(&code, sizeof(BINCODE), 1, pFile);

			//������`�F�b�N
			if (code == BIN_CODE_SCRIPT)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (code == BIN_CODE_END_SCRIPT)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (bRead == true)
			{//�ǂݎ��
				if (code == BIN_CODE_TEXTURE_FILENAME)
				{
					char aPath[PATH_LENGTH];
					fread(&aPath[0], sizeof(char), PATH_LENGTH, pFile);
					CManager::GetTexture()->Load(&aPath[0]);
				}
				else if (code == BIN_CODE_MODEL_NUM)
				{
					int nNumAll;
					fread(&nNumAll, sizeof(int), 1, pFile);
					ppFilePath = new char*[nNumAll];
				}
				else if (code == BIN_CODE_MODEL_FILENAME)
				{
					char aPath[PATH_LENGTH];
					fread(&aPath[0], sizeof(char), PATH_LENGTH, pFile);
					CXModel::Load(&aPath[0]);

					//���f���p�X�ǂݎ��i�����o���p�Ɏg���j
					ppFilePath[nReadedModel] = new char[strlen(&aPath[0]) + 1];
					strcpy(ppFilePath[nReadedModel], &aPath[0]);
					nReadedModel++;
				}
				else if (code == BIN_CODE_MODELSET)
				{
					D3DXVECTOR3 pos, rot;
					int nModelNum = -1;
					CXModel* pModel = nullptr;
					fread(&pos, sizeof(D3DXVECTOR3), 1, pFile);
					fread(&rot, sizeof(D3DXVECTOR3), 1, pFile);
					fread(&nModelNum, sizeof(int), 1, pFile);
					pModel = CXModel::Load(ppFilePath[nModelNum]);

					//����
					CObjectX::Create(pos, rot, pModel);
				}
			}
		}

		fclose(pFile);
		return RES_OK;
	}
	else
	{//�J���Ȃ������i�t�@�C���Ȃ��񂶂�ˁH�j
		return RES_ERR_FILE_NOTFOUND;
	}
}

//========================
//���O����
//========================
void CObjectX::Exclusion(void)
{
	CObjectX* pObject = m_pTop;	//�擪������

	while (pObject != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CObjectX* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�

		if (pObject->m_bExclusion == true)
		{//���S�t���O�������Ă�
			if (pObject->m_pPrev != nullptr)
			{//�O�ɃI�u�W�F������
				pObject->m_pPrev->m_pNext = pObject->m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
			}
			if (pObject->m_pNext != nullptr)
			{
				pObject->m_pNext->m_pPrev = pObject->m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
			}

			if (m_pCur == pObject)
			{//�Ō���ł���
				m_pCur = pObject->m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
			}
			if (m_pTop == pObject)
			{
				m_pTop = pObject->m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
			}

			//����
			m_nNumAll--;	//�������炷
		}

		pObject = pObjectNext;	//��������
	}
}