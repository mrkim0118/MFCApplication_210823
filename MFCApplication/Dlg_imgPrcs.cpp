// Dlg_ImgPrcs.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "Dlg_ImgPrcs.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlg_ImgPrcs 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlg_ImgPrcs, CDialogEx)

CDlg_ImgPrcs::CDlg_ImgPrcs(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_IMG_PRCS, pParent)
{
	m_pOpenCV = make_unique<COpenCV>();
	m_pDlgItem = make_unique<CDlgItem>();
}

CDlg_ImgPrcs::~CDlg_ImgPrcs()
{

	if (m_ViewDataSrc.img != NULL)
	{
		delete m_ViewDataSrc.img;
		m_ViewDataSrc.img = NULL;
	}
	if (m_ViewDataDst.img != NULL)
	{
		delete m_ViewDataDst.img;
		m_ViewDataDst.img = NULL;
	}
	if (m_ViewDataSrc.dc != NULL)
	{
		delete m_ViewDataSrc.dc;
		m_ViewDataSrc.dc = NULL;
	}
	if (m_ViewDataDst.dc != NULL)
	{
		delete m_ViewDataDst.dc;
		m_ViewDataDst.dc = NULL;
	}

	if (m_pDlgThreshold != NULL)
	{
		delete m_pDlgThreshold;
		m_pDlgThreshold = NULL;
	}
}

void CDlg_ImgPrcs::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_MODE, m_Cmb_Mode);
	DDX_Control(pDX, IDC_TEACHING_TAB, m_Teaching_Tab);
}

void CDlg_ImgPrcs::HideAllTeachingDlg()
{
	m_pDlgMorphology->ShowWindow(SW_HIDE);
	m_pDlgThreshold->ShowWindow(SW_HIDE);
	m_pDlgTemplateMatch->ShowWindow(SW_HIDE);
}

void CDlg_ImgPrcs::InitTeachingTab()
{
	m_Teaching_Tab.InsertItem(0, _T("Threshold"));
	m_Teaching_Tab.InsertItem(1, _T("Morphology"));
	m_Teaching_Tab.InsertItem(2, _T("TemplateMatch"));
	m_Teaching_Tab.SetCurSel(0);

	CRect rect;
	m_Teaching_Tab.GetWindowRect(&rect);

	m_pDlgThreshold = new CDlg_Teaching_Threshold;
	m_pDlgThreshold->Create(IDD_DLG_THRESHOLD, &m_Teaching_Tab);
	m_pDlgThreshold->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgThreshold->ShowWindow(SW_HIDE);

	m_pDlgMorphology = new CDlg_Teaching_Morphology;
	m_pDlgMorphology->Create(IDD_DLG_MORPHOLOGY, &m_Teaching_Tab);
	m_pDlgMorphology->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgMorphology->ShowWindow(SW_HIDE);

	m_pDlgTemplateMatch = new CDlg_Teaching_Template_Match;
	m_pDlgTemplateMatch->Create(IDD_DLG_TEMPLATE_MATCH, &m_Teaching_Tab);
	m_pDlgTemplateMatch->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pDlgTemplateMatch->ShowWindow(SW_HIDE);

}

int CDlg_ImgPrcs::GetInspMode()
{
	CString strMode = _T("");
	m_Cmb_Mode.GetLBText(m_Cmb_Mode.GetCurSel(), strMode);

	if (strMode == _T("Morphorogy"))
		m_iInspMode = CImgPrcs::MODE_MORPHOLOGY_;
	else if (strMode == _T("Threshold"))
		m_iInspMode = CImgPrcs::MODE_THRESHOLD_;
	else if (strMode == _T("Mask"))
		m_iInspMode = CImgPrcs::MODE_MASK_;
	else if (strMode == _T("Labeling"))
		m_iInspMode = CImgPrcs::MODE_LABELING_;
	else if (strMode == _T("Contour"))
		m_iInspMode = CImgPrcs::MODE_CONTOUR_;
	else if (strMode == _T("GrayHistogram"))
		m_iInspMode = CImgPrcs::MODE_HISTOGRAM_;
	else if (strMode == _T("TemplateMatch"))
		m_iInspMode = CImgPrcs::MODE_TEMPLATE_MATCH_;

	return m_iInspMode;
}

