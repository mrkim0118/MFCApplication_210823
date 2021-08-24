#pragma once

// CDlg_ImgPrcs ��ȭ �����Դϴ�.

#include "afxwin.h"
#include "afxcmn.h"

#include "Dlg_Teaching_Threshold.h"
#include "Dlg_Teaching_Morphology.h"


using namespace cv;
using namespace std;
using namespace cv::ml;



class CDlg_ImgPrcs : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_ImgPrcs)

public:
	CDlg_ImgPrcs(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlg_ImgPrcs();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_IMG_PRCS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	//COpenCV *m_pOpenCV;
	unique_ptr<COpenCV> m_pOpenCV;
	unique_ptr<CDlgItem> m_pDlgItem;
	Mat* m_pMessageImg;

	CDlg_Teaching_Threshold *m_pDlgThreshold;
	CDlg_Teaching_Morphology *m_pDlgMorphology;

	CDlgItem::ViewData m_ViewDataSrc;
	CDlgItem::ViewData m_ViewDataDst;
	CDlgItem::ViewData m_ViewData_ThresholdTest;

	int m_iInspMode;
	CComboBox m_Cmb_Mode;
public:

	void HideAllTeachingDlg();
	void InitTeachingTab();
	int GetInspMode();

	afx_msg void OnBnClickedBtnLoadImg();
	afx_msg void OnMenuImgPrcs();
	afx_msg void OnBnClickedBtnSaveImg();
	afx_msg void OnBnClickedBtnImgPrcsStart();
	afx_msg void OnTcnSelchangeTeachingTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDstToSrc();
	
	virtual BOOL OnInitDialog();

	CTabCtrl m_Teaching_Tab;
	
	afx_msg void OnBnClickedBtnDstToThresholdDlg();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCmbMode();
};
