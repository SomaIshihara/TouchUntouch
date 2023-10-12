//======================================================
//
//�L�����N�^�[����[character.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "Culc.h"
#include "file.h"
#include "block3D.h"
#include "switch.h"

//�ÓI�����o�ϐ�
CCharacter* CCharacter::m_aChara[] = { nullptr,nullptr };

//=================================
//�R���X�g���N�^
//=================================
CCharacter::CCharacter()
{
	m_ppModel = nullptr;
	m_nNumModel = CManager::INT_ZERO;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_bJump = false;
	m_nCounterJumpTime = CManager::INT_ZERO;
	m_type = TYPE_MAX;
}

//=================================
//�f�X�g���N�^
//=================================
CCharacter::~CCharacter()
{
}

//=================================
//������
//=================================
HRESULT CCharacter::Init(void)
{
	SetModel();
	return S_OK;
}

//=================================
//�I��
//=================================
void CCharacter::Uninit(void)
{
	//���[�V�����j��
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{//�������
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Uninit();
				delete m_ppModel[cnt];
				m_ppModel[cnt] = nullptr;
			}
		}
		delete[] m_ppModel;	//�z�񂻂̂��̂�j��
	}

	Release();
}

//=================================
//�X�V
//=================================
void CCharacter::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 pos = m_pos;

	if (pKeyboard->GetPress(DIK_A))
	{
		m_move.x -= 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		m_move.x += 2.0f;
	}

	//�W�����v�J�E���^���₷
	m_nCounterJumpTime++;

	//���f���ݒ�
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Update();
			}
		}
	}

	//���[�V����������
	if (m_pMotion != nullptr)
	{
		//���[�V�����X�V
		m_pMotion->Update();
	}

	//�����蔻��
	pos.x += m_move.x;
	pos.y += m_move.y - (ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS);
	pos.z += m_move.z;

	if (CollisionBlock(&pos))
	{//���n����
		m_bJump = false;
		//�W�����v
		if (pKeyboard->GetRepeate(DIK_SPACE))
		{//�W�����v����
			m_bJump = true;
			m_nCounterJumpTime = 0;
			m_move.y = 5.0f;
		}
	}
	if(CollisionSwitch(&pos))
	{//���n����
		m_bJump = false;
		//�W�����v
		if (pKeyboard->GetRepeate(DIK_SPACE))
		{//�W�����v����
			m_bJump = true;
			m_nCounterJumpTime = 0;
			m_move.y = 5.0f;
		}
	}

	m_pos = pos;


	//�ړ��ʌ���
	m_move.x = CManager::FLT_ZERO;
	m_move.z = CManager::FLT_ZERO;
}

