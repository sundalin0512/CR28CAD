
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "CR28CAD.h"

#include "MainFrm.h"
#include "CR28CADView.h"
#include "CADTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(MN_HELP_COMMANDSORT, &CMainFrame::OnMnHelpCommandsort)
	ON_COMMAND_RANGE(ID_PLUGIN, ID_PLUGIN + 0x100, OnPlugin)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	LoadPlugin();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnMnHelpCommandsort()
{
	// TODO:  在此添加命令处理程序代码
	//AfxMessageBox(_T("CMainFrame::OnMnHelpCommandsort"));

	TRACE(_T("%s"), _T(" CMainFrame::OnMnHelpCommandsort"));
	TRACE0("OnMnHelpCommandsort");
	TRACE1("%s", _T("OnMnHelpCommandsort"));
	TRACE2("%s %d", _T("OnMnHelpCommandsort"), 0);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	BOOL bRet = m_wndSplitter.CreateStatic(this, 1, 2);
	if (bRet)
	{
		bRet = m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CADTreeView), SIZE{ 200,100 }, pContext);
		bRet = m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCR28CADView), SIZE{ 100,100 }, pContext);
	}

	CRect rcClient;
	GetClientRect(rcClient);
	m_wndSplitter.SetRowInfo(0,
		rcClient.Height() / 2,
		rcClient.Height() / 3);

	return bRet;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
bool CMainFrame::LoadPlugin()
{
	CMenu *pMenu = GetMenu();
	CMenu *pSubMenu = NULL;
	int nMenuCount = 0;
	int ID = 0;


	pMenu->AppendMenu(MF_STRING | MF_POPUP,
		(UINT)pMenu->GetSafeHmenu(),
		L"插件(&P)");
	nMenuCount = pMenu->GetMenuItemCount();
	pSubMenu = pMenu->GetSubMenu(nMenuCount - 1);

	//遍历文件夹
	CFileFind find;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(_T("..\\plugin\\*.dll"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		HMODULE hDll = LoadLibrary(finder.GetFilePath());
		if (hDll == NULL)
			continue;

		pfn_GetShapeFactoryObj pfnGetObj = (pfn_GetShapeFactoryObj)GetProcAddress(hDll, "GetShapeFactoryObj");
		if (pfnGetObj == NULL)
		{
			FreeLibrary(hDll);
			continue;
		}

		IShapeFactory *pObj = (*pfnGetObj)();
		pObj->SetID(ID_PLUGIN + ID);

		//保护插件
		m_Plugins.push_back(pObj);

		pSubMenu->AppendMenu(MF_STRING,
			ID_PLUGIN + ID++,
			pObj->GetMenuName());



		//AfxMessageBox((LPCTSTR)finder.GetFileName());
	}
	return false;
}

void CMainFrame::OnPlugin(UINT nID)
{
	//迭代器遍历
	for (auto it = m_Plugins.begin();
		it != m_Plugins.end();
		it++)
	{
		auto *pObj = *it;
		if (pObj->GetID() == nID)
		{
			CCR28CADView* pLeftPaneView = (CCR28CADView*)m_wndSplitter.GetPane(0, 1);
			pLeftPaneView->m_pShapeFactory = pObj;
			pLeftPaneView->m_dwOperaterType = CCR28CADView::OPTYPE_CREARTESHAPE;
			break;
		}
	}
}
