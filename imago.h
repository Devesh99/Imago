#ifndef IMAGO_H
#define IMAGO_H

// default images in application
#define DefResourceImage ":/boldt.jpg" // resource file
#define DefImage "boldt.jpg" // run directory

#include <QMainWindow>
#include "processmanager.h"

namespace Ui {
class Imago;
}

class Imago : public QMainWindow
{
    Q_OBJECT

public:
    explicit Imago(QWidget *parent = 0);
    ~Imago();

private:
    Ui::Imago *ui;

    // controller
    processmanager *controller;

    void initializeConnections(void)const;

    void initializeDefaultInputImage(void)const;

    void setRanges(void);

    void UpdateListWidget(std::string);

    short determineFlipCode(void)const;


private slots:
    void on_actionOpen_Image_triggered();

    void DisplayInputImage(); // function to display input image in input label
    void DisplayOutputImage(); // function to display output image in output label

    void on_actionOpen_Video_triggered();
    void on_actionOpen_Livestream_triggered();


    void on_PauseTimer_clicked();
    void on_RestartTimer_clicked();


    void on_AddMorphologyErode_clicked();

    void morphologyErodeParamChanged();

    void on_AddFlipImage_clicked();

    void flipImageParamChanged();

    void on_AddSaltAndPepper_clicked();
    void saltAndPepperParamChanged();

signals:
    void s_addSaltandPepper(const double&);
    void updateSaltAndPepper(const int&, const double&);

    void s_addMorphologyErode(int, int);
    void updateMorphologyErode(int, int, int);

    void s_addFlipImage(const short int);
    void updateFlipImage(const int&, const short int&);


};

#endif // IMAGO_H
