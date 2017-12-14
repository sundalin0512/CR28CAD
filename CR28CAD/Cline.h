#pragma once
#include "IShape.h"
class CLine :public  IShape
{
	DECLARE_SERIAL(CLine)
	public:
	CLine();
	virtual ~CLine();

	virtual void OnDraw(CDC* pDC) override;
	virtual void OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) override;
	virtual void OnMouseMove(UINT nFlags, CPoint point) override;
	virtual void SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush) override;
	static IShape* CreateShape();

	BOOL IsSelected(POINT pt) override;

	virtual void OnDrawSelect(CDC* pDC) override;

	virtual void MoveShape(POINT ptMoveBegin, POINT ptEnd) override;

	virtual CPoint GetCenterPos() override;

	virtual float GetRotate() override;

	virtual void AddRotate(float rotate) override;

//	virtual void Serialize(CArchive& ar) override;
	private:
	float m_rotate = 0.0;
	LOGPEN m_logpen;
	LOGBRUSH m_logbrush;
	CPoint m_ptBegin; //直线起点
	CPoint m_ptEnd; //直线的终点
	public:
	virtual void Serialize(CArchive& ar) override;
};

class CLineFactory :public IShapeFactory
{
	public:
	IShape * CreateShape()
	{
		return new CLine();
	}
};
