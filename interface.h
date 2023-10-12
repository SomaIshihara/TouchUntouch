//======================================================
//
//インターフェース一覧[interface.h]
//Author:石原颯馬
//
//======================================================
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

//インターフェース
__interface IControllStat
{
	int GetType(void) = 0;		//操作中のキャラタイプ
	int GetPress(void) = 0;		//操作状況
};

#endif // !_INTERFACE_H_
