#pragma once
#include "IShape.h"
class CEllipse :
	public IShape
{
	DECLARE_SERIAL(CEllipse)
	public:
	CEllipse();
	~CEllipse();

	virtual void OnDraw(CDC* pDC) override;

	virtual void OnDrawSelect(CDC* pDC) override;

	virtual void OnLButtonDown(UINT nFlags, CPoint point) override;

	virtual void OnLButtonUp(UINT nFlags, CPoint point) override;

	virtual void OnMouseMove(UINT nFlags, CPoint point) override;

	virtual void SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush) override;

	virtual BOOL IsSelected(POINT pt) override;

	virtual void MoveShape(POINT ptMoveBegin, POINT ptEnd) override;

	virtual CPoint GetCenterPos() override;


	virtual float GetRotate() override;

	virtual void AddRotate(float rotate) override;
	virtual void Serialize(CArchive& ar) override;
private:
	LOGPEN m_logpen;
	LOGBRUSH m_logbrush;
	float m_rotate;
	private:
	CRect m_rect;
	public:
};

class CEllipseFactory :public IShapeFactory
{
	public:
	IShape* CreateShape()
	{
		return new CEllipse();
	}
};
