#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>

using namespace std;

class Puzzle
{
public:
    Puzzle(string problem, string solution);
    bool checkSolution(string input);
    string getProblem();

private:
    string solution;
    string problem;
};

#endif // PUZZLE_H
