#include "geneticalgorithmbase.h"

GeneticAlgorithmBase::GeneticAlgorithmBase()
{
    crossover_rate = 0.5;
    mutation_rate = 0.3; // 10 %

    min_func = 10000000;

    numChromosomes = 10;
    numGenes = 9;

    verbose = 0;

    expected_result = 0;

    func_const = 0.;
}

int GeneticAlgorithmBase::chromosomeFunc(int c, int g){
    return 0;
}

void GeneticAlgorithmBase::initChromosomes(){
    if(verbose == 1){
        cout << "GA Base initChromosomes()" << endl;
    }
    for(int i = 0; i < numChromosomes; i++){
        for(int j = 0; j < numGenes; j++){
            chromosome[i][j] = chromosomeFunc(i, j);
            if(verbose == 1){
                std::cout << chromosome[i][j] << " ";
            }
        }
        if(verbose == 1){
            std::cout << std::endl;
        }
    }
}


void GeneticAlgorithmBase::calculateFunction(){
    if(verbose == 1){
        cout << "GA Base calculateFunction()" << endl;
    }
    for(int i = 0; i < numChromosomes; i++){
        f_obj[i] = 0.;
        for(int j = 0; j < numGenes; j++){
            f_obj[i] += pow(chromosome[i][j] - func_val[j], 2.);
        }
        //f_obj[i] += func_const;
        f_obj[i] = qFabs(f_obj[i]);
        if(f_obj[i] < min_func){
            min_values[num_steps] = f_obj[i];
            num_steps++;
            min_func = f_obj[i];
            for(int j = 0; j < numGenes; j++){
                minChromosome[j] = chromosome[i][j];
            }
            if(verbose == 1){
                std::cout << " Func "<<f_obj[i] << std::endl;
            }
            if(f_obj[i] <= expected_result){
                bestChromosome = i;
                flag_reached_result = true;
            }
        }

    }
}

void GeneticAlgorithmBase::calculateFitness(){
    fitTot = 0.;
    for(int i = 0; i < numChromosomes; i++){
        fitness[i] = 1. / (1. + f_obj[i]);
        fitTot += fitness[i];
    }
}

void GeneticAlgorithmBase::calculateProbability(){
    for(int i = 0; i < numChromosomes; i++){
        prob[i] = fitness[i] / fitTot;
    }
}

void GeneticAlgorithmBase::calculateCumulativeProbability(){
    for(int i = 0; i < numChromosomes; i++){
        cProb[i] = 0.;
        for(int j = 0; j <=i; j++){
            cProb[i] += prob[j];
        }
    }
}

void GeneticAlgorithmBase::newChromosomes(){
    for(int i = 0; i < numChromosomes; i++){
        float rand_num = ((float) rand()) / (float) RAND_MAX;
        //std::cout << rand << " " << cProb[i] << std::endl;
        for(int j = 0; j < numChromosomes; j++){
            if(j == 0){
                if(rand_num < cProb[j]){
                    for(int k = 0; k < numGenes; k++){
                        newChromosome[i][k] = chromosome[j][k];
                    }
                }
            }
            else{
                if(rand_num >= cProb[j - 1] && rand_num < cProb[j]){
                    for(int k = 0; k < numGenes; k++){
                        newChromosome[i][k] = chromosome[j][k];
                    }
                }
            }
        }
    }
    for(int i = 0; i < numChromosomes; i++){
        for(int k = 0; k < numGenes; k++){
            if(verbose == 1){
                std::cout << newChromosome[i][k] << " ";
            }
        }
        if(verbose == 1){
            std::cout << std::endl;
        }
    }
}

void GeneticAlgorithmBase::crossover(){
    if(verbose == 1){
        std::cout << "crossover  " << std::endl;
    }
    int crossP[1000];
    int crossPCount = 0;
    for(int i = 0; i < numChromosomes; i++){
        float rand_num = ((float) rand()) / (float) RAND_MAX;
        //std::cout << randn << std::endl;
        if(rand_num < crossover_rate){
            crossP[crossPCount] = i;
            crossPCount++;
            //std::cout << "crossover parents  " << i << std::endl;
        }
    }

    for(int i = 0; i < numChromosomes; i++){
        for(int k = 0; k < numGenes; k++){
            newChromosomeCross[i][k] = newChromosome[i][k];
        }
    }

    for(int i = 0; i < crossPCount; i++){
        int num = 0;
        while (num < 1 || num > numGenes - 1){
            double numr = ((float) rand()) / (float) RAND_MAX;
            //std::cout << numr << std::endl;
            num = numr * numChromosomes;
        }
        //std::cout << "crossover loc  " << num << std::endl;
        for(int j = num; j < numGenes; j++){
            if(i < crossPCount - 1){
                newChromosomeCross[crossP[i]][j] = newChromosome[crossP[i+1]][j];
            }
            else{
                newChromosomeCross[crossP[i]][j] = newChromosome[crossP[0]][j];
            }
        }
    }

    for(int i = 0; i < numChromosomes; i++){
        for(int k = 0; k < numGenes; k++){
            if(verbose == 1){
                std::cout << newChromosomeCross[i][k] << " ";
            }
        }
        if(verbose == 1){
            std::cout << std::endl;
        }
    }
}

void GeneticAlgorithmBase::mutation(){
    int total_gen = numChromosomes * numGenes;
    int num_mutation = total_gen * mutation_rate;

    for(int i = 0; i < num_mutation; i++){
        int j = (numChromosomes) * ((float) rand()) / (float) RAND_MAX;
        int k = (numGenes) * ((float) rand()) / (float) RAND_MAX;

        newChromosomeCross[j][k] = chromosomeFunc(j, k);
    }
    if(verbose == 1){
        std::cout << "Final " << std::endl;
    }
    for(int i = 0; i < numChromosomes; i++){
        for(int k = 0; k < numGenes; k++){
            chromosome[i][k] = newChromosomeCross[i][k];
            if(verbose == 1){
                std::cout << chromosome[i][k] << " ";
            }
        }
        if(verbose == 1){
            std::cout << std::endl;
        }
    }
}

void GeneticAlgorithmBase::setVerbose(int v){
    verbose = v;
}

void GeneticAlgorithmBase::setChromosomeGenes(int c, int g){
    numChromosomes = c;
    numGenes = g;
}


void GeneticAlgorithmBase::runAlgo(int iter){
    num_steps = 0;
    initChromosomes();
    flag_reached_result = false;
    for(int i=0; i < iter; i++){
        calculateFunction();
        if(flag_reached_result){
            cout << "Reached result in " << i << " steps" << endl;
            showResults(bestChromosome);
            break;
        }
        calculateFitness();
        calculateProbability();
        calculateCumulativeProbability();
        newChromosomes();
        crossover();
        mutation();
    }
}

void GeneticAlgorithmBase::showResults(int c){
    if(verbose == 1){
        for(int j = 0; j < numGenes; j++){
            std::cout << minChromosome[j] << " ";
        }
        cout << endl;
    }
}

int GeneticAlgorithmBase::getNumGenes(){
    return numGenes;
}

void GeneticAlgorithmBase::set_func_const(float c){
    func_const = c;
}

