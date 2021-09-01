#pragma once
class CDlgItem
{
public:
	CDlgItem();
	virtual ~CDlgItem();

	struct ViewData
	{
		CClientDC *dc;
		CRect rect;
		Mat *img;
		BITMAPINFO *BitMapInfo;
	};
	CWnd * m_pWnd;
	CWnd * m_pWnd_Ext = NULL;

	ViewData m_ViewData_SrcImg;
	ViewData m_ViewData_DstImg;

	void CreateBitMapInfo(ViewData &View);
	void DrawImage(ViewData &View);

	void InitViewData(CWnd* pWnd , CWnd* pWnd_Ext = NULL);
};

