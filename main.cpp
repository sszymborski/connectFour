#include <iostream>

using namespace std;

int board[7][6];    // 7 fields horizontally and 6 fields vertically    //0 when empty, 1 when red player, -1 when yellow player

bool checkWinNow()   // tests whether someone has won on the board at the moment
{
    int actual;
    for(int i = 0; i < 7; ++i)   // tests 4 fields vertically to up
        for(int j = 0; j < 3; ++j)
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
    for(int i = 0; i < 4; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < 6; ++j)
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
    for(int i = 0; i < 4; ++i)   // tests 4 fields across to up and right
        for(int j = 0; j < 3; ++j)
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
    for(int i = 0; i < 4; ++i)   // tests 4 fields across to down and right
        for(int j = 3; j < 6; ++j)
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
    for(int i = 0; i < 7; ++i)
        for(int j = 0; j < 6; ++j)
            board[i][j]=0;
}

int main()
{
    cout << "Hello world!" << endl;
    clearField();
    if(checkWinNow())
        cout << "Win" << endl;
    return 0;
}
