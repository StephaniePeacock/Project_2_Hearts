/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on June 2, 2023, 6:41 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

struct Card {
    int  card[52];  // Number of the card in the deck (1-52)
    int  fv[13];      // For setting the char face
    char face[13];    // Card's face value: 2-10, J, Q, K, A (high)
    char suit[4];    // Card's suit
};

struct Player {
    int order;
    string name; 
    int hand[13];
    int choice;
    string cards[13];
};

// Input function prototypes
void shuffle(int [], const unsigned short, string[]);
void deal(Player &,Player &,Player &,Player &, int[], string[]);
void bSort(Player &, int [], const short, string []);
void sSort(Player &, int [], const short, string []);
void mSort(Player &, int [], const short, string []);
void print(Player &, int [], string [], const short, int, int);
void faceVal(string [], char [][13], string [], const short, const short);
void set(Player &, int&, int[]);
void unset(Player &, int&, int[], string[], int&);
void npcUn(Player &, int &, int[], string[]);
void played(Player &, string, int, string[]);
bool linSrch(int[],const unsigned short,int&);
void playCard(Player&, Player&, Player&, Player&, int&, int, int [], string, int); 

#endif /* HEARTS_H */