void CDlg_ImgPrcs::OnDrawROI(CDlgItem::ViewData& viewdata)
{
	// Picture Control DC를 생성.
	// IDC_PC_IMAGE는 Picture Control의 Resource ID.

	// Picture Control 크기를 얻는다.
	//CRect rect;
	//GetDlgItem(IDC_STATIC_SRC_VIEW)->GetClientRect(&rect);

	//CWnd* pWnd = NULL;
	//pWnd = GetDlgItem(IDC_STATIC_SRC_VIEW);
	//CDC *pDCc = pWnd->GetDC();

	CDC memDC;
	CBitmap *pOldBitmap, bitmap;
	CPen *pOldPen = NULL;
	CBrush *pOldBrush = NULL;

	CPen penRed(PS_SOLID, 1, RGB(255, 0, 0));
	CBrush brushRed;
	brushRed.CreateStockObject(NULL_BRUSH);

	// Picture Control DC에 호환되는 새로운 CDC를 생성. (임시 버퍼)
	memDC.CreateCompatibleDC(viewdata.dc);
	// Picture Control의 크기와 동일한 비트맵을 생성.
	bitmap.CreateCompatibleBitmap(viewdata.dc, viewdata.rect.Width(), viewdata.rect.Height());
	// 임시 버퍼에서 방금 생성한 비트맵을 선택하면서, 이전 비트맵을 보존.
	pOldBitmap = memDC.SelectObject(&bitmap);

	SetStretchBltMode(memDC.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(memDC.GetSafeHdc(), 0, 0, viewdata.rect.Width(), viewdata.rect.Height(), 0, 0, viewdata.img->cols, viewdata.img->rows, viewdata.img->data, viewdata.BitMapInfo, DIB_RGB_COLORS, SRCCOPY);

	pOldPen = memDC.SelectObject(&penRed);
	pOldBrush = memDC.SelectObject(&brushRed);

	//memDC.Rectangle(m_ptRect_Start.x-30 , m_ptRect_Start.y-40 , m_ptRect_End.x-30 , m_ptRect_End.y-40);
	memDC.Rectangle(m_ptRect_Start.x, m_ptRect_Start.y, m_ptRect_End.x, m_ptRect_End.y);
	//memDC.Rectangle(CRect(m_ptRect_Start , m_ptRect_End));
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	// 임시 버퍼에 검은색으로 채움.
	//memDC.PatBlt(0, 0, viewdata.rect.Width(), viewdata.rect.Height(), BLACKNESS);
	// 임시 버퍼를 Picture Control에 그린다.
	viewdata.dc->BitBlt(0, 0, viewdata.rect.Width(), viewdata.rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 이전 비트맵으로 재설정.
    memDC.SelectObject(pOldBitmap);

	pOldBrush->DeleteObject();
	pOldPen->DeleteObject();

	// 생성한 리소스 해제.
	memDC.DeleteDC();
	bitmap.DeleteObject();

}


BEGIN_MESSAGE_MAP(CDlg_ImgPrcs, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD_IMG, &CDlg_ImgPrcs::OnBnClickedBtnLoadImg)
	ON_COMMAND(ID_MENU_IMG_PRCS, &CDlg_ImgPrcs::OnMenuImgPrcs)
	ON_BN_CLICKED(IDC_BTN_SAVE_IMG, &CDlg_ImgPrcs::OnBnClickedBtnSaveImg)
	ON_BN_CLICKED(IDC_BTN_IMG_PRCS_START, &CDlg_ImgPrcs::OnBnClickedBtnImgPrcsStart)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TEACHING_TAB, &CDlg_ImgPrcs::OnTcnSelchangeTeachingTab)
	ON_BN_CLICKED(IDC_BTN_DST_TO_SRC, &CDlg_ImgPrcs::OnBnClickedBtnDstToSrc)
	ON_BN_CLICKED(IDC_BTN_DST_TO_THRESHOLD_DLG, &CDlg_ImgPrcs::OnBnClickedBtnDstToThresholdDlg)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CMB_MODE, &CDlg_ImgPrcs::OnCbnSelchangeCmbMode)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlg_ImgPrcs 메시지 처리기입니다.


void CDlg_ImgPrcs::OnBnClickedBtnLoadImg()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();

		CT2CA pszString(path);
		string strPath(pszString);

		*m_ViewDataSrc.img =  m_pOpenCV->LoadImg(strPath);
		m_pDlgItem->CreateBitMapInfo(m_ViewDataSrc);
		m_pDlgItem->DrawImage(m_ViewDataSrc);
	}
}




void CDlg_ImgPrcs::OnMenuImgPrcs()
{
	DoModal();
}


void CDlg_ImgPrcs::OnBnClickedBtnSaveImg()
{
	CFileDialog fileDlg(FALSE, L"bmp", L"*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, L"All Files (*.*)|*.*|Bmp Files (*.bmp)|*.bmp|",this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		string strPath(pszString);
		m_pOpenCV->SaveImg(strPath, *m_ViewDataDst.img);
	}
}


