#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include "iprocesstechnique.h"

class cannyedgedetector : public Iprocesstechnique
{
private:
    int threshold; // edge detection low threshold

public:
    cannyedgedetector();
    cannyedgedetector(const int&);
    cannyedgedetector(const cannyedgedetector&);
    ~cannyedgedetector();

    void process(cv::Mat &, cv::Mat &);

    void setParameters(QString, ...);

    // internally used mutator
    void setParams(const int&);



};

#endif // CANNYEDGEDETECTOR_H
