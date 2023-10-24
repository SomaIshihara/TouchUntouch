//======================================================
//
//�`���[�g���A���V�[��[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "tutorial.h"
#include "input.h"
#include "texture.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"
#include "character.h"
#include "player.h"
#include "objloader.h"
#include "switchmanager.h"
#include "block3D.h"

//�V�[���n
#include "result.h"

//UI�n
#include "fade.h"

//��
#include "goal.h"

//=================================
//�R���X�g���N�^
//=================================
CTutorial::CTutorial()
{
	m_pPlayer = nullptr;
	m_pSwitchManager = nullptr;
	m_pFade = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CTutorial::~CTutorial()
{
}

//=================================
//������
//=================================
HRESULT CTutorial::Init(void)
{
	//�J�������Z�b�g
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->ResetPos();

	//����v���C���[�̃N���X����
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
	}

	//�X�C�b�`�Ǘ��I�u�W�F�����Ɛݒ�
	m_pSwitchManager = CSwitchManager::Create();
	CBlock3D::SetSwitchManager(m_pSwitchManager);
	CObjLoader::LoadData("data\\tut_mapdata_tutorial.ismd");
	
	//�L��������
	CCharacter::Create(D3DXVECTOR3(100.0f,150.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);
	return S_OK;
}

//=================================
//�I��
//=================================
void CTutorial::Uninit(void)
{
	CObject::ReleaseAll();
	//CManager::GetInstance()->GetSound()->Stop();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

//=================================
//�X�V
//=================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾
	CGoal* pGoal = CGoal::GetTop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	bool bGoal = false;

	//�I������
	if (pGoal != nullptr)
	{
		while (pGoal != nullptr)
		{
			if (pGoal->IsGoal() == true)
			{//���~
				bGoal = true;
				break;
			}
			pGoal = pGoal->GetNext();
		}
	}

	//�`���[�g���A���X�L�b�v
	if (pKeyboard->GetTrigger(DIK_P) == true)
	{
		bGoal = true;
	}

	if (bGoal == true)
	{//�S�[������
		m_pPlayer->SetControll(false);
		if (m_pFade == nullptr)
		{
			m_pFade = CFade::Create(CScene::MODE_GAME);
		}
	}
	else
	{//�S�[�����ĂȂ�
		m_pPlayer->SetControll(true);
	}

	//�Ƃ肠�����񂷁i�L���E�����͏�ł��j
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}

	if (pCamera != nullptr)
	{//�J�����ړ�
		D3DXVECTOR3 posV = pCamera->GetPosV();
		D3DXVECTOR3 posR = pCamera->GetPosR();
		CCharacter** chara = CCharacter::GetChara();

		float posXCenter = (chara[0]->GetPos().x + chara[1]->GetPos().x) * 0.5f;
		float lenXHalf = fabsf(chara[0]->GetPos().x - chara[1]->GetPos().x) * 0.5f;
		float posYCenter = (chara[0]->GetPos().y + chara[1]->GetPos().y) * 0.5f;
		float lenYHalf = fabsf(chara[0]->GetPos().y - chara[1]->GetPos().y) * 0.5f;
		posV.x = posXCenter;
		posR.x = posXCenter;
		posV.y = posYCenter;
		posR.y = posYCenter;

		pCamera->SetPosV(posV);
		pCamera->SetPosR(posR);

		if (lenXHalf * 2.0f >= 900.0f)
		{//��
			pCamera->SetLength(lenXHalf * 2.0f);
		}
		else
		{
			pCamera->SetLength(900.0f);
		}
	}
}

//=================================
//�`��
//=================================
void CTutorial::Draw(void)
{
	//���i�͂��ׂ�CObject�N���X�p�����Ă���̂������Ă���̂Ŏ����`��
	//�|�[�Y�̒��g�����ׂ�CObject�N���X�p�����Ă�̂Ŏ����`��
	//����Ă����ł��邱�Ƃ͂Ȃ�
}