
// CR28CADView.h : CCR28CADView 类的接口
//

#pragma once
#include "PenBrushDlg.h"
#include "OperatorManager.h"
#include "CR28CADDoc.h"

#define  WM_MYMESSAGE WM_USER + 1
class CCR28CADView : public CView
{
	protected: // 仅从序列化创建
	CCR28CADView();
	DECLARE_DYNCREATE(CCR28CADView)
	private:
	typedef struct tagLINE
	{
		CPoint m_ptBegin; //直线起点
		CPoint m_ptEnd; //直线的终点
	}LINE, *PLINE;


	

	public:
	enum
	{
		OPTYPE_NULL,
		OPTYPE_CREARTESHAPE,//画图
		OPTYPE_SELECTSHAPE,//选择
		OPTYPE_ROTATESHAPE, //旋转
		OPTYPE_MOVESHAPE //移动
	};
	LOGPEN m_logpen;
	LOGBRUSH m_logbrush;

	typedef IShape* (*PFN_CREATESHAPE)();

	public:
	CPoint m_ptMoveBegin0; //移动图形起点
	CPoint m_ptMoveBegin; //移动图形起点
	CPoint m_ptMoveEnd;//移动图形终点

	BOOL m_bOnDraw; //是否正在绘制图形
	DWORD m_dwOperaterType; //操作类型,指明当前用户的操作(创建新图形,选择图形,旋转图形)

	IShapeFactory* m_pShapeFactory;
	IShape* m_pCurrentShape; //当前正在绘制的图形
	IShape* m_pSelectShape; //选中的图形
	CList<IShape*, IShape*>* m_lstShapes; //保存所有绘制的图形
	OperatorManager m_optmgr;

  // 特性
	public:
	CCR28CADDoc * GetDocument() const;

	// 操作
	public:

	// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
	public:
	virtual ~CCR28CADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	protected:

	// 生成的消息映射函数
	protected:
	DECLARE_MESSAGE_MAP()
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMnHelpCommandsort();
	protected:
	afx_msg LRESULT OnMymessage(WPARAM wParam, LPARAM lParam);
	public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMnShapeLine();
	afx_msg void OnMnShapeRect();
	afx_msg void OnShapePenbrush();
	afx_msg void OnShapeSellect();
	afx_msg void OnMnShapeEllipse();
	afx_msg void OnMnShapeRotate();
	afx_msg void OnEditRedo();
	afx_msg void OnEditUndo();

};

#ifndef _DEBUG  // CR28CADView.cpp 中的调试版本
inline CCR28CADDoc* CCR28CADView::GetDocument() const
{
	return reinterpret_cast<CCR28CADDoc*>(m_pDocument);
}
#endif

