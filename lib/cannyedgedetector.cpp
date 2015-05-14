#include "cannyedgedetector.h"

cannyedgedetector::cannyedgedetector()
{
    setParams(0); // default value
}

cannyedgedetector::cannyedgedetector(const int & thresh){
    setParams(thresh);
}

cannyedgedetector::cannyedgedetector(const cannyedgedetector & C){
    setParams(C.threshold);
}

cannyedgedetector::~cannyedgedetector(){
    // empty destructor
}


void cannyedgedetector::process(cv::Mat & ip, cv::Mat & op){
    cv::Canny(ip, op, threshold, 3*threshold); // using 3*threshold as higher threshold as suggested in paper and docs [3]
}


void cannyedgedetector::setParams(const int &thresh){
    threshold = thresh;
}

void cannyedgedetector::setParameters(QString str, ...){
    va_list args;
    va_start (args, str);

    int thresh = va_arg(args, int);
    setParams(thresh);

    va_end(args);
}
