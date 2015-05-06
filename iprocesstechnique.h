#ifndef IPROCESSTECHNIQUE_H
#define IPROCESSTECHNIQUE_H

#include <iostream>
#include <QString>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


// --------------------------
// Abstract base/interface class
// --------------------------
class Iprocesstechnique
{
public:
    Iprocesstechnique();

    // pure virtual processing function (to be completed by each derived algorithm class)
    virtual void process(cv::Mat&, cv::Mat&) = 0;


    // mutator with variable number of arguments
    // since algorithms (may) differ in types AND number of parameters
    virtual void setParameters(QString, ...) = 0;
};




#endif // IPROCESSTECHNIQUE_H
