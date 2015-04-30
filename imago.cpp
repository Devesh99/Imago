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

    //updateComboBox();
}

Imago::~Imago()
{
    delete controller; // deleting controller instance
    delete ui;
}

void Imago::on_actionOpen_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",tr("Image files(*.png *.jpg *.bmp"));
    controller->setInputImage(fileName.toStdString());
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

}

//void Imago::updateComboBox(void)const{
//    std::vector<std::string> v = controller->getTechniquesList();
//    std::vector<std::string>::iterator it;
//    for (it = v.begin(); it!=v.end();it++){
//        ui->AddTechniquesComboBox->addItem(QString::fromStdString(*it));
//    }
//}
