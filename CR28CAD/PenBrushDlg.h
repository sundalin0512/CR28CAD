#pragma once
#include "afxwin.h"
#include "ColorButton.h"

// CPenBrushDlg �Ի���

class CPenBrushDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPenBrushDlg)
public:
  LOGPEN m_logpen; //���ʵ�����
  LOGBRUSH m_logBrush;//��ˢ������


public:
	CPenBrushDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPenBrushDlg();

// �Ի�������
	enum { IDD = DLG_PENBRUSH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
