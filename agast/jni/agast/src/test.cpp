
#include <agast/test.h>

void agastwraptest::detect(Mat& mgray, std::vector<cv::KeyPoint>& v){

    FastFeatureDetector detector(50);
    detector.detect(mgray, v);

}
