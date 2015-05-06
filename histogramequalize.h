#ifndef HISTOGRAMEQUALIZE_H
#define HISTOGRAMEQUALIZE_H

#include"iprocesstechnique.h"

class histogramequalize : public Iprocesstechnique
{
private:

public:
    histogramequalize();
    ~histogramequalize();

    void process(cv::Mat &, cv::Mat &);

    void setParameters(QString, ...);


};

#endif // HISTOGRAMEQUALIZE_H
