// Ellipse.h: Ellipse DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "..\CR28CAD\IShape.h"


// CEllipseApp
// 有关此类实现的信息，请参阅 Ellipse.cpp
//

class CEllipseApp : public CWinApp
{
	public:
	CEllipseApp();

	// 重写
	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
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
	const wchar_t* GetShapeName()
	{
		return L"Ellipse";
	}
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
	IShape * CreateShape()
	{
		return new CEllipse();
	}
	virtual void SetID(int nID)
	{
		m_nID = nID;
	}
	virtual int GetID()
	{
		return m_nID;
	}
	virtual const wchar_t* GetMenuName()
	{
		return L"Ellipse";
	}

	private:
	int m_nID;
};
IShapeFactory* GetShapeFactoryObj()
{
	return new CEllipseFactory;
}