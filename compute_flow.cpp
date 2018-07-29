#include <iostream>
#include "flowutils.h"

using namespace std;
using namespace cv;
using namespace cv::cuda;


GpuMat get_flow_from_files(string file_name1, string file_name2, Ptr<BroxOpticalFlow>& brox) {
    /*
        :param file_name1: full path to 1st jpeg 
        :param file_name2: full path to 2nd jpeg
        :return: GpuMat object containing the optical flow
    */
    Mat frame0 = imread(file_name1, IMREAD_GRAYSCALE);
    Mat frame1 = imread(file_name2, IMREAD_GRAYSCALE);

    GpuMat d_frame0(frame0);
    GpuMat d_frame1(frame1);

    GpuMat d_flow(frame0.size(), CV_32FC2);

    GpuMat d_frame0f;
    GpuMat d_frame1f;

    d_frame0.convertTo(d_frame0f, CV_32F, 1.0 / 255.0);
    d_frame1.convertTo(d_frame1f, CV_32F, 1.0 / 255.0);

    brox->calc(d_frame0f, d_frame1f, d_flow);
    
    return d_flow;
}

void usage() {
    cout << "Usage: ./compute_flow <file_1> <file_2> <prefix>\n";
    cout << "prefix eg: ../test_data/flow\n";
    cout << "output is saved as ../test_data/flow_x.jpg, ../test_data/flow_x.jpg, ../test_data/flow_minmax.txt\n";
}

int main(int argc, char** argv){

    if (argc < 4) {
        usage();
        return 1;
    }

    string file1 = argv[1];
    string file2 = argv[2];
    string out_prefix = argv[3];
    //string file1 = "../test_data/01.jpg";
    //string file2 = "../test_data/02.jpg";

    Ptr<BroxOpticalFlow> brox = BroxOpticalFlow::create(0.197f, 50.0f, 0.8f, 10, 77, 10);

    GpuMat flow = get_flow_from_files(file1, file2, brox);

    //string flow_name = "flow";

    saveFlow(out_prefix, flow);
    return 0;
}