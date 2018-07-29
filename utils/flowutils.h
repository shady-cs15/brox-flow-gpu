#include <opencv2/opencv.hpp>
#include "string"

using namespace cv;
using namespace std;
using namespace cv::cuda;

void saveFlow(string name, const GpuMat& d_flow);