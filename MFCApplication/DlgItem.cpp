#include "stdafx.h"
#include "DlgItem.h"


CDlgItem::CDlgItem()
{
}


CDlgItem::~CDlgItem()
{
}


void CDlgItem::CreateBitMapInfo(ViewData &ViewData)
{
	int bpp = ViewData.img->channels() * 8;
	if (ViewData.BitMapInfo != NULL)
	{
		delete ViewData.BitMapInfo;
		ViewData.BitMapInfo = NULL;
	}

	if (bpp == 8)
		ViewData.BitMapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		ViewData.BitMapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	ViewData.BitMapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	ViewData.BitMapInfo->bmiHeader.biPlanes = 1;
	ViewData.BitMapInfo->bmiHeader.biBitCount = bpp;
	ViewData.BitMapInfo->bmiHeader.biCompression = BI_RGB;
	ViewData.BitMapInfo->bmiHeader.biSizeImage = 0;
	ViewData.BitMapInfo->bmiHeader.biXPelsPerMeter = 0;
	ViewData.BitMapInfo->bmiHeader.biYPelsPerMeter = 0;
	ViewData.BitMapInfo->bmiHeader.biClrUsed = 0;
	ViewData.BitMapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			ViewData.BitMapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			ViewData.BitMapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			ViewData.BitMapInfo->bmiColors[i].rgbRed = (BYTE)i;
			ViewData.BitMapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	ViewData.BitMapInfo->bmiHeader.biWidth = ViewData.img->cols;
	ViewData.BitMapInfo->bmiHeader.biHeight = -ViewData.img->rows;
}

void CDlgItem::DrawImage(ViewData &View)
{
	SetStretchBltMode(View.dc->GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(View.dc->GetSafeHdc(), 0, 0, View.rect.Width(), View.rect.Height(), 0, 0, View.img->cols, View.img->rows, View.img->data, View.BitMapInfo , DIB_RGB_COLORS, SRCCOPY);
}

void CDlgItem::InitViewData(CWnd * pWnd)
{
	this->m_ViewData_SrcImg.BitMapInfo = NULL;
	this->m_ViewData_SrcImg.img = new Mat;
	this->m_ViewData_SrcImg.dc = new CClientDC(pWnd);
	this->m_ViewData_DstImg.BitMapInfo = NULL;
	this->m_ViewData_DstImg.img = new Mat;
	this->m_ViewData_DstImg.dc = new CClientDC(pWnd);

	pWnd->GetClientRect(&this->m_ViewData_SrcImg.rect);
	pWnd->GetClientRect(&this->m_ViewData_DstImg.rect);

	this->CreateBitMapInfo(this->m_ViewData_DstImg);
	this->CreateBitMapInfo(this->m_ViewData_SrcImg);
}