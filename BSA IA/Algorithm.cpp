#include "algorithm.h"


Algorithm::Algorithm(const Problem& pbm, const SetUpParams& setup) :
    _setup(setup), _population()
{
    _fitness_values_of_current_population.resize(setup.independent_runs());

    //Tableaux dynamiques 2D
    double** oldP = new double* [setup.population_size()];
    double** P = new double* [setup.population_size()];
    double** Mutant = new double* [setup.population_size()];
    double** map = new double* [setup.population_size()];
    double** T = new double* [setup.population_size()];

    //Tableaux dynamique 1D : popsize*1
    double* fitP = new double[setup.population_size()];
    double* fitT = new double[setup.population_size()];
    double* globalMinimizer = new double[pbm.dimension()];

    int* mutT = new int[pbm.dimension()];

    //Initialisation des variables pour la comparaison de fitnesse
    _global_best_solution->random(pbm.UpperLimit, pbm.LowerLimit);
    _lower_cost = _global_best_solution.fitness(_global_best_solution.tabLine);
    _upper_cost = _lower_cost;

    //Variables interm?diaires pour la fitnesse
    double min;
    double max;

    double fitBest;

    //Variable d'index du tableau
    int indexBest;
    int indexWorst;

    int i, j;

    globalMin = std::numeric_limits<double>::infinity(); //  valeur = infini

    for (int r = 0; r < setup.independent_runs(); r++)
    {
        cout << "Nb d'execution : " << r << endl;

        //Creation des tableaux
        for (i = 0; i < setup.population_size(); i++)
        {
            P[i] = new double[pbm.dimension()];
        }

        for (i = 0; i < setup.population_size(); i++)
        {
            oldP[i] = new double[pbm.dimension()];
        }

        for (i = 0; i < setup.population_size(); i++)
        {
            Mutant[i] = new double[pbm.dimension()];
        }

        for (i = 0; i < setup.population_size(); i++)
        {
            map[i] = new double[pbm.dimension()];
        }

        for (i = 0; i < setup.population_size(); i++)
        {
            T[i] = new double[pbm.dimension()];
        }

        int flag = 0;

        //Assign?s des valeurs ? la Population
        for (i = 0; i < setup.population_size(); i++)
        {
            _global_best_solution.tabLine.clear();
            _global_best_solution.random(pbm.UpperLimit, pbm.LowerLimit);
            for (j = 0; j < pbm.dimension(); j++)
            {
                P[i][j] = _global_best_solution.tabLine[j];
            }
            fitP[i] = _global_best_solution.fitness(_global_best_solution.tabLine);   // initialisation du tableau de fitnesse de Population
        }

        //Assign?s des valeurs ? la OldPopulation
        for (i = 0; i < setup.population_size(); i++)
        {
            _global_best_solution.tabLine.clear();
            _global_best_solution.random(pbm.UpperLimit, pbm.LowerLimit);
            for (j = 0; j < pbm.dimension(); j++)
            {
                oldP[i][j] = _global_best_solution.tabLine[j];
            }
        }


        for (int k = 0; k < setup.nb_evolution_steps(); k++)
        {
            min = fitP[0];
            max = fitP[0];

            int id;

            for (i = 0; i < setup.population_size(); i++)
            {
                if (fitP[i] == fitP[0])
                {
                    _lower_cost = fitP[0];
                    _upper_cost = fitP[0];
                    flag = 1;
                    id = i;
                }
                else if (fitP[i] < min) {
                    _lower_cost = fitP[i];
                    min = best_cost();
                    flag = 2;
                    id = i;
                }
                else if (fitP[i] > max) {
                    _upper_cost = fitP[i];
                    max = worst_cost();
                    flag = 3;
                    id = i;
                }
                else {}

                if (flag == 1)
                {
                    indexBest = id + 1;
                    indexWorst = id + 1;
                }
                else if (flag == 2)
                {
                    indexBest = id + 1;
                }
                else if (flag == 3)
                {
                    indexWorst = id + 1;
                }
                else {}
            }

            // valeurs al?atoires entre 0 et 1
            double a = rand() / (RAND_MAX + 1.0);
            double b = rand() / (RAND_MAX + 1.0);
            double c = rand() / (RAND_MAX + 1.0);
            double d = rand() / (RAND_MAX + 1.0);


            //selection 1
            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension(); j++)
                {
                    if (a < b)
                    {
                        oldP[i][j] = P[i][j];
                    }
                }
            }

            //permutation
            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension() / 2; j++)
                {
                    // g?n?ration de 2 position al?atoires
                    int randA = rand() % setup.population_size();
                    int randB = rand() % setup.population_size();

                    double temp;

                    temp = oldP[randA][j];
                    oldP[randA][j] = oldP[randB][j];
                    oldP[randB][j] = temp;
                }
            }

            /*---------------------------------------------------------------------*/

            //Generation of Trial-Population

            //Mutation

            // g?n?rer des valeurs al?atoires selon la distribution normale

            default_random_engine generator;
            normal_distribution<double> distribution(0.0, 1.0);
            double F;

            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension(); j++)
                {
                    F = 3 * distribution(generator);

                    Mutant[i][j] = P[i][j] + ((oldP[i][j] - P[i][j]) * F);
                }
            }

            //Crossover

            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension(); j++)
                {
                    map[i][j] = 1;
                }
            }

            randomMutants = (int)ceil(setup.getMixRate() * pbm.dimension() * a);
            if (c < d)
            {
                for (i = 0; i < setup.population_size(); i++)
                {
                    tempMut = rand() % pbm.dimension();
                    for (j = 1; j <= randomMutants; j++)
                    {
                        while (Exists(tempMut) && mutT != NULL)
                        {
                            tempMut = rand() % pbm.dimension();
                        }

                        mutT[j] = tempMut;

                        int m = mutT[j];
                        map[i][m] = 0;
                    }
                }
            }
            else
            {
                int randi;
                for (i = 0; i < setup.population_size(); i++)
                {
                    randi = rand() % pbm.dimension();
                    map[i][randi] = 0;
                }
            }

            // Generation of a trial population

            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension(); j++)
                {
                    T[i][j] = Mutant[i][j];
                }
            }

            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension(); j++)
                {
                    if (map[i][j] == 1)
                    {
                        T[i][j] = P[i][j];
                    }
                }
            }

            //Boundary Control Mechanism

            for (i = 0; i < setup.population_size(); i++)
            {
                _global_best_solution.tabLine.clear();

                for (j = 0; j < pbm.dimension(); j++)
                {
                    if (T[i][j] < pbm.LowerLimit || T[i][j] > pbm.UpperLimit)
                    {
                        T[i][j] = pbm.LowerLimit + (pbm.UpperLimit - pbm.LowerLimit) * (double)rand() / RAND_MAX;
                    }
                    _global_best_solution.tabLine.push_back(T[i][j]);
                }
                fitT[i] = _global_best_solution.fitness(_global_best_solution.tabLine); // la modification de T change la fitnesse
            }

            /*---------------------------------------------------------------------*/

            //Selection 2

            for (i = 0; i < setup.population_size(); i++)
            {
                for (j = 0; j < pbm.dimension(); j++)
                {

                    if (fitT[i] < fitP[i])
                    {
                        P[i][j] = T[i][j];
                        fitP[i] = fitT[i];
                    }
                }

            }

            //Global fit

            fitBest = best_cost();

            if (fitBest <= globalMin)
            {
                globalMin = fitBest;
                for (i = 0; i < setup.population_size(); i++)
                {
                    for (j = 0; j < pbm.dimension(); j++)
                    {
                        if (i == indexBest)
                        {
                            globalMinimizer[j] = P[i][j];
                        }
                    }
                }
            }
        } // fin k

        //cout << "Meilleur individu : " << indexBest << endl;
        for (j = 0; j < pbm.dimension(); j++)
        {
            //cout << globalMinimizer[j] << " ";
        }
        //cout << endl;

        runTab[r] = globalMin;

        ofstream file;
        file.open("result.txt", ios::app);
        file << "IndexBest:" << indexBest << endl;
        file << "BestFitness:" << fitBest << endl << endl;
        file.close();

    } // fin r


    double sum = 0.0;
    double mean = 0.0;
    double temp = 0.0;
    double variance = 0.0;
    double deviation = 0.0;

    for (i = 0; i < setup.independent_runs(); i++)
    {
        sum += runTab[i];
    }

    mean = sum / setup.independent_runs();
    cout << "Moyenne : " << mean << endl;

    for (i = 0; i < setup.independent_runs(); i++)
    {
        temp += pow((runTab[i] - mean), 2);
    }

    variance = temp / setup.independent_runs();
    cout << "Variance : " << variance << endl;

    deviation = sqrt(variance);
    cout << "Ecart-type : " << deviation << endl;

    //delete tab
    for (i = 0; i < pbm.dimension(); ++i) {
        delete[] P[i];
    }
    delete[] P;

    for (i = 0; i < pbm.dimension(); ++i) {
        delete[] oldP[i];
    }
    delete[] oldP;

    for (i = 0; i < pbm.dimension(); ++i) {
        delete[] Mutant[i];
    }
    delete[] Mutant;

    for (i = 0; i < pbm.dimension(); ++i) {
        delete[] map[i];
    }
    delete[] map;

    for (i = 0; i < pbm.dimension(); ++i) {
        delete[] T[i];
    }
    delete[] T;

    delete[] fitP;
    delete[] fitT;
    delete[] globalMinimizer;
    delete[] mutT;
    delete[] runTab;
}

double MyAlgorithm::best_cost()  const
{
    return _lower_cost;
}

double MyAlgorithm::worst_cost()  const
{
    return _upper_cost;
}

bool MyAlgorithm::Exists(int tempM)
{
    int j;
    for (j = 1; j <= randomMutants; j++)
    {
        if (mutT[j] == tempM)
            return true;
    }
    return false;
}
