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
	cout << "	1 - Discus" << endl << "	2 - Bent Cigar" << endl << "        3 - Weierstrass" << endl;
	cout << "	4 - Katsuura" << endl << "	5 - HappyCat" << endl << "	6 - HGBat" << endl;
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
	case 1: // Discus
		pbm.LowerBound = -5;
		pbm.UpperBound = 5;
		break;
	case 2: //  Bent Cigar
		pbm.LowerBound = -100;
		pbm.UpperBound = 100;
		break;
	case 3: // Weierstrass
		pbm.LowerBound = -0.5;
		pbm.UpperBound = 0.5;
		break;
	case 4: // Katsuura
		pbm.LowerBound = -100;
		pbm.UpperBound = 100;
		break;
	case 5: // HappyCat
		pbm.LowerBound = -2;
		pbm.UpperBound = 2;
		break;
	case 6: // HGBat
		pbm.LowerBound = -5;
		pbm.UpperBound = 5;
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