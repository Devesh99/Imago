#include "flipimage.h"


flipimage::flipimage(){
    setParams(0); // possible choices: 0,>0,<0
}

flipimage::flipimage(const short& f){
    setParams(f);
}

flipimage::flipimage(const flipimage& f){
    setParams(f.flipcode); // NOTE: not ussing accessors right now (depends on strategy for this - to be decided)
}

flipimage::~flipimage(){
    // empty destructor
}


// virtual process function definition
void flipimage::process(cv::Mat& ip, cv::Mat& op){
    // + : horizontal, 0 : vertical, - :both
    cv::flip(ip, op, flipcode);
}


// mutators
void flipimage::setParams(const short &f){
    flipcode = f;
}

void flipimage::setParameters(QString str, ...){
    va_list args;
    va_start(args, str);

    int f = va_arg(args, int);
    setParams(static_cast<short>(f)); // va sets short to int, so using int first and casting [4]

    va_end(args);
}
