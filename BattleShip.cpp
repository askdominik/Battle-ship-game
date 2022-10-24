#include <iostream>

using namespace std;

class BattleShips // used a class as will have 2 instances, one for computer, one for human
{
private:
	const static int rows = 10;
	const static int columns = 10;
	int coOrd;
	int maximumShips;
	int matrix[rows][columns];
public:
	BattleShips()
	{ // CLASS CONSTRUCTOR
		coOrd = 0;
		maximumShips = 10;
	}

	void ClearGrid() // simple function to clear the matrix.
	{
		for (int y = 0; y < rows; y++) // loops while y is less than rows, and increments y
		{
			for (int x = 0; x < columns; x++) // loops while x is less than columns and increments x
			{
				matrix[y][x] = 0; // sets each matrix row and column to 0
			}
		}
	}


	void ShowGrid()
	{
		cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
		cout << "-----------------------" << endl;
		for (int x = 0; x < rows; x++)
		{
			cout << coOrd << "| ";
			coOrd++;
			for (int y = 0; y < rows; y++)
			{
				cout << matrix[x][y] << " ";
			}
			cout << endl;
		}
	}

	int numberOfShips() // very similar to other methods but returns an int value, this will be to check the amount of ships left after the user inputs their data
	{
		int c = 0;
		for (int x = 0; x < rows; x++)
		{
			for (int y = 0; y < columns; y++)
			{
				if (matrix[x][y] == 1)
				{
					c++;
				}
			}
		}
		return c;
	}

	void setShips()
	{
		int ships = 0;
		while (ships < maximumShips)
		{
			int xPos = rand() % 10; 
			int yPos = rand() % 10; 

			if (matrix[xPos][yPos] != 1)
			{
				ships++;
				matrix[xPos][yPos] = 1; // sets position to 1
			}

		}

	}
	bool Attack(int _x, int _y) // makes a function with a boolean return type
	{
		if (matrix[_x][_y] == 1) // checks if the given parameters are a 'ship' on the matrix
		{
			matrix[_x][_y] = 2; // sets the position to 2 so the same position can not be re used
			return true; 
		}
		return false; 
	}
};



class Boards // makes another class called boards, will be used to initiate the game boards the user can see
{
private:
	const static int rows = 10; 
	const static int columns = 10;
	char grid[rows][columns]; 
public:
	void MakeBoards() // declares a function to make the game boards
	{
		for (int x = 0; x < rows; x++) 
		{
			for (int y = 0; y < columns; y++) 
			{
				grid[x][y] = '-'; // sets the element in the position to a '-'
			}
		}
	}

	void updateBoards(bool i, int x, int y) // makes a function to update the game boards, takes 3 paramaters. a boolean, and two integers
	{
		int xPos = x; 
		int yPos = y;

		if (i == true) 
		{
			grid[xPos][yPos] = 'Y'; // sets the element in the position to 'Y'
		}
		else
		{
			grid[xPos][yPos] = 'N'; // sets the element in the position to 'N'
		}
	}

	void PrintBoards() // makes a function to print the boards
	{
		int amt = 0; 

		cout << "  0 1 2 3 4 5 6 7 8 9" << endl; 
		for (int x = 0; x < rows; x++) { 
			cout << amt << " "; // outputs the amount variable to the console + a space
			amt++; 
			for (int y = 0; y < columns; y++) { 
				cout << grid[x][y] << " "; // outputs the element of the grid to the console, plus a space
			}
			cout << endl; 
		}
	}
};



int main() 
{
	char rerun; 

	do 
	{
		srand((unsigned)time(NULL)); // to prevent sequence repetition between runs
		BattleShips human; // the two objects
		BattleShips cpu;

		Boards humanBoard; // instantiates the Board objects
		Boards cpuBoard;

		human.ClearGrid(); // clears the existing matrix
		human.setShips(); // sets the position of the ships

		cpu.ClearGrid();  // clears the existing grid
		cpu.setShips();

		humanBoard.MakeBoards(); // makes the gameboards
		cpuBoard.MakeBoards();

		cout << "Your Board: " << endl;
		humanBoard.PrintBoards(); // prints the new boards
		cout << "CPU's Board" << endl;
		cpuBoard.PrintBoards();

		int position1, position2; // makes two integers for the positions to be stored inside
		char which; 
		int found = 0; 
		int toGo = 10; 

		int cpuFound = 0; // ^ does the same for the cpu counters
		int cpuToGet = 10;

		bool isTrue; // initializes two boolean variables.
		bool isTrueCpu;

		while (found < 10 || cpuFound < 10)
		{
			int cpuX = rand() % 10;
			int cpuY = rand() % 10;

			if (cpu.Attack(cpuX, cpuY)) // checks the boolean output of the Attack function for the cpu
			{
				isTrueCpu = true; 
				cpuFound++; 
				cpuToGet--; 
				cout << "The Computer has found one of your battleships at: " << "(" << cpuX << ", " << cpuY << ")" << endl; // outputs the position that the cpu found a battleship at.
			}
			else
			{
				isTrueCpu = false; 
				cout << "The Computer did not find a battleship this time" << endl; // outputs that the cpu did not find a battleship this time.
			}

			//------------------------------------------------------------------------------------------------------------

			position1 = 11;
			position2 = 11; 

			while (position1 > 9 || position2 > 9) 
			{
				if (cpuFound == 10 || found == 10)
				{
					break;
				}
				cout << "Please input the location on the grid you think a battleship is: "; 

				cin >> position1 >> position2;

				while (cin.fail()) // this will inintiate if the user enters a non integer input.
				{
					cin.clear(); // clears the cin.
					cin.ignore(); // ignores so it does not go in to an infinite loop
					cout << "not int, try again: "; cin >> position1 >> position2; 
				}
			}

			if (human.Attack(position1, position2)) // checks if the boolean value for the Attack function is true
			{
				isTrue = true; 
				found++; 
				toGo--; 
				cout << "You have found: " << found << " battleships, you have: " << toGo << " to go" << endl;
			}
			else 
			{
				isTrue = false; 
				cout << "there is no ship at that position, keep trying" << endl; 
			}

			cout << "There are: " << human.numberOfShips() << " left" << endl;
			cout << "would you like to surrender (y/n)?: "; cin >> which; 

			system("CLS"); 

			humanBoard.updateBoards(isTrue, position1, position2); // updates the boards
			cpuBoard.updateBoards(isTrueCpu, cpuX, cpuY);

			cout << "Your Board: " << endl;
			humanBoard.PrintBoards(); // prints the new boards
			cout << "CPU's Board" << endl;
			cpuBoard.PrintBoards();

			if (which == 'y') 
			{
				break; 
			}
			else if (found == 10 || cpuFound == 10)
			{
				break;
			}

		}


		cout << "Game Over!" << endl; 
		cout << "your grid: " << endl; 
		cout << "The number 2 represents ships that have been hit" << endl;
		human.ShowGrid(); // shows the human objects grid
		cout << "----------------------------------------------------" << endl;
		cout << "CPU's Grid" << endl;
		cpu.ShowGrid(); // shows the cpu grid to the user

		cout << "Would you like to rerun, or exit (r/e)"; cin >> rerun; 
	} while (rerun == 'r' || rerun == 'R'); 

	return 0;
}