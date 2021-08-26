// Dlg_Teaching_Morphology.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "Dlg_Teaching_Morphology.h"
#include "afxdialogex.h"


// CDlg_Teaching_Morphology 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlg_Teaching_Morphology, CDialogEx)

CDlg_Teaching_Morphology::CDlg_Teaching_Morphology(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MORPHOLOGY, pParent)
	, m_iEdit_Element_AnchorX(-1)
	, m_iEdit_Element_AnchorY(-1)
	, m_iEdit_Morph_AnchorX(-1)
	, m_iEdit_Morph_AnchorY(-1)
	, m_iEdit_Element_SizeX(0)
	, m_iEdit_Element_SizeY(0)
{

}

CDlg_Teaching_Morphology::~CDlg_Teaching_Morphology()
{
}

void CDlg_Teaching_Morphology::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_ELEMENT_SHAPE, m_Cmb_Element_Shape);
	DDX_Text(pDX, IDC_EDIT_ELEMENT_ANCHOR_X, m_iEdit_Element_AnchorX);
	DDX_Text(pDX, IDC_EDIT_ELEMENT_ANCHOR_Y, m_iEdit_Element_AnchorY);
	DDX_Control(pDX, IDC_CMB_MORPHOLOGY_OPERATION, m_Cmb_Morph_Operation);
	DDX_Text(pDX, IDC_EDIT_MORPHOLOGY_ANCHOR_X, m_iEdit_Morph_AnchorX);
	DDX_Text(pDX, IDC_EDIT_MORPHOLOGY_ANCHOR_Y, m_iEdit_Morph_AnchorY);
	DDX_Text(pDX, IDC_EDIT_ELEMENT_SIZE_X, m_iEdit_Element_SizeX);
	DDX_Text(pDX, IDC_EDIT_ELEMENT_SIZE_Y, m_iEdit_Element_SizeY);
}


BEGIN_MESSAGE_MAP(CDlg_Teaching_Morphology, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ELEMENT_ANCHOR_X, &CDlg_Teaching_Morphology::OnEnChangeEditElementAnchorX)
	ON_EN_CHANGE(IDC_EDIT_ELEMENT_ANCHOR_Y, &CDlg_Teaching_Morphology::OnEnChangeEditElementAnchorY)
	ON_EN_CHANGE(IDC_EDIT_MORPHOLOGY_ANCHOR_X, &CDlg_Teaching_Morphology::OnEnChangeEditMorphologyAnchorX)
	ON_EN_CHANGE(IDC_EDIT_MORPHOLOGY_ANCHOR_Y, &CDlg_Teaching_Morphology::OnEnChangeEditMorphologyAnchorY)
	ON_EN_CHANGE(IDC_EDIT_ELEMENT_SIZE_X, &CDlg_Teaching_Morphology::OnEnChangeEditElementSizeX)
	ON_EN_CHANGE(IDC_EDIT_ELEMENT_SIZE_Y, &CDlg_Teaching_Morphology::OnEnChangeEditElementSizeY)
END_MESSAGE_MAP()


// CDlg_Teaching_Morphology 메시지 처리기입니다.


BOOL CDlg_Teaching_Morphology::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pDlgItem->m_pWnd = GetDlgItem((IDC_STATIC_MORPHOLOGY_TEST));
	m_pDlgItem->InitViewData(m_pDlgItem->m_pWnd);

	m_Cmb_Element_Shape.AddString(_T("MORPH_RECT"));
	m_Cmb_Element_Shape.AddString(_T("MORPH_CROSS"));
	m_Cmb_Element_Shape.AddString(_T("MORPH_ELIPSE"));
	m_Cmb_Element_Shape.SetCurSel(0);

	m_Cmb_Morph_Operation.AddString(_T("MORPH_ERODE"));
	m_Cmb_Morph_Operation.AddString(_T("MORPH_DILATE"));
	m_Cmb_Morph_Operation.AddString(_T("MORPH_OPEN"));
	m_Cmb_Morph_Operation.AddString(_T("MORPH_CLOSE"));
	m_Cmb_Morph_Operation.AddString(_T("MORPH_GREDIENT"));
	m_Cmb_Morph_Operation.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlg_Teaching_Morphology::OnEnChangeEditElementAnchorX()
{
	UpdateData(TRUE);

	if (m_iEdit_Element_AnchorX < -1)
		m_iEdit_Element_AnchorX = -1;

	UpdateData(FALSE);
}


void CDlg_Teaching_Morphology::OnEnChangeEditElementAnchorY()
{
	UpdateData(TRUE);

	if (m_iEdit_Element_AnchorY < -1)
		m_iEdit_Element_AnchorY = -1;

	UpdateData(FALSE);
}


void CDlg_Teaching_Morphology::OnEnChangeEditMorphologyAnchorX()
{
	UpdateData(TRUE);

	if (m_iEdit_Morph_AnchorX< -1)
		m_iEdit_Morph_AnchorX = -1;

	UpdateData(FALSE);
}


void CDlg_Teaching_Morphology::OnEnChangeEditMorphologyAnchorY()
{
	UpdateData(TRUE);

	if (m_iEdit_Morph_AnchorY < -1)
		m_iEdit_Morph_AnchorY = -1;

	UpdateData(FALSE);
}
int CDlg_Teaching_Morphology::GetElementShape()
{
	CString strMode = _T("");
	int iType = 0;
	m_Cmb_Element_Shape .GetLBText(m_Cmb_Element_Shape.GetCurSel(), strMode);

	if (strMode == _T("MORPH_ERODE"))
		iType = MorphTypes::MORPH_ERODE;
	else if (strMode == _T("MORPH_DILATE"))
		iType = MorphTypes::MORPH_DILATE;
	else if (strMode == _T("MORPH_OPEN"))
		iType = MorphTypes::MORPH_OPEN;
	else if (strMode == _T("MORPH_CLOSE"))
		iType = MorphTypes::MORPH_CLOSE;
	else if (strMode == _T("MORPH_GRADIENT"))
		iType = MorphTypes::MORPH_GRADIENT;

	return iType;
}

int CDlg_Teaching_Morphology::GetMorphologyOperation()
{
	CString strMode = _T("");
	int iMethod = 0;
	m_Cmb_Morph_Operation.GetLBText(m_Cmb_Morph_Operation.GetCurSel(), strMode);

	if (strMode == _T("THRESH_BINARY"))
		iMethod = ThresholdTypes::THRESH_BINARY;
	else if (strMode == _T("THRESH_BINARY_INV"))
		iMethod = ThresholdTypes::THRESH_BINARY_INV;

	return iMethod;
}

void CDlg_Teaching_Morphology::OnEnChangeEditElementSizeX()
{
	UpdateData(TRUE);

	if (m_iEdit_Element_SizeX< 1)
		m_iEdit_Element_SizeX = 1;

	UpdateData(FALSE);
}


void CDlg_Teaching_Morphology::OnEnChangeEditElementSizeY()
{
	UpdateData(TRUE);

	if (m_iEdit_Element_SizeY< 1)
		m_iEdit_Element_SizeY = 1;

	UpdateData(FALSE);
}
