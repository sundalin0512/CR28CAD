
// CR28CAD.h : CR28CAD Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCR28CADApp:
// �йش����ʵ�֣������ CR28CAD.cpp
//

class CCR28CADApp : public CWinAppEx
{
public:
	CCR28CADApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
  afx_msg void OnUpdateAppAbout(CCmdUI *pCmdUI);
  afx_msg void OnMnHelpCommandsort();
};

extern CCR28CADApp theApp;
