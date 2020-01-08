#include "algorithm.h"
#include <time.h>
#define PI 3.14

Solution::Solution(const Problem& _pbm) :
	_pbm(_pbm)
{}

Solution::Solution(const Solution& sol) :
	_fitness_current(sol._fitness_current), _pbm(sol.pbm)
{}

ostream& operator << (ostream& os, Solution& sol)
{
	os << "Current Fitness : " << sol.get_fitness() << endl;
	return os;
}

void Solution::initialize()
{
	SetUpParams set;

	int j;
	for (j = 0; j < _pbm.dimension(); j++)
	{
		_solution.push_back(lower + (upper - lower) * (double)rand() / RAND_MAX);
	}
}

vector<double>& Solution::get_solution() {
	return _solution;
}

double Solution::fitness()
{
	double sum = 0.0;
	_fitness_current = 0.0;

	int j; // limité à la dim

	switch (_pbm.getFuncId())
	{
	case 1: // Rosenbrock

		for (j = 0; j < _pbm.dimension() - 1; j++)
		{
			if (j + 1 < _solution.size()) {
				sum = 100 * (pow((_solution[j + 1] - pow(_solution[j], 2)), 2)) + pow(_solution[j] - 1, 2);
			}
		}

		_fitness_current = sum;

		break;

	case 2: // Rastrigin

		for (j = 0; j < _pbm.dimension(); j++)
		{
			if (j < _solution.size()) {
				sum = pow(_solution[j], 2) - (10 * cos(2 * PI * _solution[j]));
			}
		}

		_fitness_current = (10 * _pbm.dimension()) + sum;

		break;

	case 3: // Ackley

		double A, B;

		for (j = 0; j < _pbm.dimension(); j++)
		{
			A = pow(_solution[j], 2);
			B = cos(2 * PI * _solution[j]);
		}
		sum = -20 * exp(-0.2 * sqrt((1 / _pbm.dimension()) * A)) - exp((1 / _pbm.dimension()) * B) + 20 + exp(1);

		_fitness_current = sum;

		break;

	case 4: // Schwefel

		for (int j = 0; j < _pbm.dimension(); j++)
		{
			if (j < _solution.size()) {
				sum = _solution[j] * sin(sqrt(abs(_solution[j])));
			}
		}

		_fitness_current = 418.9829 * _pbm.dimension() - sum;

		break;

	case 5: // schaffer

		for (int j = 0; j < _pbm.dimension() - 1; j++)
		{
			if (j < _solution.size()) {
				sum = (pow(sin(pow(_solution[j], 2) - pow(_solution[j + 1], 2)), 2) - 0.5) / (pow(1 + 0.001 * (pow(_solution[j], 2) + pow(_solution[j + 1], 2)), 2));
			}
		}

		_fitness_current = 0.5 + sum;

		break;

	case 6: // Weierstrass

		int i = 0;
		double a, b;
		unsigned int k_max;
		a = 0.5;
		b = 3.0;
		k_max = 20;

		for (int j = 0; j < _pbm.dimension(); j++)
		{
			for (unsigned int t = 0; t <= k_max; t++)
			{
				if (j < _solution.size()) {
					sum += pow(a, (double)t) * cos(2.0 * PI * pow(b, (double)t) * (_solution[j] + 0.5));
				}
			}
		}

		_fitness_current = sum;

		break;
	}
	return _fitness_current;
}

double Solution::get_fitness() {
	return _fitness_current;
}