#include "AI.h"

AI::AI()
{
    cout << "hej, tu AI" << endl;
    srand( time( NULL ) );
}

AI::~AI()
{
    //dtor
}

AI::doRandMove()
{
    int number = rand();
    cout << "Wylosowano: " << number << endl;
    int goodNumber = number%7;
    cout << "Pionek na: " << goodNumber << endl;
    return goodNumber;
}

