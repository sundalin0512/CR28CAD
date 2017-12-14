#pragma once
#include "afxwin.h"
#include "ColorButton.h"

// CPenBrushDlg 对话框

class CPenBrushDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPenBrushDlg)
public:
  LOGPEN m_logpen; //画笔的属性
  LOGBRUSH m_logBrush;//画刷的属性


public:
	CPenBrushDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPenBrushDlg();

// 对话框数据
	enum { IDD = DLG_PENBRUSH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  CComboBox m_cmbPenStyle;
  afx_msg void OnBnClickedOk();
  CColorButton m_btnPenColor;
  CComboBox m_cmbBrushHatch;
  CComboBox m_cmbBrushStyle;
  CColorButton m_btnBrushColor;
};
