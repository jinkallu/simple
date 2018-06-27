#ifndef GENETICENTHOUGHT_H
#define GENETICENTHOUGHT_H
#include "geneticalgorithmbase.h"
#include <QString>
#include <QtDebug>
#include <QObject>



class GeneticEnthought : public GeneticAlgorithmBase
{
    Q_OBJECT
public:
    GeneticEnthought();
    int chromosomeFunc(int c, int g) override;
    void showResults(int c) override;


    void createGeneSet();
    QString getRes();
    void setIter(int it);
    void getSteps(int *steps, float *val);

public slots:
    void process();

signals:
    void finished();

private:
    int enParms[9];
    QString geneSet;
    int multiPar[9];
    QString resString;
    int iter;
};

#endif // GENETICENTHOUGHT_H
