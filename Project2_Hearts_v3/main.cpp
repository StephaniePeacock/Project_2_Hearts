/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on June 4, 2023, 4:45 PM
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
            1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, // indx 0 - 12
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, // indx 13 - 25
            27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, // indx 26 - 38
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52};// indx 39 - 51
    // Holds the numerical face value
    int fv[HAND] = {1,2,3,4,5,6,7,8,9,10,11,12,13};    
    int count = 0;
    int indx;
    int wins;
    int total;
    float winLoss;
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
    player.score = larry.score = curly.score = moe.score = 0;

    // Open file & read current win / total 
    ifstream inWins("wins.txt");
    inWins >> wins >> total;
    // Close the file for at the end!
    inWins.close();
    
    // Make sure we don't divide by 0!
    if(total != 0 ) {
        // Previous games have been played - output the ratio
        winLoss = (wins/static_cast<float>(total)) * 100;    
        cout << "It looks like you have played before. You have won " << fixed << setprecision(2) << winLoss << "% of the games you have played." << endl;
    }
    else{
        cout << "\"Hey buddy, we need a fourth player!" << endl
            << " Join us for a game of Hearts?" << endl
            << " My name is Larry, this is my good friend Curly," << endl
            << " and that's his brother, Moe.\"" << endl << endl;
           cout << "\"So what's your name?\"" << endl;
        cin >> player.name;
        cout << "\"Alright " << player.name << ", let's play Hearts! I'll deal.\"" << endl;
    }
     // Assign face values
    faceVal(show,face,suit,SUITS,HAND);
    // put the outer do while loop for the game here
    do {
    //Initialize indx 
    indx = 0;   // used for the linear search to find 2 of clubs - reset to 0 each hand
  
    // Set initial trick scores to 0 & match to false
    player.tScore = larry.tScore = curly.tScore = moe.tScore = 0;
    // Shuffle the deck
    shuffle(deck, NCARDS, show);
    // Deal cards
    deal(player, larry, curly, moe, deck, show);
    //Sort each player's Hand
    bSort(player, player.hand, HAND, player.cards);
    sSort(larry, larry.hand, HAND, larry.cards);
    mSort(curly, curly.hand, HAND, curly.cards);
    mSort(moe, moe.hand, HAND, moe.cards);
    // Loop to play the hand
    for (int i = 0; i < 13; i++) {
        // used for the linear search to find 2 of clubs - resets to 0 each hand
        indx = 0;

        // For the first trick, find the player with 2 of clubs
        if(i == 0) {
            linSrch(deck,NCARDS,indx);    

            if     (indx < 13)              { player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3; }
            else if(indx > 12 && indx < 26) { player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2; }
            else if(indx > 25 && indx < 39) { player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1; }
            else                            { player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0; }
           
        }
        // reset match
        player.match = larry.match = curly.match = moe.match = false;
        // Loop 4 times with If/Else to play trick
        for(int trick = 0; trick < 4; trick++){
            
        //Player's Turn    
            if (player.order == trick) {         
            // Print player's cards
            print(player, player.hand, player.cards, HAND, player.choice, count);        
            // Get player Choice - validates selection
            do {
                cout << "Choose a card in your hand you wish to play: ";
                cin >> player.choice;
                // Add 2clubs validation                                   
                while (player.order == 0 && player.hand[0] == 1 && player.choice != 1) {
                        cout << "Please play 2\u2663: ";
                        cin >> player.choice; 
                }
                if(player.order == 0){
                    player.match = true;
                }
                // Add suit validation
                // Check for Clubs
                    if((larry.order == 0 && larry.choice < 14) ||
                       (curly.order == 0 && curly.choice < 14) ||
                       (moe.order == 0 && moe.choice < 14)) {
                       for(int i = 0; i < 12; i++) {
                           int vc = i+1;

                            while(player.choice == vc && player.hand[i] != 0 && (player.hand[i] >13 && player.hand[i+1] < 13 )) {

                                        cout << "Please play \u2663: ";
                                        cin >> player.choice;     
                            }
                            player.match = true;
                        }
                    }
                // Check for Diamonds
                    if((larry.order == 0 && larry.choice > 13 && larry.choice < 27) ||
                       (curly.order == 0 && curly.choice > 13 && curly.choice < 27) ||
                       (moe.order == 0 && moe.choice > 13 && moe.choice < 27)) { 
                        for(int i = 0; i < 12; i++) {
                           int vc = i+1;
                        
                            while(player.choice == vc && player.hand[i] !=0 && (player.hand[i] <14 && player.hand[i] >26 && player.hand[i+1] >13 && player.hand[i+1] <27)) {
                                        cout << "Please play \u2662: ";
                                        cin >> player.choice;
                            }
                            player.match = true;
                        }
                    }
                // Check for Spades
                    if((larry.order == 0 && larry.choice > 26 && larry.choice < 40) ||
                       (curly.order == 0 && curly.choice > 26 && curly.choice < 40) ||
                       (moe.order == 0 && moe.choice > 26 && moe.choice < 40)) { 
                        for(int i = 0; i < 12; i++) {
                           int vc = i+1;
                        
                            while(player.choice == vc && player.hand[i] !=0 && (player.hand[i] <27 && player.hand[i] >39 && player.hand[i+1] >26 && player.hand[i+1] <40)) {
                        
                                    cout << "Please play \u2660: ";
                                    cin >> player.choice;
                            }
                        player.match = true;
                        }
                    }
                // Check for hearts
                    if((larry.order == 0 && larry.choice > 39) ||
                       (curly.order == 0 && curly.choice > 39) ||
                       (moe.order == 0 && moe.choice > 39)) { 
                        
                        for(int i = 0; i < 12; i++) {
                           int vc = i+1;
                        
                            while(player.choice == vc && player.hand[i] !=0 && (player.hand[i] <40 && player.hand[i+1] >39)) {
                       
                                    cout << "Please play \u2661: ";
                                    cin >> player.choice; 
                            }
                        player.match = true;
                        }
                    }
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
            // Valid card chosen, set match to true
            player.match = true;
            // Output the card played
            played(player, player.name, player.choice, player.cards);
            // Set choice value to the played card value for scoring
            set(player, player.choice, player.hand);       
        // Larry's Turn        
            } else if (larry.order == trick) {
            //    cout << "Larry's cards";
            //    print(larry, larry.hand, larry.cards, HAND, larry.choice, count);
                playCard(larry,curly,moe, player, larry.choice, larry.order, larry.hand, larry.name, trick, larry.match);
                // Output the card played
                played(larry, larry.name, larry.choice, larry.cards);
                // Set the played card for scoring
                set(larry, larry.choice, larry.hand);
        // Curly's Turn        
            }else if(curly.order == trick) { 
            //    cout << "Curly's cards";
            //    print(curly, curly.hand, curly.cards, HAND, curly.choice, count);
                playCard(larry,curly,moe, player, curly.choice, curly.order, curly.hand, curly.name, trick, curly.match);
                // Output the card played
                played(curly, curly.name, curly.choice, curly.cards);
                // Set the played card for scoring
                set(curly, curly.choice, curly.hand);
        // Moe's Turn        
            }else if(moe.order == trick) {
            //    cout << "Moe's cards"<< endl;
            //    print(moe, moe.hand, moe.cards, HAND, moe.choice, count); 
                playCard(larry,curly,moe, player, moe.choice, moe.order, moe.hand, moe.name, trick, moe.match);
                // Output the card played
                played(moe, moe.name, moe.choice, moe.cards);
                // Set the played card for scoring
                set(moe, moe.choice, moe.hand);
            }
        }
        // Score Trick & set the player order for the next trick
        trick(player,larry,curly,moe,
              player.choice,larry.choice,curly.choice,moe.choice,
              player.tScore,larry.tScore,curly.tScore,moe.tScore,
              player.order,larry.order,curly.order,moe.order,
              player.match,larry.match,curly.match,moe.match);
        // Change choice back it's original value and remove played cards 
        unset(player,player.choice, player.hand, player.cards,count);
        npcUn(larry,larry.choice, larry.hand, larry.cards);
        npcUn(curly,curly.choice, curly.hand, curly.cards);
        npcUn(moe,moe.choice, moe.hand, moe.cards);    


        }
    
    count = 0;
    // Shuffle the deck
    shuffle(deck, NCARDS, show);
    // Deal cards
    deal(player, larry, curly, moe, deck, show);
    //Sort each player's Hand
    bSort(player, player.hand, HAND, player.cards);
    sSort(larry, larry.hand, HAND, larry.cards);
    mSort(curly, curly.hand, HAND, curly.cards);
    mSort(moe, moe.hand, HAND, moe.cards);
    
            // Check for Shooting the Moon
        player.tScore == 26 ? player.tScore = 0, larry.tScore = 26, curly.tScore = 26, moe.tScore = 26,cout << "Hey, Wiseguy! You shot the moon! The Stooges takes all points." << endl << endl :
        larry.tScore == 26 ? larry.tScore = 0, player.tScore = 26, curly.tScore = 26, moe.tScore = 26, cout << "Larry shot the moon! The rest of you schmucks can take the points."  << endl << endl :
        curly.tScore == 26 ? curly.tScore = 0, player.tScore = 26, larry.tScore = 26, moe.tScore = 26, cout << "Curly shot the moon! The rest of you schmucks can take the points."  << endl << endl :
        moe.tScore == 26 ? moe.tScore = 0, player.tScore = 26, curly.tScore = 26, larry.tScore = 26, cout << "Larry shot the moon! The rest of you schmucks can take the points."  << endl << endl :    
        cout << endl << "What a fun hand!" << endl << endl;
    
    
    
    player.score += player.tScore;
    larry.score += larry.tScore;
    curly.score += curly.tScore;
    moe.score += moe.tScore;
    
            cout << "The current game score is:" << endl
             << "Player   : " << player.score << endl
             << "Larry    : " << larry.score << endl
             << "Curly    : " << curly.score << endl
             << "Moe      : " << moe.score << endl       ;
    
    } while (player.score < 50 && larry.score < 50 && curly.score < 50 && moe.score <50);
    cout << endl;
    if (player.score < larry.score && player.score < curly.score && player.score < moe.score) { wins++, cout << "You won the game!" << endl; }
    else {total++, cout << "You lost the game. Better luck next time!" << endl; }
    
    // Let them know how good they are
    winLoss = (wins/static_cast<float>(total)) * 100;
    
    cout << "You have won " << fixed << setprecision(2) << winLoss << "% of the games you have played." << endl;
    
    // Record win ratio to file
    ofstream outWins("wins.txt");
    outWins << wins << " " << total;
    outWins.close();

    return 0;
}

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
int linSrch(int deck[],const unsigned short NCARDS,int& indx) {
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
void print(Player &, int hand[], string cards[], const short HAND, int choice, int count) {
        if (count < 14) {
        // output Player's remaining cards - if value is 0 an empty string is output
        cout << endl << "Play Card #:\t";
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
        cout << endl;
    }
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
void playCard(Player& larry,Player& curly,Player& moe, Player& player, int& choice, int & order, int hand[], string name, int trick, bool& match) {
    bool chosen = false;
    // If npc is first to play in the trick - check for 2 clubs first
    if(order == 0) { 
        if ( hand[0] == 1) {choice = 1; match = true;}
        // If no 2 clubs, play lowest card
        else if (order == 0){
            for(int i = 0; i < 13 && !chosen; i++){
                if(hand[i] != 0) { choice = i+1; chosen = true; match = true; }
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
                    choice = (i+1); chosen = true; match = true; }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 39) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 38) {choice = (j+1); chosen = true; match = false;}
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; match = false; }
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
                    choice = (i+1); chosen = true; match = true; }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 39) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 38) {choice = (j+1); chosen = true; match = false;}
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; match = false; }
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
                    choice = (i+1); chosen = true; match = true; }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 39) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 38) {choice = (j+1); chosen = true; match = false;}
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; match = false; }
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
                    choice = (i+1); chosen = true; match = true; }
            }
        // Play Q spades, A spades, or K spades first if can't match suit   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] == 37) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 39) {choice = (j+1); chosen = true; match = false;}
                    if (hand[j] == 38) {choice = (j+1); chosen = true; match = false;}
                }
            }
        // Lastly, play the highest card available   
            if(!chosen){
                for (int j = 12; j > 0 && !chosen; j--) {
                    if (hand[j] != 0) {choice = (j+1); chosen = true; match = false; }
                }
            }                     
        }
    }
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

