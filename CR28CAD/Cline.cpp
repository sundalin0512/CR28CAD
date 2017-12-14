#include "stdafx.h"
#include "Cline.h"

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
