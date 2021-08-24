#pragma once

#include "ImgPrcs.h"
#include "OpenCV.h"
#include "../MFC/Etc.h"

using namespace cv;
using namespace std;
using namespace cv::ml;

typedef vector<vector<Point>> ContoursType;

#define SCALAR_COLOR_WHITE Scalar(255,255,255)
#define SCALAR_COLOR_BLACK Scalar(0,0,0)
#define SCALAR_COLOR_YELLOW Scalar(0,255,255)
#define SCALAR_COLOR_RED Scalar(0,0,255)

class COpenCV
{
public:
	COpenCV();
	~COpenCV();
private:
	CString m_strLog;
	CEtc  m_Etc;

public:

	struct ThresHoldParams
	{
		int iThreshold = 128;
		int iMaxValue = 255;
		ThresholdTypes eType = THRESH_BINARY;
	};

	struct AdaptiveThresHoldParams
	{
		int iBlockSize = 3;
		int iC = 5;
		int iMaxValue = 255;
		AdaptiveThresholdTypes eMethod = ADAPTIVE_THRESH_MEAN_C;
		ThresholdTypes eType = THRESH_BINARY;
	};

	struct MorphologyParams
	{
		MorphTypes eOperation;
		Mat Kernel = Mat();
		Point Anchor = Point(-1, -1);
		int iIterator = 1;
		BorderTypes eBorderType = BORDER_CONSTANT;
		const Scalar& borderValue = morphologyDefaultBorderValue();
	};

	struct ElementParams
	{
		MorphShapes eShape = MORPH_RECT;
		Size ksize = Size(3, 3);
		Point anchor = Point(-1, -1);
	};
	
	struct LabelingParams
	{
		Mat labels;
		Mat stats;
		Mat centroids;
		bool bDrawRect = false;
		Scalar RectColor = SCALAR_COLOR_RED;
		int iConnectivity = 8;
		int iType = CV_32S;
	};

	struct ContourParams
	{
		bool bDrawLine = false;
		RetrievalModes eRetrievalMode = RETR_LIST;
		ContourApproximationModes eContourApproximationMode = CHAIN_APPROX_NONE;
	};

public:
	bool CheckImg(Mat img);
	bool CheckImgPath(String strFilePath);
	bool SaveImg(String strImgPath, InputArray Arrayimg, vector<int> Param = {0});
    Mat LoadImg(String strImgPath, ImreadModes eMode = IMREAD_COLOR);
	bool Mask(InputArray SrcImg, Mat& DstImg, InputArray MaskImg);
	bool Histogram(InputArray SrcImg);
	bool ThresHold_Adaptive(InputArray SrcImg , Mat& DstImg, AdaptiveThresHoldParams &tAdaptiveThresHoldParams);
	bool ThresHold(InputArray SrcImg, Mat& DstImg, ThresHoldParams &ThresHoldParams);
	bool Morphology(InputArray SrcImg , Mat& DstImg, MorphologyParams &tMorPhologyParams, ElementParams &tElementParams);
	int Labeling(InputArray SrcImg , Mat& DstImg, LabelingParams &tLabelingParams);
	ContoursType Contour(InputArray SrcImg, Mat& DstImg, ContourParams tContourParams);

};
