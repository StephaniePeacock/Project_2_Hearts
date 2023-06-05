/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on June 2, 2023, 6:30 PM
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
    int deck[NCARDS] = {
            1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52};
    // Holds the numerical face value
    int fv[HAND] = {1,2,3,4,5,6,7,8,9,10,11,12,13};    
    int count = 0;
    int indx;
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
    larry.name = "Larry";
    curly.name = "Curly";
    moe.name = "Moe";    
    // <editor-fold defaultstate="collapsed" desc="Remove fold later">
    
    // put the outer do while loop for the game here
    
    //Initialize indx & get player's name
    indx = 0;   // used for the linear search to find 2 of clubs - reset to 0 each hand
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
    shuffle(deck, NCARDS, show);
    // Sort each player's Hand
    deal(player, larry, curly, moe, deck, show);
    bSort(player, player.hand, HAND, player.cards);
    sSort(larry, larry.hand, HAND, larry.cards);
    mSort(curly, curly.hand, HAND, curly.cards);
    mSort(moe, moe.hand, HAND, moe.cards);
    // Loop to play the hand
    for (int i = 0; i < 13; i++) {        
        // For the first trick, find the player with 2 of clubs
        if(i == 0) {
            linSrch(deck,NCARDS,indx);
            if     (indx < 14)              { player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3; }
            else if(indx > 13 && indx < 27) { player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2; }
            else if(indx > 26 && indx < 40) { player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1; }
            else                            { player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0; }
        }
        


        
        
        // Loop 4 times with If/Else to play trick
        for(int trick = 0; trick < 4; trick++){
            if (player.order == trick) { //Player Goes        
            // Print player's cards
            print(player, player.hand, player.cards, HAND, player.choice, count);        
                // Get player Choice - validates selection
                do {
                    cout << "Choose a card in your hand you wish to play: ";
                    cin >> player.choice;
                    // Add 2clubs validation
                    
                    // Add suit validation
                    
                } while ((player.choice < 1 || player.choice > 13)    ||
                        (player.choice == 1  && player.hand[0]  == 0) ||
                        (player.choice == 2  && player.hand[1]  == 0) ||
                        (player.choice == 3  && player.hand[2]  == 0) ||
                        (player.choice == 4  && player.hand[3]  == 0) ||
                        (player.choice == 5  && player.hand[4]  == 0) ||
                        (player.choice == 6  && player.hand[5]  == 0) ||
                        (player.choice == 7  && player.hand[6]  == 0) ||
                        (player.choice == 8  && player.hand[7]  == 0) ||
                        (player.choice == 9  && player.hand[8]  == 0) ||
                        (player.choice == 10 && player.hand[9]  == 0) ||
                        (player.choice == 11 && player.hand[10] == 0) ||
                        (player.choice == 12 && player.hand[11] == 0) ||
                        (player.choice == 13 && player.hand[12] == 0));
                // Output the card played
                played(player, player.name, player.choice, player.cards);
                // Set the played card for scoring
                set(player, player.choice, player.hand);       

        // Larry's Turn        
            }else if (larry.order == trick) {
                cout << "Larry's cards";
                print(larry, larry.hand, larry.cards, HAND, larry.choice, count);
                playCard(larry,curly,moe, player, larry.choice, larry.order, larry.hand, larry.name, trick);
                // Output the card played
                played(larry, larry.name, larry.choice, larry.cards);
                // Set the played card for scoring
                set(larry, larry.choice, larry.hand);
        // Curly's Turn        
            }else if(curly.order == trick) { 
                cout << "Curly's cards";
                print(curly, curly.hand, curly.cards, HAND, curly.choice, count);
                playCard(larry,curly,moe, player, curly.choice, curly.order, curly.hand, curly.name, trick);
                // Output the card played
                played(curly, curly.name, curly.choice, curly.cards);
                // Set the played card for scoring
                set(curly, curly.choice, curly.hand);
        // Moe's Turn        
            }else if(moe.order == trick) {
                cout << "Moe's cards"<< endl;
                print(moe, moe.hand, moe.cards, HAND, moe.choice, count); 
                playCard(larry,curly,moe, player, moe.choice, moe.order, moe.hand, moe.name, trick);
                // Output the card played
                played(moe, moe.name, moe.choice, moe.cards);
                // Set the played card for scoring
                set(moe, moe.choice, moe.hand);
            }
        }
        // Score Trick & set the player order for the next trick
        unset(player,player.choice, player.hand, player.cards,count);
        npcUn(larry,larry.choice, larry.hand, larry.cards);
        npcUn(curly,curly.choice, curly.hand, curly.cards);
        npcUn(moe,moe.choice, moe.hand, moe.cards);    


    }


    return 0;
}// </editor-fold>

