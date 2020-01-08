#include "algorithm.h"

Problem::Problem() :
	_dimension(30), LowerBound(-2.048), UpperBound(2.048)
{}

int Problem::dimension() const
{
	return _dimension;
}