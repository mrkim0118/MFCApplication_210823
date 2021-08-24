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

	void CreateBitMapInfo(ViewData &View);
	void DrawImage(ViewData &View);
};

