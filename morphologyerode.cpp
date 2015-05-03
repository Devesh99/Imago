#include "morphologyerode.h"

morphologyerode::morphologyerode()
{
    setParams(0,3);
}

morphologyerode::morphologyerode(const int & val1, const int & val2){
    setParams(val1, val2);
}

morphologyerode::morphologyerode(const morphologyerode &M){
    setParams(M.elem_shape, M.elem_size);
}

morphologyerode::~morphologyerode(){
    // empty destructor
}


void morphologyerode::process(cv::Mat &ip, cv::Mat &op){
    cv::Mat element = getStructuringElement(elem_shape,cv::Size(elem_size,elem_size));

    cv::erode(ip,op,element);
}

int morphologyerode::determineElementShape(const int &elem_shapeindx){
    switch (elem_shapeindx){
    case 0:
        return cv::MORPH_RECT;
    case 1:
        return cv::MORPH_CROSS;
    case 2:
        return cv::MORPH_ELLIPSE;
    default:
        return cv::MORPH_RECT;
    }
}


void morphologyerode::setParams(const int &val1, const int &val2){
    elem_shape = determineElementShape(val1);
    elem_size = val2;
}
