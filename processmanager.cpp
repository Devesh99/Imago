#include "processmanager.h"

#include <QFileInfo>

// --------------------------
// Controller class
// --------------------------

processmanager::processmanager()
{
    QObject::connect(this, SIGNAL(ImageReadyInput()), this, SLOT(process())); // this way, opening a new image/video/live stream continues the defined process flow processing for the new frame(s) as well, as process is called

    framedelay = 0; // error-handling: otherwise garbage value. (though handlers set timer framedelay anyway, so not necessarily required)
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),this, SLOT(ReadFrame())); // video/livestream reaading frame with timer firing

    QObject::connect(this, SIGNAL(ImageReadyOutput()), this, SLOT(SaveFrame())); // save video as output ready
    isSaveVideo = false; // flag to determine daving video
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
        // error handling: if no image received (eg: user pressed cancel in dialog box)
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
// Algorithm add + mutators
// --------------------------
void processmanager::AddTechnique(QString str, ...){
    va_list args;
    va_start(args, str);

    Iprocesstechnique* pt;

    // string comparison determines which algorithm is added (sent from interface)
    // parameter constructor of algorithm classes
    if (str.compare(canny) == 0){
        int thresh = va_arg(args, int);
        pt = new cannyedgedetector(thresh);
    }
    if (str.compare(morphology) == 0){
        int m_operation = va_arg(args, int);
        int m_selem = va_arg(args, int);
        int m_ssize = va_arg(args, int);
        pt = new morphologyoperation(m_operation, m_selem, m_ssize);
    }
    if (str.compare(flip_image) == 0){
        int f = va_arg(args, int);
        short flipcode = static_cast<float>(f);
        pt = new flipimage(flipcode);
    }
    if (str.compare(equalize_hist) == 0){
        pt = new histogramequalize;
    }
    if (str.compare(lpf) == 0){
        int lpfindx = va_arg(args, int);
        int fs = va_arg(args, int);
        pt = new lowpassfilter(lpfindx, fs);
    }
    if (str.compare(hpf) == 0){
        int hpfindx = va_arg(args, int);
        pt = new highpassfilter(hpfindx);
    }
    if (str.compare(salt_and_pepper) == 0){
        pt = new saltandpepper(va_arg(args, double));
    }
    if (str.compare(hough_circles) == 0){
        double m_dist = va_arg(args, double);
        double c_thresh = va_arg(args, double);
        double ce_thresh = va_arg(args, double);
        int min_rad = va_arg(args, int);
        int max_rad = va_arg(args, int);
        pt = new houghcircles(m_dist, c_thresh, ce_thresh, min_rad, max_rad);
    }
    if (str.compare(hough_lines) == 0){
        int hlindx = va_arg(args, int);
        double r = va_arg(args, double);
        double t = va_arg(args, double);
        int th = va_arg(args, int);

        pt = new houghlines(hlindx, r, t, th);
    }


    processtechniquesList.push_back(pt); // add to process flow

    va_end(args);

    process();

}

// mutators
void processmanager::setParameters(QString str, int indx, ...){
    va_list args;
    va_start(args, indx);

    // index to determine which element of process flow (also sent from interface - list widget index)
    if (str.compare(canny) == 0){
        int thresh = va_arg(args, int);
        processtechniquesList[indx]->setParameters(str, thresh);
    }
    if (str.compare(morphology) == 0){
        int m_operation = va_arg(args, int);
        int m_selem = va_arg(args, int);
        int m_ssize = va_arg(args, int);
        processtechniquesList[indx]->setParameters(str, m_operation, m_selem, m_ssize);
    }
    if (str.compare(flip_image) == 0){
        int f = va_arg(args, int);
        short flipcode = static_cast<float>(f);
        processtechniquesList[indx]->setParameters(str, flipcode);
    }
    if (str.compare(lpf) == 0){
        int lpfindx = va_arg(args, int);
        int fs = va_arg(args, int);
        processtechniquesList[indx]->setParameters(str, lpfindx, fs);
    }
    if (str.compare(hpf) == 0){
        int hpfindx = va_arg(args, int);
        processtechniquesList[indx]->setParameters(str, hpfindx);

    }
    if (str.compare(salt_and_pepper) == 0){
        processtechniquesList[indx]->setParameters(str, va_arg(args, double));
    }
    if (str.compare(hough_circles) == 0){
        double m_dist = va_arg(args, double);
        double c_thresh = va_arg(args, double);
        double ce_thresh = va_arg(args, double);
        int min_rad = va_arg(args, int);
        int max_rad = va_arg(args, int);
        processtechniquesList[indx]->setParameters(str, m_dist, c_thresh, ce_thresh, min_rad, max_rad);
    }
    if (str.compare(hough_lines) == 0){
        int hlindx = va_arg(args, int);
        double r = va_arg(args, double);
        double t = va_arg(args, double);
        int th = va_arg(args, int);
        processtechniquesList[indx]->setParameters(str, hlindx, r, t, th);
    }

    va_end(args);

    process();
}


