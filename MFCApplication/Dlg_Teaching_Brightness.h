#pragma once
#include "afxcmn.h"


// CDlg_Teaching_Brightness ��ȭ �����Դϴ�.

class CDlg_Teaching_Brightness : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Teaching_Brightness)

public:
	CDlg_Teaching_Brightness(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlg_Teaching_Brightness();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_BRIGHTNESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
	unique_ptr<CDlgItem> m_pDlgItem;
	unique_ptr<COpenCV>m_pOpenCV;
	Mat* m_pModelImg;

	UINT m_iEdit_Brightness;
	float m_fEdit_Contrast;

public:

	CSliderCtrl m_Slider_Brightness;
	CSliderCtrl m_Slider_Contrast;
	UINT m_iEdit_Value_Brightness;
	float m_fEdit_Value_Contrast;
	void UpdateTestImg(CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedBtnCvtgray();
	afx_msg void OnEnChangeEditBrightnessVal();
	afx_msg void OnEnChangeEditContrastVal();
	afx_msg LRESULT OnReceiveImg(WPARAM wParam, LPARAM lParam);


	int GetBrightness();
	float GetContrast();
	afx_msg void OnEnChangeEditBrightness();
	afx_msg void OnEnChangeEditContrast();
};
