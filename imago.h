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

    void updateComboBox(void)const;

    void initializeDefaultInputImage(void)const;

    void setRanges(void);

private slots:
    void on_actionOpen_Image_triggered();

    void DisplayInputImage(); // function to display input image in input label
    void DisplayOutputImage(); // function to display output image in output label

    void on_AddTechnique_clicked();

    void on_actionOpen_Video_triggered();
    void on_actionOpen_Livestream_triggered();

    void UpdateListWidget();

    void on_PauseTimer_clicked();
    void on_RestartTimer_clicked();

    void on_sp_noiselevel_valueChanged(int value);

signals:
    void updateSaltAndPepper(int, double);
};

#endif // IMAGO_H
