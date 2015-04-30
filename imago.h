#ifndef IMAGO_H
#define IMAGO_H

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

//    void updateComboBox(void)const;

private slots:
    void on_actionOpen_Image_triggered();

    void DisplayInputImage(); // function to display input image in input label

    void DisplayOutputImage(); // function to display output image in output label
};

#endif // IMAGO_H
