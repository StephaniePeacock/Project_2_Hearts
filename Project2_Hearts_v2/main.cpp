/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on June 1, 2023, 6:30 PM
 * Purpose: Play a game of Hearts vs the Three Stooges.
 */

//System Libraries
#include <iostream>  // Input / Output Library
#include <cstdlib>   // Random Function Library
#include <ctime>     // Time Library
#include <iomanip>   // Formatting Library
#include <fstream>   // File Library

using namespace std;

//User Libraries
#include "hearts.h"  // Hearts specific library
//Global Constants - Math/Physics/Chemistry/Conversions Only
//Function Prototypes - included in hearts.h


//Execution Begins Here
int main(int argc, char** argv) {
    //Set Random number seed
    srand(static_cast<unsigned int>(time(0)));
    
//Declare Variable Data Types and Constants 
    const unsigned short NCARDS = 52; // 52 cards in a deck - no jokers
    const short HAND = NCARDS/4;      // divides the deck into 4 
    const short SUITS = 4;
    // Array to hold the card number in the deck
    int card[NCARDS] = {
            1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52};
    // Holds the numerical face value
    int fv[HAND] = {1,2,3,4,5,6,7,8,9,10,11,12,13};    
    // Sets the suit number - used to validate legal card choice
    int sn;      
    // Displays Face Values of cards - Aces High
    char face[SUITS][HAND] = {{'2','3','4','5','6','7','8','9','T','J','Q','K','A'},
                              {'2','3','4','5','6','7','8','9','T','J','Q','K','A'},
                              {'2','3','4','5','6','7','8','9','T','J','Q','K','A'},
                              {'2','3','4','5','6','7','8','9','T','J','Q','K','A'}};
    // Displays the suit icon
    string suit[SUITS] = {"\u2663",    // Clubs
                          "\u2662",    // Diamonds
                          "\u2660",    // Spades
                          "\u2661"};   // Hearts
    string show[NCARDS];
    // Assigns a structure for each player
    Player player, larry, curly, moe;
    int choice;

    // <editor-fold defaultstate="collapsed" desc="Remove fold later">
    //Initial setup - get player name
    cout << "\"Hey buddy, we need a fourth player!" << endl
            << " Join us for a game of Hearts?" << endl
            << " My name is Larry, this is my good friend Curly," << endl
            << " and that's his brother, Moe.\"" << endl << endl;
    cout << "\"So what's your name?\"" << endl;
    cin >> player.name;
    cout << "\"Alright " << player.name << ", let's play Hearts! I'll deal.\"" << endl;
    // Assign face values
    faceVal(show,face,suit,SUITS,HAND);

    // Shuffle the deck
    shuffle(card, NCARDS, show);

    // Sort each player's Hand
    deal(player, larry, curly, moe, card);
    bSort(player, player.hand, HAND);
    sSort(larry, larry.hand, HAND);
    mSort(curly, curly.hand, HAND);
    mSort(moe, moe.hand, HAND);














    // Print out Cards
    cout << player.name << "'s cards: ";
    print(player, player.hand, HAND);
    cout << endl << "Larry's cards: ";
    print(larry, larry.hand, HAND);
    cout << endl << "Curly's cards: ";
    print(curly, curly.hand, HAND);
    cout << endl << "Moe's cards: ";
    print(moe, moe.hand, HAND);

    // Loop to play the hand
    for (int i = 0; i < 13; i++) {
        // Determine who goes first in the trick
        // Loop 4 times with If/Else to play trick
        // If Larry first
        // If Curly first
        // If Moe first
        // If player first - verifies valid, unplayed card
        //  else {
        do {
            cout << "Choose a card in your hand you wish to play: ";
            cin >> choice;
        } while ((choice < 1 || choice > 13) ||
                (choice == 1 && player.hand[0] == 0) ||
                (choice == 2 && player.hand[1] == 0) ||
                (choice == 3 && player.hand[2] == 0) ||
                (choice == 4 && player.hand[3] == 0) ||
                (choice == 5 && player.hand[4] == 0) ||
                (choice == 6 && player.hand[5] == 0) ||
                (choice == 7 && player.hand[6] == 0) ||
                (choice == 8 && player.hand[7] == 0) ||
                (choice == 9 && player.hand[8] == 0) ||
                (choice == 10 && player.hand[9] == 0) ||
                (choice == 11 && player.hand[10] == 0) ||
                (choice == 12 && player.hand[11] == 0) ||
                (choice == 13 && player.hand[12] == 0));
    }


    return 0;
}// </editor-fold>

void faceVal(string show[], char face[][13], string suit[], const short SUITS, const short HAND) {    
    int cFace = 0;
    for(int sym = 0; sym < SUITS; sym++) {
        for(int rank = 0; rank < HAND; rank++) {
            show[cFace]  = face[sym][rank];
            show[cFace] += suit[sym];
            ++cFace;
        }
    }
}
void shuffle(int card[], const unsigned short NCARDS, string show[]) {
    for (int i = 0; i < NCARDS; i++) {
        int n = i + (rand()%(52 - i));
        swap(card[i], card[n]);
        swap(show[i], show[n]);
    }
}
void deal(Player &player,Player &larry,Player &curly,Player &moe, int card[]){
    for(int i = 0; i < 13; i++) {
        player.hand[i] =  card[i];   
        larry.hand[i]  =  card[(i+13)];   
        curly.hand[i]  =  card[(i+26)];   
        moe.hand[i]    =  card[(i+39)];   
    }
}
void bSort(Player &, int hand[], const short HAND) {
    bool swap;
    do {
        swap = false;
        int n = 1;
        for (int i = 0; i < HAND - n; i++) {
            if (hand[i] > hand [i+1]) {
                int temp = hand[i];
                hand[i] = hand[i+1];
                hand[i+1] = temp;
                swap = true;
            }
        }
        n--;
    } while (swap);
}
void sSort(Player &, int hand[], const short HAND) {
    int indx;
    for(int i = 0; i < HAND; i++) {
        indx = i;
        for(int j = i+1; j < HAND; j++)
            if (hand[j] < hand[indx])
                indx = j;
        swap(hand[i],hand[indx]);    
    }
}  
void mSort(Player &, int hand[],const short HAND){
    for(int j = 0; j < HAND - 1; j++){
        for(int i = j + 1; i < HAND; i++){
            if(hand[j] > hand[i]){
                int temp = hand[j];
                hand[j] = hand[i];
                hand[i] = temp;
            }
        }
    }
}
void print(Player , int hand[], const short HAND) {
    for (int i = 0; i < HAND; i++) {
            cout << hand[i] << " ";   
    }
}    
 