#include<iostream>

using namespace std;

//enum Direction{N,S,E,W};

struct Node
{
	bool Left,Right,Forward;
};		//if a path to the left,right,forward exists 

//Direction facing;

class Orientation
{
	public:
		int degree;
		Orientation()
		{
			degree=90;
		}
		void check()
		{
			degree=degree%360;
		}
};			//Which angle they are facing

Orientation facing;

//facing.degree=90;
 
const int mazeSize=100;				//maze size
bool maze[mazeSize][mazeSize];			//maze
const int StartX=mazeSize/2,StartY=mazeSize/2;				//starting at the middle of the array
int currentx=StartX,currenty=StartY;					//current=start

bool isTraversing=true,isBackTracking=false;		//if it is backtracking or traversing

void initializeMaze()
{
	for(int i=0;i<mazeSize;i++)
		for(int j=0;j<mazeSize;j++)
			maze[i][j]=0;
}		//initializing maze

bool Record(bool input)
{
	if(maze[currentx][currenty]==true)			//if it has been to this co-ordinate then loop detected; should backTrack 
		return true ;
	if(facing.degree==90)						//change the currnt position based on which way they are facing
		currenty++;
	else if(facing.degree==270)
		currenty--;
	else if(facing.degree==0)
		currentx++;
	else if(facing.degree==180)
		currentx--;
	maze[currentx][currenty]=true;				//marking the path in matrix maze
	
	return false;			//loop not detected
}	   

void backTrack()
{
	isTraversing=false;
	isBackTracking=true;
	turnBack();
}			//	   //backTracking


bool NodeFound(Node node)			//returns if it has reached the starting point
{	
	if((currentx==StartX)&&(currenty==StartY))		//if it has returned to starting position
		return true;
	
	if(isTraversing==true)							// if it is traversing
	{
		if(node.Left==true)
		{
			turnLeft();
			return false;
		}

		else if(node.Forward==true)
		{
			return false;
		}
		else if(node.Right==true)
		{
			turnRight();
			return false;
		}
		else 
		{
			turnBack();

			isTraversing=false;
			isBackTracking=true;
			return false;
		}
	}
	else											// if it is backTracking
	{
	/*	if((currentx-1==0)&&(node.West==true))
			{
				turnLeft();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}

		if((currentx+1==0)&&(node.East==true))
			{
				turnLeft();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}*/
		if(facing.degree==90)							//check other unvisited paths while back tracking 
		{
			if((currentx-1==0)&&(node.Left==true))
			{
				turnLeft();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}

			if((currentx+1==0)&&(node.Right==true))
			{
				turnRight();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}
		}
		else if(facing.degree==270)
		{
			if((currentx+1==0)&&(node.Left==true))
			{
				turnLeft();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}

			if((currentx-1==0)&&(node.Right==true))
			{
				turnRight();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}
		}
		else if(facing.degree==0)
		{
			if((currenty+1==0)&&(node.Left==true))
			{
				turnLeft();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}

			if((currenty-1==0)&&(node.Right==true))
			{
				turnRight();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}
		}
		else if(facing.degree==180)
		{
			if((currenty-1==0)&&(node.Left==true))
			{
				turnLeft();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}

			if((currenty+1==0)&&(node.Right==true))
			{
				turnRight();
				isBackTracking=false;
				isTraversing=true;
				return false;
			}
		}
	}
}