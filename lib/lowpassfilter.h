#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "iprocesstechnique.h"

class lowpassfilter :public Iprocesstechnique
{
private:
    int filter_size;
    int operation_indx; // type of LPF
public:
    lowpassfilter();
    lowpassfilter(const int&, const int&);
    lowpassfilter(const lowpassfilter&);
    ~lowpassfilter();

    void process(cv::Mat &, cv::Mat &);

    void setParams(const int&, const int&);

    void setParameters(QString, ...);

};

#endif // LOWPASSFILTER_H
