
#ifndef INC_METAHEURISTIC
#define INC_METAHEURISTIC
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

//=======================================================================
class Problem
{
public:
	Problem();
	~Problem();

	int dimension() const;

private:

	int _dimension;
	double LowerBound, UpperBound;
};
//=======================================================================
class Solution
{

private:
	vector<double> _solution;
	double _fitness_current;
	const Problem& _pbm;

public:
	Solution(const Problem& pbm);
	Solution(const Solution& sol);
	~Solution();

	const Problem& pbm() const;

	void initialize();
	double fitness();
	double get_fitness();

	vector<double>& get_solution();

	double& get_position_in_solution(const int index);
	void  set_position_in_solution(const int index, const double value);

};

//=======================================================================

class SetUpParams
{
	//ici vous devez mettre quelques param�tres tels que :

private:
	unsigned int   _independent_runs;         //number of independent runs
	unsigned int   _nb_evolution_steps;       // number of iterations per run
	unsigned int   _population_size;		// number of solutions in the population
	unsigned int   _solution_size;	        // size of each particle

public:
	SetUpParams();

	const unsigned int   independent_runs() const;
	const unsigned int   nb_evolution_steps() const;
	const unsigned int   population_size() const;
	const unsigned int   solution_size() const;
	void independent_runs(const unsigned int val);
	void nb_evolution_steps(const unsigned int val);
	void population_size(const unsigned int val);
	void solution_size(const unsigned int val);

	~SetUpParams();
};
//=======================================================================


class Algorithm
{
private:
	vector<Solution*> _population;     // individuals in population
	vector<double> _fitness_values_of_current_population;
	const SetUpParams& _setup;
	Solution* _global_best_solution;

public:
	Algorithm(const Problem& pbm, const SetUpParams& setup);
	~Algorithm();

	const SetUpParams& setup() const;
	void initialize();

	// evaluate the current population
	void evaluate();

	const vector<Solution*>& current_solutions() const;

	unsigned double global_best_cost() const;

	Solution& solution(const unsigned int index) const;

	Solution& global_best_solution() const;

	// main loop of the algorithm 
	void evolution();

};

#endif
