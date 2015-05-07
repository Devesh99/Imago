#include "houghlines.h"

houghlines::houghlines()
{
    setParams(0, 1, CV_PI/180, 80); // default values from [A]
}

houghlines::houghlines(const int &indx, const double &r, const double &t, const int &th){
    setParams(indx, r, t, th);
}

houghlines::houghlines(const houghlines &H){
    setParams(H.hlindx, H.rho, H.theta, H.threshold);
}

houghlines::~houghlines(){
    // empty destructor
}


void houghlines::process(cv::Mat &ip, cv::Mat &op){


    cv::Mat contours;

    // processing on binary image, display on original image
    if (ip.channels()>1){
        cv::cvtColor(op, contours, CV_BGR2GRAY);
    }
    else{
        op.copyTo(contours);
    }
    cv::Canny(contours, contours, 125, 300); //canny threshold set from [A]


    if (hlindx == 0){
        // standard transform
        std::vector<cv::Vec2f> lines;
        cv::HoughLines(contours, lines, rho, theta, threshold);

        // Display
        std::vector<cv::Vec2f>::const_iterator it;
        for (it = lines.begin(); it!=lines.end(); it++) {
            float hlrho= (*it)[0];   // first element is distance rho
            float hltheta= (*it)[1]; // second element is angle theta
            if (hltheta < CV_PI/4. || hltheta > 3.*CV_PI/4.) { // ~vertical line
                // point of intersection of the line with first row
                cv::Point pt1(hlrho/cos(hltheta),0);
                // point of intersection of the line with last row
                cv::Point pt2((hlrho-op.rows*sin(hltheta))/
                              cos(hltheta),op.rows);
                // draw a white line
                cv::line(op, pt1, pt2, cv::Scalar(255), 1);
            }
            else { // ~horizontal line
                // point of intersection of the
                // line with first column
                cv::Point pt1(0,hlrho/sin(hltheta));
                // point of intersection of the line with last column
                cv::Point pt2(op.cols,(hlrho-op.cols*cos(hltheta))/sin(hltheta));
                // draw a white line
                cv::line(op, pt1, pt2, cv::Scalar(255), 1);
            }
        }
    }
    else{
        // probabilistic transform
        std::vector<cv::Vec4i> linesP;
        cv::HoughLinesP(contours, linesP, rho, theta, threshold);

        // Display
        for( size_t i = 0; i < linesP.size(); i++ )
        {
            cv::line(op, cv::Point(linesP[i][0], linesP[i][1]),cv::Point(linesP[i][2], linesP[i][3]), cv::Scalar(255), 1 );
        }
    }

}


void houghlines::setParameters(QString str, ...){
    va_list args;
    va_start(args, str);

    int indx = va_arg(args, int);
    double r = va_arg(args, double);
    double t = va_arg(args, double);
    int th = va_arg(args, int);

    setParams(indx, r, t, th);

    va_end(args);
}

void houghlines::setParams(const int &indx, const double &r, const double &t, const int &th){
    hlindx = indx;
    rho = r;
    theta = t/180; // normalized
    threshold = th;
}
