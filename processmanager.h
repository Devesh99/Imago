#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "iprocesstechnique.h"
#include "allalgorithms.h"

#include <QObject>
#include <QImage>
#include <QString>

// --------------------------
// Controller class
// --------------------------
class processmanager : public QObject
{
    Q_OBJECT // derived from QObject to emit signals, for instance for displaying images

private:
    cv::Mat ip;
    cv::Mat op;
    std::vector<Iprocesstechnique*> processtechniquesList;

    // storing image matrices used for display in rendering on pixmap
    cv::Mat ipRGB;
    cv::Mat opRGB;

    QImage ipQImage;
    QImage opQImage;

    std::vector<std::string> techniquesList; // stores names of all available techniques (for display in combo box)


public:
    processmanager(); // constructor

    // --------------------------
    // accessors and mutators for images
    // --------------------------

    // accessors Input/output
    cv::Mat getInputImage(void)const;
    cv::Mat getOutputImage(void)const;
    // mutators input/output
    bool setInputImage(const cv::Mat&);
    bool setInputImage(std::string filename); // overloaded mutator for input with filename

    // accessors (RGB)
    const cv::Mat getInputImageRGB(void)const;
    const cv::Mat getOutputImageRGB(void)const;
    // mutators (RGB)
    bool setInputImageRGB(const cv::Mat&);

    // accessors (QImage)
    QImage getInputImageQImage(void)const;
    QImage getOutputImageQImage(void)const;
    // mutators (QImage)
    bool setInputImageQImage(QImage);
    bool setOutputImageQImage(QImage);

    // --------------------------
    // accessor for techniqueslist
    // --------------------------
    const std::vector<std::string> getTechniquesList(void)const;


    // --------------------------
    // Add/remove processing techniques
    // --------------------------
    void addProcessTechnique();


    // --------------------------
    // Execute
    // --------------------------
    void process();


signals:
    void ImageReadyInput(); // to display input image
    void ImageReadyOutput(); // to display output image

};

#endif // PROCESSMANAGER_H
