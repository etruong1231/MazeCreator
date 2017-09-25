#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "vector"


using namespace std;

class EddieSolver: public MazeSolver
{
public:
//abstract class function that it deprives from
void solveMaze(const Maze& maze, MazeSolution& mazeSolution);

void fill_visited_vector(const Maze& maze);

//a recursive path taht will find it way towards the end
void recursive_path(int x, int y, const Maze& maze, MazeSolution& mazeSolution);

//checks the possible path
vector<Direction> check_possible_path(int x, int y, const Maze& maze);

void change_position(int& x, int& y, MazeSolution& mazeSolution);

private:
vector < vector <int> > point_visited;
};

#endif 
