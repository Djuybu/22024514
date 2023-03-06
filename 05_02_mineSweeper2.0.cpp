//Minesweeper 2.0:
//Quét các ô xung quanh ô ng dùng chọn
//Đếm số mìn xung quanh ô --> hiện ra số

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cmath>

using namespace std;

//map used by the game:
vector<vector<string>> map;

//length and width
int a, b;

//number of bombs;
int bombNum;

//bomb coordinates
vector<int> bombX;
vector<int> bombY;

//coordnates checked
vector<int> flagX;
vector<int> flagY;

//count the time guesed:
int count;

//game condition:
bool quit = false;

bool victory = false;

//functions

//print the tutorials:
void tutorPrint();

//draw map for the 1st time:
void drawMap(int a, int b, vector<vector<string>>& map);

//initialize bombs:
void bombSetup(int n, vector<int>& bombX, vector<int>& bombY, int a, int b);

//print maps:
void printMap(int a, int b, vector<vector<string>>& map);

//update maps after user guessing:
int updateMap(int a, int b, vector<vector<string>>& map);

//count distance between bombs and the button
void countDistance(int x, int y, vector<vector<string>>& map, vector<int> bombX, vector<int> bombY);

void flagCheck( vector<int>flagX, vector<int>flagY, vector<int>bombX, vector<int>bombY );

void flag(int x, int y, vector<int>flagX, vector<int>flagY);

void deFlag(int x, int y, vector<int> flagX, vector<int> flagY);

//clear map and variable:
void clear();

void tutorPrint()
{
	cout << "Hello \n";
}

void printMap(int a, int b, vector<vector<string>>& map)
{
	for(int i = 0; i < b ; i++ )
	{
		for(int j = 0; j < a; j++ )
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
		
	}
}

void drawMap(int a, int b, vector<vector<string>>& map)
{
	map = vector<vector<string>>(b, vector<string>(a, "."));
	
    printMap(a, b, map);
}


void bombSetup(int n, vector<int>& bombX, vector<int>& bombY, int a, int b)
{
	//parse value to bombNum
	bombNum = n;
	
	for(int i = 0; i < n; i++)
	{
		//generate num
		int newX = rand() % a;
		int newY = rand() % b;
		
		//append bomb location:
		bombX.push_back(newX);
		bombY.push_back(newY);
	}
}

void updateMap(int x, int y, vector<vector<string>>& map, vector<int> bombX, vector<int> bombY)
{
	if(map[y][x] == "0")
	{
		printMap(a, b, map);
	}
	else
	{
		count++;
	    for (int i = 0; i < bombNum; i++)
	    {
	        if (x == bombX[i] && y == bombY[i])
	        {
	            quit = true;
	            map[y][x] = "X";
	        }
	    }
	
	    if (map[y][x] == ".") // Compare first character of the string
	    {
	        map[y][x] = "0";    
	        countDistance(x, y, map, bombX, bombY);
	    }
	    else if (map[y][x] != "0" &&  map[y][x] != ".") // Compare first character of the string
	    {
	        map[y][x] = "0";
	    }
	    printMap(a, b, map);
	}
}


void countDistance(int x, int y, vector<vector<string>>& map, vector<int> bombX, vector<int> bombY)
{
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            // count the number of bombs nearby
            int nearCount = 0;

            // size of bombX/Y vectors
            int size = bombX.size();
            if (i > a - 1 || j > b - 1 || i < 0 || j < 0)
            {
                // do nothing
            }
            else if (x == j && y == i)
            {
                // do nothing
            }
            else
            {
                for (int k = 0; k < size; k++)
                {
                    // by bombX first
                    if (j == bombX[k])
                    {
                        if (abs(bombY[k] - i) < 3)
                        {
                            nearCount++;
                        }
                    }

                    // by bombY first
                    if (i == bombY[k])
                    {
                        if (abs(bombX[k] - j) < 3 && (bombX[k] - j) != 0)
                        {
                            nearCount++;
                        }
                    }
                }

                if (nearCount == 0)
                {
                    if (map[i][j] != "0")
                    {
                        map[i][j] = "0";
                        countDistance(j, i, map, bombX, bombY);
                    }
                }
                else
                {
                    map[i][j] = to_string(nearCount);
                }
            }

            // reset nearCount for the next nearby cell
            nearCount = 0;
        }
    }
}

