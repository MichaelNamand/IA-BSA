#include "algorithm.h"

Problem::Problem() :
	_dimension(30), LowerBound(-2.048), UpperBound(2.048)
{}

int Problem::dimension() const
{
	return _dimension;
}
istream& operator >> (istream& is, Problem& pbm) {
	int id;
	cout << "Function Id : ";
	is >> id;
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
	return is;
}
