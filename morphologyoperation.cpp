#include "morphologyoperation.h"

morphologyoperation::morphologyoperation()
{
    setParams(0,0,3);
}

morphologyoperation::morphologyoperation(const int & val1, const int & val2, const int& val3){
    setParams(val1, val2, val3);
}

morphologyoperation::morphologyoperation(const morphologyoperation &M){
    setParams(M.operation_indx, M.elem_shape, M.elem_size);
}

morphologyoperation::~morphologyoperation(){
    // empty destructor
}


void morphologyoperation::process(cv::Mat &ip, cv::Mat &op){
    cv::Mat element = getStructuringElement(elem_shape,cv::Size(elem_size,elem_size));

    switch(operation_indx){
    case 0:
        cv::erode(ip,op,element);
        break;
    case 1:
        cv::dilate(ip, op, element);
        break;
    case 2:
        cv::morphologyEx(ip, op, operation_indx, element); // open
        break;
    case 3:
        cv::morphologyEx(ip, op, operation_indx, element); // close
        break;
    case 4:
        cv::morphologyEx(ip, op, operation_indx, element); // gradient
        break;
    case 5:
        cv::morphologyEx(ip, op, operation_indx, element); // top hat
        break;
    case 6:
        cv::morphologyEx(ip, op, operation_indx, element); // black hat
        break;
    default:
        cv::erode(ip,op,element);
    }


}

int morphologyoperation::determineElementShape(const int &elem_shapeindx){
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


void morphologyoperation::setParams(const int &val1, const int &val2, const int& val3){
    operation_indx = val1;
    elem_shape = determineElementShape(val2);
    elem_size = val3;
}
