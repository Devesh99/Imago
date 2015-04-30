#include "processmanager.h"

// --------------------------
// Controller class
// --------------------------

processmanager::processmanager()
{
//    const char* strarray[] = {"flip image"};
//    std::vector<std::string> strvector(strarray, strarray+3); // [1]
//    techniquesList = strvector;
}

// --------------------------
// Accessors/mutators for images
// --------------------------
bool processmanager::setInputImage(const cv::Mat &M){
    if (M.data){
        ip = M.clone();
        ipRGB = ip.clone(); // set as copy of input image (otherwise error in display image when uninitialized)
        emit ImageReadyInput();
        return true;
    }
    else{
        return false;
    }
}

bool processmanager::setInputImage(std::string filename){
    ip = cv::imread(filename);

    if (!ip.data){
        return false;
    }
    else{
        ipRGB = ip.clone(); // set as copy of input image for initialization (otherwise error in display image when uninitialized)
        emit ImageReadyInput();
        return true;
    }
}

const cv::Mat processmanager::getInputImage()const{
    return ip;
}

const cv::Mat processmanager::getOutputImage()const{
    return op;
}

// --------------------------
// Accessors/mutators for images (RGB)
// --------------------------
bool processmanager::setInputImageRGB(const cv::Mat &M){
    if (M.data){
        ipRGB = M.clone();
        return true;
    }
    else{
        return false;
    }
}

const cv::Mat processmanager::getInputImageRGB()const{
    return ipRGB;
}

const cv::Mat processmanager::getOutputImageRGB()const{
    return opRGB;
}


// --------------------------
// Accessors/mutators for images (QImage)
// --------------------------
bool processmanager::setInputImageQImage(QImage M){
    if (!M.isNull()){
        ipQImage = M.copy();
        return true;
    }
    else{
        return false;
    }
}

QImage processmanager::getInputImageQImage()const{
    return ipQImage;
}

QImage processmanager::getOutputImageQImage()const{
    return opQImage;
}


// --------------------------
// Accessor for techniquesList
// --------------------------
//const std::vector<std::string> processmanager::getTechniquesList(void)const{
//    return techniquesList;
//}


// References

// [1] http://stackoverflow.com/questions/34987/how-to-declare-an-array-of-strings-in-c