//=================================
//�`��
//=================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//�v�Z�p
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���`��
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Draw();
			}
		}
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=================================
//����
//=================================
CCharacter* CCharacter::Create(const TYPE type)
{
	if (m_aChara[type] == nullptr)
	{
		CCharacter* pChara = nullptr;

		if (pChara == nullptr)
		{
			//�I�u�W�F�N�g2D�̐���
			pChara = new CCharacter;

			//������
			pChara->Init();

			//�f�[�^�ݒ�
			pChara->m_type = type;

			//�����
			m_aChara[type] = pChara;

			return pChara;
		}
	}

	return nullptr;
}

//=================================
//�u���b�N�����蔻��
//=================================
bool CCharacter::CollisionBlock(D3DXVECTOR3* pPos)
{
	//�����̓����蔻��
	float fPlayerWidth = m_fWidth * 0.5f, fPlayerHeight = m_fHeight * 0.5f, fPlayerDepth = m_fDepth * 0.5f;

	//���n����
	bool bLand = false;

	//X
	ColFloat playerCol;
	playerCol.pPosMain = &pPos->x;
	playerCol.pPosSubA = pPos->y;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerWidth;
	playerCol.fSizeSubA = fPlayerHeight;
	playerCol.fSizeSubB = fPlayerDepth;

	CBlock3D* pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther = pBlock->GetPos();
		otherCol.pPosMain = &posOther.x;
		otherCol.pPosSubA = posOther.y;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pBlock->GetWidth() * 0.5f;
		otherCol.fSizeSubA = pBlock->GetHeight() * 0.5f;
		otherCol.fSizeSubB = pBlock->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.x, otherCol))	//�����蔻��
		{
			m_move.x = 0.0f;
		}

		pBlock = pBlock->GetNext();	//���̃u���b�N
	}

	//Y
	playerCol.pPosMain = &pPos->y;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerHeight;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerDepth;

	pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther = pBlock->GetPos();
		otherCol.pPosMain = &posOther.y;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pBlock->GetHeight() * 0.5f;
		otherCol.fSizeSubA = pBlock->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pBlock->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.y, otherCol) == true)	//�����蔻��
		{//���n����
			m_move.y = 0.0f;
			m_nCounterJumpTime = 0;
			bLand = true;
		}

		pBlock = pBlock->GetNext();	//���̃u���b�N
	}

	//Z
	playerCol.pPosMain = &pPos->z;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->y;
	playerCol.fSizeMain = fPlayerDepth;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerHeight;

	pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther = pBlock->GetPos();
		otherCol.pPosMain = &posOther.z;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.y;
		otherCol.fSizeMain = pBlock->GetDepth() * 0.5f;
		otherCol.fSizeSubA = pBlock->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pBlock->GetHeight() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.z, otherCol))	//�����蔻��
		{
			m_move.z = 0.0f;
		}

		pBlock = pBlock->GetNext();	//���̃u���b�N
	}

	return bLand;
}

//=================================
//�X�C�b�`�����蔻��
//=================================
bool CCharacter::CollisionSwitch(D3DXVECTOR3* pPos)
{
	//�����̓����蔻��
	float fPlayerWidth = m_fWidth * 0.5f, fPlayerHeight = m_fHeight * 0.5f, fPlayerDepth = m_fDepth * 0.5f;

	//���n����
	bool bLand = false;

	//X
	ColFloat playerCol;
	playerCol.pPosMain = &pPos->x;
	playerCol.pPosSubA = pPos->y;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerWidth;
	playerCol.fSizeSubA = fPlayerHeight;
	playerCol.fSizeSubB = fPlayerDepth;

	CSwitch* pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther;

		//����
		posOther = pSwitch->GetMove()->GetPos();
		otherCol.pPosMain = &posOther.x;
		otherCol.pPosSubA = posOther.y;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetMove()->GetWidth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetMove()->GetHeight() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetMove()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.x, otherCol))	//�����蔻��
		{
			m_move.x = 0.0f;
		}

		//�y��
		posOther = pSwitch->GetBase()->GetPos();
		otherCol.pPosMain = &posOther.x;
		otherCol.pPosSubA = posOther.y;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetBase()->GetWidth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetBase()->GetHeight() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetBase()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.x, otherCol))	//�����蔻��
		{
			m_move.x = 0.0f;
		}

		pSwitch = pSwitch->GetNext();	//���̃X�C�b�`
	}

	//Y
	playerCol.pPosMain = &pPos->y;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->z;
	playerCol.fSizeMain = fPlayerHeight;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerDepth;

	pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther;

		//����
		posOther = pSwitch->GetMove()->GetPos();
		otherCol.pPosMain = &posOther.y;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetMove()->GetHeight() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetMove()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetMove()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.y, otherCol) == true)	//�����蔻��
		{//���n����
			m_move.y = 0.0f;
			m_nCounterJumpTime = 0;
			bLand = true;
			pSwitch->Push();
		}

		//�y��
		posOther = pSwitch->GetBase()->GetPos();
		otherCol.pPosMain = &posOther.y;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.z;
		otherCol.fSizeMain = pSwitch->GetBase()->GetHeight() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetBase()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetBase()->GetDepth() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.y, otherCol) == true)	//�����蔻��
		{//���n����
			m_move.y = 0.0f;
			m_nCounterJumpTime = 0;
			bLand = true;
		}

		pSwitch = pSwitch->GetNext();	//���̃X�C�b�`
	}

	//Z
	playerCol.pPosMain = &pPos->z;
	playerCol.pPosSubA = pPos->x;
	playerCol.pPosSubB = pPos->y;
	playerCol.fSizeMain = fPlayerDepth;
	playerCol.fSizeSubA = fPlayerWidth;
	playerCol.fSizeSubB = fPlayerHeight;

	pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		ColFloat otherCol;
		D3DXVECTOR3 posOther;

		//����
		posOther = pSwitch->GetMove()->GetPos();
		otherCol.pPosMain = &posOther.z;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.y;
		otherCol.fSizeMain = pSwitch->GetMove()->GetDepth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetMove()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetMove()->GetHeight() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.z, otherCol))	//�����蔻��
		{
			m_move.z = 0.0f;
		}

		//�y��
		posOther = pSwitch->GetBase()->GetPos();
		otherCol.pPosMain = &posOther.z;
		otherCol.pPosSubA = posOther.x;
		otherCol.pPosSubB = posOther.y;
		otherCol.fSizeMain = pSwitch->GetBase()->GetDepth() * 0.5f;
		otherCol.fSizeSubA = pSwitch->GetBase()->GetWidth() * 0.5f;
		otherCol.fSizeSubB = pSwitch->GetBase()->GetHeight() * 0.5f;

		if (CollisionAxis(playerCol, m_pos.z, otherCol))	//�����蔻��
		{
			m_move.z = 0.0f;
		}

		pSwitch = pSwitch->GetNext();	//���̃X�C�b�`
	}

	return bLand;
}

//=================================
//���f���ݒ�
//=================================
void CCharacter::SetModel(void)
{
	//���[�V���������E������
	m_pMotion = new CMotion;
	m_pMotion->Init();

	//���[�V�����r���[�A�̃t�@�C����ǂݍ���
	LoadMotionViewerFile("data\\motion_exithuman.txt", &m_ppModel, m_pMotion, &m_nNumModel);

	//���[�V�����ݒ�
	m_pMotion->Set(0);
}

//=================================
//���P�ʂł̓����蔻��
//=================================
bool CCharacter::CollisionAxis(ColFloat source, const float fPosMainOld, ColFloat dest)
{
	bool bCollision = false;

	if (source.pPosSubA - source.fSizeSubA < dest.pPosSubA + dest.fSizeSubA &&
		source.pPosSubA + source.fSizeSubA > dest.pPosSubA - dest.fSizeSubA &&
		source.pPosSubB - source.fSizeSubB < dest.pPosSubB + dest.fSizeSubB &&
		source.pPosSubB + source.fSizeSubB > dest.pPosSubB - dest.fSizeSubB)
	{
		if (fPosMainOld + source.fSizeMain <= *dest.pPosMain - dest.fSizeMain &&
			*source.pPosMain + source.fSizeMain > *dest.pPosMain - dest.fSizeMain)
		{
			*source.pPosMain = *dest.pPosMain - dest.fSizeMain - source.fSizeMain;
			bCollision = true;
		}
		else if (fPosMainOld - source.fSizeMain >= *dest.pPosMain + dest.fSizeMain &&
			*source.pPosMain - source.fSizeMain < *dest.pPosMain + dest.fSizeMain)
		{
			*source.pPosMain = *dest.pPosMain + dest.fSizeMain + source.fSizeMain;
			bCollision = true;
		}
	}

	return bCollision;
}
