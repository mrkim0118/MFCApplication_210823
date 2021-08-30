#pragma once

#include "opencv2/opencv.hpp"

class CImgPrcs
{
public:
	CImgPrcs();
	~CImgPrcs();

#define COLOR_WHITE RGB(255,255,255)
#define COLOR_BLACK RGB(0,0,0)
#define COLOR_YELLOW RGB(0,255,255)
#define COLOR_RED RGB(255,0,0)

	enum ImgPrcsMode
	{
		MODE_THRESHOLD_ = 0,
		MODE_MORPHOLOGY_,
		MODE_TEMPLATE_MATCH_,
		MODE_MASK_,
		MODE_LABELING_,
		MODE_CONTOUR_,
		MODE_HISTOGRAM_,
		MODE_COUNT_MAX
	};
};

