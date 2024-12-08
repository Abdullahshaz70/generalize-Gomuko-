#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
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
void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
void box(int Dim,int r,int c) {
    int bh = ROWS / Dim;
    char sym = -37;
    for (int i = 0; i < bh; i++) {
        for (int j = 0; j < bh; j++) {
            if (i==0 or i==bh-1 or j==0 or j==bh-1) {
            gotoRowCol(i+r, j+c);
            cout << sym;
            }
        }
    }

}
void goti(int Dim, int r, int c, int n) {
    color(n+1);
    int bh = ROWS / Dim;
    char sym = -37;
    for (int i = 0; i < bh - 2; i++) {
        for (int j = 0; j < bh - 2; j++) {
            gotoRowCol(i + r - 1  , j + c -1 );
            cout << sym;
        }
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

    for (int i = 0; i < dim - 5; i++) {
        for (int j = 0; j < dim - 5; j++) {
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
bool iswin(char** B, char ps, int dim) {

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
void grid(int Dim) {
    int bh = ROWS / Dim;
    for (int i = 0; i < Dim; i++) {
        for (int j = 0; j < Dim; j++) {
            int r = bh * i;
            int c = bh * j;
            box(Dim, r, c);
        }
    }
}
void init(char**& B, int& Dim, int& NOF, string*& Nof, char*& ps) {
    Dim = 19;


    B = new char* [Dim];
    for (int i = 0; i < Dim; i++)
        B[i] = new char[Dim];


    for (int r = 0; r < Dim; r++) {
        for (int c = 0; c < Dim; c++) {
            B[r][c] = '-';
        }
    }

    NOF = 2; 
    Nof = new string[NOF];
    Nof[0] = "Human";
    Nof[1] = "Computer";

    ps = new char[2];
    ps[0] = '#';
    ps[1] = '&'; 
}

void display_turn(string* nop,int n) {
    color(n+3);
    gotoRowCol(50, 140);
    cout << nop[n] << "  turns!";
}
void remove_turn() {
    gotoRowCol(50, 140);
    cout <<"                    ";
}
bool isValid(char** B, int dim, int r, int c, int Dim , char n) {

    if (r % dim <= 1.5 or c % dim <= 1.5)
        return false;

    if (r > ROWS or c > COLS)
        return false;

    if (B[r / dim][c / dim] == '-')
        return true;

    return false;

}

void calculating_indexes(int r, int c, char**& B, int dim, char n) {
    int R = 0, C = 0;
    while (R <= r)
        R++;
    while (C <= c)
        C++;

    R /= dim;
    C /= dim;
    B[r / dim][c / dim] = n;
}
void calculating_goti_box_cpu(int r, int c, int dim, int turn, int Dim) {

    int R = 0, C = 0;
    R = r / dim;
    C = c / dim;
    R = R * dim + dim / 2;
    C = C * dim + dim / 2;
    gotoRowCol(R, C);
    goti(Dim, R - 1, C - 1, turn);

}
void calculating_goti_box(int r, int c, int dim, int turn, int Dim, char n) {

    int R = 0, C = 0;
    R = r / dim;
    C = c / dim;
    R = R * dim + dim / 2;
    C = C * dim + dim / 2;
    gotoRowCol(R - 1, C - 1);
    cout << n;

}
void checking_click(char**& B, int dim, int& r, int& c, int Dim, char n, int turn) {
    do {
        getRowColbyLeftClick(r, c);
    } while (!isValid(B, dim, r, c, Dim, n));
    if (!isValid(B, dim, r, c, Dim, n)) {
        gotoRowCol(60, 140);
        cout << "Wrong turn!";
        Sleep(500);
        gotoRowCol(60, 140);
        cout << "             ";
    }

    else {
        calculating_indexes(r, c, B, dim, n);
        calculating_goti_box(r, c, dim, turn,Dim ,n);
    }

}

void printarray(char** B, int Dim) {

    for (int i = 0; i < Dim; i++) {
        for (int j = 0; j < Dim; j++) {
            gotoRowCol(70 + i * 2, 140 + j);
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
}
int TurnChange(int& turn, int Nop)
{
    return turn = (turn + 1) % Nop;
}
bool check_array(char** B, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (B[i][j] == '-')
                return false;

        }
    }
    return true;
}

void computer_turn(char** B, int Dim, int box_dim, char* symbol_of_players, int& r, int& c) {
    char computer_symbol = symbol_of_players[1];
    char player_symbol = symbol_of_players[0];

    color(4);
    for (int i = 0; i < Dim; i++) {
        for (int j = 0; j < Dim; j++) {
            if (B[i][j] == '-') {
                B[i][j] = computer_symbol; 
                if (iswin(B, computer_symbol, Dim)) {
                    r = i;
                    c = j;
                    return; 
                }
                B[i][j] = '-'; 
            }
        }
    }

    for (int i = 0; i < Dim; i++) {
        for (int j = 0; j < Dim; j++) {
            if (B[i][j] == '-') {
                B[i][j] = player_symbol; 
                if (iswin(B, player_symbol, Dim)) {
                    r = i;
                    c = j;
                    B[i][j] = computer_symbol; 
                    return;
                }
                B[i][j] = '-'; 
            }
        }
    }
    for (int i = 0; i < Dim; i++) {
        for (int j = 0; j < Dim; j++) {
            if (B[i][j] == '-') {
                r = i;
                c = j;
                B[r][c] = computer_symbol;
                return;
            }
        }
    }
}

int main() {
    int Dim=19,number_of_players=2;
    char** B= nullptr;
    string* name_of_players=nullptr ;
    int r = 0, c = 0;
    int Turn = 0;
    char* symbol_of_players=nullptr;
    int* WC = new int[number_of_players];
    init(B, Dim, number_of_players, name_of_players, symbol_of_players);
 
    int box_dim = ROWS / Dim;
    system("cls");
    grid(Dim);
    do {
        Turn = 0;
        display_turn(name_of_players, Turn);
        checking_click(B,box_dim, r, c,Dim,symbol_of_players[Turn],Turn);
        printarray(B, Dim);
        remove_turn();
        if (iswin(B, symbol_of_players[Turn], Dim))
            break;
        Turn= TurnChange(Turn, number_of_players);
        
        if (Turn == 1) {
            computer_turn(B, Dim, 5, symbol_of_players, r, c);

            B[r][c] = symbol_of_players[Turn];
            gotoRowCol((r * 6) + 2, (c * 6) + 2);
            cout << *(*(B + r) + (c));
            if (iswin(B, symbol_of_players[Turn], Dim))
                break;
        }
        

        printarray(B, Dim);
    } while (true);
  
    system("cls");

    gotoRowCol(ROWS / 2, COLS / 2);
    cout << Turn << " WINS!" << endl;




    _getch();
	return 0;
}