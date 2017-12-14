#pragma once
#include "IShape.h"
class CRectangle :public IShape
{
	DECLARE_SERIAL(CRectangle)
	public:
	CRectangle();
	virtual ~CRectangle();
	virtual void OnDraw(CDC* pDC) override;
	virtual void OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) override;
	virtual void OnMouseMove(UINT nFlags, CPoint point) override;
	virtual void SetPenBrush(LOGPEN logpen, LOGBRUSH logbrush) override;
	static IShape* CreateShape();

	virtual BOOL IsSelected(POINT pt) override;

	virtual void OnDrawSelect(CDC* pDC) override;

	virtual void MoveShape(POINT ptMoveBegin, POINT ptEnd) override;

	virtual CPoint GetCenterPos() override;

	virtual float GetRotate() override;

	virtual void AddRotate(float rotate) override;
	private:
	float m_rotate = 0.0;
	LOGPEN m_logpen;
	LOGBRUSH m_logbrush;

	private:
	CRect m_rect;
	public:
	void Serialize(CArchive& ar) override;
};

class CRectangleFactory :public IShapeFactory
{
	public:
	virtual IShape* CreateShape() override
	{
		return new CRectangle();
	}
};
