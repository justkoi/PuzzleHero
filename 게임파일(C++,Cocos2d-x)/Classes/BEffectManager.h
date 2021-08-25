#pragma once


#include "stdafx.h" 
#include <list>
using namespace std;

USING_NS_CC;

typedef struct
{
	CCAnimation* m_pBlockAni;
	CCSprite * m_pBlock;
	int m_nIndex;
	float m_fTimer;
}stAnimation;

class BEffectManager
{
public:
	CCLayer* m_pThisScene;			//!< ��� ��� ��
	
	list<BAnimation*> m_pEffectList;	//!< ��� ������� ����Ʈ ���� STL LIST

public:
	
	void Insert(int nIndex, float fX, float fY, float fSizeW = 1.0f, float fSizeH = 1.0f, float fAngle = 0.0f);



	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();

	void Pause();
	void Resume();
};