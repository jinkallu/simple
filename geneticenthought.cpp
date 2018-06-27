#include "geneticenthought.h"

GeneticEnthought::GeneticEnthought()
{
    createGeneSet(); // create the geneset with english alphabet

    // the function eqation is pow(a - E, 2) + pow(b - N, 2) + pow(c - T, 2) +  ..

    enParms[0] = 19.; // "S" position of S in alphabets
    enParms[1] = 1.; // "A"
    enParms[2] = 19.; // "S"
    enParms[3] = 7.; // "G"
    enParms[4] = 12.; // "L"
    enParms[5] = 15.; // "O"
    enParms[6] = 2.; // "B"
    enParms[7] = 1.; // "A"
    enParms[8] = 12.; // "L"

    for(int i = 0; i < 9; i++){
        func_val[i] = enParms[i]; // setting the funcval for calculation
    }
    setChromosomeGenes(100, 9); //setting chromosomes and genes

    iter = 10000;
}

int GeneticEnthought::chromosomeFunc(int c, int g){
    int randGene = qrand() % 26;// generating a random number to select alpha bete from A - Z.
    int gen = randGene + 1;

    return gen;
}

void GeneticEnthought::showResults(int c){
    resString.clear();
    for(int j = 0; j < getNumGenes(); j++){
        int p = minChromosome[j];
        resString.append( geneSet.at(p - 1));
        cout << p  << " ";
    }
    cout << resString.toLatin1().data() << endl;
}

void GeneticEnthought::createGeneSet(){
    geneSet.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

QString GeneticEnthought::getRes(){
    return resString;
}

void GeneticEnthought::process(){
    runAlgo(iter);
    emit finished();
}

void GeneticEnthought::setIter(int it){
    iter = it;
}

void GeneticEnthought::getSteps(int *steps, float *val){
    steps[0] = num_steps;
    for(int i = 0; i < num_steps; i++){
        val[i] = min_values[i];
    }
}



