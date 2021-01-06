#include <iostream>
using namespace std;

//CleanStrike class is having the functions which returns the points as per the move and is called in the play function of main.cpp file.
class CleanStrike
{
    public:

    int strike(int &blackCoins,int &totalCoins)
    {   
        blackCoins--;
        totalCoins--;
        return 1;
    }

    int multiStrike()
    {
        return 2;
    }

    int redStrike(int &redCoins,int &totalCoins)
    {
        redCoins--;
        totalCoins--;
        return 3;
    }

    int strikerStrike()
    {
        return -1;
    }

    int defuntCoin(int &redCoins,int &blackCoins,int &totalCoins)
    {
        int defCoinValue=0;
        cout<<"Enter the color of the coins\n 1.Black \n 2.Red"<<endl;
        cin>>defCoinValue;
        if(defCoinValue==2)
        {
            if(redCoins!=0)
            {
                redCoins--;
                totalCoins--;
            }
            else
            {
                cout<<"NO red coins is available, select again"<<endl;
                defuntCoin(redCoins,blackCoins,totalCoins);
            }    
        }
        else
        {
            blackCoins--;
            totalCoins--;
        }   
        return -2;
    }
};
