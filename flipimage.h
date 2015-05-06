#ifndef FLIPIMAGE_H
#define FLIPIMAGE_H

#include "iprocesstechnique.h"

// --------------------------
// Algorithm 1 - flip image
// --------------------------
class flipimage : public Iprocesstechnique
{
private:
    // algorithm parameters
    short int flipcode; // direction of flip
public:
    // constructors and destructor
    flipimage(); // default
    flipimage(const short int&); // parameter
    flipimage(const flipimage&); // clone
    ~flipimage(); // destructor

    // virtual process function definition
    void process(cv::Mat&, cv::Mat&); // not virtual since would not be derived further

    // mutator
    void setParams(const short int&);

    void setParameters(QString, ...);
};

#endif // FLIPIMAGE_H
