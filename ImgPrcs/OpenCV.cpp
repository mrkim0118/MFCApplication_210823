// OpenCV.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

//#include "stdafx.h"
//#include "opencv2/opencv.hpp"
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	cout << "Hello OpenCV" << CV_VERSION << endl;
//    
//	Mat img;
//
//	img = imread("lenna.bmp");
//
//	if (img.empty())
//	{
//		cerr << "image load failed" << endl;
//		return -1;
//	}
//	
//	namedWindow("image");
//	imshow("image", img);
//
//	waitKey();
//
//	return 0;
//}
//
#include "stdafx.h"
#include "OpenCV.h"

//#include "opencv2/opencv.hpp"
//#include <iostream>
//#include "OpenCV.h"
//
//using namespace cv;
//using namespace std;
//using namespace cv::ml;
//
//Mat img;
//Mat train, label;
//Ptr<KNearest> knn;
//int k_value = 1;
//
//void on_k_changed(int, void*);
//void addPoint(const Point& pt, int cls);
//void trainAndDisplay();




int main()
{
	//img = Mat::zeros(Size(500, 500), CV_8UC3);
	//knn = KNearest::create();

	//namedWindow("knn");
	//createTrackbar("k", "knn", &k_value, 5, on_k_changed);

	//const int NUM = 30;
	//Mat rn(NUM, 2, CV_32SC1);

	//randn(rn, 0, 50);
	//for (int i = 0; i < NUM; i++)
	//	addPoint(Point(rn.at<int>(i, 0) + 150, rn.at<int>(i, 1) + 150), 0);

	//randn(rn, 0, 50);
	//for (int i = 0; i < NUM; i++)
	//	addPoint(Point(rn.at<int>(i, 0) + 350, rn.at<int>(i, 1) + 150), 1);

	//randn(rn, 0, 70);
	//for (int i = 0; i < NUM; i++)
	//	addPoint(Point(rn.at<int>(i, 0) + 250, rn.at<int>(i, 1) + 400), 2);

	//trainAndDisplay();

	//waitKey();
	return 0;
}

//void on_k_changed(int, void*)
//{
//	if (k_value < 1)
//		k_value = 1;
//	trainAndDisplay();
//}
//
//void addPoint(const Point& pt, int cls)
//{
//	Mat new_sample = (Mat_<float>(1, 2) << pt.x, pt.y);
//	train.push_back(new_sample);
//
//	Mat new_label = (Mat_<int>(1, 1) << cls);
//	label.push_back(new_label);
//}
//
//void trainAndDisplay()
//{
//	knn->train(train, ROW_SAMPLE, label);
//
//	for (int i = 0; i < img.rows; ++i)
//	{
//		for (int j = 0; j < img.cols; ++j)
//		{
//			Mat sample = (Mat_<float>(1, 2) << j, i);
//
//			Mat res;
//			knn->findNearest(sample, k_value, res);
//
//			int response = cvRound(res.at<float>(0, 0));
//
//			if (response == 0)
//				img.at<Vec3b>(i, j) = Vec3b(128, 128, 255); //R
//			else if (response == 1)
//				img.at<Vec3b>(i, j) = Vec3b(128, 255, 128); //G
//			else if (response == 2)
//				img.at<Vec3b>(i, j) = Vec3b(255, 128, 128); //B
//		}
//	}
//
//	for (int i = 0; i < train.rows; i++)
//	{
//		int x = cvRound(train.at<float>(i, 0));
//		int y = cvRound(train.at<float>(i, 1));
//		int l = label.at<int>(i, 0);
//
//		if (l == 0)
//			circle(img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA);
//		else if (l == 1)
//			circle(img, Point(x, y), 5, Scalar(0, 128, 0), -1, LINE_AA);
//		else if (l == 2)
//			circle(img, Point(x, y), 5, Scalar(128, 0, 0), -1, LINE_AA);
//	}
//
//	imshow("knn", img);
//}