BOOL CDlg_ImgPrcs::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitTeachingTab();

	m_Cmb_Mode.AddString(_T("Morphorogy"));
	m_Cmb_Mode.AddString(_T("Mask"));
	m_Cmb_Mode.AddString(_T("Threshold"));
	m_Cmb_Mode.AddString(_T("Labeling"));
	m_Cmb_Mode.AddString(_T("Contour"));
	m_Cmb_Mode.AddString(_T("GrayHistogram"));
	m_Cmb_Mode.AddString(_T("TemplateMatch"));
	m_Cmb_Mode.SetCurSel(0);


	m_ViewDataSrc.dc = new CClientDC(GetDlgItem(IDC_STATIC_SRC_VIEW));
	m_ViewDataDst.dc = new CClientDC(GetDlgItem(IDC_STATIC_DST_VIEW));

	GetDlgItem(IDC_STATIC_SRC_VIEW)->GetClientRect(&m_ViewDataSrc.rect);
	GetDlgItem(IDC_STATIC_DST_VIEW)->GetClientRect(&m_ViewDataDst.rect);
	
	GetDlgItem(IDC_STATIC_SRC_VIEW)->GetWindowRect(&m_DlgRect);
	ScreenToClient(&m_DlgRect);

	m_ViewDataSrc.img = new Mat;
	m_ViewDataDst.img = new Mat;
	m_pMessageImg = new Mat;

	m_ViewDataSrc.BitMapInfo = NULL;
	m_ViewDataDst.BitMapInfo = NULL;

	m_pDlgItem->CreateBitMapInfo(m_ViewDataSrc);
	m_pDlgItem->CreateBitMapInfo(m_ViewDataDst);

	m_pDlgThreshold->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlg_ImgPrcs::OnBnClickedBtnImgPrcsStart()
{

	m_iInspMode = GetInspMode();

	switch (m_iInspMode)
	{
	case CImgPrcs::MODE_MORPHOLOGY_:
	{
		COpenCV::ElementParams tElementParams;
		tElementParams.eShape = (MorphShapes)m_pDlgMorphology->GetElementShape();
		tElementParams.anchor = Point(m_pDlgMorphology->m_iEdit_Element_AnchorX, m_pDlgMorphology->m_iEdit_Element_AnchorY);
		tElementParams.ksize = Size(m_pDlgMorphology->m_iEdit_Element_Size , m_pDlgMorphology->m_iEdit_Element_Size);

		COpenCV::MorphologyParams tMorphologyParams;
		tMorphologyParams.eOperation = (MorphTypes)m_pDlgMorphology->GetMorphologyOperation();
		tMorphologyParams.Anchor = Point(m_pDlgMorphology->m_iEdit_Morph_AnchorX, m_pDlgMorphology->m_iEdit_Morph_AnchorY);
		tMorphologyParams.Kernel = getStructuringElement(tElementParams.eShape, tElementParams.ksize, tElementParams.anchor);

		m_pOpenCV->Morphology(*m_ViewDataSrc.img, *m_ViewDataDst.img, tMorphologyParams, tElementParams);
		break;
	}
	case CImgPrcs::MODE_THRESHOLD_:
	{
		
		if (m_pDlgThreshold->m_Chk_Adaptive_Use.GetCheck() == TRUE)
		{
			COpenCV::AdaptiveThresHoldParams tAdaptiveThresHoldParams;
			tAdaptiveThresHoldParams.eMethod = (AdaptiveThresholdTypes)m_pDlgThreshold->GetAdpThresholdMethod();
			tAdaptiveThresHoldParams.eType = (ThresholdTypes)m_pDlgThreshold->GetAdpThresholdType();
			tAdaptiveThresHoldParams.iBlockSize = m_pDlgThreshold->GetAdaptive_BlockSize();
			tAdaptiveThresHoldParams.iC = m_pDlgThreshold->GetAdaptiveC();

			m_pOpenCV->ThresHold_Adaptive(*m_ViewDataSrc.img, *m_ViewDataDst.img, tAdaptiveThresHoldParams);
		}
		else
		{
			COpenCV::ThresHoldParams tThresHoldParams;
			tThresHoldParams.eType = (ThresholdTypes)m_pDlgThreshold->GetThresholdMethod();
			tThresHoldParams.iThreshold = m_pDlgThreshold->GetThreshold();

			m_pOpenCV->ThresHold(*m_ViewDataSrc.img, *m_ViewDataDst.img, tThresHoldParams);
		}
		break;
	}
	case CImgPrcs::MODE_MASK_:
		break;
	case CImgPrcs::MODE_LABELING_:
	{
		COpenCV::LabelingParams tLabelingParams;
		m_pOpenCV->Labeling(*m_ViewDataDst.img, *m_ViewDataDst.img, tLabelingParams);
		break;
	}
	case CImgPrcs::MODE_CONTOUR_:
	{
		COpenCV::ContourParams tContourParams;
		m_pOpenCV->Contour(*m_ViewDataDst.img, *m_ViewDataDst.img, tContourParams);
		break;
	}
	case CImgPrcs::MODE_HISTOGRAM_:
	{
		m_pOpenCV->Histogram(*m_ViewDataSrc.img, *m_ViewDataDst.img);
		break;
	}
	case CImgPrcs::MODE_TEMPLATE_MATCH_:
	{
		COpenCV::TemplateMatchParams tTemplateMatchParams;
		m_pOpenCV->TemplateMatching(*m_ViewDataDst.img, *m_ViewDataDst.img, tTemplateMatchParams.Model, tTemplateMatchParams.eTemplateMatchModes);
	}
	}


	m_pDlgItem->CreateBitMapInfo(m_ViewDataDst);
	m_pDlgItem->DrawImage(m_ViewDataDst);
}


