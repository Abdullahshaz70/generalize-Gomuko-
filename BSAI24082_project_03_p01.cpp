#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<math.h>
#include<iomanip>
using namespace std;
#define ROWS 130
#define COLS 130

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void color(int textColor, int backgroundColor = 0) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = (backgroundColor << 4) | (textColor & 0x0F);
	SetConsoleTextAttribute(hConsole, color);
}
void init(char**& B, int& Dim, int& NOF , string*& Nof,char*& ps) {
	cout << "Enter dimensions: ";
	cin >> Dim;
	B = new char*[Dim];

	for (int i = 0; i < Dim; i++)
		B[i] = new char[Dim];

	for (int r = 0; r < Dim; r++) {
		for (int c = 0; c < Dim; c++) {
			B[r][c] = '-';
		}
	}

	cout << endl;

	do {
		cout << "\nEnter number of players: ";
		cin >> NOF;
		if (NOF < 2)
			cout << "\nEnter atleast 2 players:";

	} while (NOF < 2);

	Nof = new string[NOF];

	for (int i = 0; i < NOF; i++) {
		string n;
		cout << "\nEnter name of " << i + 1 << " :";
		cin >> n;
		Nof[i] = n;
	}

	ps = new char[NOF];
	for (int i = 0; i < NOF; i++)
	{
		char sym;
		cout << "\nEnter symbol (goti) of " << i + 1 << " player:";
		cin >> sym;
		ps[i] = sym;
	}

}
void display_board(char** B , int Dim) {

	B = new char*[Dim];

	for (int i = 0; i < Dim; i++)
		B[i] = new char[Dim];

	for (int r = 0; r < Dim; r++) {
		for (int c = 0; c < Dim; c++) {
			cout <<setw(4)<< B[r][c] << " ";
		}
				cout << endl;
	}

}
void printing_slash(int dim) {
	int boxHeight = ROWS / dim;
	int boxWidth = COLS / dim;
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			
			int centerRow = r * boxHeight + boxHeight / 2;
			int centerCol = c * boxWidth + boxWidth / 2;
			gotoRowCol(centerRow, centerCol);
			cout << "-";
		}
	}
}
void box(int sr, int sc, int dim) {
	char sym = -37;
	int boxHeight = ROWS / dim;
	int boxWidth = COLS / dim; 

	for (int r = 0; r < boxHeight; r++) {
		for (int c = 0; c < boxWidth; c++) {
			gotoRowCol(sr + r, sc + c); 
			if (r == 0 or r == boxHeight - 1 or c == 0 or c == boxWidth - 1)
				cout << sym;
		}
	}
}
void grid_maker(int dim) {
	int boxHeight = ROWS / dim;
	int boxWidth = COLS / dim; 

	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			int sr = r * boxHeight;
			int sc = c * boxWidth; 
			box(sr, sc, dim); 
		}
	}
}
void display_turn(string nop , char ps,int c) {
	color(c + 10);
	gotoRowCol(31,150);
	cout << nop << " turns! " << " and the symbol is " << ps << endl;
}
void remove_turn() {
	
	gotoRowCol(31, 150);
	cout << "                                                        "  << endl;
}

