// ColorButton.cpp : 实现文件
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



// CColorButton 消息处理程序
void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  /*
  * 按钮按下
   */
  if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
    && (lpDrawItemStruct->itemState & ODS_SELECTED))
  {
    CColorDialog dlgColor;
    if (dlgColor.DoModal() == IDOK)
    {
      m_clr = dlgColor.GetColor();
    }
    OutputDebugString(_T("按钮被按下"));
  }

  CDC* pDc = CDC::FromHandle(lpDrawItemStruct->hDC);
  pDc->FillSolidRect(&lpDrawItemStruct->rcItem, m_clr);
//   else if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
//     && !(lpDrawItemStruct->itemState & ODS_SELECTED))
//   {
// 
//     OutputDebugString(_T("按钮没有被按下"));
//   }

  CString csFmt;
  csFmt.Format(_T("itemAction:%08x itemState:%08x"),
    lpDrawItemStruct->itemAction, 
    lpDrawItemStruct->itemState);
  OutputDebugString(csFmt);
}
