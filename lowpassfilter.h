#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "iprocesstechnique.h"

class lowpassfilter :public Iprocesstechnique
{
private:
    int filter_size;
    int operation_indx;
public:
    lowpassfilter();
    lowpassfilter(const int&, const int&);
    lowpassfilter(const lowpassfilter&);
    ~lowpassfilter();

    void process(cv::Mat &, cv::Mat &);

    void setParams(const int&, const int&);
};

#endif // LOWPASSFILTER_H
