
#pragma once

#include "stdafx.h"
//=====================================================

/**
	@file    : < BTextDisplay >
	@author  : < 백노연 >
	@version : < 0.1 >
	@brief   : < 텍스트를 여러가지 옵션을 넣어 보여주는 클래스 입니다. >
 */

//!< '/' 이 들어가 있을경우 개행
//=====================================================

class BTextDisplay
{
public:

	CCLayer* m_pThisScene; //!< Commit할 씬 보관

	string m_String;	//!< 총 텍스트 보관
	string m_NowString; //!< 현재 텍스트 보관
	string m_ViewString; //!< 보여주는 텍스트 보관 (한글의 경우 뒤에 ?등이 붙으며 이상하게 보이는 것을 차단)

	string m_stdFont; //!< 폰트 보관
	string m_stdName; //!< Commit에 쓰일 이름 보관

	list<CCLabelTTF*> m_pTextList; //!< 모든 줄의 텍스트를 리스트에 보관

	int			m_nCodeAndroid; //!< 안드로이드 호환코드

	int			m_nMaxChar; //!< 글자개수 최대
	int			m_nNowChar; //!< 현재 글자 개수

	float		m_fProgressTime; //!< 하나하나의 글자 진행 시간
	float		m_fNowProgressTime; //!< 현재 계산 중인 '하나하나의 글자 진행 시간'

	int			m_nOffsetSpace; //!< 한글이 아닌경우의 수를 모두 더해 저장

	int			m_nLineMaxChar; //!< 줄 최대글자
	int			m_nLineHeight; //!< 줄 간격
	int			m_nNowLineMaxChar; //!< 줄 최대글자
	int			m_nNowLine; //!< 현재 줄 수

	bool		m_nLineChanged; //!< 줄이 갱신된경우 표시
	int			m_nLineWidth_Basic; //!< 기본 줄 넓이
	int			m_nHangulLevel; //!< 0일 경우 한글 완성, 1일 경우 한글 미완성 표시.

	bool		m_bSkip; //!< Skip중일경우 true, 아닐경우 false
	bool		m_bFastView;//!< FastView중일경우 true, 아닐경우 false
	bool		m_bPause;//!< 일시정지

	int			m_nFontSize;//!< 글자 크기
	//CCPoint		m_stSize; //!< 글자 크기
	CCPoint		m_stPos; //!< 출력 좌표 보관
	ccColor3B	m_Color; //!<글자 색

	int			m_nLayer; //!< 레이어

	Point m_AnchorPoint; //!< 정렬지점
	
	void DestroyText(); //!< 현재 내부에서만 가능

public:

	BTextDisplay()
	{
		
	};
	~BTextDisplay()
	{

	};
	
	void SetShow(bool bShow);
	
	void Init(CCLayer* pThisScene,int nLayer,Point AnchorPoint, string stdName, float fX, float fY, int nLineWidth, int nLineHeight, int nFontSize, ccColor3B Color, string stdFont = "으뜸체", bool Ortho2D = true);
	void Update(float dt);
	void Exit();

	void SetText(string String);
	void SetProgressTime(float fProgressTime);
	void Skip();

	bool IsViewing();

	void SetFastView(bool bFastView = true);
	void SetPause(bool bPause = true);
	
	bool GetFastView();
	bool GetPause();

	void NextLine();


	/// 추가 예정

	/*
	void SetLineHeight();
	

	*/
	

};