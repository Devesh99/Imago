#include "highpassfilter.h"


highpassfilter::highpassfilter()
{
    setParams(0); // laplacian by default
}

highpassfilter::highpassfilter(const int &indx){
    setParams(indx);
}

highpassfilter::highpassfilter(const highpassfilter &H){
    setParams(H.hpfindx);
}

highpassfilter::~highpassfilter(){
    // empty destructor
}


void highpassfilter::process(cv::Mat &ip, cv::Mat &op){
    switch(hpfindx){
    case 0:
        cv::Laplacian(ip, op, op.depth());
        break;
    case 1:
        cv::Sobel(ip, op, op.depth(), 1, 1); // setting first derivative (could icnlude as parameter in ui later)
        break;
    case 2:
        cv::Scharr(ip, op, op.depth(), 1, 0); // setting x first derivative (could include as parameter in ui later)
        break;
    case 3:
        cv::Scharr(ip, op, op.depth(), 0, 1); // setting y first derivative (could include as parameter in ui later)
        break;
    default:
        cv::Laplacian(ip, op, op.depth());
        break;
    }
}


void highpassfilter::setParameters(QString str, ...){
    va_list args;
    va_start(args, str);

    int hpfi = va_arg(args, int);
    setParams(hpfi);

    va_end(args);
}

void highpassfilter::setParams(const int &indx){
    hpfindx = indx;
}
