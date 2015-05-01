#include "processmanager.h"

// --------------------------
// Controller class
// --------------------------

processmanager::processmanager()
{
    // creating a vector of string to store the names of the techniques
    const char* strarray[] = {"flip image", "salt and pepper"};
    std::vector<std::string> strvector(strarray, strarray + sizeof(strarray)/sizeof(strarray[0])); // [1]
    techniquesList = strvector;
}

// --------------------------
// Accessors/mutators for images
// --------------------------
bool processmanager::setInputImage(const cv::Mat &M){
    if (M.data){
        ip = M.clone();
        ipRGB = ip.clone(); // set as copy of input image (otherwise error in display image when uninitialized)
        op = ip.clone(); // set as copy of input image (otherwise error in display image when uninitialized)
        opRGB = ip.clone(); // set as copy of input image (otherwise error in display image when uninitialized)
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
        // error handling: if no image received (eg: user pressed cancel in dialog box)
        return false;
    }
    else{
        ipRGB = ip.clone(); // set as copy of input image for initialization (otherwise error in display image when uninitialized)
        op = ip.clone(); // set as copy of input image (otherwise error in display image when uninitialized)
        opRGB = ip.clone(); // set as copy of input image (otherwise error in display image when uninitialized)
        emit ImageReadyInput();
        return true;
    }
}

cv::Mat processmanager::getInputImage()const{
    return ip;
}

cv::Mat processmanager::getOutputImage()const{
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

bool processmanager::setOutputImageQImage(QImage M){
    if (!M.isNull()){
        opQImage = M.copy();
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
const std::vector<std::string> processmanager::getTechniquesList(void)const{
    return techniquesList;
}


// --------------------------
// Add/remove process technique
// --------------------------
void processmanager::addProcessTechnique(){
    Iprocesstechnique* pt = new flipimage;
    processtechniquesList.push_back(pt);

    process();
}

// --------------------------
// Process function
// --------------------------
void processmanager::process(){
    std::vector<Iprocesstechnique*>::iterator it;
    for (it=processtechniquesList.begin(); it!=processtechniquesList.end(); it++){
        (*it)->process(ip, op);
    }

    emit ImageReadyOutput();
}


// References

// [1] http://stackoverflow.com/questions/34987/how-to-declare-an-array-of-strings-in-c
