#pragma once


// CColorButton

class CColorButton : public CButton
{
	DECLARE_DYNAMIC(CColorButton)
  COLORREF m_clr;

public:
	CColorButton();
	virtual ~CColorButton();

  void SetColor(COLORREF color);
  COLORREF GetColor();
protected:
	DECLARE_MESSAGE_MAP()
public:
  virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


