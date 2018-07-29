# include "minmax.h"


Minmax minMaxFlow(Mat& flow) {
    /*
        computes min and max values given flow
    */
    Minmax m;
    m.min = flow.at<float>(0,0);
    m.max = flow.at<float>(0,0);
    for (int i=0; i < flow.rows ; i++) {
    for (int j=0; j < flow.cols ; j++) {
        float f = flow.at<float>(i,j);
        if (m.max < f) {
        m.max = f;
        }
        if (m.min > f) {
    m.min = f;
        }
            
    }
    }  
    return m;
}