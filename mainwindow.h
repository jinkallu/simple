#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "glwidget.h"
#include "geneticenthought.h"
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QVBoxLayout>


class GeneticEnthought;

class GLWidget;


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void On_Pb_clicked();
    void updateLablel();

private:
    GLWidget *glWidget;
    GeneticEnthought *genEnthought;
    QPushButton *pb, *pbRes;
    QLabel *label;
    QThread* thread;
    QGridLayout *mainLayout;
};

#endif // MAINWINDOW_H
