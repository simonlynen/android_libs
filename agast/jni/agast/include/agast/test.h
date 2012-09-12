#ifndef AGASTTEST
#define AGASTTEST

#include <string.h>
#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace std;
using namespace cv;

class agastwraptest{

public:
	void detect(Mat& mgray, std::vector<cv::KeyPoint>& v);
};


#endif