void faceVal(string show[], char face[][13], string suit[], const short SUITS, const short HAND) {    
    int cFace = 0;
    for(int sym = 0; sym < SUITS; sym++) {
        for(int rank = 0; rank < HAND; rank++) {
            show[cFace]  = face[sym][rank];
            show[cFace] += suit[sym] + "\t";
            ++cFace;
        }
    }
}
void shuffle(int deck[], const unsigned short NCARDS, string show[]) {
    for (int i = 0; i < NCARDS; i++) {
        int n = i + (rand()%(52 - i));
        swap(deck[i], deck[n]);
        swap(show[i], show[n]);
    }
}
void deal(Player &player,Player &larry,Player &curly,Player &moe, int deck[], string show[]){
    for(int i = 0; i < 13; i++) {
        player.hand[i] =  deck[i];   
        larry.hand[i]  =  deck[(i+13)];   
        curly.hand[i]  =  deck[(i+26)];   
        moe.hand[i]    =  deck[(i+39)];
        player.cards[i] =  show[i];   
        larry.cards[i]  =  show[(i+13)];   
        curly.cards[i]  =  show[(i+26)];   
        moe.cards[i]    =  show[(i+39)];
    }
}
void bSort(Player &, int hand[], const short HAND, string cards[]) {
    bool swap;
    do {
        swap = false;
        int n = 1;
        for (int i = 0; i < HAND - n; i++) {
            if (hand[i] > hand [i+1]) {
                int temp = hand[i];
                hand[i] = hand[i+1];
                hand[i+1] = temp;
                string tmp = cards[i];
                cards[i] = cards[i+1];
                cards[i+1] = tmp;
                swap = true;
            }
        }
        n--;
    } while (swap);
}
void sSort(Player &, int hand[], const short HAND, string cards[]) {
    int indx;
    for(int i = 0; i < HAND; i++) {
        indx = i;
        for(int j = i+1; j < HAND; j++)
            if (hand[j] < hand[indx])
                indx = j;
        swap(hand[i],hand[indx]);
        swap(cards[i],cards[indx]);
    }
}  
void mSort(Player &, int hand[], const short HAND, string cards[]){
    for(int j = 0; j < HAND - 1; j++){
        for(int i = j + 1; i < HAND; i++){
            if(hand[j] > hand[i]){
                int temp = hand[j];
                hand[j] = hand[i];
                hand[i] = temp;
                string tmp = cards[j];
                cards[j] = cards[i];
                cards[i] = tmp;
            }
        }
    }
}
void print(Player &, int hand[], string cards[], const short HAND, int choice, int count) {
        if (count < 14) {
        // output Player's remaining cards - if value is 0 an empty string is output
        cout << endl << endl << "Play Card #:\t";
        if (hand[0] == 0) { cout << ""; } else { cout << "1" << "\t"; }
        if (hand[1] == 0) { cout << ""; } else { cout << "2" << "\t"; }
        if (hand[2] == 0) { cout << ""; } else { cout << "3" << "\t"; }
        if (hand[3] == 0) { cout << ""; } else { cout << "4" << "\t"; }
        if (hand[4] == 0) { cout << ""; } else { cout << "5" << "\t"; }
        if (hand[5] == 0) { cout << ""; } else { cout << "6" << "\t"; }
        if (hand[6] == 0) { cout << ""; } else { cout << "7" << "\t"; }
        if (hand[7] == 0) { cout << ""; } else { cout << "8" << "\t"; }
        if (hand[8] == 0) { cout << ""; } else { cout << "9" << "\t"; }
        if (hand[9] == 0) { cout << ""; } else { cout << "10"<< "\t"; }
        if (hand[10]== 0) { cout << ""; } else { cout << "11"<< "\t"; }
        if (hand[11]== 0) { cout << ""; } else { cout << "12"<< "\t"; }
        if (hand[12]== 0) { cout << ""; } else { cout << "13"<< "\t"; }
        // now output the remaining face values
        cout << endl << setw(14) << "\t";
        for (int j = 0; j < HAND; j++) {
            cout << cards[j];
        }
        cout << endl << endl;
    }
} 
void set(Player &, int &choice, int hand[] ){
            // Set choice to card value for scoring
            choice == 1  ? choice = hand[0] : choice == 2  ? choice = hand[1] :
            choice == 3  ? choice = hand[2] : choice == 4  ? choice = hand[3] : 
            choice == 5  ? choice = hand[4] : choice == 6  ? choice = hand[5] :  
            choice == 7  ? choice = hand[6] : choice == 8  ? choice = hand[7] : 
            choice == 9  ? choice = hand[8] : choice == 10 ? choice = hand[9] : 
            choice == 11 ? choice = hand[10]: choice == 12 ? choice = hand[11]: 
            choice = hand[12];
}
void unset(Player &, int &choice, int hand[], string cards[], int &count){
    // Set choice back to the card number instead of card value & set used card to 0
    choice == hand[0]  ? choice = 1  : choice == hand[1]  ? choice = 2  : 
    choice == hand[2]  ? choice = 3  : choice == hand[3]  ? choice = 4  : 
    choice == hand[4]  ? choice = 5  : choice == hand[5]  ? choice = 6  :     
    choice == hand[6]  ? choice = 7  : choice == hand[7]  ? choice = 8  : 
    choice == hand[8]  ? choice = 9  : choice == hand[9]  ? choice = 10 : 
    choice == hand[10] ? choice = 11 : choice == hand[11] ? choice = 12 :     
    choice = 13;     
    // set chosen card to 0
    if (choice == 1) { hand[0]  = 0; cards[0]  = ""; count++; }
    if (choice == 2) { hand[1]  = 0; cards[1]  = ""; count++; }
    if (choice == 3) { hand[2]  = 0; cards[2]  = ""; count++; }
    if (choice == 4) { hand[3]  = 0; cards[3]  = ""; count++; }
    if (choice == 5) { hand[4]  = 0; cards[4]  = ""; count++; }
    if (choice == 6) { hand[5]  = 0; cards[5]  = ""; count++; }
    if (choice == 7) { hand[6]  = 0; cards[6]  = ""; count++; }
    if (choice == 8) { hand[7]  = 0; cards[7]  = ""; count++; }
    if (choice == 9) { hand[8]  = 0; cards[8]  = ""; count++; }
    if (choice == 10){ hand[9]  = 0; cards[9]  = ""; count++; }
    if (choice == 11){ hand[10] = 0; cards[10] = ""; count++; }
    if (choice == 12){ hand[11] = 0; cards[11] = ""; count++; }
    if (choice == 13){ hand[12] = 0; cards[12] = ""; count++; }
}
void played(Player &, string name, int choice, string cards[]) {
    cout << name << " played: ";
    switch (choice) {
        case 1: cout << cards[0]; break;
        case 2: cout << cards[1]; break;
        case 3: cout << cards[2]; break;
        case 4: cout << cards[3]; break;
        case 5: cout << cards[4]; break;
        case 6: cout << cards[5]; break;
        case 7: cout << cards[6]; break;
        case 8: cout << cards[7]; break;
        case 9: cout << cards[8]; break;
        case 10:cout << cards[9]; break;
        case 11:cout << cards[10];break;
        case 12:cout << cards[11];break; 
        default:cout << cards[12];break;
    }
    cout << endl;
}
bool linSrch(int deck[],const unsigned short NCARDS,int& indx) {
    // start off with false
    bool found = false;
    // run until the val is found or we run through all the numbers
    while (indx < NCARDS && !found){
        // if the val is found it returns true and stops the loop, if false it adds to the count
        deck[indx] == 1 ?  found = true : indx++;
    }
    // sends back what index 2 of clubs (1) was found at
    return indx;
}
void playCard(Player& larry,Player& curly,Player& moe, Player& player, int& choice, int order, int hand[], string name, int trick) {
    bool chosen = false;
    // If npc is first to play in the trick - check for 2 clubs first
    if(order == 0) { 
        if ( hand[0] == 1) {choice = 1;}
        // If no 2 clubs, play lowest card
        else if (order == 0){
            for(int i = 0; i < 13 && !chosen; i++){
                if(hand[i] != 0) { choice = i+1; chosen = true;}
            }
        }
    }    
    else {
        // Check against player first
        if(player.order == 0) {
            int min = player.choice < 14 ? 0 : player.choice < 27 ? 14 : player.choice < 40 ? 27 : 40;
            int max = min + 13;
        // Match the suit if possible - playing lowest card possible    
            for (int i = 0; i < 13 && !chosen; i++) {
                if (hand[i] >= min && hand[i] <= max && hand[i] != 0) {
                   choice = (i+1); chosen = true;
                }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; }
                    if (hand[j] == 39) {choice = (j+1); chosen = true; }
                    if (hand[j] == 38) {choice = (j+1); chosen = true; }
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; }
                }
            } 
        }
        // Check against Larry second
        else if(larry.order == 0 && order != larry.order) {
            int min = larry.choice < 14 ? 0 : larry.choice < 27 ? 14 : larry.choice < 40 ? 27 : 40;
            int max = min + 13;
        // Match the suit if possible - playing lowest card possible    
            for (int i = 0; i < 13 && !chosen; i++) {
                if (hand[i] >= min && hand[i] <= max && hand[i] != 0) {
                   choice = (i+1); chosen = true;
                }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; }
                    if (hand[j] == 39) {choice = (j+1); chosen = true; }
                    if (hand[j] == 38) {choice = (j+1); chosen = true; }
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; }
                }
            } 
        }
        // Check against Curly third
        else if(curly.order == 0 && order != curly.order) {
            int min = curly.choice < 14 ? 0 : curly.choice < 27 ? 14 : curly.choice < 40 ? 27 : 40;
            int max = min + 13;
        // Match the suit if possible - playing lowest card possible    
            for (int i = 0; i < 13 && !chosen; i++) {
                if (hand[i] >= min && hand[i] <= max && hand[i] != 0) {
                   choice = (i+1); chosen = true;
                }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; }
                    if (hand[j] == 39) {choice = (j+1); chosen = true; }
                    if (hand[j] == 38) {choice = (j+1); chosen = true; }
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; }
                }
            } 
        }
        // Check against Moe Last
        else {
            int min = moe.choice < 14 ? 0 : moe.choice < 27 ? 14 : moe.choice < 40 ? 27 : 40;
            int max = min + 13;
        // Match the suit if possible - playing lowest card possible    
            for (int i = 0; i < 13 && !chosen; i++) {
                if (hand[i] >= min && hand[i] <= max && hand[i] != 0) {
                   choice = (i+1); chosen = true;
                }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; }
                    if (hand[j] == 39) {choice = (j+1); chosen = true; }
                    if (hand[j] == 38) {choice = (j+1); chosen = true; }
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; }
                }
            }                     
        }
    }
}
void npcUn(Player &, int &choice, int hand[], string cards[]){
    // Set choice back to the card number instead of card value & set used card to 0
    choice == hand[0]  ? choice = 1  : choice == hand[1]  ? choice = 2  : 
    choice == hand[2]  ? choice = 3  : choice == hand[3]  ? choice = 4  : 
    choice == hand[4]  ? choice = 5  : choice == hand[5]  ? choice = 6  :     
    choice == hand[6]  ? choice = 7  : choice == hand[7]  ? choice = 8  : 
    choice == hand[8]  ? choice = 9  : choice == hand[9]  ? choice = 10 : 
    choice == hand[10] ? choice = 11 : choice == hand[11] ? choice = 12 :     
    choice = 13;     
    // set chosen card to 0
    if (choice == 1) { hand[0]  = 0; cards[0]  = ""; }
    if (choice == 2) { hand[1]  = 0; cards[1]  = ""; }
    if (choice == 3) { hand[2]  = 0; cards[2]  = ""; }
    if (choice == 4) { hand[3]  = 0; cards[3]  = ""; }
    if (choice == 5) { hand[4]  = 0; cards[4]  = ""; }
    if (choice == 6) { hand[5]  = 0; cards[5]  = ""; }
    if (choice == 7) { hand[6]  = 0; cards[6]  = ""; }
    if (choice == 8) { hand[7]  = 0; cards[7]  = ""; }
    if (choice == 9) { hand[8]  = 0; cards[8]  = ""; }
    if (choice == 10){ hand[9]  = 0; cards[9]  = ""; }
    if (choice == 11){ hand[10] = 0; cards[10] = ""; }
    if (choice == 12){ hand[11] = 0; cards[11] = ""; }
    if (choice == 13){ hand[12] = 0; cards[12] = ""; }
}    
