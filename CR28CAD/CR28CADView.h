
// CR28CADView.h : CCR28CADView ��Ľӿ�
//

#pragma once
#include "PenBrushDlg.h"
#include "OperatorManager.h"
#include "CR28CADDoc.h"

#define  WM_MYMESSAGE WM_USER + 1
class CCR28CADView : public CView
{
	protected: // �������л�����
	CCR28CADView();
	DECLARE_DYNCREATE(CCR28CADView)
	private:
	typedef struct tagLINE
	{
		CPoint m_ptBegin; //ֱ�����
		CPoint m_ptEnd; //ֱ�ߵ��յ�
	}LINE, *PLINE;


	

	public:
	enum
	{
		OPTYPE_NULL,
		OPTYPE_CREARTESHAPE,//��ͼ
		OPTYPE_SELECTSHAPE,//ѡ��
		OPTYPE_ROTATESHAPE, //��ת
		OPTYPE_MOVESHAPE //�ƶ�
	};
	LOGPEN m_logpen;
	LOGBRUSH m_logbrush;

	typedef IShape* (*PFN_CREATESHAPE)();

	public:
	CPoint m_ptMoveBegin0; //�ƶ�ͼ�����
	CPoint m_ptMoveBegin; //�ƶ�ͼ�����
	CPoint m_ptMoveEnd;//�ƶ�ͼ���յ�

	BOOL m_bOnDraw; //�Ƿ����ڻ���ͼ��
	DWORD m_dwOperaterType; //��������,ָ����ǰ�û��Ĳ���(������ͼ��,ѡ��ͼ��,��תͼ��)

	IShapeFactory* m_pShapeFactory;
	IShape* m_pCurrentShape; //��ǰ���ڻ��Ƶ�ͼ��
	IShape* m_pSelectShape; //ѡ�е�ͼ��
	CList<IShape*, IShape*>* m_lstShapes; //�������л��Ƶ�ͼ��
	OperatorManager m_optmgr;

  // ����
	public:
	CCR28CADDoc * GetDocument() const;

	// ����
	public:

	// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
	public:
	virtual ~CCR28CADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	protected:

	// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // CR28CADView.cpp �еĵ��԰汾
inline CCR28CADDoc* CCR28CADView::GetDocument() const
{
	return reinterpret_cast<CCR28CADDoc*>(m_pDocument);
}
#endif