void calculating_indexes(int r, int c, char**& B,int dim, char n) {
	int R = 0, C = 0;
	while (R <= r) 
		R++;
	while(C <= c)
		C++;

	B[R/dim][C/dim] = n;
}
bool isvalid(char**&B , int r , int c,int dim) {
	if (B[r/dim][c/dim] == '-')
		return true;

	if( r % dim == 0 and c % dim ==0)
	return false;

	return false;
}
void printarray(char** B, int Dim) {
	
	for (int i = 0; i < Dim; i++) {
		for (int j = 0; j < Dim; j++) {
			gotoRowCol(70+i*2, 140+j);
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
}

bool vertical_win(char** B, char ps, int dim) {
	
	for (int i = 0; i < dim; i++) {
		int count = 0;
		for (int j = 0; j < dim; j++) {
			if (B[j][i] == ps) {
				count++;
				if (count == 5)
					return true;
			}
			else
				count = 0;
		}
	}

	return false;
}
bool horizontal_win(char** B, char ps, int dim) {
	
	for (int i = 0; i < dim; i++) {
		int count = 0;
		for (int j = 0; j < dim; j++) {
			if (B[i][j] == ps) {
				count++;
			if (count == 5)
				return true;
			}
			else
				count = 0;
		}
	}

	return false;
}
bool digonal_right(char** B, char ps, int dim) {

	for (int i = 0; i < dim-5; i++) {
		for (int j = 0; j < dim-5; j++) {
			int count = 0;
			if (B[i][j] == ps) {
				for (int k = 0; k < 5; k++)
					if (B[i + k][j + k] == ps) {
						count++;
						if (count == 5)
							return true;
					}
					else
						count = 0;

			}
		}
	}
	return false;
}
bool digonal_left(char** B, char ps, int dim) {

	for (int i = 0; i < dim - 5; i++) {
		for (int j = 4; j < dim; j++) {
			int count = 0;
			if (B[i][j] == ps) {
				for (int k = 0; k < 5; k++)
					if (B[i + k][j - k] == ps) {
						count++;
						if (count == 5)
							return true;
					}
					else
						count = 0;

			}
		}
	}
	return false;
}
bool iswin(char** B, char ps , int dim) {

	if (vertical_win(B, ps, dim))
		return true;
	else if (horizontal_win(B, ps, dim))
		return true;
	else if (digonal_left(B, ps, dim))
		return true;
	else if (digonal_right(B, ps, dim))
		return true;

	return false;
}
void print_symbol(char ps, int c) {
	color(c+10);
	cout << ps;
}
bool check_array(char** B,int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (B[i][j] == '-')
				return false;

		}
	}
	return true;
}
void printStartButton() {



	cout << "--------------------------------------" << endl;
	cout << "                                                                 |                                    |" << endl;
	cout << "                                                                 |  *****  *****  *****  *****  ***** |" << endl;
	cout << "                                                                 |  *        *    *   *  *   *    *   |" << endl;
	cout << "                                                                 |  *****    *    *****  *****    *   |" << endl;
	cout << "                                                                 |      *    *    *   *  *   *    *   |" << endl;
	cout << "                                                                 |  *****    *    *   *  *   *    *   |" << endl;
	cout << "                                                                 |                                    |" << endl;
	cout << "                                                                  -------------------------------------" << endl;

}
int main() {
	int Dim, ri, ci,no_of_players;
	char** B ;
	string* Names_of_players;
	char* player_symbol;
	int Turn = 0;
	int r, c;

	gotoRowCol(ROWS / 2, COLS / 2);
	printStartButton();
	do {
		getRowColbyLeftClick(r, c);
	} while (!(r >= 60 and r <= 78 and c >= 50 and c <= 87));
	system("cls");
	init(B, Dim, no_of_players, Names_of_players, player_symbol);
	float dim = 130 / Dim;
	system("cls");
	grid_maker(Dim);

	do {
			
			for (Turn = 0; Turn < no_of_players; Turn++) {
				display_turn(Names_of_players[Turn], player_symbol[Turn],Turn);

				start:
				getRowColbyLeftClick(ri, ci);
				if (isvalid(B, ri, ci, dim)) {
					gotoRowCol(40, 120);
					cout << "              ";
					calculating_indexes(ri, ci, B, dim, player_symbol[Turn]);
					printarray(B, Dim);
					gotoRowCol(ri, ci);
					print_symbol(player_symbol[Turn], Turn);
					
				}
				else {
					gotoRowCol(40, 120);
					cout << "wrong input";
					goto start;
				}
				
				if (iswin(B, player_symbol[Turn], Dim)) {
					system("pause");
					system("cls");
					gotoRowCol(ROWS / 2, COLS / 2);
					cout << "hurrah!";
					cout << endl;
					gotoRowCol(ROWS / 2 + 1, COLS / 2);
					cout << Names_of_players[Turn] << " win" << endl;
					return 0;
				}

				if (check_array(B, Dim)) {
					system("pause");
					system("cls");
					gotoRowCol(ROWS / 2, COLS / 2);
					cout << "DRAW!";
					return 0;
				}

				remove_turn();
	
			}
		
	} while (true);

	


	_getch();
	return 0;
}













