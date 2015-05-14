#ifndef HOUGHLINES_H
#define HOUGHLINES_H

#include "iprocesstechnique.h"

class houghlines : public Iprocesstechnique
{
private:
    int hlindx; // standard or probabilistic
    double rho;
    double theta;
    int threshold;

public:
    houghlines();
    houghlines(const int&, const double&, const double&, const int&);
    houghlines(const houghlines&);
    ~houghlines();

    void process(cv::Mat &, cv::Mat &);

    void setParameters(QString, ...);

    void setParams(const int&, const double&, const double&, const int&);
};

#endif // HOUGHLINES_H
