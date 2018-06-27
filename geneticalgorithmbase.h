#ifndef GENETICALGORITHMBASE_H
#define GENETICALGORITHMBASE_H
#include <iostream>
#include <QtGlobal>
#include <QtMath>
#include <cstdlib>
//#include "genes.h"
#include <QObject>


//class Genes;

using namespace std;

class GeneticAlgorithmBase : public QObject
{
    Q_OBJECT
public:
    GeneticAlgorithmBase();

    void initChromosomes();
    void calculateFunction();
    void calculateFitness();
    void calculateProbability();
    void calculateCumulativeProbability();
    void newChromosomes();
    void crossover();
    void mutation();
    virtual int chromosomeFunc(int c, int g);
    void runAlgo(int iter);

    void setVerbose(int v);

    void setChromosomeGenes(int c, int g);

    virtual void showResults(int c);
    int getNumGenes();

    void set_func_const(float c);

    int bestChromosome;


    double chromosome[100][100];
    double newChromosome[100][100];
    double newChromosomeCross[100][100];
    double f_obj[1000];
    double fitness[1000];
    double fitTot;
    double prob[1000];
    double cProb[1000];

    double crossover_rate;
    double mutation_rate;
    double min_func;
    double minChromosome[1000];
    double expected_result;

    bool flag_reached_result;

    int verbose;

    int func_val[100];

    int num_steps;
    float min_values[100000];

    //Genes gene;

private:
    int numChromosomes;
    int numGenes;
    int func_const;
};

#endif // GENETICALGORITHMBASE_H
