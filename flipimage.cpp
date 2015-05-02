#include "flipimage.h"

// --------------------------
// Algorithm 1 - flip image
// --------------------------
flipimage::flipimage(){
    flipcode = 0; // possible choices: 0,>0,<0
}

flipimage::flipimage(const short &f){
    flipcode = f; // NOTE: not ussing accessors right now (depends on strategy for this - to be decided)
}

flipimage::flipimage(const flipimage &f){
    flipcode = f.flipcode; // NOTE: not ussing accessors right now (depends on strategy for this - to be decided)
}

flipimage::~flipimage(){
    // empty destructor
}

// virtual process function definition
void flipimage::process(cv::Mat& ip, cv::Mat& op){
    // + : horizontal, 0 : vertical, - :both
    cv::flip(ip, op, flipcode);
}