void trick( Player& player, Player& larry, Player& curly, Player& moe,
            int playerchoice,int larrychoice,int curlychoice,int moechoice,
            int& playertScore, int& larrytScore,int& curlytScore,int& moetScore,
            int& playerorder,int& larryorder,int& curlyorder,int& moeorder,
            bool playermatch,bool larrymatch,bool curlymatch,bool moematch){
            
            // All Play Hearts
            if (player.choice > 39 && larry.choice > 39 && curly.choice > 39 && moe.choice > 39) {
                cout << "Trick worth four points." << endl;
                // Player wins trick
                if (player.choice > larry.choice && player.choice > curly.choice && player.choice > moe.choice) {
                    cout << "Player takes the trick." << endl;
                    player.tScore += 4;
                    player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                }
                // Larry wins trick
                else if (larry.choice > player.choice && larry.choice > curly.choice && larry.choice > moe.choice){
                    cout << "Larry takes the trick." << endl;
                    larry.tScore += 4;
                    player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2;                    
                }
                // Curly wins trick
                else if (curly.choice > player.choice && curly.choice > larry.choice && curly.choice > moe.choice){
                    cout << "Curly takes the trick." << endl;
                    curly.tScore += 4;
                    player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1;
                }
                // Moe wins trick
                else {
                    cout << "Moe takes the trick." << endl;
                    larry.tScore += 4;
                    player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0;
                }
            }    
              

            // Three Play Hearts

            else if ((player.choice > 39 && larry.choice > 39 && curly.choice > 39) ||
                (player.choice > 39 && larry.choice > 39 && moe.choice   > 39) ||
                (player.choice > 39 && curly.choice > 39 && moe.choice   > 39) ||
                (larry.choice  > 39 && curly.choice > 39 && moe.choice   > 39)){
                // No Queen Spades Played
                if(player.choice != 37 && larry.choice != 37 && curly.choice != 37 && moe.choice != 37) {
                    cout << "Trick worth three points." << endl;    
                }
                // Queen of Spades Played
                else if(larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ) {
                    cout << "Trick worth sixteen points." << endl;    
                }
                // Player wins trick
                if((player.order == 0 && larry.match == true && curly.match == true && player.choice > larry.choice && player.choice > curly.choice) ||
                   (player.order == 0 && curly.match == true && moe.match == true && player.choice > curly.choice && player.choice > moe.choice) ||
                   (player.order == 0 && larry.match == true && moe.match == true && player.choice > larry.choice && player.choice > moe.choice) ||
                   (larry.order = 0 && curly.match == true && player.match == true && player.choice > larry.choice && player.choice > curly.choice) ||
                   (larry.order = 0 && moe.match == true && player.match == true &&player.choice > larry.choice && player.choice > moe.choice) ||
                   (curly.order = 0 && larry.match == true && player.match == true &&player.choice > larry.choice && player.choice > curly.choice) ||
                   (curly.order = 0 && moe.match == true && player.match == true &&player.choice > curly.choice && player.choice > curly.choice) ||
                   (moe.order = 0 && curly.match == true && player.match == true &&player.choice > moe.choice && player.choice > curly.choice) ||
                   (moe.order = 0 && larry.match == true && player.match == true &&player.choice > larry.choice && player.choice > moe.choice)) {
                    cout << "Player takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37){
                        player.tScore += 16;
                        player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                    }
                    // No one played Q spades
                    else {
                        player.tScore += 3;
                        player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                    }
                }
                // Larry wins trick
                else if((larry.order == 0 && player.match == true && curly.match == true && larry.choice > player.choice && larry.choice > curly.choice) ||
                       (larry.order == 0 && curly.match == true && moe.match == true && larry.choice > curly.choice && larry.choice > moe.choice) ||
                       (larry.order == 0 && player.match == true && moe.match == true && larry.choice > player.choice && larry.choice > moe.choice) ||
                       (player.order = 0 && curly.match == true && larry.match == true && larry.choice > player.choice && larry.choice > curly.choice) ||
                       (player.order = 0 && moe.match == true && larry.match == true && larry.choice > player.choice && larry.choice > moe.choice) ||
                       (curly.order = 0 && player.match == true && larry.match == true && larry.choice > player.choice && larry.choice > curly.choice) ||
                       (curly.order = 0 && moe.match == true && larry.match == true && larry.choice > curly.choice && larry.choice > curly.choice) ||
                       (moe.order = 0 && curly.match == true && larry.match == true && larry.choice > moe.choice && larry.choice > curly.choice) ||
                       (moe.order = 0 && player.match == true && larry.match == true && larry.choice > player.choice && larry.choice > moe.choice)) {
                
                        cout << "larry takes the trick." << endl;
                        // Check for Q spades
                        if (player.choice == 37 || curly.choice == 37 || moe.choice == 37 || larry.choice == 37){
                            larry.tScore += 16;
                            larry.order = 0; player.order = 1; curly.order = 2; moe.order = 3;
                        }
                        // No one played Q spades
                        else {
                            larry.tScore += 3;
                            larry.order = 0; player.order = 1; curly.order = 2; moe.order = 3;
                        }
                    }
                // curly wins trick
                else if((curly.order == 0 && player.match == true && larry.match == true && curly.choice > player.choice && curly.choice > larry.choice) ||
                       (curly.order == 0 && larry.match == true && moe.match == true && curly.choice > larry.choice && curly.choice > moe.choice) ||
                       (curly.order == 0 && player.match == true && moe.match == true && curly.choice > player.choice && curly.choice > moe.choice) ||
                       (player.order = 0 && larry.match == true && curly.match == true && curly.choice > player.choice && curly.choice > larry.choice) ||
                       (player.order = 0 && moe.match == true && curly.match == true && curly.choice > player.choice && curly.choice > moe.choice) ||
                       (larry.order = 0 && player.match == true && curly.match == true && curly.choice > player.choice && curly.choice > larry.choice) ||
                       (larry.order = 0 && moe.match == true && curly.match == true && curly.choice > larry.choice && curly.choice > larry.choice) ||
                       (moe.order = 0 && larry.match == true && curly.match == true && curly.choice > moe.choice && curly.choice > larry.choice) ||
                       (moe.order = 0 && player.match == true && curly.match == true && curly.choice > player.choice && curly.choice > moe.choice)) {
                
                        cout << "curly takes the trick." << endl;
                        // Check for Q spades
                        if (player.choice == 37 || larry.choice == 37 || moe.choice == 37 || curly.choice == 37){
                            curly.tScore += 16;
                            curly.order = 0; player.order = 1; larry.order = 2; moe.order = 3;
                        }
                        // No one played Q spades
                        else {
                            curly.tScore += 3;
                            curly.order = 0; player.order = 1; larry.order = 2; moe.order = 3;
                        }
                    }
                // moe wins trick
                else if((moe.order == 0 && player.match == true && larry.match == true && moe.choice > player.choice && moe.choice > larry.choice) ||
                       (moe.order == 0 && larry.match == true && curly.match == true && moe.choice > larry.choice && moe.choice > curly.choice) ||
                       (moe.order == 0 && player.match == true && curly.match == true && moe.choice > player.choice && moe.choice > curly.choice) ||
                       (player.order = 0 && larry.match == true && moe.match == true && moe.choice > player.choice && moe.choice > larry.choice) ||
                       (player.order = 0 && curly.match == true && moe.match == true && moe.choice > player.choice && moe.choice > curly.choice) ||
                       (larry.order = 0 && player.match == true && moe.match == true && moe.choice > player.choice && moe.choice > larry.choice) ||
                       (larry.order = 0 && curly.match == true && moe.match == true && moe.choice > larry.choice && moe.choice > larry.choice) ||
                       (curly.order = 0 && larry.match == true && moe.match == true && moe.choice > curly.choice && moe.choice > larry.choice) ||
                       (curly.order = 0 && player.match == true && moe.match == true && moe.choice > player.choice && moe.choice > curly.choice)) {
                
                        cout << "moe takes the trick." << endl;
                        // Check for Q spades
                        if (player.choice == 37 || larry.choice == 37 || curly.choice == 37 || moe.choice == 37){
                            moe.tScore += 16;
                            moe.order = 0; player.order = 1; larry.order = 2; curly.order = 3;
                        }
                        // No one played Q spades
                        else {
                            moe.tScore += 3;
                            moe.order = 0; player.order = 1; larry.order = 2; curly.order = 3;
                        }
                    }
                }           
