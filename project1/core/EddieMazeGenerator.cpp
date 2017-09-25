#include "EddieMazeGenerator.hpp"
#include "MazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include "Maze.hpp"
#include "Direction.hpp"
#include <random>

using namespace std;
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, EddieGenerator, "Eddie's Algorithm (Required)");


EddieGenerator:: EddieGenerator(){}


void EddieGenerator:: generateMaze(Maze& maze)
{  
   
   //now need to resize matrix and fill the matrix in
   makeMazeandMatrix(maze);
   // creates the path recursively
   recursivePath(0,0,maze);
}

void EddieGenerator:: makeMazeandMatrix(Maze& maze)
{
    //build all walls
    maze.addAllWalls();
    //needs to resize the vector accordinly to the maze size
   int new_rows = maze.getWidth();
   int new_cols = maze.getHeight();
   mazeMatrix.resize(new_rows);
   for(auto &row: mazeMatrix)
           row.resize(new_cols);
   //need to fill the maze Matrix 0 for non-visited, 1 for visited
   for(int x = 0; x < new_rows; ++x)
   {
        for(int y = 0; y < new_cols; ++y)
        {
            mazeMatrix[x][y] = 0;
        }

   }
   cout << maze.getHeight() <<"," << maze.getWidth() << endl;
}


void EddieGenerator:: recursivePath(int x, int y, Maze& maze)
{

//change the vector spot as visited
mazeMatrix[x][y] = 1;

//checks for possible path
vector<Direction> possibleRoute = possiblePath(x,y,maze);
    
if(possibleRoute.size() > 0)
{
        //shuffle the possible routes and get one back
    Direction randomRoute = randomPath(possibleRoute);
    // once you have the route of the random gonna move the path
    int old_x = x;
    int old_y = y;
    changePosition(x,y,randomRoute);
        /*if(randomRoute == Direction::up)
        cout << "Going up"<<endl ;
        if(randomRoute == Direction::down)
        cout << "Going Down"<<endl;
        if(randomRoute == Direction::left)
        cout << "Going left" << endl;
        if(randomRoute == Direction::right)
        cout << "Going right" << endl; */
    maze.removeWall(old_x,old_y,randomRoute);
        //then call the function recursively with new x and y
    recursivePath(x,y,maze);
    
    
    //once it gets our of the one recursive, itll go backwards to check other path
recursivePath(old_x,old_y,maze);    
}
}


vector<Direction> EddieGenerator:: possiblePath(int x, int y, Maze& maze)
{
    //need a vector that holds the possible routes
    vector <Direction> pathway;
    //check up directions ensure that it is inbound and if it has not been visited
    if(y-1 >= 0 && mazeMatrix[x][y-1] == 0)
         pathway.push_back(Direction::up);
    //check if the down direction
    if(y+1 < maze.getHeight() && mazeMatrix[x][y+1] == 0)
       pathway.push_back(Direction::down);
    //check the left direction
    if(x-1 >= 0 && mazeMatrix[x-1][y] == 0)
        pathway.push_back(Direction::left);
    //check the right direction
    if(x+1 < maze.getWidth() && mazeMatrix[x+1][y] == 0 )   
        pathway.push_back(Direction::right);
    
    return pathway;

}

//gets a random possible direction
Direction EddieGenerator:: randomPath(vector<Direction> possible)
{
    random_device device;
    default_random_engine engine{device()};
    if(possible.size() == 1)
        return possible[0];
    else{       
        int possiblePath = possible.size() - 1;
        uniform_int_distribution<int> distribution(0,possiblePath);
        int path = distribution(engine);
        return possible[path];
        }
}


void EddieGenerator::changePosition(int& x, int& y, Direction route) 
{
    if(route == Direction::up){ y-=1;}
    else if(route == Direction::down){y+=1;}
    else if(route == Direction::left){x-=1;}
    else if(route == Direction::right){x+=1;}

}

EddieGenerator::~EddieGenerator()
{}
