// Dlg_Teaching_Brightness.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "Dlg_Teaching_Brightness.h"
#include "afxdialogex.h"


// CDlg_Teaching_Brightness ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlg_Teaching_Brightness, CDialogEx)

CDlg_Teaching_Brightness::CDlg_Teaching_Brightness(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_BRIGHTNESS, pParent)
	, m_iEdit_Value_Brightness(1)
	, m_fEdit_Value_Contrast(1)
	, m_iEdit_Brightness(0)
	, m_fEdit_Contrast(0)
{
	m_pOpenCV = make_unique<COpenCV>();
	m_pDlgItem = make_unique<CDlgItem>();
}

CDlg_Teaching_Brightness::~CDlg_Teaching_Brightness()
{
}

void CDlg_Teaching_Brightness::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_Slider_Brightness);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_Slider_Contrast);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS_VAL, m_iEdit_Value_Brightness);
	DDX_Text(pDX, IDC_EDIT_CONTRAST_VAL, m_fEdit_Value_Contrast);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_iEdit_Brightness);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_fEdit_Contrast);
}


BEGIN_MESSAGE_MAP(CDlg_Teaching_Brightness, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_CVTGRAY, &CDlg_Teaching_Brightness::OnBnClickedBtnCvtgray)
	ON_EN_CHANGE(IDC_EDIT_BRIGHTNESS_VAL, &CDlg_Teaching_Brightness::OnEnChangeEditBrightnessVal)
	ON_EN_CHANGE(IDC_EDIT_CONTRAST_VAL, &CDlg_Teaching_Brightness::OnEnChangeEditContrastVal)
	ON_MESSAGE(WM_BRIGHTNESS, OnReceiveImg)
	ON_EN_CHANGE(IDC_EDIT_BRIGHTNESS, &CDlg_Teaching_Brightness::OnEnChangeEditBrightness)
	ON_EN_CHANGE(IDC_EDIT_CONTRAST, &CDlg_Teaching_Brightness::OnEnChangeEditContrast)
END_MESSAGE_MAP()


// CDlg_Teaching_Brightness �޽��� ó�����Դϴ�.


void CDlg_Teaching_Brightness::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (IDC_SLIDER_BRIGHTNESS == pScrollBar->GetDlgCtrlID())
	{
		UpdateData(TRUE);

		m_iEdit_Value_Brightness = m_Slider_Brightness.GetPos();

		if (m_pDlgItem->m_ViewData_Src.img->empty() != TRUE)
		{
			UpdateTestImg(pScrollBar);
		}

		UpdateData(FALSE);
	}
	else if (IDC_SLIDER_CONTRAST == pScrollBar->GetDlgCtrlID())
	{
		UpdateData(TRUE);

		m_fEdit_Value_Contrast = m_Slider_Contrast.GetPos();

		if (m_pDlgItem->m_ViewData_Src.img->empty() != TRUE)
		{
			UpdateTestImg(pScrollBar);
		}

		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlg_Teaching_Brightness::OnBnClickedBtnCvtgray()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
void CDlg_Teaching_Brightness::UpdateTestImg(CScrollBar* pScrollBar)
{

	COpenCV::BrightnessParams tBrightnessParams;

	tBrightnessParams.fContrast = m_fEdit_Value_Contrast;
	tBrightnessParams.iBrightness = m_iEdit_Value_Brightness;

	m_pOpenCV->Brightness(*m_pDlgItem->m_ViewData_Src.img, *m_pDlgItem->m_ViewData_Dst.img, tBrightnessParams);

}


BOOL CDlg_Teaching_Brightness::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pDlgItem->m_pWnd = GetDlgItem((IDC_STATIC_BRIGHTNESS_TEST));
	m_pDlgItem->InitViewData(m_pDlgItem->m_pWnd);

	m_Slider_Brightness.SetRange(1, 255);
	m_Slider_Brightness.SetPos(m_iEdit_Value_Brightness);
	m_Slider_Brightness.SetLineSize(1);
	m_Slider_Brightness.SetPageSize(1);

	m_Slider_Contrast.SetRange(1, 100);
	m_Slider_Contrast.SetPos((m_fEdit_Value_Contrast*10));
	m_Slider_Contrast.SetLineSize(1);
	m_Slider_Contrast.SetPageSize(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlg_Teaching_Brightness::OnEnChangeEditBrightnessVal()
{
	int iMin = m_Slider_Brightness.GetRangeMin();
	int iMax = m_Slider_Brightness.GetRangeMax();

	UpdateData(TRUE);

	if (m_iEdit_Value_Brightness < iMin)
		m_iEdit_Value_Brightness = iMin;

	else if (m_iEdit_Value_Brightness > iMax)
		m_iEdit_Value_Brightness = iMax;

	m_Slider_Brightness.SetPos(m_iEdit_Value_Brightness);

	if (m_pDlgItem->m_ViewData_Src.img != NULL)
	{
		UpdateTestImg((CScrollBar*)GetDlgItem(IDC_SLIDER_BRIGHTNESS));
	}

	UpdateData(FALSE);
}


void CDlg_Teaching_Brightness::OnEnChangeEditContrastVal()
{
	int iMin = m_Slider_Contrast.GetRangeMin() / 10;
	int iMax = m_Slider_Contrast.GetRangeMax() / 10;

	UpdateData(TRUE);

	if (m_fEdit_Value_Contrast < iMin)
		m_fEdit_Value_Contrast = iMin;

	else if (m_fEdit_Value_Contrast > iMax)
		m_fEdit_Value_Contrast = iMax;

	m_Slider_Contrast.SetPos(m_fEdit_Value_Contrast);

	if (m_pDlgItem->m_ViewData_Src.img != NULL)
	{
		UpdateTestImg((CScrollBar*)GetDlgItem(IDC_SLIDER_CONTRAST));
	}

	UpdateData(FALSE);
}

LRESULT CDlg_Teaching_Brightness::OnReceiveImg(WPARAM wParam, LPARAM lParam)
{
	m_pDlgItem->m_ViewData_Src.img = (Mat*)lParam;
	m_pDlgItem->DrawViewData(m_pDlgItem->m_ViewData_Src);

	return 0;
}

int CDlg_Teaching_Brightness::GetBrightness()
{
	return m_iEdit_Brightness;
}

float CDlg_Teaching_Brightness::GetContrast()
{
	return m_fEdit_Contrast;
}


void CDlg_Teaching_Brightness::OnEnChangeEditBrightness()
{
	if (m_iEdit_Brightness < 1)
		m_iEdit_Brightness = 1;
}


void CDlg_Teaching_Brightness::OnEnChangeEditContrast()
{
	if (m_fEdit_Contrast < 1)
		m_fEdit_Contrast = 1;
}
