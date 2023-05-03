#include "puzzle.h"
#include <string>

using namespace std;

Puzzle::Puzzle(string problem, string solution)
{
    this->problem = problem;
    this->solution = solution;
}

string Puzzle::getProblem()
{
    return problem;
}

bool Puzzle::checkSolution(string input)
{
    return input == solution;
}