// Two Play Hearts
            else if ((player.choice > 39 && larry.choice > 39) ||
                (player.choice > 39 && curly.choice > 39) ||
                (player.choice > 39 && moe.choice > 39)   ||
                (larry.choice > 39 && curly.choice > 39)  ||
                (larry.choice > 39 && moe.choice > 39)    ||
                (curly.choice > 39 && moe.choice > 39)){
        // No Queen Spades played
                if(player.choice != 37 && larry.choice != 37 && curly.choice != 37 && moe.choice != 37) {
                    cout << "Trick worth two points." << endl;    
                }
                else if(larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ) {
                    cout << "Trick worth fifteen  points." << endl;    
                }
            // player wins trick
                    if((player.order == 0 && player.choice > 39 && larry.choice > 39 && player.choice > larry.choice) ||
                       (player.order == 0 && player.choice > 39 && curly.choice > 39 && player.choice > curly.choice) ||
                       (player.order == 0 && player.choice > 39 && moe.choice > 39 && player.choice > moe.choice) ||
                       (player.order == 0 && player.choice < 40 && larry.choice > 39 && curly.choice > 39) ||
                       (player.order == 0 && player.choice < 40 && larry.choice > 39 && moe.choice > 39) ||
                       (player.order == 0 && player.choice < 40 && moe.choice > 39 && curly.choice > 39) ||
                       (moe.order == 0 && moe.choice > 39 && player.match == true && player.choice > moe.choice) ||
                       (larry.order == 0 && larry.choice > 39 && player.match == true && player.choice > larry.choice) ||
                       (curly.order == 0 && curly.choice > 39 && player.match == true && player.choice > curly.choice)) {
                
                        cout << "player takes the trick." << endl;
                        // Check for Q spades
                        if (moe.choice == 37 || larry.choice == 37 || curly.choice == 37 || player.choice == 37){
                            player.tScore += 15;
                            player.order = 0; moe.order = 1; larry.order = 2; curly.order = 3;
                        }
                        // No one played Q spades
                        else {
                            player.tScore += 2;
                            player.order = 0; moe.order = 1; larry.order = 2; curly.order = 3;
                        }
                    }
            // larry wins trick
                else if((larry.order == 0 && larry.choice > 39 && player.choice > 39 && larry.choice > player.choice) ||
                       (larry.order == 0 && larry.choice > 39 && curly.choice > 39 && larry.choice > curly.choice) ||
                       (larry.order == 0 && larry.choice > 39 && moe.choice > 39 && larry.choice > moe.choice) ||
                       (larry.order == 0 && larry.choice < 40 && player.choice > 39 && curly.choice > 39) ||
                       (larry.order == 0 && larry.choice < 40 && player.choice > 39 && moe.choice > 39) ||
                       (larry.order == 0 && larry.choice < 40 && moe.choice > 39 && curly.choice > 39) ||
                       (moe.order == 0 && moe.choice > 39 && larry.match == true && larry.choice > moe.choice) ||
                       (player.order == 0 && player.choice > 39 && larry.match == true && larry.choice > player.choice) ||
                       (curly.order == 0 && curly.choice > 39 && larry.match == true && larry.choice > curly.choice)) {
                
                        cout << "larry takes the trick." << endl;
                        // Check for Q spades
                        if (moe.choice == 37 || player.choice == 37 || curly.choice == 37 || larry.choice == 37){
                            larry.tScore += 15;
                            larry.order = 0; moe.order = 1; player.order = 2; curly.order = 3;
                        }
                        // No one played Q spades
                        else {
                            larry.tScore += 2;
                            larry.order = 0; moe.order = 1; player.order = 2; curly.order = 3;
                        }
                    }
            // curly wins trick
                else if((curly.order == 0 && curly.choice > 39 && player.choice > 39 && curly.choice > player.choice) ||
                       (curly.order == 0 && curly.choice > 39 && larry.choice > 39 && curly.choice > larry.choice) ||
                       (curly.order == 0 && curly.choice > 39 && moe.choice > 39 && curly.choice > moe.choice) ||
                       (curly.order == 0 && curly.choice < 40 && player.choice > 39 && larry.choice > 39) ||
                       (curly.order == 0 && curly.choice < 40 && player.choice > 39 && moe.choice > 39) ||
                       (curly.order == 0 && curly.choice < 40 && moe.choice > 39 && larry.choice > 39) ||
                       (moe.order == 0 && moe.choice > 39 && curly.match == true && curly.choice > moe.choice) ||
                       (player.order == 0 && player.choice > 39 && curly.match == true && curly.choice > player.choice) ||
                       (larry.order == 0 && larry.choice > 39 && curly.match == true && curly.choice > larry.choice)) {
                
                        cout << "curly takes the trick." << endl;
                        // Check for Q spades
                        if (moe.choice == 37 || player.choice == 37 || larry.choice == 37 || curly.choice == 37){
                            curly.tScore += 15;
                            curly.order = 0; moe.order = 1; player.order = 2; larry.order = 3;
                        }
                        // No one played Q spades
                        else {
                            curly.tScore += 2;
                            curly.order = 0; moe.order = 1; player.order = 2; larry.order = 3;
                        }
                    }
                    // moe wins trick
                else if((moe.order == 0 && moe.choice > 39 && player.choice > 39 && moe.choice > player.choice) ||
                       (moe.order == 0 && moe.choice > 39 && larry.choice > 39 && moe.choice > larry.choice) ||
                       (moe.order == 0 && moe.choice > 39 && curly.choice > 39 && moe.choice > curly.choice) ||
                       (moe.order == 0 && moe.choice < 40 && player.choice > 39 && larry.choice > 39) ||
                       (moe.order == 0 && moe.choice < 40 && player.choice > 39 && curly.choice > 39) ||
                       (moe.order == 0 && moe.choice < 40 && curly.choice > 39 && larry.choice > 39) ||
                       (curly.order == 0 && curly.choice > 39 && moe.match == true && moe.choice > curly.choice) ||
                       (player.order == 0 && player.choice > 39 && moe.match == true && moe.choice > player.choice) ||
                       (larry.order == 0 && larry.choice > 39 && moe.match == true && moe.choice > larry.choice)) {
                
                        cout << "moe takes the trick." << endl;
                        // Check for Q spades
                        if (curly.choice == 37 || player.choice == 37 || larry.choice == 37 || moe.choice == 37){
                            moe.tScore += 15;
                            moe.order = 0; curly.order = 1; player.order = 2; larry.order = 3;
                        }
                        // No one played Q spades
                        else {
                            moe.tScore += 2;
                            moe.order = 0; curly.order = 1; player.order = 2; larry.order = 3;
                        }
                    }
                }
