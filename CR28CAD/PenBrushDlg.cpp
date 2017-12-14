// PenBrushDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CR28CAD.h"
#include "PenBrushDlg.h"
#include "afxdialogex.h"


// CPenBrushDlg �Ի���

IMPLEMENT_DYNAMIC(CPenBrushDlg, CDialogEx)

CPenBrushDlg::CPenBrushDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPenBrushDlg::IDD, pParent)
{

}

CPenBrushDlg::~CPenBrushDlg()
{
}

void CPenBrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, CMB_PENSYLE, m_cmbPenStyle);
	DDX_Control(pDX, BTN_COLOR, m_btnPenColor);
	DDX_Control(pDX, CMB_BRUSHHATCH, m_cmbBrushHatch);
	DDX_Control(pDX, CMB_BRUSHSYLE, m_cmbBrushStyle);
	DDX_Control(pDX, BTN_BRUSHCOLOR, m_btnBrushColor);
}


BEGIN_MESSAGE_MAP(CPenBrushDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPenBrushDlg::OnBnClickedOk)
	//  ON_BN_CLICKED(BTN_COLOR, &CPenBrushDlg::OnBnClickedColor)
END_MESSAGE_MAP()


// CPenBrushDlg ��Ϣ�������


BOOL CPenBrushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cmbPenStyle.AddString(_T("ʵ��"));
	m_cmbPenStyle.AddString(_T("����"));
	m_cmbPenStyle.AddString(_T("����"));
	m_cmbPenStyle.AddString(_T("�㻮��"));

	/*
	*  ��ʼ��ˢ��
	*/
	m_cmbBrushStyle.AddString(_T("����"));
	m_cmbBrushStyle.AddString(_T("ʵ��"));
	m_cmbBrushStyle.AddString(_T("��Ӱ"));

	//��Ӱ
	m_cmbBrushHatch.AddString(_T("����"));
	m_cmbBrushHatch.AddString(_T("����"));
	m_cmbBrushHatch.AddString(_T("��б��"));
	m_cmbBrushHatch.AddString(_T("��б��"));
	m_cmbBrushHatch.AddString(_T("ˮƽ����"));
	m_cmbBrushHatch.AddString(_T("б����"));

	m_cmbPenStyle.SetCurSel(0);
	m_btnPenColor.SetColor(0);
	m_cmbBrushHatch.SetCurSel(0);
	m_cmbBrushStyle.SetCurSel(0);
	m_btnBrushColor.SetColor(0);
	SetDlgItemInt(EDT_PENWITH, 1);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CPenBrushDlg::OnBnClickedOk()
{
	/*
	* ��ȡ���ʵķ��
	*/
	int aryPenStyle[] = {
	PS_SOLID,
	PS_DASH,
	PS_DOT,
	PS_DASHDOT
	};
	int nIdx = m_cmbPenStyle.GetCurSel();
	int nPenStyle = aryPenStyle[nIdx];

	/*
	* ��ȡ���ʵĿ��
	*/
	UINT nPenWith = GetDlgItemInt(EDT_PENWITH); //��ȡ���ʵĿ��

	/*
	* ��ȡ���ʵ���ɫ
	*/
	COLORREF clrPen = m_btnPenColor.GetColor();

	/*
	* ��ȡ��ˢ�ķ��
	*/
	int aryBrushStyle[] = {
	  BS_NULL,
	  BS_SOLID,
	  BS_HATCHED,
	};
	nIdx = m_cmbBrushStyle.GetCurSel();
	int nBrushStyle = aryBrushStyle[nIdx];

	/*
	* ���滭�ʵķ��
	*/
	m_logpen.lopnStyle = nPenStyle;
	m_logpen.lopnWidth.x = nPenWith;
	m_logpen.lopnColor = clrPen;

	/*
	* ��ȡ��ˢ����Ӱ���
	*/
	int aryBrushHatch[] =
	{
	  HS_HORIZONTAL,
	  HS_VERTICAL,
	  HS_FDIAGONAL,
	  HS_BDIAGONAL,
	  HS_CROSS,
	  HS_DIAGCROSS
	};
	nIdx = m_cmbBrushHatch.GetCurSel();
	int nHatched = aryBrushHatch[nIdx];

	/*
	* ��ȡ��ˢ����ɫ
	*/
	int nBrushColor = m_btnBrushColor.GetColor();


	/*
	* ���滭ˢ�ķ��
	*/
	m_logBrush.lbStyle = nBrushStyle;
	m_logBrush.lbHatch = nHatched;
	m_logBrush.lbColor = nBrushColor;

	CDialogEx::OnOK();
}


//void CPenBrushDlg::OnBnClickedColor()
//{
//  CColorDialog dlgColor;
//  if (dlgColor.DoModal() == IDOK)
//  {
//    COLORREF clr = dlgColor.GetColor();
//    int n = 0; 
//  }
//}
