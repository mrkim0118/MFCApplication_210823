#pragma once
#include "afxcmn.h"


// CDlg_Teaching_Histogram ��ȭ �����Դϴ�.

class CDlg_Teaching_Histogram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Teaching_Histogram)

public:
	CDlg_Teaching_Histogram(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlg_Teaching_Histogram();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
	unique_ptr<CDlgItem> m_pDlgItem;
	unique_ptr<COpenCV> m_pOpenCV;
public:
	UINT m_iEdit_Bin_Num;
	CSliderCtrl m_Slider_Histogram;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	UINT m_iEdit_Value_Bin_Number;

	void UpdateTestImg();

	UINT m_iEdit_Value_Min;
	UINT m_iEdit_Value_Max;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditValueBinNumber();
	afx_msg LRESULT OnReceiveImg(WPARAM wParam, LPARAM lParam);
};
