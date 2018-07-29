# include "flowutils.h"
# include "minmax.h"

void saveFlow(string name, const GpuMat& d_flow) {
    /*
        gets the prefix (name) and save the optical flow into
        name_x.jpg and name_y.jpg, also save name_minmax.txt
    */
    string minmax_name = name + "_minmax.txt";
    GpuMat planes[2];
    cuda::split(d_flow, planes);

    Mat flowx(planes[0]);
    Mat flowy(planes[1]);

    Minmax mx = minMaxFlow(flowx);
    for (int i=0; i < flowx.rows ; i++) {
    for (int j=0; j < flowx.cols ; j++) {
        if ((mx.max - mx.min) < 0.0001) {
    flowx.at<float>(i,j) = 0.0;
        }
        else {
    flowx.at<float>(i,j) = round((255.0 * (flowx.at<float>(i,j) - mx.min))/(mx.max - mx.min));
        }
    }
    }

    Minmax my = minMaxFlow(flowy);
    for (int i=0; i < flowy.rows ; i++) {
    for (int j=0; j < flowy.cols ; j++) {
        if ((my.max - my.min) < 0.0001) {
    flowy.at<float>(i,j) = 0.0;
        }
        else {
    flowy.at<float>(i,j) = round((255.0 * (flowy.at<float>(i,j) - my.min))/(my.max - my.min));
        }
    }
    }

    Mat flowx_int;
    Mat flowy_int;

    flowx.convertTo(flowx_int, CV_8U);
    flowy.convertTo(flowy_int, CV_8U);

    imwrite(name + "_x.jpg", flowx);
    imwrite(name + "_y.jpg", flowy);

    ofstream outputFile;
    outputFile.open(minmax_name);
    outputFile << "xmin: " << mx.min << endl;
    outputFile << "xmax: " << mx.max << endl;
    outputFile << "ymin: " << my.min << endl;
    outputFile << "ymax: " << my.max << endl;

    outputFile.close();
}