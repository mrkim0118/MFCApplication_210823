// Dlg_Teaching_Template_Match.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "Dlg_Teaching_Template_Match.h"
#include "afxdialogex.h"


// CDlg_Teaching_Template_Match 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlg_Teaching_Template_Match, CDialogEx)

CDlg_Teaching_Template_Match::CDlg_Teaching_Template_Match(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_TEMPLATE_MATCH, pParent)
{
	m_pDlgItem = make_unique<CDlgItem>();
}

CDlg_Teaching_Template_Match::~CDlg_Teaching_Template_Match()
{
}

void CDlg_Teaching_Template_Match::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_METHOD, m_Cmb_Method);
}


BEGIN_MESSAGE_MAP(CDlg_Teaching_Template_Match, CDialogEx)
	ON_MESSAGE(WM_TEMPLATE_MATCH_TEST, OnReceiveImg)
END_MESSAGE_MAP()


// CDlg_Teaching_Template_Match 메시지 처리기입니다.


BOOL CDlg_Teaching_Template_Match::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pDlgItem->m_pWnd = GetDlgItem((IDC_STATIC_TEMPLATE_MODEL));
	m_pDlgItem->InitViewData(m_pDlgItem->m_pWnd);

	m_Cmb_Method.AddString(_T("TM_SQDIFF"));
	m_Cmb_Method.AddString(_T("TM_SQDIFF_NORMED"));
	m_Cmb_Method.AddString(_T("TM_CCORR"));
	m_Cmb_Method.AddString(_T("TM_CCORR_NORMED"));
	m_Cmb_Method.AddString(_T("TM_CCOEFF"));
	m_Cmb_Method.AddString(_T("TM_CCOEFF_NORMED"));
	m_Cmb_Method.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CDlg_Teaching_Template_Match::GetTemplateMatchMethod()
{
	CString strMode = _T("");
	int iMethod = 0;
	m_Cmb_Method.GetLBText(m_Cmb_Method.GetCurSel(), strMode);

	if (strMode == _T("TM_SQDIFF"))
		iMethod = TemplateMatchModes::TM_SQDIFF;
	else if (strMode == _T("TM_SQDIFF_NORMED"))
		iMethod = TemplateMatchModes::TM_SQDIFF_NORMED;
	else if (strMode == _T("TM_CCORR"))
		iMethod = TemplateMatchModes::TM_CCORR;
	else if (strMode == _T("TM_CCORR_NORMED"))
		iMethod = TemplateMatchModes::TM_CCORR_NORMED;
	else if (strMode == _T("TM_CCOEFF"))
		iMethod = TemplateMatchModes::TM_CCOEFF;
	else if (strMode == _T("TM_CCOEFF_NORMED"))
		iMethod = TemplateMatchModes::TM_CCOEFF_NORMED;

	return iMethod;
}
LRESULT CDlg_Teaching_Template_Match::OnReceiveImg(WPARAM wParam, LPARAM lParam)
{
	m_pDlgItem->m_ViewData_SrcImg.img = (Mat*)lParam;
	m_pDlgItem->CreateBitMapInfo(m_pDlgItem->m_ViewData_SrcImg);
	m_pDlgItem->DrawImage(m_pDlgItem->m_ViewData_SrcImg);

	return 0;
}