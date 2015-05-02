#include "convertcolorspace.h"

convertcolorspace::convertcolorspace()
{
    colorspace = 0; // default color space (gray scale)
}

convertcolorspace::convertcolorspace(const int &c){
    colorspace = c;
}

convertcolorspace::convertcolorspace(const convertcolorspace &c){
    colorspace = c.colorspace;
}

convertcolorspace::~convertcolorspace(){
    // empty destructor
}


void convertcolorspace::process(cv::Mat &ip, cv::Mat &op){
    switch(colorspace){
    case 0:
        cv::cvtColor(ip, op, CV_BGR2GRAY );
        break;
    case 1:
        cv::cvtColor(ip, op, CV_BGR2RGB);
        break;
    case 2:
        cv::cvtColor(ip, op, CV_BGR2HLS);
        break;
    case 3:
        cvtColor(ip, op, CV_BGR2HSV);
        break;
    case 4:
        cvtColor(ip, op, CV_BGR2Lab);
        break;
    case 5:
        cvtColor(ip, op, CV_BGR2Luv);
        break;
    case 6:
        cvtColor(ip, op, CV_BGR2YCrCb);
        break;
    case 7:
        cvtColor(ip, op, CV_BGR2YUV);
        break;
    case 8:
        cvtColor(ip, op, CV_BGR2XYZ);
        break;
    }
}
