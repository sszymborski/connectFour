#include <iostream>

using namespace std;

int board[6][7];    // 7 fields horizontally and 6 fields vertically    //0 when empty, 1 when red player, -1 when yellow player

bool checkWinNow()   // tests whether someone has won on the board at the moment
{
    int actual;
    for(int i = 0; i < 6; ++i)   // tests 4 fields vertically to up
        for(int j = 0; j < 4; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i][j+1] && actual == board[i][j+2] && actual == board[i][j+3])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i << "x" << j+1 <<", "
                    << i << "x" << j+2 <<", "
                    << i << "x" << j+3 << "."
                    << endl;
                    return true;
                }
            }
    for(int i = 0; i < 3; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < 7; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j] && actual == board[i+2][j] && actual == board[i+3][j])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j <<", "
                    << i+2 << "x" << j <<", "
                    << i+3 << "x" << j << "."
                    << endl;
                    return true;
                }
            }
    for(int i = 0; i < 3; ++i)   // tests 4 fields across to up and right
        for(int j = 0; j < 4; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j+1] && actual == board[i+2][j+2] && actual == board[i+3][j+3])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j+1 <<", "
                    << i+2 << "x" << j+2 <<", "
                    << i+3 << "x" << j+3 << "."
                    << endl;
                    return true;
                }
            }
    for(int i = 0; i < 3; ++i)   // tests 4 fields across to down and right
        for(int j = 3; j < 7; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j-1] && actual == board[i+2][j-2] && actual == board[i+3][j-3])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j-1 <<", "
                    << i+2 << "x" << j-2 <<", "
                    << i+3 << "x" << j-3 << "."
                    << endl;
                    return true;
                }
            }

    return false;
}

void clearField()
{
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 7; ++j)
            board[i][j]=0;
}

void showWindow()
{
    for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
            if(board[i][j]==0)
                cout << "O";
            if(board[i][j]==1)
                cout << "R";
            if(board[i][j] == -1)
                cout << "Y";
            cout << "\t";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Hello world!" << endl;
    clearField();
    board[1][1] = 1;
    board[2][2] = 1;
    board[3][3] = 1;
    board[4][4] = 1;



    if(checkWinNow())
        cout << "Win" << endl;
    showWindow();
    return 0;
}
