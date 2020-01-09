#include "algorithm.h"

SetUpParams::SetUpParams() :
    _independent_runs(30), _nb_evolution_steps((int)((2 * pow(10, 6)) / 30)), _population_size(30), _solution_size(30)//,  mixrate(0.5)
{}


ostream& operator << (ostream& os, SetUpParams& setup) {
    os << "_population_size : " << setup.population_size() << endl;
    os << "_solution_sizeension : ";
    os << setup.solution_size() << endl;
    os << "Nb d'Execution : " << setup.independent_runs() << endl;
    os << "Nb de Generation :" << setup.nb_evolution_steps() << endl;
    os << "Probabilite de Mutation entre 0 et 1 : ";
    /*if (setup.mixrate >= 1 || setup.mixrate <= 0) {
        setup.defineMixRate(0.5);
        cout << " Utilisation de valeur par defaut : 0.5" << endl << endl;
    }
    else os << setup.getMixRate() << endl << endl;*/
    return os;
}

istream& operator >> (istream& is, SetUpParams& setup) {
    cout << "_population_size : ";
     setup.population_size(is.get());
    cout << "_solution_sizeension : ";
    setup.solution_size(is.get());
    cout << "Nb d'Execution : ";
    setup.independent_runs(is.get());
    cout << "Nb de Generation : ";
    if (setup.population_size() >= 30)
    {
        setup.nb_evolution_steps(((2 * pow(10, 6)) / setup.population_size()));
    }
    else {
        setup.nb_evolution_steps(3000);
    }
    cout << setup.nb_evolution_steps() << endl;
   

    return is;
}

const unsigned int SetUpParams::independent_runs() const
{
    return _independent_runs;
}

const unsigned int SetUpParams::nb_evolution_steps() const
{
    return _nb_evolution_steps;
}

const unsigned int SetUpParams::population_size() const
{
    return _population_size;
}

const unsigned int SetUpParams::solution_size() const
{
    return _solution_size;
}

void SetUpParams::independent_runs(unsigned int val)
{
    _independent_runs = val;
}

void SetUpParams::nb_evolution_steps(unsigned int val)
{
    _nb_evolution_steps = val;
}

void SetUpParams::population_size(unsigned int val)
{
    _population_size = val;
}

void SetUpParams::solution_size(unsigned int val)
{
    _solution_size = val;
}

SetUpParams::~SetUpParams()
{
}
