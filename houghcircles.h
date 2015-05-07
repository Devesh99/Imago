#ifndef HOUGHCIRCLES_H
#define HOUGHCIRCLES_H

#include "iprocesstechnique.h"

class houghcircles : public Iprocesstechnique
{
private:
    double min_dist;
    double canny_thresh;
    double center_thresh;
    int min_radius;
    int max_radius;

public:
    houghcircles();
    houghcircles(const double&, const double&, const double&, const int&, const int&);
    houghcircles(const houghcircles&);
    ~houghcircles();

    void process(cv::Mat &, cv::Mat &);

    void setParameters(QString, ...);

    void setParams(const double&, const double&, const double&, const int&, const int&);
};

#endif // HOUGHCIRCLES_H
