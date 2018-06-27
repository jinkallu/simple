#include "mainwindow.h"


MainWindow::MainWindow()
{
    glWidget = new GLWidget();
    pb = new QPushButton("Calculate SASGLOBAL");
    label = new QLabel("");
    label->setStyleSheet("QLabel {color : blue; }");



    mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0, 1, 2);
    mainLayout->addWidget(pb, 1, 0);
    mainLayout->addWidget(label, 1, 1);

    setLayout(mainLayout);

    genEnthought = new GeneticEnthought();
    genEnthought->setVerbose(1);
    genEnthought->setIter(10000); // maximum number of iterations

    thread = new QThread(); // thread initialization

    genEnthought->moveToThread(thread); // moving genetic class to thread

    connect(thread, SIGNAL (started()), genEnthought, SLOT (process())); // signal and slots when thread starts, start process of genetic
    connect(genEnthought, SIGNAL (finished()), thread, SLOT (quit()));
    connect(genEnthought, SIGNAL (finished()), this, SLOT (updateLablel()));

    connect(pb, SIGNAL(clicked(bool)), this, SLOT(On_Pb_clicked()));
}

MainWindow::~MainWindow()
{
    delete thread;
    delete genEnthought;
    delete mainLayout;
    delete glWidget;
}

void MainWindow::On_Pb_clicked(){
    thread->start();
}

void MainWindow::updateLablel(){
    label->setText(genEnthought->getRes());
    int steps;
    float steps_val[10000];

    genEnthought->getSteps(&steps, steps_val);

    for(int i = 0; i < steps; i++){
        cout << steps_val[i] << endl;
    }

    glWidget->setValues(&steps, steps_val);
}
