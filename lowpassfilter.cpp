#include "lowpassfilter.h"

lowpassfilter::lowpassfilter()
{
    setParams(0, 3);
}

lowpassfilter::lowpassfilter(const int& indx, const int &fs){
    setParams(indx, fs);
}

lowpassfilter::lowpassfilter(const lowpassfilter &l){
    setParams(l.operation_indx, l.filter_size);
}

lowpassfilter::~lowpassfilter(){
    // empty destructor
}


void lowpassfilter::process(cv::Mat& ip, cv::Mat& op){
    switch(operation_indx){
    case 0:
        cv::blur(ip, op, cv::Size(filter_size, filter_size)); // normalized block filter
        break;
    case 1:
        cv::GaussianBlur(ip, op, cv::Size(filter_size, filter_size), 0, 0); // sigma_x,y calculated using filter size by setting to zero
        break;
    case 2:
        cv::medianBlur(ip, op, filter_size);
        break;
    default:
        cv::blur(ip, op, cv::Size(filter_size, filter_size)); // normalized block filter
    }
}


void lowpassfilter::setParams(const int &indx, const int &fs){
    operation_indx = indx;
    filter_size = fs;
}