void CDlg_ImgPrcs::OnTcnSelchangeTeachingTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iSelected = m_Teaching_Tab.GetCurSel();

	HideAllTeachingDlg();

	switch (iSelected)
	{
	case CImgPrcs::MODE_MORPHOLOGY_:
	{
		m_pDlgMorphology->ShowWindow(SW_SHOW);
		break;
	}
	case CImgPrcs::MODE_THRESHOLD_:
	{
		m_pDlgThreshold->ShowWindow(SW_SHOW);
		break;
	}
	case CImgPrcs::MODE_TEMPLATE_MATCH_:
	{
		m_pDlgTemplateMatch->ShowWindow(SW_SHOW);
		break;
	}
	}

	*pResult = 0;
}


void CDlg_ImgPrcs::OnBnClickedBtnDstToSrc()
{
	*m_ViewDataSrc.img = m_ViewDataDst.img->clone();
	m_pDlgItem->CreateBitMapInfo(m_ViewDataSrc);
	m_pDlgItem->DrawImage(m_ViewDataSrc);
}


void CDlg_ImgPrcs::OnBnClickedBtnDstToThresholdDlg()
{
	m_iInspMode = GetInspMode();

	switch (m_iInspMode)
	{
	case CImgPrcs::MODE_THRESHOLD_:
	{
		if (m_pDlgThreshold != NULL)
		{
			*m_pMessageImg = m_ViewDataSrc.img->clone();
			::SendMessage(m_pDlgThreshold->GetSafeHwnd(), WM_THRESHOLD_TEST, NULL, (LPARAM)m_pMessageImg);
		}
		break;
	}
	case CImgPrcs::MODE_MORPHOLOGY_:
	{
		if (m_pDlgMorphology != NULL)
		{
			*m_pMessageImg = m_ViewDataSrc.img->clone();
			::SendMessage(m_pDlgMorphology->GetSafeHwnd(), WM_MORPHOLOGY_TEST, NULL, (LPARAM)m_pMessageImg);
		}
		break;
	}
	case CImgPrcs::MODE_TEMPLATE_MATCH_:
	{
		if (m_pDlgTemplateMatch != NULL)
		{
			Mat img;
			img = m_ViewDataSrc.img->clone();

			double dRectWidth = m_ViewDataSrc.rect.Width();
			double dRectHeight = m_ViewDataSrc.rect.Height();

			double dResolutionX = dRectWidth / img.rows;
			double dResolutionY = dRectHeight / img.cols;

			int iModelWidth = m_ptRect_End.x - m_ptRect_Start.x;
			int iModelHeight = m_ptRect_End.y - m_ptRect_Start.y;

			double rx = ((double)m_ptRect_Start.x / m_ViewDataSrc.rect.right);
			double rx2 =((double)m_ptRect_End.x / m_ViewDataSrc.rect.right);

			double ry = ((double)m_ptRect_Start.y / m_ViewDataSrc.rect.bottom);
			double ry2 = ((double)m_ptRect_End.y / m_ViewDataSrc.rect.bottom);



			//int iModelSpanWidth = 0;

			//if (iModelSpanWidth % 4 != 0)
			//{
			//	iModelSpanWidth = iModelWidth + (4 - iModelWidth % 4);
			//}
			//else
			//{
			//	iModelSpanWidth = iModelWidth;
			//}

			////m_pModelImage[eModel] = new BYTE[nModelSpanWidth * nModelHeight];
			////ZeroMemory(m_pModelImage[eModel], nModelSpanWidth * nModelHeight);

			//Mat newimg;
			//newimg.zeros(iModelSpanWidth, iModelHeight, CV_8UC1);

			//for (int j = 0; j<iModelHeight; j++)
			//{
			//	for (int i = 0; i<iModelSpanWidth; i++)
			//	{
			//		if (i >= iModelWidth)
			//		{
			//			newimg.at<uchar>(j, iModelSpanWidth*i) = 0;
			//			//m_pModelImage[eModel][j * nModelSpanWidth + i] = 0;
			//		}
			//		else
			//		{
			//			newimg.at<uchar>(j, iModelSpanWidth+i) = img.at<uchar>((m_ptRect_Start.y *dRectWidth) , (j*dRectWidth) + m_ptRect_Start.x+i) ;
			//			//m_pModelImage[eModel][j * nModelSpanWidth + i] = pImgSrc[(nStartY * nImgWidth) + (j * nImgWidth) + nStartX + i];
			//		}
			//	}
			//}



			Rect rect(img.rows*rx, img.cols*ry, (img.rows*rx2 - img.rows*rx), (img.cols*ry2 - img.cols*ry));
			//img(Rect(m_ptRect_Start.x*dResolutionX, m_ptRect_Start.y*dResolutionY, (m_ptRect_End.x - m_ptRect_Start.x)*dResolutionX, (m_ptRect_End.y - m_ptRect_Start.y)*dResolutionY));
			Mat rectimg = img(rect);
			imshow("TEST", rectimg);

			*m_pMessageImg = rectimg.clone();
			//Rect Crop(m_ptRect_Start.x, m_ptRect_Start.y, m_ptRect_End.x, m_ptRect_End.y);
			//*m_pMessageImg = m_ViewDataSrc.img->clone();  (Crop);
			::SendMessage(m_pDlgTemplateMatch->GetSafeHwnd(), WM_TEMPLATE_MATCH_TEST, NULL, (LPARAM)m_pMessageImg);
		}
		break;
	}
	}

}

