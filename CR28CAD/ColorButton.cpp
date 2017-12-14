// ColorButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CR28CAD.h"
#include "ColorButton.h"


// CColorButton

IMPLEMENT_DYNAMIC(CColorButton, CButton)

CColorButton::CColorButton()
{

}

CColorButton::~CColorButton()
{
}

void CColorButton::SetColor(COLORREF color)
{
  m_clr = color;
}

COLORREF CColorButton::GetColor()
{
  return m_clr;
}

BEGIN_MESSAGE_MAP(CColorButton, CButton)
END_MESSAGE_MAP()



// CColorButton ��Ϣ�������
void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  /*
  * ��ť����
   */
  if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
    && (lpDrawItemStruct->itemState & ODS_SELECTED))
  {
    CColorDialog dlgColor;
    if (dlgColor.DoModal() == IDOK)
    {
      m_clr = dlgColor.GetColor();
    }
    OutputDebugString(_T("��ť������"));
  }

  CDC* pDc = CDC::FromHandle(lpDrawItemStruct->hDC);
  pDc->FillSolidRect(&lpDrawItemStruct->rcItem, m_clr);
//   else if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
//     && !(lpDrawItemStruct->itemState & ODS_SELECTED))
//   {
// 
//     OutputDebugString(_T("��ťû�б�����"));
//   }

  CString csFmt;
  csFmt.Format(_T("itemAction:%08x itemState:%08x"),
    lpDrawItemStruct->itemAction, 
    lpDrawItemStruct->itemState);
  OutputDebugString(csFmt);
}
