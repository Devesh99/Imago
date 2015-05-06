#include "imago.h"
#include "ui_imago.h"

#include <iostream>
#include <QFileDialog>

#include "stringsglobals.h"


Imago::Imago(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Imago)
{
    ui->setupUi(this);

    // instantiating controller (single instance per application run, accomplishes singleton pattern)
    controller = new processmanager;

    // --------------------------
    // Signals/slots
    //---------------------------
    initializeConnections();

    // --------------------------
    // Initialization function calls
    // --------------------------


    // set default input image (from resource file)
    initializeDefaultInputImage();

    // set widget ranges
    setRanges();
}

Imago::~Imago()
{
    delete controller; // deleting controller instance
    delete ui;
}

void Imago::initializeConnections(void)const{
    // connecting display input signal from process manager(controller) with slot
    QObject::connect(controller, SIGNAL(ImageReadyInput()), this, SLOT(DisplayInputImage()));
    QObject::connect(controller, SIGNAL(ImageReadyOutput()), this, SLOT(DisplayOutputImage()));


    // Algorithm function mutators

    QObject::connect(ui->sp_noiselevel, SIGNAL(valueChanged(int)), this, SLOT(paramChanged()));

    QObject::connect(ui->MorphologySE, SIGNAL(currentIndexChanged(int)), this, SLOT(paramChanged()));
    QObject::connect(ui->MorphologySESize, SIGNAL(valueChanged(int)), this, SLOT(paramChanged()));
    QObject::connect(ui->MorphologyOperation, SIGNAL(currentIndexChanged(int)), this, SLOT(paramChanged()));

    QObject::connect(ui->LowPassFilter, SIGNAL(currentIndexChanged(int)), this, SLOT(paramChanged()));
    QObject::connect(ui->LowPassFilterSize, SIGNAL(valueChanged(int)), this, SLOT(paramChanged()));

    QObject::connect(ui->flipHorizontal, SIGNAL(clicked()), this, SLOT(paramChanged()));
    QObject::connect(ui->flipVertical, SIGNAL(clicked()), this, SLOT(paramChanged()));
    QObject::connect(ui->flipBoth, SIGNAL(clicked()), this, SLOT(paramChanged()));

    QObject::connect(ui->sliderCanny, SIGNAL(valueChanged(int)), this, SLOT(paramChanged()));
}

void Imago::initializeDefaultInputImage(void)const{
    // OpenCV could not access resource file, copying to run directory [A]
    // resource file image could be loaded as QImage or QPixmap, but appeared distorted once used as Mat (no time to investigate this right now)
    QFile::copy(DefResourceImage, DefImage);

    controller->loadImage("boldt.jpg");
}

