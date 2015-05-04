#ifndef MORPHOLOGYERODE_H
#define MORPHOLOGYERODE_H

#include "iprocesstechnique.h"

class morphologyoperation: public Iprocesstechnique
{
private:
    int elem_shape;
    int elem_size;
    int operation_indx;
public:
    morphologyoperation();
    morphologyoperation(const int&, const int&, const int&);
    morphologyoperation(const morphologyoperation&);
    ~morphologyoperation();

    void process(cv::Mat &, cv::Mat &);

    // helper function for process
    int determineElementShape(const int&);

    // mutator (independent from base class)
    void setParams(const int&, const int&, const int&);
};

#endif // MORPHOLOGYERODE_H

