

#include "EddieMazeSolver.hpp"
#include <iostream>
#include <ics46/factory/DynamicFactory.hpp>
#include "Direction.hpp"
#include "vector"
#include "utility"


using namespace std;
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, EddieSolver, "Eddie's Algorithm (Required)");


void EddieSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
//makes a vector of ints that keeps track of what has been visited
fill_visited_vector(maze);
//recursive function to solve the maze
recursive_path(0,0, maze, mazeSolution);


}
void EddieSolver::fill_visited_vector(const Maze& maze)
{
    //set up the vector according to the maze size
    int new_rows = maze.getWidth();
    int new_cols = maze.getHeight();
    
    point_visited.resize(new_rows);
    for(auto & rows: point_visited)
        rows.resize(new_cols);

    for(int x = 0; x< new_rows; ++x)
    {
        for(int y= 0; y < new_cols; ++y)
        {
            point_visited[x][y] = 0;
        }


    }

}

void EddieSolver:: recursive_path(int x, int y, const Maze& maze, MazeSolution& mazeSolution)
{
    //mark the point visited
    point_visited[x][y] = 1;
   
        //gets all possible direction
    if(!mazeSolution.isComplete())
    {   
        vector<Direction> routes  = check_possible_path(x,y,maze);
        //if it has a route itll check that way
        if(routes.size() > 0)
        {   
           // cout << routes.size() << endl;
            mazeSolution.extend(routes[0]);
            //change position to new spot
            change_position(x,y,mazeSolution);
            //continue the path
            recursive_path(x,y,maze, mazeSolution);
            //gets out of the recursive function then checks if it is complete if not backup
            if(!mazeSolution.isComplete())
            {
                mazeSolution.backUp();
                //get the original position/backup position
                change_position(x,y, mazeSolution);
                //call recursive again for backtrack
                recursive_path(x,y,maze,mazeSolution);

            }
        }
    }

   

}

vector<Direction> EddieSolver:: check_possible_path(int x, int y, const Maze& maze)
{
    vector <Direction> possible_path;
    //checks if there a path that has not been visited and has no wall
    if(x+1 < maze.getWidth() && !maze.wallExists(x+1,y,Direction::left) &&point_visited[x+1][y] == 0)
        possible_path.push_back(Direction::right);
    if(y+1 < maze.getHeight() && !maze.wallExists(x,y+1,Direction::up) && point_visited[x][y+1] == 0)
        possible_path.push_back(Direction::down);
    if(y-1 >= 0 && !maze.wallExists(x,(y-1), Direction::down) && point_visited[x][y-1] == 0 )
        possible_path.push_back(Direction::up);
    if(x-1 >= 0 && !maze.wallExists((x-1),y, Direction::right) && point_visited[x-1][y] == 0)
        possible_path.push_back(Direction::left);
    //returns all possible path 
    return possible_path;
}

void EddieSolver:: change_position(int& x, int& y, MazeSolution& mazeSolution)
{
    //change position according to the movement
    x = mazeSolution.getCurrentCell().first;
    y = mazeSolution.getCurrentCell().second;


}