void Imago::setRanges(void){
    // process flow icons [a,b,c,d]
    // push buttons sizes modified for the icons to appear nice, refer ui
    ui->moveProcessUp->setIcon(QIcon(QPixmap(":/icon_arrowup.png")));
    ui->moveProcessUp->setIconSize(ui->moveProcessUp->size());
    ui->moveProcessUp->setFlat(true); // [A] set flat true: to disable boundaries display of push button, i.e. to show the icon. but boundaries displayed upon click to show response of click

    ui->moveProcessDown->setIcon(QIcon(QPixmap(":/icon_arrowdown.png")));
    ui->moveProcessDown->setIconSize(ui->moveProcessDown->size());
    ui->moveProcessDown->setFlat(true);

    ui->removeProcess->setIcon(QIcon(QPixmap(":/icon_delete.jpg")));
//    ui->removeProcess->setIconSize(QSize(ui->removeProcess->size().width() + 10, ui->removeProcess->height()));
    ui->removeProcess->setIconSize(ui->removeProcess->size());
    ui->removeProcess->setFlat(true);


    ui->refreshProcess->setIcon(QIcon(QPixmap(":/icon_refresh.png")));
    ui->refreshProcess->setIconSize(ui->refreshProcess->size());
    ui->refreshProcess->setFlat(true);

    // Add technique icons [b]
    // not setting to flat as outline looks nice
    ui->AddSaltAndPepper->setIcon(QIcon(QPixmap(":/icon_addtechnique.png")));
    ui->AddSaltAndPepper->setIconSize(ui->AddSaltAndPepper->size());

    ui->AddMorphologyOperation->setIcon(QIcon(QPixmap(":/icon_addtechnique.png")));
    ui->AddMorphologyOperation->setIconSize(ui->AddMorphologyOperation->size());

    ui->AddFlipImage->setIcon(QIcon(QPixmap(":/icon_addtechnique.png")));
    ui->AddFlipImage->setIconSize(ui->AddFlipImage->size());

    ui->AddLowPassFilter->setIcon(QIcon(QPixmap(":/icon_addtechnique.png")));
    ui->AddLowPassFilter->setIconSize(ui->AddFlipImage->size());

    ui->AddEqualizeHistogram->setIcon(QIcon(QPixmap(":/icon_addtechnique.png")));
    ui->AddEqualizeHistogram->setIconSize(ui->AddFlipImage->size());

    // process flow frame set to panel, sunken in ui through form

    // salt and pepper
    ui->sp_noiselevel->setRange(0,100); // noise level slider
    ui->sp_noiselevel->setTickInterval(10); // 0.1 interval between ticks
    ui->sp_noiselevel->setTickPosition(QSlider::TicksBelow); // ticks below slider

    // morphology structuring element shape
    const char* strarray[] = {"Rectangle", "Cross", "Ellipse"};
    std::vector<std::string> v(strarray, strarray + sizeof(strarray)/sizeof(strarray[0])); // [1]
    std::vector<std::string>::iterator it;
    for (it = v.begin(); it!=v.end();it++){
        ui->MorphologySE->addItem(QString::fromStdString(*it)); // conversion to qstring required
    }


    // morphology operations
    const char* strarray1[] = {"Erode", "Dilate", "Open", "Close", "Gradient", "Top hat", "Black hat"};
    std::vector<std::string> v1(strarray1, strarray1 + sizeof(strarray1)/sizeof(strarray1[0])); // [1]
    std::vector<std::string>::iterator it1;
    for (it1 = v1.begin(); it1!=v1.end();it1++){
        ui->MorphologyOperation->addItem(QString::fromStdString(*it1)); // conversion to qstring required
        morphology_operations.push_back(QString::fromStdString("Morphology " + *it1));
    }

    ui->MorphologySESize->setRange(3,15);
    ui->MorphologySESize->setSingleStep(2);


    // low pass filter
    const char* strarray2[] = {"Blur", "Gaussian", "Median"};
    std::vector<std::string> v2(strarray2, strarray2 + sizeof(strarray2)/sizeof(strarray2[0])); // [1]
    std::vector<std::string>::iterator it2;
    for (it2 = v2.begin(); it2!=v2.end();it2++){
        ui->LowPassFilter->addItem(QString::fromStdString(*it2)); // conversion to qstring required
        lpf_operations.push_back(QString::fromStdString("LPF " + *it2));
    }

    ui->LowPassFilterSize->setRange(3,15);
    ui->LowPassFilterSize->setSingleStep(2);

    // flip image default method
    ui->flipVertical->setChecked(true);

    // canny edge detection slider
    ui->sliderCanny->setRange(0, 100);
    ui->sliderCanny->setTickPosition(QSlider::TicksBelow);
}


void Imago::on_actionOpen_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image files(*.png *.jpg *.bmp"));
    // error-handling: empty filename (eg: user press cancel)
    // allows current process to continue executing (consider live stream/video) if open image is clicked followed by cancel
    if (!fileName.isEmpty()){
        controller->loadImage(fileName.toStdString());
    }

}

void Imago::on_actionOpen_Video_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), ".",tr("Video files(*.avi *.mov *.wmv, *.mp4"));
    // error-handling: empty filename (eg: user press cancel)
    if (!fileName.isEmpty()){
        controller->loadVideo(fileName.toStdString());
    }

}

void Imago::on_actionOpen_Livestream_triggered()
{
    controller->loadLiveStream();
}


