#ifndef _DOG_PEE_DETECTOR_H_
#define _DOG_PEE_DETECTOR_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;
using namespace std;

struct DogPeeDetectorInitData {
	cv::Size szResize;			// 내부 계산을 위한 이미지 리사이즈 크기
	cv::Range colorRange;		// 오줌 색의 범위(노란색)
	cv::Rect roi;				// 유효 영역 지정
	int saturationThreshold;	// 채도한계 지정(높으면 순수한 색에 가까운 것만, 낮을수록 흑백까지 잡음)
};

struct DogPeeResultData {
	cv::Mat image;
	cv::Mat mask;
	std::vector<std::vector<cv::Point> > peeContours;
	std::vector<double> peeAreas;
};

class DogPeeDetector
{
public:
	DogPeeDetector();
	DogPeeDetector(DogPeeDetectorInitData initData);
	~DogPeeDetector();

	// initialize
	static DogPeeDetectorInitData getDefaultInitData();
	void initDetector(DogPeeDetectorInitData initData);
	DogPeeDetectorInitData getInitData();

	// run
	int calcDogPeeArea(Mat img);	
	DogPeeResultData getResults();
private:
	DogPeeDetectorInitData curInitData;

	cv::Mat image;
	Mat bw;
	Mat hsv;

	cv::Mat peeMask;
	std::vector<std::vector<cv::Point> > peeContours;
	std::vector<double> peeAreas;
};

#endif //_DOG_PEE_DETECTOR_H_