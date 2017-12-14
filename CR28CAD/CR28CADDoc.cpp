
// CR28CADDoc.cpp : CCR28CADDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CCR28CADDoc ����/����

CCR28CADDoc::CCR28CADDoc()
{
	// TODO:  �ڴ����һ���Թ������

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

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCR28CADDoc ���л�

void CCR28CADDoc::Serialize(CArchive& ar)
{
	m_lstShapes.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
		auto pos = m_lstShapes.GetHeadPosition();
		for(int i = 0; i < m_lstShapes.GetCount(); i++)
		{
			ar << (CObject*&)m_lstShapes.GetNext(pos);
		}
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
		auto pos = m_lstShapes.GetHeadPosition();
		for (int i = 0; i < m_lstShapes.GetCount(); i++)
		{
			ar >> (CObject*&)m_lstShapes.GetNext(pos);
		}
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCR28CADDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CCR28CADDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CCR28CADDoc ���

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


// CCR28CADDoc ����


void CCR28CADDoc::OnMnHelpCommandsort()
{
  // TODO:  �ڴ���������������
  AfxMessageBox(_T("CCR28CADDoc::OnMnHelpCommandsort"));
}


BOOL CCR28CADDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDocument::OnSaveDocument(lpszPathName);
}
