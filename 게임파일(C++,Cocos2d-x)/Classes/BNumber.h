#pragma once 
#include "stdafx.h"

using namespace std;

class BNumber
{
private:
	vector<CCSprite*> m_pNumberList;//!< ������ �ѹ�
	int m_nNumber;//!< ǥ���� ����
	int m_nTargetNumber;//!< ǥ���� ����
	CCLayer* m_pThisScene;
	int m_nLayer;
	bool m_bVisible;
	float m_fOpacity;
	CCPoint m_stAnchorPoint;
	int m_nStyle;

public:
	CCPoint m_stPos;
	CCPoint m_stSize;

public:
	void Init(CCLayer* pThisScene, CCPoint stSize, int nNumber, CCPoint stPos, int nLayer,int nStyle = 1);
	void Update(float dt);
	void Exit();

	void SetNumber(int nNumber);
	void SetSize(CCPoint stSize);
	void SetVisible(bool bVisible);
	void SetOpacity(float fOpacity);
	void SetColor(ccColor3B ccColor);
	void SetAnchorPoint(CCPoint ccAnchorPoint);

	void EffectNumber(int nNumber);
	void SetPositionY(float fPosY);
	
	void SetPos(CCPoint stPos);
};