// Line.h: Line DLL 的主标头文件
//

#pragma once
#include "..\CR28CAD\IShape.h"
#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CLineApp
// 有关此类实现的信息，请参阅 Line.cpp
//

class CLineApp : public CWinApp
{
	public:
	CLineApp();

	// 重写
	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


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
	const wchar_t* GetShapeName()
	{
		return L"Line";
	}
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
		return L"Line";
	}


	private:
	int m_nID;

};

IShapeFactory* GetShapeFactoryObj()
{
	return new CLineFactory;
}