void CDlg_ImgPrcs::OnPaint()
{
	CPaintDC dc(this); 
	m_pDlgItem->DrawImage(m_ViewDataDst);
	m_pDlgItem->DrawImage(m_ViewDataSrc);
}


void CDlg_ImgPrcs::OnCbnSelchangeCmbMode()
{
	m_iInspMode = GetInspMode();

	HideAllTeachingDlg();
	switch (m_iInspMode)
	{
	case CImgPrcs::MODE_THRESHOLD_:
		m_pDlgThreshold->ShowWindow(SW_SHOW);
		break;
	case CImgPrcs::MODE_MORPHOLOGY_:
		m_pDlgMorphology->ShowWindow(SW_SHOW);
		break;
	case CImgPrcs::MODE_TEMPLATE_MATCH_:
		m_pDlgTemplateMatch->ShowWindow(SW_SHOW);
		break;

	}

	m_Teaching_Tab.SetCurSel(m_iInspMode);
}


void CDlg_ImgPrcs::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_iInspMode = GetInspMode();
	if (m_iInspMode == CImgPrcs::MODE_TEMPLATE_MATCH_)
	{
		if(m_DlgRect.PtInRect(point))
		{
			point.x = point.x - m_DlgRect.left;
			point.y = point.y - m_DlgRect.top;

			m_ptRect_Start = point;
			m_bClicked = true;
		}
	}
}


void CDlg_ImgPrcs::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_iInspMode == CImgPrcs::MODE_TEMPLATE_MATCH_)
	{
		if (m_DlgRect.PtInRect(point))
		{
			point.x = point.x - m_DlgRect.left;
			point.y = point.y - m_DlgRect.top;

			m_bClicked = false;
			m_ptRect_End = point;
			OnDrawROI(m_ViewDataSrc);
		}
	}

}


void CDlg_ImgPrcs::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_DlgRect.PtInRect(point))
	{
		point.x = point.x - m_DlgRect.left;
		point.y = point.y - m_DlgRect.top;

		if (m_bClicked == true)
		{
			m_ptRect_End = point;
			OnDrawROI(m_ViewDataSrc);
		}
	}


	CDialogEx::OnMouseMove(nFlags, point);
}