COpenCV::COpenCV()
{
}


COpenCV::~COpenCV()
{
}

bool COpenCV::CheckImg(Mat img)
{
	bool bRet = TRUE;

	if (img.empty() == TRUE)
	{
		m_strLog.Format(_T("[Img is NULL (OpenCV)]"));
		m_Etc.WriteLog(m_strLog);
		return FALSE;
	}

	return bRet;
}

bool COpenCV::CheckImgPath(String strFilePath)
{
	bool bRet = TRUE;

	if (strFilePath == "")
	{
		m_strLog.Format(_T("[Img Path is Blank (OpenCV)]"), strFilePath);
		m_Etc.WriteLog(m_strLog);
		return FALSE;
	}

	return bRet;
}

bool COpenCV::SaveImg(String strImgPath,InputArray Arrayimg, vector<int> Param)
{
	Mat img = Arrayimg.getMat();
	if (CheckImg(img) == TRUE && CheckImgPath(strImgPath) == TRUE)
	{
		if (imwrite(strImgPath, img, Param) == FALSE)
		{
			m_strLog.Format(_T("[Save Img Fail (OpenCV)] - FilePath : %s"), strImgPath);
			m_Etc.WriteLog(m_strLog);
			return FALSE;
		}
	}
	return TRUE;
}

Mat COpenCV::LoadImg(String strImgPath, ImreadModes eMode)
{
	Mat img;
	if (CheckImgPath(strImgPath) == TRUE)
	{
		img = imread(strImgPath, eMode);
		if (CheckImg(img) != TRUE)
		{
			m_strLog.Format(_T("[Load Img Fail (OpenCV)] - FilePath : %s"), strImgPath);
			m_Etc.WriteLog(m_strLog);
		}
		else
		{
		}
	}
	return img;
}

bool COpenCV::Mask(InputArray SrcImg, Mat& DstImg, InputArray MaskImg)
{
	Mat mSrc = SrcImg.getMat();
	Mat mMask = MaskImg.getMat();

	if (CheckImg(mSrc) == TRUE && CheckImg(mMask) == TRUE)
	{
		mSrc.setTo(Scalar(COLOR_WHITE), mMask);
		DstImg = mSrc.clone();
	}
	return TRUE;
}

bool COpenCV::Histogram(InputArray SrcImg , Mat& DstImg , HistogramParams &tHistogramParams)
{
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == TRUE)
	{
		int iChannelCnt = mSrc.channels();

		int iChannels[] = { 0 };
		int idimensions = 1; // 구하려는 히스토그램의 채널 갯수
		const int iHistSize[] = { tHistogramParams.iBinNum }; // bin의 갯수
		float fGrayLevel[] = { tHistogramParams.iValueMin , tHistogramParams.iValueMax }; // 스케일값의 최대 최소값
		const float* fRanges[] = { fGrayLevel };
		Scalar Color = SCALAR_COLOR_BLACK;

		Mat imgHist(tHistogramParams.iValueMax, tHistogramParams.iBinNum, CV_8UC3, SCALAR_COLOR_WHITE);

		DstImg = imgHist.clone();
		if (iChannelCnt == 1)
		{
			Mat GrayHist;

			calcHist(&mSrc, 1, iChannels, noArray(), GrayHist, idimensions, iHistSize, fRanges);
			GetHistogramImg(GrayHist, DstImg , Color , tHistogramParams);
		}
		else
		{
			Mat BGR_Hist[3];
			for (int i = 0; i < iChannelCnt; i++)
			{
				if (i == _COLOR_B_)
				{
					Color = SCALAR_COLOR_BLUE;
					iChannels[0] = i;
				}
				else if (i == _COLOR_G_)
				{
					Color = SCALAR_COLOR_GREEN;
					iChannels[0] = i;
				}
				else if (i == _COLOR_R_)
				{
					Color = SCALAR_COLOR_RED;
					iChannels[0] = i;
				}
				calcHist(&mSrc, 1, iChannels, noArray(), BGR_Hist[i], idimensions, iHistSize, fRanges);
				GetHistogramImg(BGR_Hist[i], DstImg , Color , tHistogramParams);
			}

		}
	}
	return 0;
}

