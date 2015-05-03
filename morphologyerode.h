#ifndef MORPHOLOGYERODE_H
#define MORPHOLOGYERODE_H

#include "iprocesstechnique.h"

class morphologyerode : public Iprocesstechnique
{
private:
    int elem_shape;
    int elem_size;

public:
    morphologyerode();
    morphologyerode(const int&, const int&);
    morphologyerode(const morphologyerode&);
    ~morphologyerode();

    void process(cv::Mat &, cv::Mat &);

    int determineElementShape(const int&);

    void setParams(const int&, const int&);
};

#endif // MORPHOLOGYERODE_H

