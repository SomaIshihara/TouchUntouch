//======================================================
//
//�C���^�[�t�F�[�X�ꗗ[interface.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

//�C���^�[�t�F�[�X
__interface IControllStat
{
	int GetType(void) = 0;		//���쒆�̃L�����^�C�v
	int GetPress(void) = 0;		//�����
};

#endif // !_INTERFACE_H_
