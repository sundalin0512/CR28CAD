
// CR28CADDoc.cpp : CCR28CADDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CR28CAD.h"
#endif

#include "CR28CADDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCR28CADDoc

IMPLEMENT_DYNCREATE(CCR28CADDoc, CDocument)

BEGIN_MESSAGE_MAP(CCR28CADDoc, CDocument)
  //ON_COMMAND(MN_HELP_COMMANDSORT, &CCR28CADDoc::OnMnHelpCommandsort)
END_MESSAGE_MAP()


// CCR28CADDoc 构造/析构

CCR28CADDoc::CCR28CADDoc()
{
	// TODO:  在此添加一次性构造代码

}

CCR28CADDoc::~CCR28CADDoc()
{
	while (!m_lstShapes.IsEmpty())
	{
		auto p = m_lstShapes.GetTail();
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
		m_lstShapes.RemoveTail();
	}
}

BOOL CCR28CADDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCR28CADDoc 序列化

void CCR28CADDoc::Serialize(CArchive& ar)
{
	m_lstShapes.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		auto pos = m_lstShapes.GetHeadPosition();
		for(int i = 0; i < m_lstShapes.GetCount(); i++)
		{
			ar << (CObject*&)m_lstShapes.GetNext(pos);
		}
	}
	else
	{
		// TODO:  在此添加加载代码
		auto pos = m_lstShapes.GetHeadPosition();
		for (int i = 0; i < m_lstShapes.GetCount(); i++)
		{
			ar >> (CObject*&)m_lstShapes.GetNext(pos);
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCR28CADDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCR28CADDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCR28CADDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCR28CADDoc 诊断

#ifdef _DEBUG
void CCR28CADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCR28CADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCR28CADDoc 命令


void CCR28CADDoc::OnMnHelpCommandsort()
{
  // TODO:  在此添加命令处理程序代码
  AfxMessageBox(_T("CCR28CADDoc::OnMnHelpCommandsort"));
}


BOOL CCR28CADDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDocument::OnSaveDocument(lpszPathName);
}
