
// CR28CADDoc.h : CCR28CADDoc ��Ľӿ�
//


#pragma once
#include "IShape.h"


class CCR28CADDoc : public CDocument
{
	public:
	friend class CCR28CADView;
	protected: // �������л�����
	CCR28CADDoc();
	DECLARE_DYNCREATE(CCR28CADDoc)

	// ����
	public:

	// ����
	public:

	// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// ʵ��
	public:
	virtual ~CCR28CADDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	protected:

	// ���ɵ���Ϣӳ�亯��
	protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	public:
	afx_msg void OnMnHelpCommandsort();
	private:
	CList<IShape*, IShape*> m_lstShapes;
	public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
