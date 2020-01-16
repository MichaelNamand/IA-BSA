#include "algorithm.h"
#include <time.h>
#define PI 3.14

Solution::Solution(const Problem& _pbm) :
	_pbm(_pbm)
{}

Solution::Solution(const Solution& sol) :
	_fitness_current(sol._fitness_current), _pbm(sol._pbm)
{}

Solution::~Solution()
{
}

const Problem& Solution::pbm() const
{
	return _pbm;
}

/*ostream& operator << (ostream& os, Solution& sol)
{
	os << "Current Fitness : " << sol.get_fitness() << endl;
	return os;
}*/

void Solution::initialize()
{
	SetUpParams set;
	int j;
	for (j = 0; j < _pbm.dimension(); j++)
	{
		_solution.push_back(_pbm.LowerBound + (_pbm.UpperBound - _pbm.LowerBound) * (double)rand() / RAND_MAX);
	}
}

vector<double>& Solution::get_solution() {
	return _solution;
}

double Solution::fitness()
{
	double sum = 0.0;
	double sum2 = 0.0;
	double prod = 0.0;
	_fitness_current = 0.0;
	int a = 0.5;
	int b = 3.0;

	int j; // limité à la _pbm.dimension()
	int fnId = 1;
	unsigned int k_max = 20;

	switch (fnId)
	{
	case 1: // Discus

		for (j = 1; j < _pbm.dimension() - 1; j++)
		{
			sum += pow(_solution[0], 2);
		}

		_fitness_current = pow(10, 6) * pow(_solution[0], 2) + sum;

		break;

	case 2: // Bent Cigar

		for (j = 0; j < _pbm.dimension(); j++)
		{
			sum += pow(_solution[j], 2);
		}

		_fitness_current = pow(_solution[0], 2) + pow(10, 6) * sum;

		break;

	case 3: // Weierstrass

		for (j = 0; j < _pbm.dimension(); j++)
		{
			for (int i = 0; i <= k_max; i++)
			{
				sum += pow(a, (double)i) * cos(2 * PI * pow(b, (double)i) * (_solution[j] + 0.5));
			}
		}

		for (int i = 0; i <= k_max; i++)
		{
			sum2 += pow(a, (double)i) * cos(2 * PI * pow(b, (double)i) * 0.5);
		}

		_fitness_current = sum - _pbm.dimension() * sum2;
		
		break;

	case 4: // Katsuura

		for (j = 0; j < _pbm.dimension() - 1; j++)
		{
			for (int i = 0; i < 32; i++)
			{
				sum += abs(pow(2.0, (double)i) * _solution[j] - round(pow(2.0, (double)i) * _solution[j])) / pow(2.0, (double)i);
			}

			prod *= 1 + j * pow(sum, (10 / pow(_pbm.dimension(), 12.0)));
		}

		_fitness_current = (10 / pow(_pbm.dimension(), 2)) * prod - (10 / pow(_pbm.dimension(), 2)+258);

		break;

	case 5: // HappyCat

		for (int j = 0; j < _pbm.dimension() - 1; j++)
		{
			sum += pow(_solution[j], 2.0);
		}

		for (int j = 0; j < _pbm.dimension() - 1; j++)
		{
			sum2 += _solution[j];
		}
		_fitness_current = pow(abs(sum - (double)_pbm.dimension()), 1 / 4) + (0.5 * sum + sum2) / _pbm.dimension() + 0.5;

		break;

	case 6: // HGBat


		for (int j = 0; j < _pbm.dimension() - 1; j++)
		{
			sum += pow(_solution[j], 2.0);
		}

		for (int j = 0; j < _pbm.dimension() - 1; j++)
		{
			sum2 += _solution[j];
		}

		_fitness_current = pow(abs(pow(sum, 2.0) - pow(sum2, 2.0)), 1 / 2) + (0.5 * sum + sum2) / _pbm.dimension() + 0.5;

		break;
	}
	return _fitness_current;
}

double Solution::get_fitness() {
	return _fitness_current;
}