// --------------------------
// move/remove/refresh process technique
// --------------------------

// move process in process flow
void processmanager::moveProcessTechnique(const int &indx1, const int &indx2){
    // Swap
    Iprocesstechnique* pt = processtechniquesList[indx1];
    processtechniquesList[indx1] = processtechniquesList[indx2];
    processtechniquesList[indx2] = pt;

    process();
}

// remove current item
void processmanager::removeProcessTechnique(const int &indx){
    processtechniquesList.erase(processtechniquesList.begin() + indx);
    process();
}

// clear entire process list
void processmanager::refreshProcessTechnique(void){
    if (!processtechniquesList.empty()){
        // error handling: check for empty process flow vector
        processtechniquesList.clear();

        process();
    }
}


// --------------------------
// Process function
// --------------------------
void processmanager::process(){
    // error-handling: necessary as output matrix is used in sucession, which should be refreshed to the original input at the beginning of the process loop
    ip.copyTo(op);

    std::vector<Iprocesstechnique*>::iterator it;
    for (it=processtechniquesList.begin(); it!=processtechniquesList.end(); it++){
        (*it)->process(op, op);
    }

    emit ImageReadyOutput();
}


// --------------------------
// Image/Video/live stream handlers
// --------------------------
void processmanager::loadImage(std::string filename){
    // handles the case where image is opened after video/live stream. (active timer must be stopped for new image to be used)
    if (timer->isActive()){
        timer->stop();
        capture.release();
    }
    setInputImage(filename);

    // ----
    // Dirty implementation: fix this to uniformly use qstring
    // ----
    QFileInfo tempObj(QString::fromStdString(filename)); // [7] QFileInfo object allows the string parsing
    setFileNameSave(tempObj.baseName().toStdString()); // extracts filename without extension (or other '.')
}

void processmanager::loadVideo(std::string filename){
    // callback from open video push button

    if (timer->isActive()){
        timer->stop();
        capture.release();
    }

    capture.open(filename);
    if (capture.isOpened()){
        double rate = capture.get(CV_CAP_PROP_FPS); // frame rate of video
        framedelay=1000/rate;
        // timer restarts (no need to stop and start) [2]
        timer->start(framedelay); // set for pause/play utilization

        // ----
        // Dirty implementation: fix this to uniformly use qstring
        // ----
        QFileInfo tempObj(QString::fromStdString(filename)); // [7] QFileInfo object allows the string parsing
        setFileNameSave(tempObj.baseName().toStdString()); // extracts filename without extension (or other '.')
    }
}

void processmanager::loadLiveStream(){
    // callback from open live stream push button

    if (timer->isActive()){
        timer->stop();
        capture.release();
    }

    capture.open(0);
    if (capture.isOpened()){
        // timer restarts (no need to stop and start) [2]
        framedelay = 0;
        timer->start(framedelay);

        setFileNameSave("livestream");
    }
}

void processmanager::ReadFrame(){
    // timer callback function to set input image frame from video/live stream
    cv::Mat frame;
    capture>>frame;
    setInputImage(frame);
}

void processmanager::SaveFrame(){
    if (getSaveVideoFlag()){
        if (writer.isOpened()){
            cv::Mat temp = getOutputImage().clone();
            if (temp.channels()>1){ // QUICK FIX: not saving grayscae images, since crashes if color + grayscale mixed in video saving. Improve this by getting the channels of the first frame to be saved, and save those which match it after processing.
                writer.write(getOutputImage());
            }

        }
    }
}


void processmanager::pauseplayTimer(void){
    // integrated functionality for both pause/play as is usually
    if (capture.isOpened()){
        if (timer->isActive()){
            timer->stop();
        }
        else{
            timer->start(framedelay);
        }
    }
}


void processmanager::saveImage(std::string filename){
    cv::imwrite(filename, getOutputImage());
}

void processmanager::saveVideo(QString filename){
    // FIXED: video writer does not seem to work with Mac [6] resolved using [8], [9]

    if (capture.isOpened()){
        if (framedelay == 0){ // live stream
            writer.open(filename.toStdString(), CV_FOURCC('j','p','e','g'), 15, cv::Size(op.cols, op.rows) ); // setting save frame rate of 15
        }
        else{
            writer.open(filename.toStdString(), CV_FOURCC('j','p','e','g'), 1000/framedelay, cv::Size(op.cols, op.rows) ); // using video frame rate for saving
        }
    }
    else{
            writer.open(filename.toStdString(), CV_FOURCC('j','p','e','g'), 1, cv::Size(op.cols, op.rows) ); // images save at 1 frame per second to see results
    }

    setSaveVideoFlag(true); // save started
}

void processmanager::setFileNameSave(std::string str){
    fileNameSave = str;
}

std::string processmanager::getFileNameSave(void)const{
    return fileNameSave;
}

void processmanager::setSaveVideoFlag(bool flag){
    isSaveVideo = flag;
}

bool processmanager::getSaveVideoFlag(void)const{
    return isSaveVideo;
}
