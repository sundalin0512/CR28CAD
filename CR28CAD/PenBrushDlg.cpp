// PenBrushDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CR28CAD.h"
#include "PenBrushDlg.h"
#include "afxdialogex.h"


// CPenBrushDlg 对话框

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


// CPenBrushDlg 消息处理程序


BOOL CPenBrushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cmbPenStyle.AddString(_T("实心"));
	m_cmbPenStyle.AddString(_T("点线"));
	m_cmbPenStyle.AddString(_T("虚线"));
	m_cmbPenStyle.AddString(_T("点划线"));

	/*
	*  初始化刷子
	*/
	m_cmbBrushStyle.AddString(_T("空心"));
	m_cmbBrushStyle.AddString(_T("实心"));
	m_cmbBrushStyle.AddString(_T("阴影"));

	//阴影
	m_cmbBrushHatch.AddString(_T("横线"));
	m_cmbBrushHatch.AddString(_T("竖线"));
	m_cmbBrushHatch.AddString(_T("右斜线"));
	m_cmbBrushHatch.AddString(_T("左斜线"));
	m_cmbBrushHatch.AddString(_T("水平交叉"));
	m_cmbBrushHatch.AddString(_T("斜交叉"));

	m_cmbPenStyle.SetCurSel(0);
	m_btnPenColor.SetColor(0);
	m_cmbBrushHatch.SetCurSel(0);
	m_cmbBrushStyle.SetCurSel(0);
	m_btnBrushColor.SetColor(0);
	SetDlgItemInt(EDT_PENWITH, 1);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPenBrushDlg::OnBnClickedOk()
{
	/*
	* 获取画笔的风格
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
	* 获取画笔的宽度
	*/
	UINT nPenWith = GetDlgItemInt(EDT_PENWITH); //获取画笔的宽度

	/*
	* 获取画笔的颜色
	*/
	COLORREF clrPen = m_btnPenColor.GetColor();

	/*
	* 获取画刷的风格
	*/
	int aryBrushStyle[] = {
	  BS_NULL,
	  BS_SOLID,
	  BS_HATCHED,
	};
	nIdx = m_cmbBrushStyle.GetCurSel();
	int nBrushStyle = aryBrushStyle[nIdx];

	/*
	* 保存画笔的风格
	*/
	m_logpen.lopnStyle = nPenStyle;
	m_logpen.lopnWidth.x = nPenWith;
	m_logpen.lopnColor = clrPen;

	/*
	* 获取画刷的阴影风格
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
	* 获取画刷的颜色
	*/
	int nBrushColor = m_btnBrushColor.GetColor();


	/*
	* 保存画刷的风格
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
