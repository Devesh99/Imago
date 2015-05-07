#ifndef HIGHPASSFILTER_H
#define HIGHPASSFILTER_H

#include "iprocesstechnique.h"

class highpassfilter : public Iprocesstechnique
{
private:
    int hpfindx;
public:
    highpassfilter();
    highpassfilter(const int&);
    highpassfilter(const highpassfilter&);
    ~highpassfilter();

    void process(cv::Mat &, cv::Mat &);

    void setParameters(QString, ...);

    void setParams(const int&);
};

#endif // HIGHPASSFILTER_H
