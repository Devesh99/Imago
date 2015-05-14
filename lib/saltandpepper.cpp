#include "saltandpepper.h"

saltandpepper::saltandpepper()
{
    nlevel = 0.1; // default value of 10%
}

saltandpepper::saltandpepper(const double& n){
    setParams(n);
}

saltandpepper::saltandpepper(const saltandpepper& s){
    setParams(s.nlevel);
}

saltandpepper::~saltandpepper(){
    // empty destructor
}


void saltandpepper::process(cv::Mat &ip, cv::Mat &op){
    int factor=nlevel*ip.cols*ip.rows; // number of pixels to add noise

    // noise level distributed equally among salt and pepper
    salt(ip, op, factor/2);
    pepper(ip, op, factor/2);
}


void saltandpepper::salt(cv::Mat &ip, cv::Mat &op, int n){
    for (int ii=0;ii<n;ii++){
        // pixels are selected with replacement, so does not necessarily conform to the desired noise level in the probability distribution
        int i=rand()%ip.rows;
        int j=rand()%ip.cols;

        if (ip.channels()==1){
            op.at<uchar>(i,j)=255;
        }
        if (ip.channels()==3) {
            // need to set each channel separately. without specifying the channel through the [] operator
            // the first channel i.e. Blue channel (Note BGR in class Mat) is set to the value
            // Tested and verified
            op.at<cv::Vec3b>(i,j)[0]=255; // .at method is better for random access. Here obtaining the row pointer could be more efficient
            op.at<cv::Vec3b>(i,j)[1]=255;
            op.at<cv::Vec3b>(i,j)[2]=255;
        }
    }
}

void saltandpepper::pepper(cv::Mat &ip, cv::Mat &op, int n){
    for (int ii=0;ii<n;ii++){
        // pixels are selected with replacement, so does not necessarily conform to the desired noise level in the probability distribution
        int i=rand()%ip.rows;
        int j=rand()%op.cols;

        if (ip.channels()==1){
            op.at<uchar>(i,j)=0;
        }
        if (ip.channels()==3) {
            op.at<cv::Vec3b>(i,j)[0]=0; // .at method is better for random access. Here obtaining the row pointer could be more efficient
            op.at<cv::Vec3b>(i,j)[1]=0;
            op.at<cv::Vec3b>(i,j)[2]=0;
        }
    }
}


void saltandpepper::setParams(const double &d){
    nlevel = d;
}

void saltandpepper::setParameters(QString str, ...){
    va_list args;
    va_start(args, str);

    setParams(va_arg(args, double));

    va_end(args);
}
