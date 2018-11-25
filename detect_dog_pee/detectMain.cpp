#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

#include "DogPeeDetector.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	if (argc < 1) {
		printf("need input image path\n");		
		return -1;
	}
	std::string path = argv[1];
	
	Mat img = imread(path);
	if (img.empty()) {
		printf("image load fail\n");
		return -1;
	}

	DogPeeDetectorInitData dogInit = DogPeeDetector::getDefaultInitData();
	
	DogPeeDetector dog(dogInit);

	int res = dog.calcDogPeeArea(img);
	if (res < 0) {
		printf("error detect pee\n");
		return -1;
	}
	DogPeeResultData result = dog.getResults();

	Mat rimg = result.image;

	char txt[100];
	for (int i = 0; i < result.peeContours.size(); i++) {
		drawContours(result.image, result.peeContours, i, Scalar(0, 0, 255), 1);
		sprintf(txt,"%.1lf",result.peeAreas[i]);
		Rect r = boundingRect(result.peeContours[i]);
		putText(rimg, txt, r.br(), CV_FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 0, 255), 1);


		printf("%dth area: %.1lf\n", i+1, result.peeAreas[i]);
	}
	imshow("dog", rimg);
	waitKey(0);

	return 0;
}