void flag(int x, int y, vector<int>flagX, vector<int>flagY)
{
	// truyen x,y:
	flagX.push_back(x);
	flagY.push_back(y);
	
	flagCheck( flagX, flagY, bombX, bombY );
	
}

void deFlag(int x, int y, vector<int> flagX, vector<int> flagY)
{
	bool Flag = false;
	
	int size = flagX.size();
	
	for(int i = 0; i < size; i++)
	{
		if( x == flagX[i] && y == flagY[i] )
		{
			flagX.erase(flagX.begin() + i);
			flagY.erase(flagY.begin() + i);
			
			flagX.shrink_to_fit();
			flagY.shrink_to_fit();
			
			i--; // decrement i to account for the shifted indices
		}
		Flag = true;
	}
	
	if(!Flag)
	{
		cout << "Invalid coordinate. ";
	}
}

void flagCheck(vector<int> flagX, vector<int> flagY, vector<int>bombX, vector<int>bombY )
{
	bool flag = true;
	
	int size = flagX.size();
	
	if( flagX.size() != bombX.size() )
	{
		return;
	}
	else
	{
		for(int i = 0; i < size; i++)
		{
			if(bombX[i] != flagX[i] || bombY[i] != flagY[i] )
			{
				flag = false;
			}
		}
	}
	
	if(flag)
	{
		quit = true;
		victory = true;
	}
	
}


int main()
{
	//game initializer:
	
	while(true)
	{
		cout << "**************************MINESWEEPEER2.0****************************** \n \n";
		cout << "Created by MMD - 22024514 \n \n";
		
		int begin;
		cout << "Press 0 to play the game, 1 to see tutorials, 2 to quit \n \n";
		cin >> begin;
		if(begin == 2)
		{
			
		}
		else if(begin == 0)
		{
			while(true)
			{
				cout << "The width of your map:  ";
				cin >> a;
				
				cout << "The height of your map: ";
				cin >> b;
				
				cout << "The number of bombs in the map: ";
				cin >> bombNum;
				
				//check condition:
				if(a <= 1 )
				{
					cout << "Invalid width. Please try again \n";
				}
				else if( b <= 1)
				{
					cout << "Inavlid width. Please try again \n";
				}
				else if(bombNum <=0 || bombNum > a * b)
				{
					cout << "Invalid bomb number. Please try again \n";
				}
				else
				{
					break;
				}
			}
			
			break;
			
		}else if(begin == 1)
		{
			tutorPrint();
		}
		else
		{
			cout << "Unknown command. Please try again";
		}
	}
					
		drawMap(a, b, map);
		bombSetup( bombNum, bombX, bombY, a, b );
			
	while ( !quit )
	{
		int mode;
		cout << "Press 1 to guess a coordinate, press 2 to flag/deflag a coordinate:  " ;
		cin >> mode;
		if(mode == 2)
		{
			mode  = 0;
			cout << "Press 1 to flag, press 2 to deflag: ";
			cin >> mode;
			
			if(mode == 1)
			{
				int x,y;
				cout << "The x coordinate: ";
				cin >> x;
				cout << "The y coordinate: ";
				cin >> y;
				flag(x, y, flagX, flagY);
			}
			else if(mode == 2)
			{
				int x,y;
				
				int size = bombX.size();
				
				cout << "All square you have flagged: ";
				for( int i = 0; i < size; i++)
				{
					cout<< flagX[i] << ", " << flagY[i] <<" ";
				}
				
				cout << "Type the x and y coordinate: ";
				cin >> x >> y;
				
				deFlag(x, y, flagX, flagY);
			}
		}
		else
		{
			cout << "Check the coordinate \n";
			int x, y;
			cout <<  "The x coodinate  ";
			cin >> x;
			cout << "The y coordinate ";
			cin >> y;
			
			if( x >= a || y >= b || x< 0 || y < 0 )
			{
				cout << "Invalid coordinate. ";
			}
			else
			{
				updateMap(x, y, map, bombX, bombY);
			}
		}
	}
	
	if(!victory)
	{
		cout << "You have lost the game. ";
	}
	else
	{
		cout << "Congratulations! You have won";
	}
}                           



