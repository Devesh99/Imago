#include "houghcircles.h"

houghcircles::houghcircles()
{
    setParams(50, 200, 100, 25, 100); // values from [A] for chariot image
}

houghcircles::houghcircles(const double & m_dist, const double &c_thresh, const double &ce_thresh, const int &min_rad, const int &max_rad){
    setParams(m_dist, c_thresh, ce_thresh, min_rad, max_rad);
}

houghcircles::houghcircles(const houghcircles &H){
    setParams(H.min_dist, H.canny_thresh, H.center_thresh, H.min_radius, H.max_radius);
}

houghcircles::~houghcircles(){
    // empty destructor
}

void houghcircles::process(cv::Mat &ip, cv::Mat &op){
    std::vector<cv::Vec3f> circles;

    // processing done on grayscale image
    if (ip.channels()>1){ // using ip instead of op here to suppress warning about unused ip (ip, op are the same anyway when called from the process function - only op is used)
        // temporary copy to compute circles, plotting over caolor image
        cv::Mat tempImg;
        cv::cvtColor(op, tempImg, CV_BGR2GRAY);
        cv::HoughCircles(tempImg, circles, CV_HOUGH_GRADIENT, 2, min_dist, canny_thresh, center_thresh, min_radius, max_radius);
    }
    else{
        cv::HoughCircles(op, circles, CV_HOUGH_GRADIENT, 2, min_dist, canny_thresh, center_thresh, min_radius, max_radius);
    }

    std::vector<cv::Vec3f>::const_iterator itc;
    for (itc = circles.begin(); itc!=circles.end(); itc++){
        cv::circle(op, cv::Point((*itc)[0], (*itc)[1]), (*itc)[2], cv::Scalar(255,0,0), 2); // plot in blue if color, else white
    }
}

void houghcircles::setParameters(QString str, ...){
    va_list args;
    va_start(args, str);

    double m_dist = va_arg(args, double);
    double c_thresh = va_arg(args, double);
    double ce_thresh = va_arg(args, double);
    int min_rad = va_arg(args, int);
    int max_rad = va_arg(args, int);

    setParams(m_dist, c_thresh, ce_thresh, min_rad, max_rad);

    va_end(args);
}

void houghcircles::setParams(const double & m_dist, const double &c_thresh, const double &ce_thresh, const int &min_rad, const int &max_rad){
    min_dist = m_dist;
    canny_thresh = c_thresh;
    center_thresh = ce_thresh;
    min_radius = min_rad;
    max_radius = max_rad;
}
