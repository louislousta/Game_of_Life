
#include <iostream>
#include <vector>
#include<random>
#include<utility>
#include<time.h>

	const int width{ 30 };
	const int height{ 30 };

std::vector<std::vector<int>> dead_state(int w, int h)  // creates a grid of dead cells
{
	std::vector<std::vector<int>> board_state(h, (std::vector<int>(w, 0)));
	return board_state;
}

std::vector<std::vector<int>> random_state(int width, int height)  // populates the grid with 1's and 0's 
{
	std::vector<std::vector<int>> board_state = dead_state(width, height);
	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			int state = (1 + (rand() % 2));
			if (state < 2)
			{
				board_state[i][j] = 0;
			}
			else
			{
				board_state[i][j] = 1;
			}
		}
	
	}
	return board_state;

}

void render(std::vector<std::vector<int>> board_state)   // takes a board_state and renders onscreen
{
	
	for (int i = 0; i < size(board_state); i++)
	{
	
		for (int j = 0; j < size(board_state[i]); j++)
		{
			if ((board_state[i][j]) < 1)
			{
				std::cout << ' ';
			}
			else
			{
				std::cout << '#';
			}
		}
		std::cout << std::endl;
	}
}


int check_neighbors(std::vector<std::vector<int>>board, int y, int x) // for given coords x,y returns no. of alive neighbors
{
	int neighbors{};
	int i = y - 1;
	
	for (i; i <= y + 1; i++)
	{
		for (int j=x-1; j <= x + 1; j++)
		{
			if ((i < 0) || (i >= size(board)) || (j < 0) || (j >= size(board))) 
			{
				continue;
			}
			if (board[i][j] == 1)
			{
				neighbors++;
			}
		}
	}
	if (board[y][x] == 1)
	{
		neighbors--;
	}
	return neighbors;
}
	


std::vector<std::vector<int>> next_board_state(std::vector<std::vector<int>>prev_board_state) //main rules for LIFE:
/* A live cell with 0 or 1 neighbors becomes dead due to underpopn
 * A live cell with 2 or 3 neighbors stays alive 
 * A live cell with more than 3 neighbors dies overpopn
 * A dead cell with exactly 3 neighbors becomes alive */
{
	std::vector<std::vector<int>> new_board_state = dead_state(width, height);
	for (int i = 0; i < size(prev_board_state); i++)
	{

		for (int j = 0; j < size(prev_board_state[i]); j++)
		{
			int neighbors = check_neighbors(prev_board_state, i, j);
			if ((prev_board_state[i][j]) < 1)  //if current cell is dead
			{
				if (neighbors == 3)
				{
					new_board_state[i][j] = 1;
				}
		
			}
			else  // current cell is alive 
			{
				if (neighbors < 2) 
				{
					new_board_state[i][j] = 0; //underpopn
				}
				else if (neighbors > 3)
				{
					new_board_state[i][j] = 0; //overpopn
				}
				else
				{
					new_board_state[i][j] = 1;  //just right
				}
			}
		}
		
	}
	return new_board_state;
}




int main()
{	
	srand((unsigned)time(0));

	std::vector<std::vector<int>>init_board_state = random_state(width, height);


		std::vector<std::vector<int>>new_board_state = next_board_state(init_board_state);
		std::vector<std::vector<int>>prev_board_state = next_board_state(init_board_state);
		while (true)
		{
			render(prev_board_state);
			new_board_state = next_board_state(prev_board_state);
			prev_board_state = new_board_state;
			
		}
	
	


}