// One person played a heart
            else if (player.choice > 39 || larry.choice > 39 || curly.choice > 39 || moe.choice > 39) {
            // No Queen spades played
                if(player.choice != 37 && larry.choice != 37 && curly.choice != 37 && moe.choice != 37) {
                    cout << "Trick worth one point." << endl;    
                }
                else if(larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ) {
                    cout << "Trick worth fourteen points." << endl;    
                }
                // Player wins trick
                if((player.order == 0 && player.choice > 39 && larry.choice < 40 && curly.choice < 40 && moe.choice < 40) ||
                   (player.order == 0 && player.choice < 40 && larry.choice > 39 && (curly.match == true && moe.match == true && player.choice > curly.choice && player.choice > moe.choice) || (curly.match == true && moe.match == false && moe.choice < 40 && player.choice > curly.choice) || (moe.match == true && curly.match == false && curly.choice < 40 && player.choice > moe.choice)) ||
                   (player.order == 0 && player.choice < 40 && curly.choice > 39 && (larry.match == true && moe.match == true && player.choice > larry.choice && player.choice > moe.choice) || (larry.match == true && moe.match == false && moe.choice < 40 && player.choice > larry.choice) || (moe.match == true && larry.match == false && larry.choice < 40 && player.choice > moe.choice)) ||	
                   (player.order == 0 && player.choice < 40 && moe.choice > 39 && (larry.match == true && curly.match == true && player.choice > larry.choice && player.choice > curly.choice) || (larry.match == true && curly.match == false && curly.choice < 40 && player.choice > larry.choice) || (curly.match == true && larry.match == false && larry.choice < 40 && player.choice > curly.choice)) ||
                   (larry.order == 0 && larry.choice < 40 && player.match == true && moe.match == true && curly.choice > 39 && player.choice > larry.choice && player.choice > moe.choice)  ||
                   (larry.order == 0 && larry.choice < 40 && player.match == true && moe.match == false && moe.choice < 40 && curly.choice > 39 && player.choice > larry.choice && player.choice > moe.choice)  ||
                   (larry.order == 0 && larry.choice < 40 && player.match == true && curly.match == true && moe.choice > 39 && player.choice > larry.choice && player.choice > curly.choice)||
                   (larry.order == 0 && larry.choice < 40 && player.match == true && curly.match == false && curly.choice < 40 && moe.choice > 39 && player.choice > larry.choice && player.choice > curly.choice)||
                   (curly.order == 0 && curly.choice < 40 && player.match == true && moe.match == true && larry.choice > 39 && player.choice > curly.choice && player.choice > moe.choice)  ||
                   (curly.order == 0 && curly.choice < 40 && player.match == true && moe.match == false && moe.choice < 40 && larry.choice > 39 && player.choice > curly.choice && player.choice > moe.choice)  ||
                   (curly.order == 0 && curly.choice < 40 && player.match == true && larry.match == true && moe.choice > 39 && player.choice > curly.choice && player.choice > larry.choice)||
                   (curly.order == 0 && curly.choice < 40 && player.match == true && larry.match == false && larry.choice < 40 && moe.choice > 39 && player.choice > curly.choice && player.choice > larry.choice)||
                   (moe.order == 0 && moe.choice < 40 && player.match == true && curly.match == true && larry.choice > 39 && player.choice > moe.choice && player.choice > curly.choice)  ||
                   (moe.order == 0 && moe.choice < 40 && player.match == true && curly.match == false && curly.choice < 40 && larry.choice > 39 && player.choice > moe.choice && player.choice > curly.choice)  ||
                   (moe.order == 0 && moe.choice < 40 && player.match == true && larry.match == true && curly.choice > 39 && player.choice > moe.choice && player.choice > larry.choice)||
                   (moe.order == 0 && moe.choice < 40 && player.match == true && larry.match == false && larry.choice < 40 && curly.choice > 39 && player.choice > moe.choice && player.choice > larry.choice))
                {
                    cout << "Player takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37){
                        player.tScore += 14;
                        player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                    }
                    // No one played Q spades
                    else {
                        player.tScore += 1;
                        player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                    }
                }
                // Larry wins trick
                else if((larry.order == 0 && larry.choice > 39 && player.choice < 40 && curly.choice < 40 && moe.choice < 40) ||
                   (larry.order == 0 && larry.choice < 40 && player.choice > 39 && (curly.match == true && moe.match == true && larry.choice > curly.choice && larry.choice > moe.choice) || (curly.match == true && moe.match == false && moe.choice < 40 && larry.choice > curly.choice) || (moe.match == true && curly.match == false && curly.choice < 40 && larry.choice > moe.choice)) ||
                   (larry.order == 0 && larry.choice < 40 && curly.choice > 39 && (player.match == true && moe.match == true && larry.choice > player.choice && larry.choice > moe.choice) || (player.match == true && moe.match == false && moe.choice < 40 && larry.choice > player.choice) || (moe.match == true && player.match == false && player.choice < 40 && larry.choice > moe.choice)) ||	
                   (larry.order == 0 && larry.choice < 40 && moe.choice > 39 && (player.match == true && curly.match == true && larry.choice > player.choice && larry.choice > curly.choice) || (player.match == true && curly.match == false && curly.choice < 40 && larry.choice > player.choice) || (curly.match == true && player.match == false && player.choice < 40 && larry.choice > curly.choice)) ||
                   (player.order == 0 && player.choice < 40 && larry.match == true && moe.match == true && curly.choice > 39 && larry.choice > player.choice && larry.choice > moe.choice)  ||
                   (player.order == 0 && player.choice < 40 && larry.match == true && moe.match == false && moe.choice < 40 && curly.choice > 39 && larry.choice > player.choice && larry.choice > moe.choice)  ||
                   (player.order == 0 && player.choice < 40 && larry.match == true && curly.match == true && moe.choice > 39 && larry.choice > player.choice && larry.choice > curly.choice)||
                   (player.order == 0 && player.choice < 40 && larry.match == true && curly.match == false && curly.choice < 40 && moe.choice > 39 && larry.choice > player.choice && larry.choice > curly.choice)||
                   (curly.order == 0 && curly.choice < 40 && larry.match == true && moe.match == true && player.choice > 39 && larry.choice > curly.choice && larry.choice > moe.choice)  ||
                   (curly.order == 0 && curly.choice < 40 && larry.match == true && moe.match == false && moe.choice < 40 && player.choice > 39 && larry.choice > curly.choice && larry.choice > moe.choice)  ||
                   (curly.order == 0 && curly.choice < 40 && larry.match == true && player.match == true && moe.choice > 39 && larry.choice > curly.choice && larry.choice > player.choice)||
                   (curly.order == 0 && curly.choice < 40 && larry.match == true && player.match == false && player.choice < 40 && moe.choice > 39 && larry.choice > curly.choice && larry.choice > player.choice)||
                   (moe.order == 0 && moe.choice < 40 && larry.match == true && curly.match == true && player.choice > 39 && larry.choice > moe.choice && larry.choice > curly.choice)  ||
                   (moe.order == 0 && moe.choice < 40 && larry.match == true && curly.match == false && curly.choice < 40 && player.choice > 39 && larry.choice > moe.choice && larry.choice > curly.choice)  ||
                   (moe.order == 0 && moe.choice < 40 && larry.match == true && player.match == true && curly.choice > 39 && larry.choice > moe.choice && larry.choice > player.choice)||
                   (moe.order == 0 && moe.choice < 40 && larry.match == true && player.match == false && player.choice < 40 && curly.choice > 39 && larry.choice > moe.choice && larry.choice > player.choice))
                {
                    cout << "Larry takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ){
                        larry.tScore += 14;
                        player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2;
                    }
                    // No one played Q spades
                    else {
                        larry.tScore += 1;
                        player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2;
                    }                    
                }
                // Curly wins trick
                else if((curly.order == 0 && curly.choice > 39 && player.choice < 40 && larry.choice < 40 && moe.choice < 40) ||
                   (curly.order == 0 && curly.choice < 40 && player.choice > 39 && (larry.match == true && moe.match == true && curly.choice > larry.choice && curly.choice > moe.choice) || (larry.match == true && moe.match == false && moe.choice < 40 && curly.choice > larry.choice) || (moe.match == true && larry.match == false && larry.choice < 40 && curly.choice > moe.choice)) ||
                   (curly.order == 0 && curly.choice < 40 && larry.choice > 39 && (player.match == true && moe.match == true && curly.choice > player.choice && curly.choice > moe.choice) || (player.match == true && moe.match == false && moe.choice < 40 && curly.choice > player.choice) || (moe.match == true && player.match == false && player.choice < 40 && curly.choice > moe.choice)) ||	
                   (curly.order == 0 && curly.choice < 40 && moe.choice > 39 && (player.match == true && larry.match == true && curly.choice > player.choice && curly.choice > larry.choice) || (player.match == true && larry.match == false && larry.choice < 40 && curly.choice > player.choice) || (larry.match == true && player.match == false && player.choice < 40 && curly.choice > larry.choice)) ||
                   (player.order == 0 && player.choice < 40 && curly.match == true && moe.match == true && larry.choice > 39 && curly.choice > player.choice && curly.choice > moe.choice)  ||
                   (player.order == 0 && player.choice < 40 && curly.match == true && moe.match == false && moe.choice < 40 && larry.choice > 39 && curly.choice > player.choice && curly.choice > moe.choice)  ||
                   (player.order == 0 && player.choice < 40 && curly.match == true && larry.match == true && moe.choice > 39 && curly.choice > player.choice && curly.choice > larry.choice)||
                   (player.order == 0 && player.choice < 40 && curly.match == true && larry.match == false && larry.choice < 40 && moe.choice > 39 && curly.choice > player.choice && curly.choice > larry.choice)||
                   (larry.order == 0 && larry.choice < 40 && curly.match == true && moe.match == true && player.choice > 39 && curly.choice > larry.choice && curly.choice > moe.choice)  ||
                   (larry.order == 0 && larry.choice < 40 && curly.match == true && moe.match == false && moe.choice < 40 && player.choice > 39 && curly.choice > larry.choice && curly.choice > moe.choice)  ||
                   (larry.order == 0 && larry.choice < 40 && curly.match == true && player.match == true && moe.choice > 39 && curly.choice > larry.choice && curly.choice > player.choice)||
                   (larry.order == 0 && larry.choice < 40 && curly.match == true && player.match == false && player.choice < 40 && moe.choice > 39 && curly.choice > larry.choice && curly.choice > player.choice)||
                   (moe.order == 0 && moe.choice < 40 && curly.match == true && larry.match == true && player.choice > 39 && curly.choice > moe.choice && curly.choice > larry.choice)  ||
                   (moe.order == 0 && moe.choice < 40 && curly.match == true && larry.match == false && larry.choice < 40 && player.choice > 39 && curly.choice > moe.choice && curly.choice > larry.choice)  ||
                   (moe.order == 0 && moe.choice < 40 && curly.match == true && player.match == true && larry.choice > 39 && curly.choice > moe.choice && curly.choice > player.choice)||
                   (moe.order == 0 && moe.choice < 40 && curly.match == true && player.match == false && player.choice < 40 && larry.choice > 39 && curly.choice > moe.choice && curly.choice > player.choice))
                {

                    cout << "Curly takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ){
                        curly.tScore += 14;
                        player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1;
                    }
                    // No one played Q spades
                    else {
                        curly.tScore += 1;
                        player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1;
                    }
                }
                // Moe wins trick
                else if((moe.order == 0 && moe.choice > 39 && player.choice < 40 && larry.choice < 40 && curly.choice < 40) ||
                   (moe.order == 0 && moe.choice < 40 && player.choice > 39 && (larry.match == true && curly.match == true && moe.choice > larry.choice && moe.choice > curly.choice) || (larry.match == true && curly.match == false && curly.choice < 40 && moe.choice > larry.choice) || (curly.match == true && larry.match == false && larry.choice < 40 && moe.choice > curly.choice)) ||
                   (moe.order == 0 && moe.choice < 40 && larry.choice > 39 && (player.match == true && curly.match == true && moe.choice > player.choice && moe.choice > curly.choice) || (player.match == true && curly.match == false && curly.choice < 40 && moe.choice > player.choice) || (curly.match == true && player.match == false && player.choice < 40 && moe.choice > curly.choice)) ||	
                   (moe.order == 0 && moe.choice < 40 && curly.choice > 39 && (player.match == true && larry.match == true && moe.choice > player.choice && moe.choice > larry.choice) || (player.match == true && larry.match == false && larry.choice < 40 && moe.choice > player.choice) || (larry.match == true && player.match == false && player.choice < 40 && moe.choice > larry.choice)) ||
                   (player.order == 0 && player.choice < 40 && moe.match == true && curly.match == true && larry.choice > 39 && moe.choice > player.choice && moe.choice > curly.choice)  ||
                   (player.order == 0 && player.choice < 40 && moe.match == true && curly.match == false && curly.choice < 40 && larry.choice > 39 && moe.choice > player.choice && moe.choice > curly.choice)  ||
                   (player.order == 0 && player.choice < 40 && moe.match == true && larry.match == true && curly.choice > 39 && moe.choice > player.choice && moe.choice > larry.choice)||
                   (player.order == 0 && player.choice < 40 && moe.match == true && larry.match == false && larry.choice < 40 && curly.choice > 39 && moe.choice > player.choice && moe.choice > larry.choice)||
                   (larry.order == 0 && larry.choice < 40 && moe.match == true && curly.match == true && player.choice > 39 && moe.choice > larry.choice && moe.choice > curly.choice)  ||
                   (larry.order == 0 && larry.choice < 40 && moe.match == true && curly.match == false && curly.choice < 40 && player.choice > 39 && moe.choice > larry.choice && moe.choice > curly.choice)  ||
                   (larry.order == 0 && larry.choice < 40 && moe.match == true && player.match == true && curly.choice > 39 && moe.choice > larry.choice && moe.choice > player.choice)||
                   (larry.order == 0 && larry.choice < 40 && moe.match == true && player.match == false && player.choice < 40 && curly.choice > 39 && moe.choice > larry.choice && moe.choice > player.choice)||
                   (curly.order == 0 && curly.choice < 40 && moe.match == true && larry.match == true && player.choice > 39 && moe.choice > curly.choice && moe.choice > larry.choice)  ||
                   (curly.order == 0 && curly.choice < 40 && moe.match == true && larry.match == false && larry.choice < 40 && player.choice > 39 && moe.choice > curly.choice && moe.choice > larry.choice)  ||
                   (curly.order == 0 && curly.choice < 40 && moe.match == true && player.match == true && larry.choice > 39 && moe.choice > curly.choice && moe.choice > player.choice)||
                   (curly.order == 0 && curly.choice < 40 && moe.match == true && player.match == false && player.choice < 40 && larry.choice > 39 && moe.choice > curly.choice && moe.choice > player.choice))
                {

                    cout << "Moe takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37){
                        moe.tScore += 14;
                        player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0;
                    }
                    // No one played Q spades
                    else {
                        moe.tScore += 1;
                        player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0;
                    }
                }
            }
