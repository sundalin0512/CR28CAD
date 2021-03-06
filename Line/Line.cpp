// Line.cpp: 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Line.h"

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

// CLineApp

BEGIN_MESSAGE_MAP(CLineApp, CWinApp)
END_MESSAGE_MAP()


// CLineApp 构造

CLineApp::CLineApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CLineApp 对象

CLineApp theApp;


// CLineApp 初始化

BOOL CLineApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
IMPLEMENT_SERIAL(CLine, CObject, 1)
CLine::CLine()
{
}


CLine::~CLine()
{
}


void CLine::OnDraw(CDC* pDC)
{
  //选入画笔
  CPen pen;
  pen.CreatePenIndirect(&m_logpen);
  pDC->SelectObject(pen);

  pDC->MoveTo(m_ptBegin);
  pDC->LineTo(m_ptEnd);
}

void CLine::OnLButtonDown(UINT nFlags, CPoint point)
{
  m_ptBegin = point;
}

void CLine::OnLButtonUp(UINT nFlags, CPoint point)
{
  m_ptEnd = point;
}

void CLine::OnMouseMove(UINT nFlags, CPoint point)
{
  m_ptEnd = point;
}

void CLine::SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush)
{
  m_logpen = logpen;
  m_logbrush = logbrush;
}
IShape* CLine::CreateShape()
{
  return new CLine();
}

BOOL CLine::IsSelected(POINT pt)
{
  //获取四个点
  POINT aryPts[4];
  const int nDelta = 5;
  aryPts[0].x = m_ptBegin.x - nDelta;
  aryPts[0].y = m_ptBegin.y;
  aryPts[1].x = m_ptBegin.x + nDelta;
  aryPts[1].y = m_ptBegin.y;
  aryPts[2].x = m_ptEnd.x + nDelta;
  aryPts[2].y = m_ptEnd.y;
  aryPts[3].x = m_ptEnd.x - nDelta;
  aryPts[3].y = m_ptEnd.y;

  //创建一个包裹住直线的封闭图形
  CRgn rgn;
  rgn.CreatePolygonRgn(aryPts, sizeof(aryPts) / sizeof(POINT), ALTERNATE);

  return rgn.PtInRegion(pt);
}

void CLine::OnDrawSelect(CDC* pDC)
{
  //选入画笔
  CPen pen;
  LOGPEN logpenSelect = m_logpen;
  logpenSelect.lopnWidth.x = 10;
  pen.CreatePenIndirect(&logpenSelect);
  pDC->SelectObject(pen);

  pDC->MoveTo(m_ptBegin);
  pDC->LineTo(m_ptEnd);
}

void CLine::MoveShape(POINT ptMoveBegin, POINT ptEnd)
{
  m_ptBegin.x = m_ptBegin.x + ptEnd.x - ptMoveBegin.x;
  m_ptBegin.y = m_ptBegin.y + ptEnd.y - ptMoveBegin.y;


  m_ptEnd.x = m_ptEnd.x + ptEnd.x - ptMoveBegin.x;
  m_ptEnd.y = m_ptEnd.y + ptEnd.y - ptMoveBegin.y;
}

CPoint CLine::GetCenterPos()
{
	return CPoint((m_ptBegin.x + m_ptEnd.x) / 2,
	              (m_ptBegin.y + m_ptEnd.y) / 2);
}

float CLine::GetRotate()
{
	return m_rotate;
}

void CLine::AddRotate(float rotate)
{
	m_rotate += rotate;
}


void CLine::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code

		ar << m_rotate << m_ptBegin << m_ptEnd;
		ar.Write(&m_logpen, sizeof(m_logpen));
		ar.Write(&m_logbrush, sizeof(m_logbrush));
	}
	else
	{	// loading code
		ar >> m_rotate >> m_ptBegin >> m_ptEnd;
		ar.Read(&m_logpen, sizeof(m_logpen));
		ar.Read(&m_logbrush, sizeof(m_logbrush));
	}
}
