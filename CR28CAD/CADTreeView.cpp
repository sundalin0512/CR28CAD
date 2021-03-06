// CADTreeView.cpp: 实现文件
//

#include "stdafx.h"
#include "CR28CAD.h"
#include "CADTreeView.h"
#include "CR28CADDoc.h"
#include "CR28CADView.h"


// CADTreeView

IMPLEMENT_DYNCREATE(CADTreeView, CTreeView)

CADTreeView::CADTreeView()
{

}

CADTreeView::~CADTreeView()
{
}

BEGIN_MESSAGE_MAP(CADTreeView, CTreeView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CADTreeView::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CADTreeView::OnNMRClick)
	ON_COMMAND(ID_MENU_TREESETTING, &CADTreeView::OnMenuTreesetting)
END_MESSAGE_MAP()


// CADTreeView 诊断

#ifdef _DEBUG
void CADTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CADTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CADTreeView 消息处理程序


void CADTreeView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCR28CADDoc)));
	auto pList = &((CCR28CADDoc*)m_pDocument)->m_lstShapes;
	GetTreeCtrl().DeleteAllItems();
	//初始化树
	int count = 0;
	POSITION pos = pList->GetHeadPosition();
	IShape* pShape = nullptr;

	while (pos)
	{
		pShape = pList->GetNext(pos);
		CString str;
		str.Format(L"%d", count);
		auto h = GetTreeCtrl().InsertItem(str + pShape->GetShapeName());
		GetTreeCtrl().SetItemData(h, (UINT)pShape);
		if (!pos)
			break;
		count++;
	}


}



void CADTreeView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	auto h = GetTreeCtrl().GetSelectedItem();
	IShape* p = (IShape*) GetTreeCtrl().GetItemData(h);
	POSITION pos = ((CCR28CADDoc*)m_pDocument)->GetFirstViewPosition();
	while (pos)
	{
		CView* pView = ((CCR28CADDoc*)m_pDocument)->GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCR28CADView)))
		{

			CCR28CADView* pMyEdit = (CCR28CADView*)pView;
			pMyEdit->m_pSelectShape = p;
			pMyEdit->Invalidate(FALSE);
			break;
		}
	}


	*pResult = 0;
}


void CADTreeView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	auto h = GetTreeCtrl().GetSelectedItem();
	if(h != NULL)
	{

		CMenu menu;
		menu.LoadMenu(IDR_TREEMENU);
		CMenu* pPopup = menu.GetSubMenu(0);

		CPoint myPoint;
		GetCursorPos(&myPoint);  //鼠标位置
		pPopup->TrackPopupMenu(TPM_LEFTALIGN, myPoint.x, myPoint.y, this);
	}
	
	*pResult = 0;
}


void CADTreeView::OnMenuTreesetting()
{
	// TODO: 在此添加命令处理程序代码
	auto h = GetTreeCtrl().GetSelectedItem();
	IShape* p = (IShape*)GetTreeCtrl().GetItemData(h);
	POSITION pos = ((CCR28CADDoc*)m_pDocument)->GetFirstViewPosition();
	while (pos)
	{
		CView* pView = ((CCR28CADDoc*)m_pDocument)->GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCR28CADView)))
		{

			CCR28CADView* pMyEdit = (CCR28CADView*)pView;
			pMyEdit->OnShapePenbrush();
			p->SetPenBrush(pMyEdit->m_logpen, pMyEdit->m_logbrush);
			pMyEdit->Invalidate(FALSE);
			break;
		}
	}


}
