#include <iostream>
#include "Player.h"
#include "CleanStrike.h"
using namespace std;

int player=1;
int totalCoins=10;
int blackCoins=9;
int redCoins=1;

//To display Menu everytime before a move is placed
void showMenu()
{
    player=(player%2)?1:2;
    cout<<"Player "<<player<<": Choose an outcome from the list below"<<endl;
    cout<<"1. Strike\n2. Multistrike\n3. Red strike\n4. Striker strike\n5. Defunct coin\n6. None"<<endl;
    return;
}

/*
//--------------------------------------------------IMPORTANT-------------------------------------------------------------//

Case 2: When multistrike:
    I am considering that whenever a player multistrike the player will get 2 points but have to return  
    all the coins he had before this move and will only get the coin he earned in this move itself.
*/

//Switch case, handling all the action that will take place as per the the move entered from the menu.
void play(int option,Player &P1,Player &P2,CleanStrike &CS)
{
    player=(player%2)?1:2;
    int point=0;
    switch(option)
    {
        case 1:
            if(blackCoins!=0)
            {
                point=CS.strike(blackCoins,totalCoins);
                if(player==1)
                {
                    P1.nBlackCoins++;
                    P1.points+=point;
                    P1.noPocket=0;
                }
                else
                {
                    P2.nBlackCoins++;
                    P2.points+=point;
                    P2.noPocket=0;
                }
            }
            else
            {
                cout<<"No black Coin available,please select carefully"<<endl;
                player--;
            }
            break;
        case 2: 
            if(blackCoins!=0)
            {   
                int nCoinsPocketed=0;
                cout<<"Enter number of coins pocketed"<<endl;
                cin>>nCoinsPocketed;
                totalCoins-=nCoinsPocketed;
                point=CS.multiStrike();
                if(player==1)
                {
                    totalCoins+=(P1.nBlackCoins+P1.nRedCoins);
                    P1.nBlackCoins=nCoinsPocketed;
                    if(P1.nRedCoins!=0)
                    {
    	                P1.nRedCoins=0;
                        redCoins=1;
                    }
                    P1.points+=point;
                    P1.noPocket=0;
                }
                else
                {
                    totalCoins+=(P2.nBlackCoins+P2.nRedCoins);
                    P2.nBlackCoins=nCoinsPocketed;
                    if(P2.nRedCoins!=0)
                    {
    	                P2.nRedCoins=0;
                        redCoins=1;
                    }
                    P2.points+=point;
                    P2.nRedCoins=0;
                    P2.noPocket=0;
                }
                if(redCoins==0)
                {
                    blackCoins=totalCoins;
                }
                else
                {
                    blackCoins=totalCoins-1;
                }
            }
            else
            {
                cout<<"No black Coin available,please select carefully"<<endl;
                player--;
            }
            break;
        case 3:
            if(redCoins!=0)
            {
                point=CS.redStrike(redCoins,totalCoins);
                if(player==1)
                {
                    P1.points+=point;
                    P1.nRedCoins++;
                    P1.noPocket=0;
                }
                else
                {
                    P2.points+=point;
                    P2.nRedCoins++;
                    P2.noPocket=0;
                }
            }
            else
            {
                cout<<"NO red coins available, please select carefully"<<endl;
                player--;
            }
           
            break;
        case 4:
            point=CS.strikerStrike();
            if(player==1)
            {
                P1.foul++;
                P1.noPocket++;
                if(P1.foul==3)
                {
                    point--;
                    P1.foul=0;
                }
                if(P1.noPocket==3)
                {
                    point--;
                    P1.noPocket=0;
                }
                P1.points+=point;
            }
            else
            {   P2.foul++;
                P2.noPocket++;
                if(P2.foul==3)
                {
                    point--;
                    P2.foul=0;
                }
                if(P2.noPocket==3)
                {
                    point--;
                    P2.noPocket=0;
                }
                P2.points+=point;
            }
            break;
        case 5:
            point=CS.defuntCoin(redCoins,blackCoins,totalCoins);
            if(player==1)
            {   P1.foul++;
                P1.noPocket++;
                if(P1.foul==3)
                {
                    point--;
                    P1.foul=0;
                }
                if(P1.noPocket==3)
                {
                    point--;
                    P1.noPocket=0;
                }
                P1.points+=point;
            }
            else
            {   P2.foul++;
                P2.noPocket++;
                if(P2.foul==3)
                {
                    point--;
                    P2.foul=0;
                }
                if(P2.noPocket==3)
                {
                    point--;
                    P2.noPocket=0;
                }
                P2.points+=point;
            }
            break;
        case 6:
            point=0;
            if(player==1)
            {   
                P1.noPocket++;
                if(P1.noPocket==3)
                {
                    point--;
                    P1.noPocket=0;
                }
                P1.points+=point;
            }
            else
            {   
                P2.noPocket++;
                if(P2.noPocket==3)
                {
                    point--;
                    P2.noPocket=0;
                }
                P2.points+=point;
            }
            break;
        default :
         cout << "Invalid move" << endl;
         player--;
    }
    // cout<<"Available Coins : "<<totalCoins<<endl;
    // cout<<"Black Coins : "<<blackCoins<<endl;
    // cout<<"Red Coins : "<<redCoins<<endl;
    cout<<"--------------------------------Player 1 Points : "<<P1.points<<"   Player 2 Points : "<<P2.points<<"-------------------------------"<<endl;
    // cout<<"PLayer 1 Coins : "<<P1.nBlackCoins <<" : "<<P1.nRedCoins<<endl;
    // cout<<"PLayer 2 Coins : "<<P2.nBlackCoins <<" : "<<P2.nRedCoins<<endl;
    // cout<<"noPocketP1 : "<<P1.noPocket<<"       noPocketP2 : "<<P2.noPocket<<endl;
    // cout<<"P1 Foul: "<<P1.foul<<" P1 Foul: "<<P2.foul<<endl;
    player++;
    return;
}

//To display the result after comparing the points and the difference between the player's points.
void result(Player &P1,Player &P2)
{
    int diff=0;
    int leader=P1.points>=P2.points?1:2;
    int lead=0;
    if(leader==1)
    {
        diff=P1.points-P2.points;
        if(diff>=3 && P1.points>=5)
        {
            cout<<"Player 1 won the game"<<endl;
        }
        else
        {
            cout<<"Its a draw."<<endl;
        }
    }
        
    else
    {
        diff=P2.points-P1.points;
        if(diff>=3 && P2.points>=5)
        {
            cout<<"Player 2 won the game"<<endl;
        }
        else
        {
            cout<<"Its a draw."<<endl;
        }
    }
    cout<<"Final Score:"<<P1.points<<"-"<<P2.points<<endl;
}


//Main function which'll create the objects and will call and pass to the function which needs them.
int main()
{
    Player P1;
    Player P2;
    CleanStrike CS;

    int option=0;
    do{
        showMenu();
        cin>>option;
        play(option,P1,P2,CS);

    }while(blackCoins>0 || redCoins>0);

    result(P1,P2);
    
    return 0;
}
