
// CR28CAD.h : CR28CAD 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CCR28CADApp:
// 有关此类的实现，请参阅 CR28CAD.cpp
//

class CCR28CADApp : public CWinAppEx
{
public:
	CCR28CADApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
  afx_msg void OnUpdateAppAbout(CCmdUI *pCmdUI);
  afx_msg void OnMnHelpCommandsort();
};

extern CCR28CADApp theApp;
