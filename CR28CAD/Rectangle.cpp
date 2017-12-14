#include "stdafx.h"
#include "Rectangle.h"
#include <complex.h>

IMPLEMENT_SERIAL(CRectangle, CObject, 1)
CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::OnDraw(CDC* pDC)
{
	//选入画笔
	CPen pen;
	pen.CreatePenIndirect(&m_logpen);
	pDC->SelectObject(pen);

	//选入画刷
	CBrush brush;
	brush.CreateBrushIndirect(&m_logbrush);
	pDC->SelectObject(brush);

	pDC->Rectangle(&m_rect);
}

void CRectangle::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_rect.TopLeft() = point;
}

void CRectangle::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
}

void CRectangle::OnMouseMove(UINT nFlags, CPoint point)
{
	m_rect.BottomRight() = point;
}

void CRectangle::SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush)
{
	m_logpen = logpen;
	m_logbrush = logbrush;
}

IShape* CRectangle::CreateShape()
{
	return new CRectangle();
}

BOOL CRectangle::IsSelected(POINT pt)
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

	for(int i = 0; i < 4; i++)
	{
		aryPts[i].x = (aryPts[i].x - GetCenterPos().x)*cos(m_rotate / 180.0*3.14159265f) - (aryPts[i].y - GetCenterPos().y)*sin(m_rotate / 180.0*3.14159265f) + GetCenterPos().x;
		aryPts[i].y = (aryPts[i].x - GetCenterPos().x)*sin(m_rotate / 180.0*3.14159265f) + (aryPts[i].y - GetCenterPos().y)*cos(m_rotate / 180.0*3.14159265f) + GetCenterPos().y;
	}

	//创建一个包裹住直线的封闭图形
	CRgn rgn;
	rgn.CreatePolygonRgn(aryPts, sizeof(aryPts) / sizeof(POINT), ALTERNATE);

	return rgn.PtInRegion(pt);
	//return m_rect.PtInRect(pt);
}

void CRectangle::OnDrawSelect(CDC* pDC)
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

	pDC->Rectangle(&m_rect);
}

void CRectangle::MoveShape(POINT ptMoveBegin, POINT ptEnd)
{
	m_rect.TopLeft().x = m_rect.TopLeft().x + ptEnd.x - ptMoveBegin.x;
	m_rect.TopLeft().y = m_rect.TopLeft().y + ptEnd.y - ptMoveBegin.y;

	m_rect.BottomRight().x = m_rect.BottomRight().x + ptEnd.x - ptMoveBegin.x;
	m_rect.BottomRight().y = m_rect.BottomRight().y + ptEnd.y - ptMoveBegin.y;

}

CPoint CRectangle::GetCenterPos()
{
	return CPoint((m_rect.TopLeft().x + m_rect.BottomRight().x) / 2,
	              (m_rect.TopLeft().y + m_rect.BottomRight().y) / 2);
}

float CRectangle::GetRotate()
{
	return m_rotate;
}

void CRectangle::AddRotate(float rotate)
{
	m_rotate += rotate;
}


void CRectangle::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_rotate << m_rect;
		ar.Write(&m_logpen, sizeof(m_logpen));
		ar.Write(&m_logbrush, sizeof(m_logbrush));
	}
	else
	{	// loading code
		ar >> m_rotate >> m_rect;
		ar.Read(&m_logpen, sizeof(m_logpen));
		ar.Read(&m_logbrush, sizeof(m_logbrush));
	}
}
