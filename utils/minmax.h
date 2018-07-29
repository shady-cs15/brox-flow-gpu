#include <opencv2/opencv.hpp>

using namespace cv;

class Minmax {
public:
  float min;
  float max;
};

Minmax minMaxFlow(Mat& flow);
