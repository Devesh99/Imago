#include "histogramequalize.h"

histogramequalize::histogramequalize()
{
    // no parameters
}

histogramequalize::~histogramequalize(){
    // empty destructor
}


void histogramequalize::process(cv::Mat &ip, cv::Mat &op){
    if (ip.channels()==3){
        // histogram of each channel is equalized and merged to one color image
        // perhaps not traditional functionality, maintained to stay in color image output
        std::vector<cv::Mat> bgrplanes;
        cv::split(ip, bgrplanes);
        cv::equalizeHist(bgrplanes[0], bgrplanes[0]);
        cv::equalizeHist(bgrplanes[1], bgrplanes[1]);
        cv::equalizeHist(bgrplanes[2], bgrplanes[2]);
        cv::merge(bgrplanes, op);
    }
    else{
        // otherwise, gray scale operation
        cv::equalizeHist(ip, op);
    }

}
