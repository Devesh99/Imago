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

    // connecting display input signal from process manager(controller) with slot
    QObject::connect(controller, SIGNAL(ImageReadyInput()), this, SLOT(DisplayInputImage()));
    QObject::connect(controller, SIGNAL(ImageReadyOutput()), this, SLOT(DisplayOutputImage()));
    QObject::connect(controller, SIGNAL(UpdateListWidgetSignal()), this, SLOT(UpdateListWidget()));

    // show list of techniques available in combo box upon start up
    updateComboBox();

    // set default input image (from resource file)
    initializeDefaultInputImage();

}

Imago::~Imago()
{
    delete controller; // deleting controller instance
    delete ui;
}


void Imago::updateComboBox(void)const{
    // updates the combo box with list of techniques available upon start up

    std::vector<std::string> v = controller->getTechniquesList(); // temporary vector to store accessed conotrller member
    std::vector<std::string>::iterator it;
    for (it = v.begin(); it!=v.end();it++){
        ui->AddTechniquesComboBox->addItem(QString::fromStdString(*it)); // conversion to qstring required
    }
}

void Imago::initializeDefaultInputImage(void)const{
    // OpenCV could not access resource file, copying to run directory [A]
    // resource file image could be loaded as QImage or QPixmap, but appeared distorted once used as Mat (no time to investigate this right now)
    QFile::copy(DefResourceImage, DefImage);

    controller->loadImage("boldt.jpg");
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
        controller->setInputImageQImage(QImage((const unsigned char*)(controller->getInputImageRGB().data),controller->getInputImageRGB().cols,controller->getInputImageRGB().rows,QImage::Format_Indexed8));
    }

    ui->LabelInput->setPixmap(QPixmap::fromImage(controller->getInputImageQImage()));

}

void Imago::DisplayOutputImage(){
    if (controller->getOutputImage().channels()==3){
        cvtColor(controller->getOutputImage(),controller->getOutputImageRGB(),CV_BGR2RGB);
        controller->setOutputImageQImage(QImage((const unsigned char*)(controller->getOutputImageRGB().data),controller->getOutputImageRGB().cols,controller->getOutputImageRGB().rows,QImage::Format_RGB888));
    }
    else{
        controller->setOutputImageQImage(QImage((const unsigned char*)(controller->getOutputImageRGB().data),controller->getOutputImageRGB().cols,controller->getOutputImageRGB().rows,QImage::Format_Indexed8));
    }

    ui->LabelOutput->setPixmap(QPixmap::fromImage(controller->getOutputImageQImage()));
}


void Imago::on_AddTechnique_clicked()
{
    controller->addProcessTechnique();
}


void Imago::UpdateListWidget(){
    ui->techniquesListWidget->addItem(ui->AddTechniquesComboBox->currentText());
}


void Imago::on_PauseTimer_clicked()
{
    controller->pauseTimer();
}

void Imago::on_RestartTimer_clicked()
{
    controller->restartTimer();
}