void COpenCV::GetHistogramImg( Mat & SrcImg , Mat &Dst , Scalar Color , HistogramParams &tHistogramParams)
{
	//CV_Assert(Img.type() == CV_32FC1);
	//CV_Assert(SrcImg.size() == Size(1,256));

	double dHistMax;
	minMaxLoc(SrcImg, 0, &dHistMax);

	for (int i = 0; i < tHistogramParams.iBinNum; i++)
	{
		//int iRefVal = cvRound(SrcImg.at<float>(i, 0) * tHistogramParams.iValueMax / dHistMax);
		line(Dst, Point(i, tHistogramParams.iValueMax+1 - cvRound(SrcImg.at<float>(i, 0) * tHistogramParams.iValueMax / dHistMax)), Point(i, tHistogramParams.iValueMax - cvRound(SrcImg.at<float>(i, 0) * tHistogramParams.iValueMax / dHistMax)), Color,2);

	}
}

bool COpenCV::ThresHold(InputArray SrcImg, Mat& DstImg, ThresHoldParams &tThresHoldParams)
{
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{
		if (SrcImg.channels() != 1)
		{
			//rgb = bgr[:, : , :: - 1]
			cvtColor(mSrc, mSrc, COLOR_RGB2GRAY);
		}
		threshold(mSrc, DstImg, tThresHoldParams.iThreshold,tThresHoldParams.iMaxValue, tThresHoldParams.eType);
	}
	else
	{
		return false;
	}
	return true;
}


bool COpenCV::ThresHold_Adaptive(InputArray SrcImg, Mat& DstImg, AdaptiveThresHoldParams &tAdaptiveThresHoldParams)
{
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{
		if (SrcImg.channels() != 1)
		{
			cvtColor(mSrc, mSrc, COLOR_RGB2GRAY);
		}
		adaptiveThreshold(mSrc, DstImg, tAdaptiveThresHoldParams.iMaxValue, tAdaptiveThresHoldParams.eMethod, tAdaptiveThresHoldParams.eType, tAdaptiveThresHoldParams.iBlockSize, tAdaptiveThresHoldParams.iC);
	}
	else
	{
		return false;
	}
	return true;
}

bool COpenCV::Morphology(InputArray SrcImg, Mat& DstImg, MorphologyParams &tMorPhologyParams, ElementParams &tElementParams)
{
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{
		if (SrcImg.channels() != 1)
		{
			cvtColor(mSrc, mSrc, COLOR_RGB2GRAY);
		}

		tMorPhologyParams.Kernel = getStructuringElement(tElementParams.eShape, tElementParams.ksize, tElementParams.anchor);
		morphologyEx(mSrc, DstImg, tMorPhologyParams.eOperation, tMorPhologyParams.Kernel, tMorPhologyParams.Anchor, tMorPhologyParams.iIterator, tMorPhologyParams.eBorderType, tMorPhologyParams.borderValue);
	}
	else
	{
		return false;
	}
	return true;
}

