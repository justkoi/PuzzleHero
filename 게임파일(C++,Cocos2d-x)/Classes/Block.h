#pragma once

#include "stdafx.h"

USING_NS_CC;

typedef enum
{
	E_BLOCKNUMBER_RED,
	E_BLOCKNUMBER_YELLOW,
	E_BLOCKNUMBER_BLUE,
	E_BLOCKNUMBER_GREEN,
	E_BLOCKNUMBER_PURPLE,
	E_BLOCKNUMBER_ORANGE,
	E_BLOCKNUMBER_MAX,
	E_BLOCKNUMBER_HERO,

}E_BLOCKNUMBER;

typedef enum
{
	E_BLOCKSTATE_FALL_NONE,
	E_BLOCKSTATE_FALL_FALLING,
}E_BLOCKSTATE_FALL;

typedef enum
{
	E_BLOCKSTATE_ACT_NONE,
	E_BLOCKSTATE_ACT_MAX,
}E_BLOCKSTATE_ACT;

typedef enum
{
	E_BLOCKITEM_NONE,
	E_BLOCKITEM_MP_PLUS,
	E_BLOCKITEM_HP_PLUS,
}E_BLOCKITEM;


typedef enum
{
	E_DERECTION_LEFT,
	E_DERECTION_RIGHT,
	E_DERECTION_UP,
	E_DERECTION_DOWN,
}E_DERECTION;

typedef struct stVec2i
{
	 int m_nX;
	 int m_nY;

	 stVec2i()
	 {
		 m_nX = 0;
		 m_nY = 0;
	 };
	 stVec2i(int nX, int nY)
	 {
		 m_nX = nX;
		 m_nY = nY;
	 };
	 ~stVec2i()
	 {

	 };

	 bool operator==(const stVec2i &ref)
	 {
		if(m_nX == ref.m_nX && m_nY == ref.m_nY)
			return true;
		else
			return false;
	 };
}stVec2i;

class CBlock
{
	
public:
	
	CCSprite*	m_pBlock;
	

	CCSprite*	m_pNoSelect;
	bool		m_bNoSelect;
	
	//CCSprite*	m_pItem;
	//CCAnimation* m_pItemAni;
	float m_fEyeContact;

	float m_fEye;
	bool m_bEye;


	int m_nGT;
	int m_nGC;

	int m_nId;

	bool m_bFallFinished;

	int  m_nBounceLevel;
	float  m_fBouncePower;
	float  m_fBounceLine;

	float	m_fGPM;//!< Gravity Plus Minus 중력보정값

	E_BLOCKNUMBER m_eBlockNumber;

	E_BLOCKITEM		m_eBlockItem;
	CCParticleSystem* m_pBlockItemParticle;

	double			m_fStartY;
	double			m_fSpeed;
	double			m_fPlusSpeed;
	double			m_fNowDistance;
	double			m_fDistance;
	double			m_fNextDistance;

	bool			m_bFreezed;
	bool			m_bDraged;
	bool			m_bDolphinHited;

	bool			m_bLive;

	float			m_fTargetColorAlpha;
	float			m_fNowColorAlpha;

	float			m_fTargetAlpha;
	float			m_fNowAlpha;

	bool			m_bAlphaing;

	CCLayer*		m_pThisScene;
	CCPoint		m_stPos;
	CCPoint		m_stOffsetPos;
	stVec2i		m_stIndex;
	E_BLOCKSTATE_FALL	m_eBlockState;

	bool			m_bChecked; //!< 체크된적 있는지
	bool			m_bFocused; //!< 포커싱된적 있는지


	//!< 교체시 이동거리
	float m_fChangeDistance;
	//!< 교체시 이동방향
	E_DERECTION m_eDerection;

	int m_nHpMax;
	int m_nHpNow;
	int m_nDamage;


public:
	CBlock(){};
	~CBlock(){};

	void Init(CCLayer* pThisScene, int nId);
	void Create(stVec2i stIndex);
	void Create_Hero(stVec2i stIndex);

	void Update(float dt);
	void Exit();

	void Die();
	bool HitTest(float nX, float nY);
	void ShowUpdate();
	void CheckReset();

	
	void Alphaing();
	
	void NextBlockNumber();//!< 다음 블록 종류로 변경
	void SetBlockNumber(E_BLOCKNUMBER eBlockNumber);//!< 블록 종류 변경 텍스쳐 변경까지
};