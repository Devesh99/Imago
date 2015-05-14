#ifndef MORPHOLOGYERODE_H
#define MORPHOLOGYERODE_H

#include "iprocesstechnique.h"

class morphologyoperation: public Iprocesstechnique
{
private:
    int elem_shape; // structuring element shape
    int elem_size; // SE size
    int operation_indx; // morphological operation
public:
    morphologyoperation();
    morphologyoperation(const int&, const int&, const int&);
    morphologyoperation(const morphologyoperation&);
    ~morphologyoperation();

    void process(cv::Mat &, cv::Mat &);

    // helper function for process
    int determineElementShape(const int&);

    // mutator
    void setParams(const int&, const int&, const int&);

    void setParameters(QString, ...);
};

#endif // MORPHOLOGYERODE_H

