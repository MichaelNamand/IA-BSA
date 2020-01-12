#include <iostream>
using namespace std;
#include "Algorithm.h"


void CreateFenetreBSA() // creation de la fenetre d'affichage adapté
{
	system("mode con LINES=50 COLS=90");

	cout << endl << "				BSA Algorithm" << endl << endl << endl;
}

void Line() // s�parateur
{
	cout << "------------------------------------------------------------------" << endl << endl;
}

void SelectParam() // indique les param�tres � choisir
{
	cout << "Entrez ces parametres :" << endl;
	cout << "	- dimension (la taille d'un individu)" << endl << "	- popsize (le nombre d'individus de la population)" << endl;
	cout << "	- indRun (le nombre d'executions)" << endl << "        - mixrate (la probabilite de mutation)" << endl << endl;
	Line();
}

void SelectFunction() // indique les fonctions disponibles
{
	Line();
	cout << "choisisez la fonction de Benchmark a executer : " << endl;
	cout << "	1 - Rosenbrock" << endl << "	2 - Rastragin" << endl << "        3 - Ackley" << endl;
	cout << "	4 - Schwefel" << endl << "	5 - schaffer" << endl << "	6 - Weierstrass" << endl;
	Line();
}

int main() {
	CreateFenetreBSA();
	SelectParam();

	SetUpParams setup;
	int pop, sol, runs;
	cout << "Population size : ";
	cin >> pop;
	setup.population_size(pop);
	cin.clear();
	cout << "Dimension : ";
	cin >> sol;
	setup.solution_size(sol);
	cout << "Nb d'Execution : ";
	cin >> runs;
	setup.independent_runs(runs);
	cout << "Nb de Generation : ";
	if (setup.population_size() >= 30)
	{
		setup.nb_evolution_steps(((2 * pow(10, 6)) / setup.population_size()));
	}
	else {
		setup.nb_evolution_steps(3000);
	}
	cout << setup.nb_evolution_steps() << endl;

	;

	Line();

	cout << "Population size : " << setup.population_size() << endl;
	cout << "Dimension : ";
	cout << setup.solution_size() << endl;
	cout << "Nb d'Execution : " << setup.independent_runs() << endl;
	cout << "Nb de Generation :" << setup.nb_evolution_steps() << endl;

	SelectFunction();

	Problem pbm;
	int id;
	cout << "Function Id : ";
	cin >> id;
	switch (id) {
	case 1: // Rosenbrock
		pbm.LowerBound = -2.048;
		pbm.UpperBound = 2.048;
		break;
	case 2: // Rastrigin
		pbm.LowerBound = -5.12;
		pbm.UpperBound = 5.12;
		break;
	case 3: // Ackley
		pbm.LowerBound = -32.768;
		pbm.UpperBound = 32.768;
		break;
	case 4: // Schwefel
		pbm.LowerBound = -500;
		pbm.UpperBound = 500;
		break;
	case 5: // schaffer
		pbm.LowerBound = -100;
		pbm.UpperBound = 100;
		break;
	case 6: // Weierstrass
		pbm.LowerBound = -30; // a changer
		pbm.UpperBound = 30;
		break;
	}

	Line();

	cout << "Resultat obtenu sur le nombre d'execution :" << endl << endl;
	Algorithm algo(pbm, setup);
	algo.initialize();

	cout << endl;
	Line();

	system("pause");
	return 0;
}