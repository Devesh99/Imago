#ifndef IMAGO_H
#define IMAGO_H

// default images in application
#define DefResourceImage ":/boldt.jpg" // resource file
#define DefImage "boldt.jpg" // run directory

#include <QMainWindow>

#include "processmanager.h"
#include "lib/stringsglobals.h"

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

    void initializeConnections(void)const; // signals-slots initialization

    void initializeDefaultInputImage(void)const;

    void setRanges(void); // parameter widgets

    // List widget updating functions
    void UpdateListWidget(QString); // add
    void UpdateListWidgetCurr(QString); // parameter update
    void UpdateListWidgetMove(const int&, const int&);
    void UpdateListWidgetRemove(const int&);
    void UpdateListWidgetRefresh();

    short determineFlipCode(void)const;

private slots:
    // Menu bar
    void on_actionOpen_Image_triggered();

    void on_actionOpen_Video_triggered();

    void on_actionOpen_Livestream_triggered();

    void on_actionPause_Play_triggered();

    void on_actionSave_Image_triggered();

    void on_actionSave_Video_triggered();

    void on_actionUser_Manual_triggered();

    void on_actionAbout_triggered();


    // Display image slots
    void DisplayInputImage(); // function to display input image in input label

    void DisplayOutputImage(); // function to display output image in output label


    // Add technique
    void on_AddMorphologyOperation_clicked();

    void on_AddFlipImage_clicked();

    void on_AddSaltAndPepper_clicked();

    void on_AddEqualizeHistogram_clicked();

    void on_AddLowPassFilter_clicked();

    void on_AddCanny_clicked();

    void on_AddHoughCircles_clicked();

    void on_AddHoughLines_clicked();

    void on_AddHighPassFilter_clicked();


    // Dynamic parameter updates slot
    void paramChanged(); // slot to connect all parameter widgets changes


    // Process flow toolbar
    void on_moveProcessDown_clicked();

    void on_moveProcessUp_clicked();

    void on_removeProcess_clicked();

    void on_refreshProcess_clicked();

signals:

};

#endif // IMAGO_H
