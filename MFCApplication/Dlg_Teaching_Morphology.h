#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlg_Teaching_Morphology ��ȭ �����Դϴ�.

class CDlg_Teaching_Morphology : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Teaching_Morphology)

public:
	CDlg_Teaching_Morphology(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlg_Teaching_Morphology();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MORPHOLOGY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	unique_ptr<CDlgItem> m_pDlgItem;
	unique_ptr<COpenCV> m_pOpenCV;
public:

	virtual BOOL OnInitDialog();

	CComboBox m_Cmb_Morph_Operation;
	CComboBox m_Cmb_Element_Shape;
	CSliderCtrl m_Slider_Morph_Size;

	afx_msg void OnEnChangeEditElementAnchorX();
	afx_msg void OnEnChangeEditElementAnchorY();
	afx_msg void OnEnChangeEditMorphologyAnchorX();
	afx_msg void OnEnChangeEditMorphologyAnchorY();
	afx_msg void OnEnChangeEditElementSize();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditMorphSizeValue();
	afx_msg LRESULT OnReceiveImg(WPARAM wParam, LPARAM lParam);


	int m_iEdit_Element_AnchorX;
	int m_iEdit_Element_AnchorY;
	int GetElementShape();
	int GetMorphologyOperation();
	int m_iEdit_Morph_AnchorX;
	int m_iEdit_Morph_AnchorY;
	int m_iEdit_Morph_Size_Value;

	UINT m_iEdit_Element_Size;

	void UpdateTestImg();
};
