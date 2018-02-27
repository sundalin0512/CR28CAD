
// CR28CADView.cpp : CCR28CADView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CR28CAD.h"
#endif

#include "MainFrm.h"
#include "CR28CADDoc.h"
#include "CR28CADView.h"
#include "AddOperator.h"
#include "MoveOperator.h"
#include "RotateOperator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCR28CADView

IMPLEMENT_DYNCREATE(CCR28CADView, CView)

BEGIN_MESSAGE_MAP(CCR28CADView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_COMMAND(MN_HELP_COMMANDSORT, &CCR28CADView::OnMnHelpCommandsort)
	ON_MESSAGE(WM_MYMESSAGE, &CCR28CADView::OnMymessage)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(MN_SHAPE_PENBRUSH, &CCR28CADView::OnShapePenbrush)
	ON_COMMAND(MN_SHAPE_SELLECT, &CCR28CADView::OnShapeSellect)
	ON_COMMAND(MN_SHAPE_ROTATE, &CCR28CADView::OnMnShapeRotate)
	ON_COMMAND(ID_EDIT_REDO, &CCR28CADView::OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CCR28CADView::OnEditUndo)

END_MESSAGE_MAP()

// CCR28CADView ����/����

CCR28CADView::CCR28CADView() :
	m_bOnDraw(FALSE),
	m_pCurrentShape(NULL),

	m_pShapeFactory(NULL),
	m_dwOperaterType(OPTYPE_NULL),
	m_optmgr(NULL)
{
	m_logpen.lopnStyle = BS_SOLID;
	m_logpen.lopnWidth.x = 1;
	m_logpen.lopnColor = RGB(0, 0, 0);
	m_logbrush.lbStyle = BS_NULL;
	m_pSelectShape = nullptr;
}

CCR28CADView::~CCR28CADView()
{

}

BOOL CCR28CADView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCR28CADView ����
void CCR28CADView::OnDraw(CDC* pDC)
{
	CCR28CADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/*
	 *  ˫�����ͼ��
	 */
	 //1.�����ڴ�DC(����DC)
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);

	//2.��������λͼ
	CRect rcClient;
	GetClientRect(&rcClient);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());


	//3. 3)	������λͼѡ���ڴ�DC
	dcMem.SelectObject(bmp);
	dcMem.FillSolidRect(rcClient, RGB(255, 255, 255));//�ð�ɫ���ͻ���

	/*
	* ���û��ʺͻ�ˢ
	*/
	//   CPen pen;
	//   pen.CreatePenIndirect(&m_logpen);
	//   dcMem.SelectObject(pen);
	//   CBrush brush;
	//   brush.CreateBrushIndirect(&m_logbrush);
	//   dcMem.SelectObject(brush);

	//4.	����ͼ��
	//����Ȼ��������е�ֱ��
	//���ƾ���
	POSITION pos = m_lstShapes->GetHeadPosition();
	IShape* pShape = nullptr;

	while (pos)
	{
		pShape = m_lstShapes->GetNext(pos);

		XFORM xForm;
		float fangle = pShape->GetRotate() / 180.0 * 3.14159265f;
		xForm.eM11 = (float)cos(fangle);
		xForm.eM12 = (float)sin(fangle);
		xForm.eM21 = (float)-sin(fangle);
		xForm.eM22 = (float)cos(fangle);
		xForm.eDx = (float)pShape->GetCenterPos().x - cos(fangle)*pShape->GetCenterPos().x + sin(fangle)*pShape->GetCenterPos().y;
		xForm.eDy = (float)pShape->GetCenterPos().y - cos(fangle)*pShape->GetCenterPos().y - sin(fangle)*pShape->GetCenterPos().x;
		int nGraphicsMode = SetGraphicsMode(dcMem, GM_ADVANCED);
		dcMem.SetWorldTransform(&xForm);
		if (pShape == m_pSelectShape)
		{
			//����ѡ�е�ͼ��
			pShape->OnDrawSelect(&dcMem);
		}
		else
		{
			pShape->OnDraw(&dcMem);
		}
		xForm.eM11 = (float)1.0;
		xForm.eM12 = (float)0;
		xForm.eM21 = (float)0;
		xForm.eM22 = (float)1.0;
		xForm.eDx = (float)0;
		xForm.eDy = (float)0;
		dcMem.SetWorldTransform(&xForm);
		SetGraphicsMode(dcMem, nGraphicsMode);
		if (!pos)
			break;
	}
	//����ֱ��
	if (m_bOnDraw && m_pCurrentShape != NULL)
	{
		m_pCurrentShape->OnDraw(&dcMem);
	}

	//5. ����ͼ��
	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(),
		&dcMem, 0, 0, SRCCOPY);
}


// CCR28CADView ��ӡ
BOOL CCR28CADView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCR28CADView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCR28CADView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CCR28CADView ���

#ifdef _DEBUG
void CCR28CADView::AssertValid() const
{
	CView::AssertValid();
}

void CCR28CADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCR28CADDoc* CCR28CADView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCR28CADDoc)));
	return (CCR28CADDoc*)m_pDocument;
}
#endif //_DEBUG


// CCR28CADView ��Ϣ�������


BOOL CCR28CADView::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CView::PreTranslateMessage(pMsg);
}


