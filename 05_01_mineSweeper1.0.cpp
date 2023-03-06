#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

//mainloop cua game:
bool quit = false;

//maps used by the game
vector<vector<char>> map;
//length and height
int a;
int b;

//time played
int count = 0;

//the number of bomb:
int bombNum;

//all the bombs coordinate
vector<int> bombX;
vector<int> bombY;


//checked coordinate:
vector<int> checkedX;
vector<int> checkedY;

//print map
void printMap(int x, int y, vector<vector<char>>map);

//draw maps and set up bomb
void makeMap(int x, int y, int* a, int* b)
{
    map = vector<vector<char>>(y, vector<char>(x, '.'));
    *a = x;
    *b = y;
    printMap(*a, *b, map);
}


void printMap(int a, int b, vector<vector<char>>map)
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

void bombSetup(int n, vector<int>& bombX, vector<int>& bombY, int x, int y)
{
	bombNum = n;
	for(int i = 0; i < n; i++)
	{
		//generate num
		int newX = rand() % x;
		int newY = rand() % y;
		
		//append bomb location:
		bombX.push_back(newX);
		bombY.push_back(newY);
	}
}

//check and return values:
int updateMap(int x, int y, vector<vector<char>>& map, vector<int> bombX, vector<int> bombY){
    //0: tiep tuc, 1: end, thua, 2: end, thang
    count++;
    int size = bombX.size();
    
    for(int i = 0; i < size; i++)
    {
        if (x == bombX[i] && y == bombY[i])
        {
            map[y][x] = 'X';
            printMap(map.size(), map[0].size(), map);
            return 1;
        }
    }
    map[y][x] = 'O';
    
    if(count == a * b - bombNum)
    {
    	printMap(a, b, map);
    	return 2;
	}
	else
	{
		printMap(a, b, map);
    	return 0;
	}
    
}

void clearGame()
{
	//dua gia tri cua bien ve 0
	a = 0;
	b = 0;	
	
	//clear map cu:
	for(auto &v : map)
	{
		v.clear();
	}
	map.clear();
	
	//clear bomb:
	bombX.clear();
	bombY.clear();
	
	//set loop to be true
	quit = false;
}



int main()
{
	int n;
	cout << "********************* MINESWEEPER 1.0 ****************** \n";
	cout << "Welcome to the game! Press 1 to enter the game, 0 to exit the program ";
	cin >> n;
	
	if(n == 0)
	{
		quit = true;		
	}
	else
	{
		int x,y,n;
		
		while(true)
		{
			cout << "The width of your map: \n";
			cin >> x;
			cout << "The height of your map: \n";
			cin >> y;
			cout << "The number of bombs you want to put: \n";
			cin >> n;
						
			if(x <= 0 )
			{
				cout << "Inappropriate width. Again \n ";
			}
			if( y <= 0 )
			{
				cout << "Imappropriate height. Again \n";
			}
			if(n <= 0 )
			{
				cout << "Inappropriate bomb number. Again \n";
			}
			else break;
		}
		makeMap(x, y, &a, &b);
		bombSetup(n, bombX, bombY, x, y);
	}
	
	
	bool victory = false;
	
	int x;
	int y;
	//loop de choi game
	while( !quit )
	{
		cout << "Make your guess \n \n";
		
		cout << "The x coordination: ";
		cin >> x;
		
		cout << "The y coordination: ";
		cin >> y;
		
		int result = updateMap(x, y, map, bombX, bombY);
		if( result == 1 )
		{
			quit = true;
		}
		else if( result == 2 )
		{
			cout << "end";
			quit = true;
			victory = true;
		}
	}
	if( victory == true )
	{
		cout << "Congratulations! You have beat the game";
	}
	else
	{
		cout << "You have lost. Better luck next time";
	}
	cout << endl;
	
	int end;
	cout << "Press 0 to replay, press 1 to quit the game";
	cin >> end;
	
	if(end == 1)
	{
		quit = true;
	}else if(end == 0)
	{
		clearGame();
		main();
	}
	
	
}