#ifndef IPROCESSTECHNIQUE_H
#define IPROCESSTECHNIQUE_H

#include <iostream>
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

};




#endif // IPROCESSTECHNIQUE_H
