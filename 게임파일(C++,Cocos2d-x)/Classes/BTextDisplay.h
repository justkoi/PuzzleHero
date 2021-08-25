
#pragma once

#include "stdafx.h"
//=====================================================

/**
	@file    : < BTextDisplay >
	@author  : < ��뿬 >
	@version : < 0.1 >
	@brief   : < �ؽ�Ʈ�� �������� �ɼ��� �־� �����ִ� Ŭ���� �Դϴ�. >
 */

//!< '/' �� �� ������� ����
//=====================================================

class BTextDisplay
{
public:

	CCLayer* m_pThisScene; //!< Commit�� �� ����

	string m_String;	//!< �� �ؽ�Ʈ ����
	string m_NowString; //!< ���� �ؽ�Ʈ ����
	string m_ViewString; //!< �����ִ� �ؽ�Ʈ ���� (�ѱ��� ��� �ڿ� ?���� ������ �̻��ϰ� ���̴� ���� ����)

	string m_stdFont; //!< ��Ʈ ����
	string m_stdName; //!< Commit�� ���� �̸� ����

	list<CCLabelTTF*> m_pTextList; //!< ��� ���� �ؽ�Ʈ�� ����Ʈ�� ����

	int			m_nCodeAndroid; //!< �ȵ���̵� ȣȯ�ڵ�

	int			m_nMaxChar; //!< ���ڰ��� �ִ�
	int			m_nNowChar; //!< ���� ���� ����

	float		m_fProgressTime; //!< �ϳ��ϳ��� ���� ���� �ð�
	float		m_fNowProgressTime; //!< ���� ��� ���� '�ϳ��ϳ��� ���� ���� �ð�'

	int			m_nOffsetSpace; //!< �ѱ��� �ƴѰ���� ���� ��� ���� ����

	int			m_nLineMaxChar; //!< �� �ִ����
	int			m_nLineHeight; //!< �� ����
	int			m_nNowLineMaxChar; //!< �� �ִ����
	int			m_nNowLine; //!< ���� �� ��

	bool		m_nLineChanged; //!< ���� ���ŵȰ�� ǥ��
	int			m_nLineWidth_Basic; //!< �⺻ �� ����
	int			m_nHangulLevel; //!< 0�� ��� �ѱ� �ϼ�, 1�� ��� �ѱ� �̿ϼ� ǥ��.

	bool		m_bSkip; //!< Skip���ϰ�� true, �ƴҰ�� false
	bool		m_bFastView;//!< FastView���ϰ�� true, �ƴҰ�� false
	bool		m_bPause;//!< �Ͻ�����

	int			m_nFontSize;//!< ���� ũ��
	//CCPoint		m_stSize; //!< ���� ũ��
	CCPoint		m_stPos; //!< ��� ��ǥ ����
	ccColor3B	m_Color; //!<���� ��

	int			m_nLayer; //!< ���̾�

	Point m_AnchorPoint; //!< ��������
	
	void DestroyText(); //!< ���� ���ο����� ����

public:

	BTextDisplay()
	{
		
	};
	~BTextDisplay()
	{

	};
	
	void SetShow(bool bShow);
	
	void Init(CCLayer* pThisScene,int nLayer,Point AnchorPoint, string stdName, float fX, float fY, int nLineWidth, int nLineHeight, int nFontSize, ccColor3B Color, string stdFont = "����ü", bool Ortho2D = true);
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


	/// �߰� ����

	/*
	void SetLineHeight();
	

	*/
	

};