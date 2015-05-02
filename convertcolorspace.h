#ifndef CONVERTCOLORSPACE_H
#define CONVERTCOLORSPACE_H

#include "iprocesstechnique.h"

// --------------------------
// Algorithm 3 - convert color space
// --------------------------
class convertcolorspace : public Iprocesstechnique
{
private:
    int colorspace;
public:
    convertcolorspace();
    convertcolorspace(const int&);
    convertcolorspace(const convertcolorspace&);
    ~convertcolorspace();

    void process(cv::Mat &, cv::Mat &);
};

#endif // CONVERTCOLORSPACE_H
