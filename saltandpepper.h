#ifndef SALTANDPEPPER_H
#define SALTANDPEPPER_H

#include "iprocesstechnique.h"

// --------------------------
// Algorithm 2 - salt and peper noise
// --------------------------
class saltandpepper : public Iprocesstechnique
{
private:
    // algorithm parameters
    double nlevel; // noise level range[0-1]
public:
    // constructors and destructor
    saltandpepper();
    saltandpepper(const double&);
    saltandpepper(const saltandpepper&);
    ~saltandpepper();

    // virtual process function definition
    void process(cv::Mat &, cv::Mat &);

    // helper functions for process
    void salt(cv::Mat &, cv::Mat &,int);
    void pepper(cv::Mat &, cv::Mat &,int);


    // mutator function (specific to this algorithm)
    void setParams(const double&);
};

#endif // SALTANDPEPPER_H



