#ifndef GENERATOR_HPP
#define GENERATOR _HPP

#include "MazeGenerator.hpp"
#include "Direction.hpp"
#include <vector>

using namespace std;


struct points{

    int x;
    int y;
};



class EddieGenerator: public MazeGenerator
{
public:


//constructor
EddieGenerator();
//generates the maze
void generateMaze(Maze& maze);

//need to fill in the vector of the maze

void makeMazeandMatrix(Maze& maze);

//need a recursive function taht will run to get a path
//the intial x and y is where it starts
void recursivePath(int x, int y, Maze& maze);

//need a random path generator that is possible path 
vector<Direction> possiblePath(int x, int y, Maze& maze);

Direction randomPath(vector<Direction> possible);
//change the x and y values
void changePosition(int& x, int& y,Direction route);

~EddieGenerator();
private:

vector < vector<int> > mazeMatrix;
vector <points> routing;
};

#endif 