bool COpenCV::TemplateMatching(InputArray SrcImg, Mat & DstImg, TemplateMatchParams tTemplateMatchParams , Mat& Normalize)
{
	Mat mSrc = SrcImg.getMat();
	Mat Result;
	if (CheckImg(mSrc) == true)
	{
		matchTemplate(mSrc, tTemplateMatchParams.Model, Result, tTemplateMatchParams.eTemplateMatchModes);
		normalize(Result, Normalize, 0, 255, NORM_MINMAX, CV_8U);

		double dMax = 0.0;
		Point MaxLoc;

		minMaxLoc(Result, 0 ,&dMax, 0 , &MaxLoc);
		DstImg =  mSrc.clone();
		string strResult = format("Result Max : %.3f", dMax);
		putText(DstImg, strResult, Point(DstImg.cols*0.05, DstImg.rows*0.05), FONT_HERSHEY_DUPLEX, 1, SCALAR_COLOR_LIGHT_SKY, 2);
		rectangle(DstImg, Rect(MaxLoc.x, MaxLoc.y, tTemplateMatchParams.Model.cols, tTemplateMatchParams.Model.rows), SCALAR_COLOR_LIGHT_SKY, 2);
	}
	return true;
}

bool COpenCV::Brightness(InputArray SrcImg, Mat & DstImg, BrightnessParams tBrightnessParams)
{
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{
		Mat Dst(mSrc.rows, mSrc.cols, mSrc.type());

		for (int j = 0; j < mSrc.rows; j++)
		{
			for (int i = 0; i < mSrc.cols; i++)
			{
				if (mSrc.channels() == 1)
				{
					Dst.at<uchar>(j, i) = saturate_cast<uchar>(mSrc.at<uchar>(j, i) + tBrightnessParams.iBrightness);
				}
				else if (mSrc.channels() == 3)
				{
					Dst.at<uchar>(j, (i * 3 + 0)) = saturate_cast<uchar>(mSrc.at<uchar>(j, (i * 3 + 0)) + tBrightnessParams.iBrightness);
					Dst.at<uchar>(j, (i * 3 + 1)) = saturate_cast<uchar>(mSrc.at<uchar>(j, (i * 3 + 1)) + tBrightnessParams.iBrightness);
					Dst.at<uchar>(j, (i * 3 + 2)) = saturate_cast<uchar>(mSrc.at<uchar>(j, (i * 3 + 2)) + tBrightnessParams.iBrightness);
				}
			}
		} 
		Contrast(Dst, DstImg, tBrightnessParams.fContrast);

		/*DstImg = Dst.clone();*/
	}
	return true;
}

bool COpenCV::Contrast(InputArray SrcImg, Mat & DstImg, float fValue)
{
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{

		DstImg = mSrc + (mSrc - 128) * fValue;
	}
	return true;
}

int COpenCV::Labeling(InputArray SrcImg, Mat &DstImg, LabelingParams &tLabelingParams)
{
	int iLabelCount = 0;
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{
		iLabelCount = connectedComponentsWithStats(SrcImg, tLabelingParams.labels, tLabelingParams.stats, tLabelingParams.centroids);
	}
	if (tLabelingParams.bDrawRect == true)
	{
		Mat Dst;
		cvtColor(SrcImg, Dst, COLOR_GRAY2BGR);
		for (int i = 0; i < iLabelCount; i++)
		{
			int *p = tLabelingParams.stats.ptr<int>(i);

			rectangle(Dst, Rect(p[0], p[1], p[2], p[3]) , tLabelingParams.RectColor, 2);
		}
		DstImg = Dst.clone();
	}
	else
	{
		DstImg = SrcImg.getMat();
	}

	return iLabelCount;
}



ContoursType COpenCV::Contour(InputArray SrcImg, Mat& DstImg, ContourParams tContourParams)
{	
	vector<vector<Point>> Contours;
	Mat mSrc = SrcImg.getMat();
	if (CheckImg(mSrc) == true)
	{
		findContours(SrcImg, Contours, tContourParams.eRetrievalMode, tContourParams.eContourApproximationMode);
	}
	cvtColor(SrcImg, DstImg, COLOR_GRAY2BGR);

	if (tContourParams.bDrawLine == true)
	{
		for (int i = 0; i < Contours.size(); i++)
		{
			Scalar c(rand() & 255, rand() & 255, rand() & 255);
			drawContours(DstImg, Contours, i, c, 2);
		}
	}

	return Contours;
}
