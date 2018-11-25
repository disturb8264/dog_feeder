#ifndef _DOG_PEE_DETECTOR_H_
#define _DOG_PEE_DETECTOR_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;
using namespace std;

struct DogPeeDetectorInitData {
	cv::Size szResize;			// ���� ����� ���� �̹��� �������� ũ��
	cv::Range colorRange;		// ���� ���� ����(�����)
	cv::Rect roi;				// ��ȿ ���� ����
	int saturationThreshold;	// ä���Ѱ� ����(������ ������ ���� ����� �͸�, �������� ������ ����)
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