int CCR28CADView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CCR28CADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return -1;
	m_lstShapes = &GetDocument()->m_lstShapes;
	m_optmgr.m_pDoc = GetDocument();
	return 0;
}


void CCR28CADView::OnMnHelpCommandsort()
{
	// TODO:  �ڴ���������������
	SendMessage(WM_MYMESSAGE, NULL, NULL);
}


afx_msg LRESULT CCR28CADView::OnMymessage(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("CCR28CADView::OnMymessage"));
	return 0;
}


void CCR28CADView::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch (m_dwOperaterType)
	{
	case OPTYPE_CREARTESHAPE:
		//����һ���µ�ͼ��
		if (m_pShapeFactory != NULL)
		{
			m_pCurrentShape = m_pShapeFactory->CreateShape();
		}

		if (m_pCurrentShape != NULL)
		{
			//��ʼ����ͼ��
			m_bOnDraw = TRUE;

			m_pCurrentShape->SetPenBrush(m_logpen, m_logbrush);
			m_pCurrentShape->OnLButtonDown(nFlags, point);

			//���մ�����������Ϣ
			SetCapture();
		}
		break;
	case OPTYPE_SELECTSHAPE:
	{
		POSITION pos = m_lstShapes->GetHeadPosition();
		while (pos)
		{
			IShape* pShape = m_lstShapes->GetNext(pos);
			if (pShape->IsSelected(point))
			{
				m_pSelectShape = pShape;
				m_dwOperaterType = OPTYPE_MOVESHAPE; //�û������ƶ�ͼ��
				m_ptMoveBegin = point; //�����ƶ������
				m_ptMoveBegin0 = point; //�����ƶ������
				break;
			}
		}

		//֪ͨ�����ػ�
		InvalidateRect(NULL, FALSE);
	}
	break;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CCR28CADView::OnLButtonUp(UINT nFlags, CPoint point)
{

	switch (m_dwOperaterType)
	{
	case OPTYPE_CREARTESHAPE:
	{
		if (m_pCurrentShape != NULL && m_bOnDraw) //���ڻ�ͼ
		{
			//ֹͣ����ͼ��
			m_bOnDraw = FALSE;

			m_pCurrentShape->OnLButtonUp(nFlags, point);
			m_lstShapes->AddTail(m_pCurrentShape);

			IOperator* pOperator =
				new AddOperator(m_lstShapes, m_pCurrentShape);
			m_optmgr.AddOperator(pOperator);
			//ֹͣ���մ�����������Ϣ
			ReleaseCapture();
		}
	}
	break;

	case OPTYPE_MOVESHAPE:
	{
		m_dwOperaterType = OPTYPE_SELECTSHAPE;
		m_ptMoveEnd = point;
		if (m_ptMoveBegin != m_ptMoveEnd)
		{
			m_pSelectShape->MoveShape(m_ptMoveBegin, m_ptMoveEnd);
		}
		if (m_ptMoveBegin0 != m_ptMoveEnd)
		{
			IOperator* pOperator = new MoveOperator(m_pSelectShape, m_ptMoveBegin0, m_ptMoveEnd);
			m_optmgr.AddOperator(pOperator);
		}
	}
	break;
	}

	//֪ͨ�����ػ�
	InvalidateRect(NULL, FALSE);

	CView::OnLButtonUp(nFlags, point);
}


void CCR28CADView::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (m_dwOperaterType)
	{
	case OPTYPE_CREARTESHAPE:
		if (m_pCurrentShape != NULL && m_bOnDraw)
		{
			m_pCurrentShape->OnMouseMove(nFlags, point);
		}
		break;
	case OPTYPE_MOVESHAPE:
		m_ptMoveEnd = point;
		m_pSelectShape->MoveShape(m_ptMoveBegin, m_ptMoveEnd);
		m_ptMoveBegin = m_ptMoveEnd; //���յ㵱�����
		break;
	}

	//֪ͨ�����ػ�
	InvalidateRect(NULL, FALSE);
	CView::OnMouseMove(nFlags, point);
}





void CCR28CADView::OnShapePenbrush()
{
	CPenBrushDlg dlgPenBrush;
	if (dlgPenBrush.DoModal() == IDOK)
	{
		m_logpen = dlgPenBrush.m_logpen;
		m_logbrush = dlgPenBrush.m_logBrush;
	}

}


void CCR28CADView::OnShapeSellect()
{
	m_dwOperaterType = OPTYPE_SELECTSHAPE; //�û�ѡ��ͼ�β���
}




void CCR28CADView::OnMnShapeRotate()
{
	// TODO: �ڴ���������������
	m_dwOperaterType = OPTYPE_ROTATESHAPE;
	if (m_pSelectShape != nullptr)
	{
		m_pSelectShape->AddRotate(15);
		IOperator* pOperator = new RotateOperator(m_pSelectShape, 15.0);
		m_optmgr.AddOperator(pOperator);

		InvalidateRect(NULL, FALSE);
	}
}


void CCR28CADView::OnEditRedo()
{
	// TODO: �ڴ���������������
	m_optmgr.Redo();
	InvalidateRect(NULL, FALSE);
}


void CCR28CADView::OnEditUndo()
{
	// TODO: �ڴ���������������
	m_optmgr.Undo();

	InvalidateRect(NULL, FALSE);
}


