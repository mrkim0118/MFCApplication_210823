// Dlg_Teaching_Histogram.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "Dlg_Teaching_Histogram.h"
#include "afxdialogex.h"


// CDlg_Teaching_Histogram ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlg_Teaching_Histogram, CDialogEx)

CDlg_Teaching_Histogram::CDlg_Teaching_Histogram(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_HISTOGRAM, pParent)
	, m_iEdit_Bin_Num(256)
	, m_iEdit_Value_Bin_Number(0)
	, m_iEdit_Value_Min(0)
	, m_iEdit_Value_Max(256)
{
	m_pOpenCV = make_unique<COpenCV>();
	m_pDlgItem = make_unique<CDlgItem>();
}

CDlg_Teaching_Histogram::~CDlg_Teaching_Histogram()
{
}

void CDlg_Teaching_Histogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BIN_NUMBER, m_iEdit_Bin_Num);
	DDX_Control(pDX, IDC_SLIDER_HISTOGRAM, m_Slider_Histogram);
	DDX_Text(pDX, IDC_EDIT_VALUE_BIN_NUMBER, m_iEdit_Value_Bin_Number);
	DDX_Text(pDX, IDC_EDIT_HISTOGRAM_VALUE_MIN, m_iEdit_Value_Min);
	DDX_Text(pDX, IDC_EDIT_HISTOGRAM_VALUE_MAX, m_iEdit_Value_Max);
}


BEGIN_MESSAGE_MAP(CDlg_Teaching_Histogram, CDialogEx)
	ON_WM_HSCROLL()
	ON_MESSAGE(WM_HISTOGRAM, OnReceiveImg)
	ON_EN_CHANGE(IDC_EDIT_VALUE_BIN_NUMBER, &CDlg_Teaching_Histogram::OnEnChangeEditValueBinNumber)
END_MESSAGE_MAP()


// CDlg_Teaching_Histogram �޽��� ó�����Դϴ�.


void CDlg_Teaching_Histogram::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (IDC_SLIDER_HISTOGRAM == pScrollBar->GetDlgCtrlID())
	{
		UpdateData(TRUE);

		m_iEdit_Value_Bin_Number = m_Slider_Histogram.GetPos();

		if (m_pDlgItem->m_ViewData_Src.img->empty() != TRUE)
		{
			UpdateTestImg();
		}

		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CDlg_Teaching_Histogram::UpdateTestImg()
{
	COpenCV::HistogramParams tHistogramParams;
	tHistogramParams.iBinNum = m_iEdit_Value_Bin_Number;
	tHistogramParams.iValueMin = m_iEdit_Value_Min;
	tHistogramParams.iValueMax = m_iEdit_Value_Max;

	m_pOpenCV->Histogram(*m_pDlgItem->m_ViewData_Src.img, *m_pDlgItem->m_ViewData_Dst.img, tHistogramParams);
	m_pDlgItem->DrawViewData(m_pDlgItem->m_ViewData_Dst);
}

BOOL CDlg_Teaching_Histogram::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pDlgItem->m_pWnd = GetDlgItem((IDC_STATIC_HISTOGRAM_TEST));
	m_pDlgItem->InitViewData(m_pDlgItem->m_pWnd);

	m_Slider_Histogram.SetRange(1, 512);
	m_Slider_Histogram.SetPos(m_iEdit_Value_Bin_Number);
	m_Slider_Histogram.SetLineSize(1);
	m_Slider_Histogram.SetPageSize(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlg_Teaching_Histogram::OnEnChangeEditValueBinNumber()
{
	int iMin = m_Slider_Histogram.GetRangeMin();
	int iMax = m_Slider_Histogram.GetRangeMax();

	UpdateData(TRUE);

	if (m_iEdit_Value_Bin_Number < iMin)
		m_iEdit_Value_Bin_Number = iMin;

	else if (m_iEdit_Value_Bin_Number > iMax)
		m_iEdit_Value_Bin_Number = iMax;

	m_Slider_Histogram.SetPos(m_iEdit_Value_Bin_Number);

	if (m_pDlgItem->m_ViewData_Src.img != NULL)
	{
		UpdateTestImg();
	}

	UpdateData(FALSE);
}

LRESULT CDlg_Teaching_Histogram::OnReceiveImg(WPARAM wParam, LPARAM lParam)
{
	m_pDlgItem->m_ViewData_Src.img = (Mat*)lParam;
	m_pDlgItem->DrawViewData(m_pDlgItem->m_ViewData_Src);

	return 0;
}