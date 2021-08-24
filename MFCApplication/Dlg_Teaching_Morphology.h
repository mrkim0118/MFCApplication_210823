#pragma once
#include "afxwin.h"


// CDlg_Teaching_Morphology 대화 상자입니다.

class CDlg_Teaching_Morphology : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Teaching_Morphology)

public:
	CDlg_Teaching_Morphology(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlg_Teaching_Morphology();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MORPHOLOGY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	CComboBox m_Cmb_Morph_Operation;
	CComboBox m_Cmb_Element_Shape;

	afx_msg void OnEnChangeEditElementAnchorX();
	afx_msg void OnEnChangeEditElementAnchorY();
	afx_msg void OnEnChangeEditMorphologyAnchorX();
	afx_msg void OnEnChangeEditMorphologyAnchorY();
	afx_msg void OnEnChangeEditElementSizeX();
	afx_msg void OnEnChangeEditElementSizeY();

	int m_iEdit_AnchorX;
	int m_iEdit_AnchorY;
	int GetElementShape();
	int GetMorphologyOperation();
	int m_iEdit_Morph_AnchorX;
	int m_iEdit_Morph_AnchorY;

	UINT m_iEdit_Size;
	UINT m_iEdit_Element_SizeX;
	UINT m_iEdit_Element_SizeY;

};
