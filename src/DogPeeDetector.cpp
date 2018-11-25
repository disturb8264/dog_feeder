#include "DogPeeDetector.h"



DogPeeDetector::DogPeeDetector()
{
}

DogPeeDetector::DogPeeDetector(DogPeeDetectorInitData initData) {	
	initDetector(initData);
}

DogPeeDetector::~DogPeeDetector()
{
}

DogPeeDetectorInitData DogPeeDetector::getDefaultInitData() {
	DogPeeDetectorInitData data;
	data.szResize = cv::Size(800, 600);	
	data.colorRange.start = 29;
	data.colorRange.end = 41;
	data.roi = cv::Rect(10, 130, 780, 450);
	data.saturationThreshold = 50;
	return data;
}

void DogPeeDetector::initDetector(DogPeeDetectorInitData initData) {
	curInitData = initData;
}

DogPeeDetectorInitData DogPeeDetector::getInitData() {
	return curInitData;
}


// algorithm
int DogPeeDetector::calcDogPeeArea(Mat img) {
	if (img.empty())
		return -1;
	peeContours.clear();
	peeAreas.clear();
	resize(img, img, curInitData.szResize);
	image = img.clone();

	cvtColor(img, hsv, CV_BGR2HSV_FULL);
	bw = Mat(img.size(), CV_8U, Scalar(0));

	for (int i = 0; i < hsv.rows; i++) {
		for (int j = 0; j < hsv.cols; j++) {
			if (hsv.at<Vec3b>(i, j)[0] > curInitData.colorRange.start && hsv.at<Vec3b>(i, j)[0] < curInitData.colorRange.end && hsv.at<Vec3b>(i, j)[1] > curInitData.saturationThreshold) {
				bw.at<uchar>(i, j) = 255;
			}
		}
	}

	erode(bw, bw, Mat(3, 3, CV_8U, Scalar(255)));
	dilate(bw, bw, Mat(3, 3, CV_8U, Scalar(255)));
	dilate(bw, bw, Mat(3, 3, CV_8U, Scalar(255)));
	   
	vector<vector<Point> > contours;
	findContours(bw, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		if (area < 1000)
			continue;
		Rect bb = boundingRect(contours[i]);
		Rect ov = bb & curInitData.roi;
		if (ov.area() < 100)
			continue;
		peeContours.push_back(contours[i]);
	}

	for (int i = 0; i < peeContours.size(); i++) {
		double area = contourArea(peeContours[i]);		
		peeAreas.push_back(area);
//		drawContours(img, peeContours, i, Scalar(0, 0, 255), 1);
	}
//	rectangle(img, curInitData.roi, Scalar(255, 0, 0), 2);

//	imshow("contours", img);

	return 0;
}


DogPeeResultData DogPeeDetector::getResults() {
	DogPeeResultData result;	
	result.image = image.clone();
	result.mask = bw;
	result.peeContours = peeContours;
	result.peeAreas = peeAreas;
	return result;
}