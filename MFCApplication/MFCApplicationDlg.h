
// MFCApplicationDlg.h : ��� ����
//
#include "Dlg_ImgPrcs.h"

#pragma once
#define SFC_GETSET(ret, fname, var)\
	ret Get##fname()\
	{\
	return var;\
	}\
	void Set##fname(ret tmp)\
	{\
	var = tmp;\
	}

// CMFCApplicationDlg ��ȭ ����
class CMFCApplicationDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCApplicationDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

private:
	CEtc         *m_pEtc;
	CDlg_ImgPrcs *m_pDlg_ImgPrcs;

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuImgPrcs();
	afx_msg void OnDestroy();

public:
	CDlg_ImgPrcs* getDlg_ImgPrcsPtr();
	CEtc* getEtcPtr();
};
