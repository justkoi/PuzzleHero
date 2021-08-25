#pragma once


#include "stdafx.h" 

using namespace std;

USING_NS_CC;

typedef struct
{
	BNumber* m_Number;
	float m_fTimer;
	float m_fStartY;
}stNumberChunk;

class BNumberManager
{
public:
	CCLayer* m_pThisScene;			//!< ��� ��� ��
	
	vector<stNumberChunk*> m_pNumberList;	//!< ��� ������� ���� ���� STL LIST

public:
	
	//!< ����, ��ǥ, ũ��
	void Insert(int nNumber, float fX, float fY, ccColor3B ccColor, float fSizeW = 0.6f, float fSizeH = 0.6f);



	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();
};