void Imago::DisplayInputImage(){
    if (controller->getInputImage().channels()==3){
        cvtColor(controller->getInputImage(),controller->getInputImageRGB(),CV_BGR2RGB);
        controller->setInputImageQImage(QImage((const unsigned char*)(controller->getInputImageRGB().data),controller->getInputImageRGB().cols,controller->getInputImageRGB().rows,QImage::Format_RGB888));
    }
    else{
        // since gray-scale, get input image rather than RGB
        controller->setInputImageQImage(QImage((const unsigned char*)(controller->getInputImage().data),controller->getInputImageRGB().cols,controller->getInputImageRGB().rows,QImage::Format_Indexed8));
    }

    // scaling to fit label, maintaining aspect ratio
    ui->LabelInput->setAlignment(Qt::AlignCenter); //[B]
    ui->LabelInput->setPixmap(QPixmap::fromImage(controller->getInputImageQImage()).scaled(ui->LabelInput->size(), Qt::KeepAspectRatio, Qt::FastTransformation)); // [B]
}

void Imago::DisplayOutputImage(){
    if (controller->getOutputImage().channels()==3){
        cvtColor(controller->getOutputImage(),controller->getOutputImageRGB(),CV_BGR2RGB);
        controller->setOutputImageQImage(QImage((const unsigned char*)(controller->getOutputImageRGB().data),controller->getOutputImageRGB().cols,controller->getOutputImageRGB().rows,QImage::Format_RGB888));
    }
    else{
        // since gray-scale, get output image rather than RGB
        controller->setOutputImageQImage(QImage((const unsigned char*)(controller->getOutputImage().data),controller->getOutputImageRGB().cols,controller->getOutputImageRGB().rows,QImage::Format_Indexed8));
    }

    // scaling to fit label, maintaining aspect ratio
    ui->LabelOutput->setAlignment(Qt::AlignCenter);
    ui->LabelOutput->setPixmap(QPixmap::fromImage(controller->getOutputImageQImage()).scaled(ui->LabelOutput->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}



void Imago::UpdateListWidget(QString str){
    ui->techniquesListWidget->addItem(str); // algorithm name
    ui->techniquesListWidget->setCurrentRow(ui->techniquesListWidget->count() - 1); // setting added technique as current item
}

void Imago::UpdateListWidgetCurr(QString str){
    ui->techniquesListWidget->currentItem()->setText(str);
}

void Imago::UpdateListWidgetMove(const int &indx1, const int &indx2){
    QString str(ui->techniquesListWidget->item(indx1)->text());
    ui->techniquesListWidget->item(indx1)->setText(ui->techniquesListWidget->item(indx2)->text());
    ui->techniquesListWidget->item(indx2)->setText(str);
    ui->techniquesListWidget->setCurrentRow(indx2);
}

void Imago::UpdateListWidgetRemove(const int &indx){
    QListWidgetItem* it = ui->techniquesListWidget->takeItem(indx);
    delete it;
}

void Imago::UpdateListWidgetRefresh(void){
    ui->techniquesListWidget->clear(); // current item set to one below automatically
}


void Imago::on_actionPause_Play_triggered()
{
    controller->pauseplayTimer();
}


void Imago::on_AddSaltAndPepper_clicked()
{
    double nlevel = ui->sp_noiselevel->value()/100.0;
    controller->AddTechnique(salt_and_pepper, nlevel);
    UpdateListWidget(salt_and_pepper + "(" + QString::number(nlevel) + ")");
}


void Imago::on_AddMorphologyOperation_clicked()
{
    controller->AddTechnique(morphology, ui->MorphologyOperation->currentIndex(), ui->MorphologySE->currentIndex(), ui->MorphologySESize->value());
    UpdateListWidget(morphology_operations[ui->MorphologyOperation->currentIndex()] + " (" + ui->MorphologySE->currentText() + ", " + QString::number(ui->MorphologySESize->value()) + ")");

}


void Imago::on_AddLowPassFilter_clicked()
{
    controller->AddTechnique(lpf, ui->LowPassFilter->currentIndex(), ui->LowPassFilterSize->value());
    UpdateListWidget(lpf_operations[ui->LowPassFilter->currentIndex()] + " (" + QString::number(ui->LowPassFilterSize->value()) + ")");
}


void Imago::on_AddFlipImage_clicked()
{
    short flipcode = determineFlipCode();
    controller->AddTechnique(flip_image, flipcode);
    UpdateListWidget(flip_image + " (" + QString::number(flipcode) + ")");
}

short Imago::determineFlipCode(void)const{
    if (ui->flipHorizontal->isChecked()) return 1;
    if (ui->flipVertical->isChecked()) return 0;
    if (ui->flipBoth->isChecked()) return -1;
    return 0;
}


void Imago::on_AddEqualizeHistogram_clicked()
{
    controller->AddTechnique(equalize_hist);
    UpdateListWidget(equalize_hist);
}

void Imago::on_AddCanny_clicked()
{
    controller->AddTechnique(canny, ui->sliderCanny->value());
    UpdateListWidget(canny + " (" + QString::number(ui->sliderCanny->value()) + ")");
}

void Imago::paramChanged(){
    if (ui->techniquesListWidget->currentRow() > -1){ // -1 if no item is selected (intialized like this)

        QString str;
        QString currString = ui->techniquesListWidget->currentItem()->text();
        int currRow = ui->techniquesListWidget->currentRow();

        if (currString.contains(flip_image)){
            short flipcode = determineFlipCode();
            controller->setParameters(flip_image, currRow, flipcode);

            str = (flip_image + " (" + QString::number(flipcode) + ")");
        }
        if (currString.contains(lpf)){
            int lpfindx = ui->LowPassFilter->currentIndex();
            int fs = ui->LowPassFilterSize->value();
            controller->setParameters(lpf, currRow, lpfindx, fs);
            str = (lpf_operations[lpfindx] + " (" + QString::number(fs) + ")");
        }
        if (currString.contains(morphology)){
            int m_indx = ui->MorphologyOperation->currentIndex();
            int m_selem = ui->MorphologySE->currentIndex();
            int m_sesize = ui->MorphologySESize->value();
            controller->setParameters(morphology, currRow, m_indx, m_selem, m_sesize);
            str = (morphology_operations[m_indx] + " (" + ui->MorphologySE->currentText() + ", " + QString::number(m_sesize) + ")");
        }
        if (currString.contains(salt_and_pepper)){
            double nlevel = ui->sp_noiselevel->value()/100.0;
            controller->setParameters(salt_and_pepper, currRow, nlevel);
            str = (salt_and_pepper + " (" + QString::number(nlevel) + ")");
        }
        if (currString.contains(canny)){
            int thresh = ui->sliderCanny->value();
            controller->setParameters(canny, currRow, thresh);
            str = (canny + " (" + QString::number(thresh));
        }
        // error handling: since no parameters in histogram equalization, maintain string. (otherwise, would update with empty (default string) in to update call below.
        if (currString.contains(equalize_hist)){
            str = currString;
        }

        UpdateListWidgetCurr(str);
    }
}


void Imago::on_moveProcessUp_clicked()
{
    int currRow = ui->techniquesListWidget->currentRow();
    if (currRow>0){
        controller->moveProcessTechnique(currRow, currRow - 1);
        UpdateListWidgetMove(currRow, currRow - 1);
    }
}

void Imago::on_moveProcessDown_clicked()
{
    int currRow = ui->techniquesListWidget->currentRow();
    if (currRow < (ui->techniquesListWidget->count() - 1)){
        controller->moveProcessTechnique(currRow, currRow + 1);
        UpdateListWidgetMove(currRow, currRow + 1);
    }
}


void Imago::on_removeProcess_clicked()
{
    int currRow = ui->techniquesListWidget->currentRow();
    if (currRow > -1){
        controller->removeProcessTechnique(currRow);
        UpdateListWidgetRemove(currRow);
    }
}

void Imago::on_refreshProcess_clicked()
{
    if (ui->techniquesListWidget->count()>0){
        controller->refreshProcessTechnique();
        UpdateListWidgetRefresh();
    }
}


void Imago::on_actionSave_Image_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"), "untitled.png", tr("Images (*.png, *.jpg"));
    if (!fileName.isEmpty()){
        // error-handling: not saved, not updated if empty (eg: user pressed cancel)
        controller->saveImage(fileName);
    }


}

void Imago::on_actionSave_Video_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save video"), "untitled.mov", tr("Videos (*.avi, *.mpeg4, *.mov, *.mp4"));
    if (!fileName.isEmpty()){
        // error-handling: not saved, not updated if empty (eg: user pressed cancel)
        controller->saveVideo(fileName);
    }


}


