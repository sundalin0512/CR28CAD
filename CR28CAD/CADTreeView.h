#pragma once


// CADTreeView 视图

class CADTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CADTreeView)

protected:
	CADTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CADTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuTreesetting();
};


