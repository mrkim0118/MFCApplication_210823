#pragma once
#include "afxwin.h"


// CDlg_Teaching_Template_Match ��ȭ �����Դϴ�.

class CDlg_Teaching_Template_Match : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Teaching_Template_Match)

public:
	CDlg_Teaching_Template_Match(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlg_Teaching_Template_Match();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TEMPLATE_MATCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	unique_ptr<CDlgItem> m_pDlgItem;
public:
	virtual BOOL OnInitDialog();
	CComboBox m_Cmb_Method;
	afx_msg LRESULT OnReceiveImg(WPARAM wParam, LPARAM lParam);
	int GetTemplateMatchMethod();
};
