#include "imago.h"
#include "ui_imago.h"

#include <iostream>
#include <QFileDialog>

using namespace std;

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
    QObject::connect(this, SIGNAL(s_addSaltandPepper(const double&)), controller, SLOT(addSaltAndPepper(const double&)));
    QObject::connect(ui->sp_noiselevel, SIGNAL(valueChanged(int)), this, SLOT(saltAndPepperParamChanged()));
    QObject::connect(this, SIGNAL(updateSaltAndPepper(const int&, const double&)), controller, SLOT(updateSaltAndPepperParams(const int&, const double&)));

    QObject::connect(this, SIGNAL(s_addMorphologyErode(int,int)), controller, SLOT(addMorphologyErode(int,int)));
    QObject::connect(ui->MorphologySE, SIGNAL(currentIndexChanged(int)), this, SLOT(morphologyErodeParamChanged()));
    QObject::connect(ui->MorphologySESize, SIGNAL(valueChanged(int)), this, SLOT(morphologyErodeParamChanged()));
    QObject::connect(this, SIGNAL(updateMorphologyErode(int, int,int)), controller, SLOT(updateMorphologyErodeParams(int,int,int)));

    QObject::connect(this, SIGNAL(s_addFlipImage(const short int)), controller, SLOT(addFlipImage(const short int)));
    QObject::connect(ui->flipHorizontal, SIGNAL(clicked()), this, SLOT(flipImageParamChanged()));
    QObject::connect(ui->flipVertical, SIGNAL(clicked()), this, SLOT(flipImageParamChanged()));
    QObject::connect(ui->flipBoth, SIGNAL(clicked()), this, SLOT(flipImageParamChanged()));
    QObject::connect(this, SIGNAL(updateFlipImage(const int&,const short int&)), controller, SLOT(updateFlipImageParams(const int&,const short int&)));
}

void Imago::initializeDefaultInputImage(void)const{
    // OpenCV could not access resource file, copying to run directory [A]
    // resource file image could be loaded as QImage or QPixmap, but appeared distorted once used as Mat (no time to investigate this right now)
    QFile::copy(DefResourceImage, DefImage);

    controller->loadImage("boldt.jpg");
}

void Imago::setRanges(void){
    // salt and pepper
    ui->sp_noiselevel->setRange(0,100); // noise level slider

    // creating a vector of string to store the names of the techniques
    const char* strarray[] = {"Rectangle", "Cross", "Ellipse"};
    std::vector<std::string> v(strarray, strarray + sizeof(strarray)/sizeof(strarray[0])); // [1]
    std::vector<std::string>::iterator it;
    for (it = v.begin(); it!=v.end();it++){
        ui->MorphologySE->addItem(QString::fromStdString(*it)); // conversion to qstring required
    }

    ui->MorphologySESize->setRange(3,15);
    ui->MorphologySESize->setSingleStep(2);
}


void Imago::on_actionOpen_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image files(*.png *.jpg *.bmp"));
    // error-handling: empty filename (eg: user press cancel)
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

    ui->LabelInput->setPixmap(QPixmap::fromImage(controller->getInputImageQImage()));

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

    ui->LabelOutput->setPixmap(QPixmap::fromImage(controller->getOutputImageQImage()));
}



void Imago::UpdateListWidget(std::string str){
    ui->techniquesListWidget->addItem(QString::fromStdString(str)); // algorithm name
    ui->techniquesListWidget->setCurrentRow(ui->techniquesListWidget->count() - 1); // setting added technique as current item
}

void Imago::on_PauseTimer_clicked()
{
    controller->pauseTimer();
}

void Imago::on_RestartTimer_clicked()
{
    controller->restartTimer();
}


void Imago::on_AddSaltAndPepper_clicked()
{
    emit s_addSaltandPepper(static_cast<double>(ui->sp_noiselevel->value()));
    UpdateListWidget("salt and pepper");
}

void Imago::saltAndPepperParamChanged(void){
    if (ui->techniquesListWidget->currentRow() > -1){ // -1 if no item is selected (intialized like this)
        if (ui->techniquesListWidget->currentItem()->text().toStdString().compare("salt and pepper") == 0){
            emit updateSaltAndPepper(ui->techniquesListWidget->currentRow(), static_cast<double>(ui->sp_noiselevel->value()/100.0));
        }
    }
}


void Imago::on_AddMorphologyErode_clicked()
{
    emit s_addMorphologyErode(ui->MorphologySE->currentIndex(), ui->MorphologySESize->value());
    UpdateListWidget("morphology erode");
}

void Imago::morphologyErodeParamChanged(){
    if (ui->techniquesListWidget->currentRow() > -1){ // -1 if no item is selected (intialized like this)
        if (ui->techniquesListWidget->currentItem()->text().toStdString().compare("morphology erode") == 0){
            emit updateMorphologyErode(ui->techniquesListWidget->currentRow(), ui->MorphologySE->currentIndex(), ui->MorphologySESize->value());
        }
    }
}


void Imago::on_AddFlipImage_clicked()
{
    short flipcode = determineFlipCode();
    emit s_addFlipImage(flipcode);
    UpdateListWidget("flip image");
}

short Imago::determineFlipCode(void)const{
    if (ui->flipHorizontal->isChecked()) return 1;
    if (ui->flipVertical->isChecked()) return 0;
    if (ui->flipBoth->isChecked()) return -1;
}

void Imago::flipImageParamChanged(){
    if (ui->techniquesListWidget->currentRow() > -1){ // -1 if no item is selected (intialized like this)
        if (ui->techniquesListWidget->currentItem()->text().toStdString().compare("flip image") == 0){
            emit updateFlipImage(ui->techniquesListWidget->currentRow(), determineFlipCode());
        }
    }
}


