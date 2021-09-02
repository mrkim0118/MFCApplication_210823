#pragma once

// CDlg_ImgPrcs 대화 상자입니다.

#include "afxwin.h"
#include "afxcmn.h"

#include "Dlg_Teaching_Threshold.h"
#include "Dlg_Teaching_Morphology.h"
#include "Dlg_Teaching_Template_Match.h"


using namespace cv;
using namespace std;
using namespace cv::ml;



class CDlg_ImgPrcs : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_ImgPrcs)

public:
	CDlg_ImgPrcs(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlg_ImgPrcs();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_IMG_PRCS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	//COpenCV *m_pOpenCV;
	unique_ptr<COpenCV> m_pOpenCV;
	unique_ptr<CDlgItem> m_pDlgItem;
	Mat* m_pMessageImg;

	unique_ptr<CDlg_Teaching_Threshold> m_pDlgThreshold;
	unique_ptr<CDlg_Teaching_Morphology> m_pDlgMorphology;
	unique_ptr<CDlg_Teaching_Template_Match> m_pDlgTemplateMatch;

	int m_iInspMode;
	CComboBox m_Cmb_Mode;
	CPoint m_ptROI_Start;
	CPoint m_ptROI_End;
	CRect m_DlgRect;
	CTabCtrl m_Teaching_Tab;
	bool m_bClicked;

public:
	virtual BOOL OnInitDialog();

	void HideAllTeachingDlg();
	void InitTeachingTab();
	int GetInspMode();
	void OnDrawROI(CDlgItem::ViewData& viewdata);

	afx_msg void OnBnClickedBtnLoadImg();
	afx_msg void OnMenuImgPrcs();
	afx_msg void OnBnClickedBtnSaveImg();
	afx_msg void OnBnClickedBtnImgPrcsStart();
	afx_msg void OnTcnSelchangeTeachingTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDstToSrc();
	afx_msg void OnBnClickedBtnDstToTeachingDlg();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCmbMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


};