// No one played a heart
            else if (player.choice < 40 && larry.choice < 40 && curly.choice < 40 && moe.choice < 40){
                if(player.choice != 37 && larry.choice != 37 && curly.choice != 37 && moe.choice != 37) {
                    cout << "Trick worth no points." << endl;    
                }
                else if(larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ) {
                    cout << "Trick worth thirteen points." << endl;    
                }
            // Player wins trick
                if((player.order == 0 && moe.match == true && larry.match == true && curly.match == true && player.choice > larry.choice && player.choice > curly.choice && player.choice > moe.choice) ||
                    (player.order == 0 && moe.match == true && larry.match == true && curly.match == false && player.choice > larry.choice && player.choice > moe.choice) ||
                    (player.order == 0 && curly.match == true && larry.match == true && moe.match == false && player.choice > larry.choice && player.choice > curly.choice) ||
                    (player.order == 0 && moe.match == true && curly.match == true && larry.match == false && player.choice > curly.choice && player.choice > moe.choice) ||
                    (player.order == 0 && moe.match == true && larry.match == true && curly.match == false && player.choice > larry.choice && player.choice > moe.choice) ||
                    (player.order == 0 && moe.match == true && larry.match == false && curly.match == false && player.choice > moe.choice) ||		
                    (player.order == 0 && larry.match == true && moe.match == false && curly.match == false && player.choice > larry.choice) ||
                    (player.order == 0 && curly.match == true && larry.match == false && moe.match == false && player.choice > curly.choice) ||
                    (player.order == 0 && moe.match == false && larry.match == false && curly.match == false) ||
		    (larry.order == 0 && moe.match == true && player.match == true && curly.match == true && player.choice > larry.choice && player.choice > curly.choice && player.choice > moe.choice) ||
                    (larry.order == 0 && curly.match == true && player.match == true && moe.match == false && player.choice > larry.choice && player.choice > curly.choice) ||
                    (larry.order == 0 && moe.match == true && player.match == true && curly.match == false && player.choice > larry.choice && player.choice > moe.choice) ||                   
                    (larry.order == 0 && player.match == true && moe.match == false && curly.match == false && player.choice > larry.choice) || 
		    (curly.order == 0 && moe.match == true && player.match == true && larry.match == true && player.choice > curly.choice && player.choice > larry.choice && player.choice > moe.choice) ||
                    (curly.order == 0 && larry.match == true && player.match == true && moe.match == false && player.choice > curly.choice && player.choice > larry.choice) ||
                    (curly.order == 0 && moe.match == true && player.match == true && larry.match == false && player.choice > curly.choice && player.choice > moe.choice) ||                   
                    (curly.order == 0 && player.match == true && moe.match == false && larry.match == false && player.choice > curly.choice) || 
		    (moe.order == 0 && curly.match == true && player.match == true && larry.match == true && player.choice > moe.choice && player.choice > larry.choice && player.choice > curly.choice) ||
                    (moe.order == 0 && larry.match == true && player.match == true && curly.match == false && player.choice > moe.choice && player.choice > larry.choice) ||
                    (moe.order == 0 && curly.match == true && player.match == true && larry.match == false && player.choice > moe.choice && player.choice > curly.choice) ||                   
                    (moe.order == 0 && player.match == true && curly.match == false && larry.match == false && player.choice > moe.choice)){
                    
                    cout << "Player takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37){
                        player.tScore += 13;
                        player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                    }
                    // No one played Q spades
                    else {
                        player.tScore += 0;
                        player.order = 0; larry.order = 1; curly.order = 2; moe.order = 3;
                    }
                }
                // Larry wins trick
                
                else if((larry.order == 0 && moe.match == true && player.match == true && curly.match == true && larry.choice > player.choice && larry.choice > curly.choice && larry.choice > moe.choice) ||
                    (larry.order == 0 && moe.match == true && player.match == true && curly.match == false && larry.choice > player.choice && larry.choice > moe.choice) ||
                    (larry.order == 0 && curly.match == true && player.match == true && moe.match == false && larry.choice > player.choice && larry.choice > curly.choice) ||
                    (larry.order == 0 && moe.match == true && curly.match == true && player.match == false && larry.choice > curly.choice && larry.choice > moe.choice) ||
                    (larry.order == 0 && moe.match == true && player.match == true && curly.match == false && larry.choice > player.choice && larry.choice > moe.choice) ||
                    (larry.order == 0 && moe.match == true && player.match == false && curly.match == false && larry.choice > moe.choice) ||		
                    (larry.order == 0 && player.match == true && moe.match == false && curly.match == false && larry.choice > player.choice) ||
                    (larry.order == 0 && curly.match == true && player.match == false && moe.match == false && larry.choice > curly.choice) ||
                    (larry.order == 0 && moe.match == false && player.match == false && curly.match == false) ||
		    (player.order == 0 && moe.match == true && larry.match == true && curly.match == true && larry.choice > player.choice && larry.choice > curly.choice && larry.choice > moe.choice) ||
                    (player.order == 0 && curly.match == true && larry.match == true && moe.match == false && larry.choice > player.choice && larry.choice > curly.choice) ||
                    (player.order == 0 && moe.match == true && larry.match == true && curly.match == false && larry.choice > player.choice && larry.choice > moe.choice) ||                   
                    (player.order == 0 && larry.match == true && moe.match == false && curly.match == false && larry.choice > player.choice) || 
		    (curly.order == 0 && moe.match == true && larry.match == true && player.match == true && larry.choice > curly.choice && larry.choice > player.choice && larry.choice > moe.choice) ||
                    (curly.order == 0 && player.match == true && larry.match == true && moe.match == false && larry.choice > curly.choice && larry.choice > player.choice) ||
                    (curly.order == 0 && moe.match == true && larry.match == true && player.match == false && larry.choice > curly.choice && larry.choice > moe.choice) ||                   
                    (curly.order == 0 && larry.match == true && moe.match == false && player.match == false && larry.choice > curly.choice) || 
		    (moe.order == 0 && curly.match == true && larry.match == true && player.match == true && larry.choice > moe.choice && larry.choice > player.choice && larry.choice > curly.choice) ||
                    (moe.order == 0 && player.match == true && larry.match == true && curly.match == false && larry.choice > moe.choice && larry.choice > player.choice) ||
                    (moe.order == 0 && curly.match == true && larry.match == true && player.match == false && larry.choice > moe.choice && larry.choice > curly.choice) ||                   
                    (moe.order == 0 && larry.match == true && curly.match == false && player.match == false && larry.choice > moe.choice)) {
                    
                    cout << "Larry takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ){
                        larry.tScore += 13;
                        player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2;
                    }
                    // No one played Q spades
                    else {
                        larry.tScore += 0;
                        player.order = 3; larry.order = 0; curly.order = 1; moe.order = 2;
                    }                    
                }
                // Curly wins trick
                else if((curly.order == 0 && moe.match == true && player.match == true && larry.match == true && curly.choice > player.choice && curly.choice > larry.choice && curly.choice > moe.choice) ||
                    (curly.order == 0 && moe.match == true && player.match == true && larry.match == false && curly.choice > player.choice && curly.choice > moe.choice) ||
                    (curly.order == 0 && larry.match == true && player.match == true && moe.match == false && curly.choice > player.choice && curly.choice > larry.choice) ||
                    (curly.order == 0 && moe.match == true && larry.match == true && player.match == false && curly.choice > larry.choice && curly.choice > moe.choice) ||
                    (curly.order == 0 && moe.match == true && player.match == true && larry.match == false && curly.choice > player.choice && curly.choice > moe.choice) ||
                    (curly.order == 0 && moe.match == true && player.match == false && larry.match == false && curly.choice > moe.choice) ||		
                    (curly.order == 0 && player.match == true && moe.match == false && larry.match == false && curly.choice > player.choice) ||
                    (curly.order == 0 && larry.match == true && player.match == false && moe.match == false && curly.choice > larry.choice) ||
                    (curly.order == 0 && moe.match == false && player.match == false && larry.match == false) ||
		    (player.order == 0 && moe.match == true && curly.match == true && larry.match == true && curly.choice > player.choice && curly.choice > larry.choice && curly.choice > moe.choice) ||
                    (player.order == 0 && larry.match == true && curly.match == true && moe.match == false && curly.choice > player.choice && curly.choice > larry.choice) ||
                    (player.order == 0 && moe.match == true && curly.match == true && larry.match == false && curly.choice > player.choice && curly.choice > moe.choice) ||                   
                    (player.order == 0 && curly.match == true && moe.match == false && larry.match == false && curly.choice > player.choice) || 
		    (larry.order == 0 && moe.match == true && curly.match == true && player.match == true && curly.choice > larry.choice && curly.choice > player.choice && curly.choice > moe.choice) ||
                    (larry.order == 0 && player.match == true && curly.match == true && moe.match == false && curly.choice > larry.choice && curly.choice > player.choice) ||
                    (larry.order == 0 && moe.match == true && curly.match == true && player.match == false && curly.choice > larry.choice && curly.choice > moe.choice) ||                   
                    (larry.order == 0 && curly.match == true && moe.match == false && player.match == false && curly.choice > larry.choice) || 
		    (moe.order == 0 && larry.match == true && curly.match == true && player.match == true && curly.choice > moe.choice && curly.choice > player.choice && curly.choice > larry.choice) ||
                    (moe.order == 0 && player.match == true && curly.match == true && larry.match == false && curly.choice > moe.choice && curly.choice > player.choice) ||
                    (moe.order == 0 && larry.match == true && curly.match == true && player.match == false && curly.choice > moe.choice && curly.choice > larry.choice) ||                   
                    (moe.order == 0 && curly.match == true && larry.match == false && player.match == false && curly.choice > moe.choice)) {
                    
                    cout << "Curly takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37 ){
                        curly.tScore += 13;
                        player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1;
                    }
                    // No one played Q spades
                    else {
                        curly.tScore += 0;
                        player.order = 2; larry.order = 3; curly.order = 0; moe.order = 1;
                    }
                }
                // Moe wins trick
                else if((moe.order == 0 && curly.match == true && player.match == true && larry.match == true && moe.choice > player.choice && moe.choice > larry.choice && moe.choice > curly.choice) ||
                    (moe.order == 0 && curly.match == true && player.match == true && larry.match == false && moe.choice > player.choice && moe.choice > curly.choice) ||
                    (moe.order == 0 && larry.match == true && player.match == true && curly.match == false && moe.choice > player.choice && moe.choice > larry.choice) ||
                    (moe.order == 0 && curly.match == true && larry.match == true && player.match == false && moe.choice > larry.choice && moe.choice > curly.choice) ||
                    (moe.order == 0 && curly.match == true && player.match == true && larry.match == false && moe.choice > player.choice && moe.choice > curly.choice) ||
                    (moe.order == 0 && curly.match == true && player.match == false && larry.match == false && moe.choice > curly.choice) ||		
                    (moe.order == 0 && player.match == true && curly.match == false && larry.match == false && moe.choice > player.choice) ||
                    (moe.order == 0 && larry.match == true && player.match == false && curly.match == false && moe.choice > larry.choice) ||
                    (moe.order == 0 && curly.match == false && player.match == false && larry.match == false) ||
		    (player.order == 0 && curly.match == true && moe.match == true && larry.match == true && moe.choice > player.choice && moe.choice > larry.choice && moe.choice > curly.choice) ||
                    (player.order == 0 && larry.match == true && moe.match == true && curly.match == false && moe.choice > player.choice && moe.choice > larry.choice) ||
                    (player.order == 0 && curly.match == true && moe.match == true && larry.match == false && moe.choice > player.choice && moe.choice > curly.choice) ||                   
                    (player.order == 0 && moe.match == true && curly.match == false && larry.match == false && moe.choice > player.choice) || 
		    (larry.order == 0 && curly.match == true && moe.match == true && player.match == true && moe.choice > larry.choice && moe.choice > player.choice && moe.choice > curly.choice) ||
                    (larry.order == 0 && player.match == true && moe.match == true && curly.match == false && moe.choice > larry.choice && moe.choice > player.choice) ||
                    (larry.order == 0 && curly.match == true && moe.match == true && player.match == false && moe.choice > larry.choice && moe.choice > curly.choice) ||                   
                    (larry.order == 0 && moe.match == true && curly.match == false && player.match == false && moe.choice > larry.choice) || 
		    (curly.order == 0 && larry.match == true && moe.match == true && player.match == true && moe.choice > curly.choice && moe.choice > player.choice && moe.choice > larry.choice) ||
                    (curly.order == 0 && player.match == true && moe.match == true && larry.match == false && moe.choice > curly.choice && moe.choice > player.choice) ||
                    (curly.order == 0 && larry.match == true && moe.match == true && player.match == false && moe.choice > curly.choice && moe.choice > larry.choice) ||                   
                    (curly.order == 0 && moe.match == true && larry.match == false && player.match == false && moe.choice > curly.choice)) {
                    
                    cout << "Moe takes the trick." << endl;
                    // Check for Q spades
                    if (larry.choice == 37 || curly.choice == 37 || moe.choice == 37 || player.choice == 37){
                        moe.tScore += 13;
                        player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0;
                    }
                    // No one played Q spades
                    else {
                        moe.tScore += 0;
                        player.order = 1; larry.order = 2; curly.order = 3; moe.order = 0;
                    }
                }
            }
    cout << "Player hand is " << player.tScore << "\t" 
         << "Larry hand is " << larry.tScore << "\t\t" 
         << "Curly hand is " << curly.tScore << "\t\t" 
         << "Moe hand is " << moe.tScore << endl;
}
