// Ellipse.cpp: 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Ellipse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CEllipseApp

BEGIN_MESSAGE_MAP(CEllipseApp, CWinApp)
END_MESSAGE_MAP()


// CEllipseApp 构造

CEllipseApp::CEllipseApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CEllipseApp 对象

CEllipseApp theApp;


// CEllipseApp 初始化

BOOL CEllipseApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
IMPLEMENT_SERIAL(CEllipse, CObject, 1)
CEllipse::CEllipse()
{
	m_rotate = 0.0;
}


CEllipse::~CEllipse()
{
}

void CEllipse::OnDraw(CDC* pDC)
{
	//选入画笔
	CPen pen;
	pen.CreatePenIndirect(&m_logpen);
	pDC->SelectObject(pen);

	//选入画刷
	CBrush brush;
	brush.CreateBrushIndirect(&m_logbrush);
	pDC->SelectObject(brush);

	pDC->Ellipse(&m_rect);
}

void CEllipse::OnDrawSelect(CDC* pDC)
{
	//选入画笔
	CPen pen;
	LOGPEN logpenSelect = m_logpen;
	logpenSelect.lopnWidth.x = 10;
	pen.CreatePenIndirect(&logpenSelect);
	pDC->SelectObject(pen);

	//选入画刷
	CBrush brush;
	brush.CreateBrushIndirect(&m_logbrush);
	pDC->SelectObject(brush);

	pDC->Ellipse(&m_rect);
}

void CEllipse::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}

void CEllipse::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
}

void CEllipse::OnMouseMove(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
}

void CEllipse::SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush)
{
	m_logpen = logpen;
	m_logbrush = logbrush;
}

BOOL CEllipse::IsSelected(POINT pt)
{
	POINT aryPts[4];
	aryPts[0].x = m_rect.TopLeft().x;
	aryPts[0].y = m_rect.TopLeft().y;
	aryPts[1].x = m_rect.TopLeft().x;
	aryPts[1].y = m_rect.BottomRight().y;
	aryPts[2].x = m_rect.BottomRight().x;
	aryPts[2].y = m_rect.BottomRight().y;
	aryPts[3].x = m_rect.BottomRight().x;
	aryPts[3].y = m_rect.TopLeft().y;

	for (int i = 0; i < 4; i++)
	{
		aryPts[i].x = (aryPts[i].x - GetCenterPos().x) * cos(m_rotate / 180.0 * 3.14159265f) - (aryPts[i].y - GetCenterPos().y
		) * sin(m_rotate / 180.0 * 3.14159265f) + GetCenterPos().x;
		aryPts[i].y = (aryPts[i].x - GetCenterPos().x) * sin(m_rotate / 180.0 * 3.14159265f) + (aryPts[i].y - GetCenterPos().y
		) * cos(m_rotate / 180.0 * 3.14159265f) + GetCenterPos().y;
	}

	//创建一个包裹住直线的封闭图形
	CRgn rgn;
	rgn.CreatePolygonRgn(aryPts, sizeof(aryPts) / sizeof(POINT), ALTERNATE);

	return rgn.PtInRegion(pt);
}

void CEllipse::MoveShape(POINT ptMoveBegin, POINT ptEnd)
{
	m_rect.TopLeft().x = m_rect.TopLeft().x + ptEnd.x - ptMoveBegin.x;
	m_rect.TopLeft().y = m_rect.TopLeft().y + ptEnd.y - ptMoveBegin.y;

	m_rect.BottomRight().x = m_rect.BottomRight().x + ptEnd.x - ptMoveBegin.x;
	m_rect.BottomRight().y = m_rect.BottomRight().y + ptEnd.y - ptMoveBegin.y;
}

CPoint CEllipse::GetCenterPos()
{
	return CPoint((m_rect.TopLeft().x + m_rect.BottomRight().x) / 2,
	              (m_rect.TopLeft().y + m_rect.BottomRight().y) / 2);
}

float CEllipse::GetRotate()
{
	return m_rotate;
}

void CEllipse::AddRotate(float rotate)
{
	m_rotate += rotate;
}


void CEllipse::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar.Write(&m_logpen, sizeof(m_logpen));
		ar.Write(&m_logbrush, sizeof(m_logbrush));
		ar << m_rotate << m_rect;
	}
	else
	{	// loading code
		ar.Read(&m_logpen, sizeof(m_logpen));
		ar.Read(&m_logbrush, sizeof(m_logbrush));
		ar >> m_rotate >> m_rect;
	}
}