//bool is_valid_position(char** Board, int row, int col, int size, char player_symbol)
//{
//    if ((*(*(Board + row) + col)) == player_symbol)
//        return false;
//    if (row < 0 || row >= size || col < 0 || col >= size)
//        return false;
//    if ((*(*(Board + row) + col)) == '-')
//        return true;
//    return false;
//}
//bool check_horizontal_win(char** Board, int row, int col, char sym, int size, int win_count)
//{
//    int count = 0;
//    if (col + win_count > size)
//        return false;
//
//    for (int ci = col; ci < col + win_count; ci++)
//    {
//        if ((*(*(Board + row) + ci)) == sym)
//            count++;
//    }
//
//    return count == win_count;
//}
//bool check_vertical_win(char** Board, int row, int col, char sym, int size, int win_count)
//{
//    if (row + win_count > size)
//        return false;
//
//    for (int ri = row; ri < row + win_count; ri++)
//    {
//        if ((*(*(Board + ri) + col)) != sym)
//            return false;
//    }
//
//    return true;
//}
//bool check_diagonal_left_win(char** Board, int row, int col, char sym, int size, int win_count)
//{
//    if (row + win_count > size)
//        return false;
//
//    for (int i = 0; i < win_count; i++)
//    {
//        if ((*(*(Board + (row + i)) + (col - i))) != sym)
//            return false;
//    }
//
//    return true;
//}
//bool check_diagonal_right_win(char** Board, int row, int col, char sym, int size, int win_count)
//{
//    if (row + win_count > size)
//        return false;
//
//    for (int i = 0; i < win_count; i++)
//    {
//        if ((*(*(Board + (row + i)) + (col + i))) != sym)
//            return false;
//    }
//
//    return true;
//}
//bool is_winning_move(char** Board, int size, int row, int col, char sym, int win_count)
//{
//    return check_horizontal_win(Board, row, col, sym, size, win_count) ||
//        check_vertical_win(Board, row, col, sym, size, win_count) ||
//        check_diagonal_right_win(Board, row, col, sym, size, win_count) ||
//        check_diagonal_left_win(Board, row, col, sym, size, win_count);
//}
//bool check_win(char** Board, int size, char player_symbols[], int turn, int win_count)
//{
//    for (int row = 0; row < size; row++)
//    {
//        for (int col = 0; col < size; col++)
//        {
//            if (is_winning_move(Board, size, row, col, player_symbols[turn], win_count))
//                return true;
//        }
//    }
//    return false;
//}
//bool can_win_at_position(char** Board, int size, char player_symbol, int win_count, int row, int col, int& position_row, int& position_col)
//{
//    if (check_horizontal_win(Board, row, col, player_symbol, size, win_count))
//    {
//        if (is_valid_position(Board, row, col + win_count, size, player_symbol))
//        {
//            position_row = row;
//            position_col = col + win_count;
//            return true;
//        }
//        else if (is_valid_position(Board, row, col - 1, size, player_symbol))
//        {
//            position_row = row;
//            position_col = col - 1;
//            return true;
//        }
//    }
//
//    if (check_vertical_win(Board, row, col, player_symbol, size, win_count))
//    {
//        if (is_valid_position(Board, row + win_count, col, size, player_symbol))
//        {
//            position_row = row + win_count;
//            position_col = col;
//            return true;
//        }
//        else if (is_valid_position(Board, row - 1, col, size, player_symbol))
//        {
//            position_row = row - 1;
//            position_col = col;
//            return true;
//        }
//    }
//
//    if (check_diagonal_right_win(Board, row, col, player_symbol, size, win_count))
//    {
//        if (is_valid_position(Board, row + win_count, col + win_count, size, player_symbol))
//        {
//            position_row = row + win_count;
//            position_col = col + win_count;
//            return true;
//        }
//        else if (is_valid_position(Board, row - 1, col - 1, size, player_symbol))
//        {
//            position_row = row - 1;
//            position_col = col - 1;
//            return true;
//        }
//    }
//
//    if (check_diagonal_left_win(Board, row, col, player_symbol, size, win_count))
//    {
//        if (is_valid_position(Board, row + win_count, col - win_count, size, player_symbol))
//        {
//            position_row = row + win_count;
//            position_col = col - win_count;
//            return true;
//        }
//        else if (is_valid_position(Board, row - 1, col + 1, size, player_symbol))
//        {
//            position_row = row - 1;
//            position_col = col + 1;
//            return true;
//        }
//    }
//
//    return false;
//}
//bool find_player_winning_positions(char** Board, int size, char player_symbol, int win_count, int& position_row, int& position_col, int& max_win_count)
//{
//    for (int row = 0; row < size; row++)
//    {
//        for (int col = 0; col < size; col++)
//        {
//            for (int w = win_count - 1; w > 1; w--)
//            {
//                if (can_win_at_position(Board, size, player_symbol, w, row, col, position_row, position_col))
//                {
//                    max_win_count = w;
//                    return true;
//                }
//            }
//        }
//    }
//
//    for (int row = 0; row < size; row++)
//    {
//        for (int col = 0; col < size; col++)
//        {
//            if (is_valid_position(Board, row, col, size, player_symbol))
//            {
//                position_row = row;
//                position_col = col;
//                max_win_count = 1;
//                return true;
//            }
//        }
//    }
//    return false;
//}
//void computer_turn(char** Board, int size, int win_count, char* symbols, int& position_row, int& position_col)
//{
//    int computer_max_win_count = 0;
//    int computer_position_row = 0;
//    int computer_position_col = 0;
//    bool computer_can_win = find_player_winning_positions(Board, size, symbols[1], win_count, computer_position_row, computer_position_col, computer_max_win_count);
//
//    int user_max_win_count = 0;
//    int user_position_row = 0;
//    int user_position_col = 0;
//    bool user_can_win = find_player_winning_positions(Board, size, symbols[0], win_count, user_position_row, user_position_col, user_max_win_count);
//
//    if (computer_max_win_count >= user_max_win_count || user_max_win_count == 1)
//    {
//        position_row = computer_position_row;
//        position_col = computer_position_col;
//    }
//    else
//    {
//        position_row = user_position_row;
//        position_col = user_position_col;
//    }
//}
